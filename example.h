#ifndef __EXAMPLE_H__
#define __EXAMPLE_H__

#include "filters.h"

/*
    f1 - f2 - f3
    every filter add timestamp by one.
*/

FilterBaseImpl BuildFilter1()
{
    auto f1 = make_shared<FilterAddTimeByOne>("first");
    auto f2 = make_shared<FilterAddTimeByOne>("second");
    auto f3 = make_shared<FilterAddTimeByOne>("third");

    f1->AddRecvFilter(f2);
    f2->AddRecvFilter(f3);
    return f1;
}

void Test1()
{
    //build filter
    FilterBaseImpl filter = BuildFilter1();
    list<string> paths = filter->PrintAllChain();
    for (auto& path: paths)
    {
        cout << path << endl;
    }
    cout << endl;

    //run filter
    EventVct event_vct;
    for (int i = 0; i < 3; i++)
    {
        Event evt;
        evt.id = i + 1;
        evt.timestamp = 0;
        event_vct.push_back(evt);
    }
    filter->ProcessAll(event_vct);
}

/*      f3         f6
       /          /
     f1 -- f4 - f5 - f7
       \  /       \
        f2         f8
    
    filters go from left to right in up graph.

    f1 add all timestamp by one.
    f2 add an event of id 4.
    f3 remove event of id 1.
    f4 add all timestamp by two.
    f5 sort events as event id backword.
    f6 do nothing.
    f7 multiply all timestamp by 10.
    f8 multiply all timestamp by 100.

    this example is to test path and event handling.
*/

FilterBaseImpl BuildFilter2()
{
    auto f1 = make_shared<FilterAddTimeByOne>("f1");
    auto f2 = make_shared<FilterAddEvent>("f2");
    auto f3 = make_shared<FilterRemoveEvent>("f3");
    auto f4 = make_shared<FilterAddTimeByTwo>("f4");
    auto f5 = make_shared<FilterSortEvent>("f5");
    auto f6 = make_shared<FilterBase>("f6");
    auto f7 = make_shared<FilterMultiplyTimeBy10>("f7");
    auto f8 = make_shared<FilterMultiplyTimeBy100>("f8");

    f1->AddRecvFilter(f2);
    f1->AddRecvFilter(f3);
    f1->AddRecvFilter(f4);
    f2->AddRecvFilter(f4);
    f4->AddRecvFilter(f5);
    f5->AddRecvFilter(f6);
    f5->AddRecvFilter(f7);
    f5->AddRecvFilter(f8);

    return f1;
}

void Test2()
{
    //build filter
    FilterBaseImpl filter = BuildFilter2();
    list<string> paths = filter->PrintAllChain();
    for (auto& path: paths)
    {
        cout << path << endl;
    }
    cout << endl;

    //run filter
    EventVct event_vct;
    for (int i = 0; i < 3; i++)
    {
        Event evt;
        evt.id = i + 1;
        evt.timestamp = 0;
        event_vct.push_back(evt);
    }
    filter->ProcessAll(event_vct);
}

#endif