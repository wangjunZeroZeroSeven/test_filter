#ifndef __FILTERS_H__   
#define __FILTERS_H__

#include "filter_base.h"
#include <algorithm>

class FilterAddTimeByOne: public FilterBase
{
public:
    FilterAddTimeByOne(string name): FilterBase(name)
    {}
protected:
    virtual void DoFilter(EventBatchImpl event_batch)
    {
        for (auto& evt: event_batch->event_vct)
        {
            evt.timestamp++;
        } 

        FilterBase::DoFilter(event_batch);
    }
};

class FilterAddEvent: public FilterBase
{
public:
    FilterAddEvent(string name): FilterBase(name)
    {}
protected:
    virtual void DoFilter(EventBatchImpl event_batch)
    {
        Event evt;
        evt.id = 4;
        evt.timestamp = 0;
        event_batch->event_vct.push_back(evt);

        FilterBase::DoFilter(event_batch);
    }
};

class FilterRemoveEvent: public FilterBase
{
public:
    FilterRemoveEvent(string name): FilterBase(name)
    {}
protected:
    virtual void DoFilter(EventBatchImpl event_batch)
    {
        auto iter = event_batch->event_vct.begin();
        while (iter != event_batch->event_vct.end())
        {
            if (iter->id == 1)
            {
                iter = event_batch->event_vct.erase(iter);
            }
            else
            {
                iter++;
            }
        }

        FilterBase::DoFilter(event_batch);
    }
};

class FilterAddTimeByTwo: public FilterBase
{
public:
    FilterAddTimeByTwo(string name): FilterBase(name)
    {}
protected:
    virtual void DoFilter(EventBatchImpl event_batch)
    {
        for (auto& evt: event_batch->event_vct)
        {
            evt.timestamp += 2;
        } 

        FilterBase::DoFilter(event_batch);
    }
};

bool sortFunc (Event a, Event b) { return a.id > b.id; }
class FilterSortEvent: public FilterBase
{
public:
    FilterSortEvent(string name): FilterBase(name)
    {}
protected:
    virtual void DoFilter(EventBatchImpl event_batch)
    {
        sort(event_batch->event_vct.begin(), event_batch->event_vct.end(), sortFunc);

        FilterBase::DoFilter(event_batch);
    }
};

class FilterMultiplyTimeBy10: public FilterBase
{
public:
    FilterMultiplyTimeBy10(string name): FilterBase(name)
    {}
protected:
    virtual void DoFilter(EventBatchImpl event_batch)
    {
        for (auto& evt: event_batch->event_vct)
        {
            evt.timestamp *= 10;
        } 

        FilterBase::DoFilter(event_batch);
    }
};

class FilterMultiplyTimeBy100: public FilterBase
{
public:
    FilterMultiplyTimeBy100(string name): FilterBase(name)
    {}
protected:
    virtual void DoFilter(EventBatchImpl event_batch)
    {
        for (auto& evt: event_batch->event_vct)
        {
            evt.timestamp *= 100;
        } 

        FilterBase::DoFilter(event_batch);
    }
};

#endif