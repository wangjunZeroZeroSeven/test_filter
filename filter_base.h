#ifndef __FILTER_BASE_H__
#define __FILTER_BASE_H__

#include <vector>
#include <stdint.h>
#include <thread>
#include <list>
#include <mutex>
#include "auto_lock.h"
#include <iostream>

using namespace std;

struct Event {
    uint64_t id = 0;
    uint32_t timestamp = 0;
};
typedef vector<Event> EventVct;

// EventBatch describes a EventVct that is processing, it's the output format
struct EventBatch;
typedef shared_ptr<EventBatch> EventBatchImpl;
struct EventBatch 
{
    EventVct event_vct;
    list<pair<uint64_t, string>> path;  // describe the process filter chain , contains every filter's id and name  

    EventBatch(const EventVct& i_event_vct)
    {
        event_vct = i_event_vct;
    }

    // copy to generate a new object
    EventBatch(EventBatchImpl batch)
    {
        event_vct = batch->event_vct;
        path = batch->path;
    }
};

class FilterBase;
typedef std::shared_ptr<FilterBase> FilterBaseImpl;


// describes a filter and its output, use in processing all filters as intermediate data 
struct FilterOut
{
    FilterBaseImpl filter;
    EventBatchImpl outputBatch;

    FilterOut(FilterBaseImpl iFilter, EventBatchImpl iBatch)
    {
        filter = iFilter;
        outputBatch = iBatch;
    }
};


// the base class of all filters
class FilterBase
{
    friend class FilterBase;
public:
    FilterBase(string name)
    {
        m_sName = name;
        {
            AutoLock autolock(&m_lockCurrSeq);
            if (m_uCurrSeq == UINT64_MAX)
            {
                m_uCurrSeq = 1;
            }
            m_uId = m_uCurrSeq++;
        }
    }

    // this filter and its recv filter and recv's recv and  .. constructs chains ,this method print all chains. often use in debug
    list<string> PrintAllChain()
    {
        string currStr = PrintSelf();
        list<FilterBaseImpl> recvFilters = GetRecvFilters();
        if (recvFilters.empty())
        {
            list<string> result;
            result.push_back(currStr);
            return result;
        }
        else 
        {
            list<string> result;
            for (FilterBaseImpl filter: recvFilters)
            {
                list<string> paths = filter->PrintAllChain();
                for (auto& path: paths)
                {
                    char buf[4096];
                    sprintf(buf, "%s->%s", currStr.c_str(), path.c_str());
                    result.push_back(buf);
                }
            }
            return result;
        }
    }

    // put event collection into this filter , run filter task and ouput result to other filters to do task until the final.
    // final result is output by OutputResult method.
    void ProcessAll(EventVct& event_vct)
    {
        EventBatchImpl batch = make_shared<EventBatch>(event_vct);
        DoFilter(batch);

        list<FilterBaseImpl> recvFilters = GetRecvFilters();
        if (recvFilters.empty())
        {
            // it is the final
            OuputResult(batch);
            return;
        }
        
        // run filters from step to step
        list<FilterOut> currFiltersOut; // all filters in same deep level
        for (auto filter : recvFilters)
        {
            auto newBatch = make_shared<EventBatch>(batch);  // should copy a new object , avoid interact each other
            filter->DoFilter(newBatch);
            currFiltersOut.push_back(FilterOut(filter, newBatch));
        }

        while (!currFiltersOut.empty())
        {
            // every time goes one step ahead for every path
            auto lastFiltersOut = currFiltersOut;
            currFiltersOut.clear();

            // generate new currFiltersOut
            for (FilterOut filterOut: lastFiltersOut)
            {
                list<FilterBaseImpl> recvFilters = filterOut.filter->GetRecvFilters();
                if (recvFilters.empty())
                {
                    // it's the final
                    filterOut.filter->OuputResult(filterOut.outputBatch);
                }
                else
                {
                    for (auto filter : recvFilters)
                    {
                        // do filter for every recv filter , and generate new FilterOut
                        auto newBatch = make_shared<EventBatch>(filterOut.outputBatch);  // should copy a new object , avoid interact each other
                        filter->DoFilter(newBatch);
                        currFiltersOut.push_back(FilterOut(filter, newBatch));
                    }
                }
            }
        }
    }

    // add filter that receive this filter's output, one filter can add more than one recv filters.
    bool AddRecvFilter(FilterBaseImpl revcFilter)
    {
        // cannot add self
        if (m_uId == revcFilter->m_uId)
        {
            return false;
        }

        // judge loop
        AutoLock autolock(&m_lockLstRecvFilters);
        list<FilterBaseImpl> descendant = revcFilter->GetAllDescendant();
        //to judge if this filter is revcFilter's descendant
        for (auto desc: descendant)
        {
            if (m_uId == desc->m_uId)
            {
                // revcFilter and this filter is in a loop, cannot add it!
                return false;
            }
        }

        m_lstRecvFilters.push_back(revcFilter);
        return true;
    }

    uint64_t GetId()
    {
        return m_uId;
    }

    string GetName()
    {
        return m_sName;
    }

protected:
    // do filter work , return data after filtered
    virtual void DoFilter(EventBatchImpl event_batch)
    {
        // do filter work

        // record the path
        event_batch->path.push_back(make_pair(m_uId, m_sName));
    }

    // when all filter run over, output the final result
    // expected output format: (events:{evt_id:evt_time}{evt_id:evt_time} path:[filterId:filterName]->[filterId:filterName])
    virtual void OuputResult(EventBatchImpl event_batch)
    {
        string result = "(events:";
        for (Event& evt: event_batch->event_vct)
        {
            char buf[255];
            sprintf(buf, "{%u:%u}", evt.id, evt.timestamp);
            result += buf;
        }
        result += " path:";
        size_t evt_num = event_batch->path.size();
        size_t index = 0;
        for (pair<uint64_t, string>& filterInfo: event_batch->path)
        {
            index++;
            char buf[255];
            sprintf(buf, "[%u:%s]", filterInfo.first, filterInfo.second.c_str());
            result += buf;
            if (index != evt_num)
            {
                result += "->";
            }
        }
        result += ")";
        
        cout << result << endl;
    }

    // get recv filters
    list<FilterBaseImpl> GetRecvFilters()
    {
        AutoLock autolock(&m_lockLstRecvFilters);
        return m_lstRecvFilters;
    }

    // get all descendant, do not lock
    list<FilterBaseImpl> GetAllDescendant()
    {
        list<FilterBaseImpl> result;
        list<FilterBaseImpl> recvFilters = m_lstRecvFilters;
        if (recvFilters.empty())
        {
            return result;
        }
        
        list<FilterBaseImpl> currFilters = recvFilters;  // all filters in same deep level
        result.insert(result.end(), recvFilters.begin(), recvFilters.end());

        while (!currFilters.empty())
        {
            // every time goes one step ahead for every path
            auto lastFilters= currFilters;
            currFilters.clear();

            // generate new currFilters
            for (FilterBaseImpl filter: lastFilters)
            {
                list<FilterBaseImpl> recvFilters = filter->m_lstRecvFilters;
                if (!recvFilters.empty())
                {
                    // it's the final
                    currFilters.insert(currFilters.end(), recvFilters.begin(), recvFilters.end());
                    result.insert(result.end(), recvFilters.begin(), recvFilters.end());
                }
            }
        }
        return result;
    }

    // to print this filter
    string PrintSelf()
    {
        char buf[1024];
        sprintf(buf, "[%s:%u]", m_sName.c_str(), m_uId);
        return buf;
    }
    
protected:
    list<FilterBaseImpl> m_lstRecvFilters;  // filters that receive this filter's output
    mutex   m_lockLstRecvFilters; // lock that lock m_lstRecvFilters

    string m_sName;  // filter name, read only after filter created.
    uint64_t m_uId;  // filter id, read only after filter created.
    static uint64_t m_uCurrSeq;  // to generate filter id
    static mutex m_lockCurrSeq;  // lock that lock m_uCurrSeq
};
uint64_t FilterBase::m_uCurrSeq = 1;
mutex FilterBase::m_lockCurrSeq;

#endif