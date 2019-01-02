// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "RuleOf5.h"
#include "copy-and-swap.h"
#include "slicing.h"
#include "raii.h"

#include <iostream>

// detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>  
#include <crtdbg.h>  

using namespace std;

RuleOf5 create_object()
{
    uint8_t data[]{ 0x41, 0x42, 0x43 };
    return RuleOf5 { &data[0], 3 };
}

void test_RuleOf5()
{
    // ctor()
    RuleOf5 r1;

    // ctor( , )
    uint8_t data[] = { 0x44, 0x45 };
    RuleOf5 r2{ &data[0], 2 };

    // uses RVO, so no move ctor
    RuleOf5 r3 = create_object();

    // force enable move to use move ctor
    RuleOf5 r4 = std::move(r3);

    // copy=
    r4 = r4;
    r4 = r2;

    // move=
    r4 = r4;
    r4 = std::move(r2);
}

void test_RuleOf4Half()
{
    uint8_t data[] = { 0x44, 0x45 };
    RuleOf4Half r1{ &data[0], 2 };
    
    RuleOf4Half r2;
    r2 = std::move(r1);
    r1 = r2;
}

void test_slicing(B& b)
{
    // object attributes are sliced by assigning derived-to-base
    // here the method is sliced
    // disabled by deleting copy ctor and copy=

    auto b2 = b; // oops, slices the object; d.m() will return 'B'
    auto &b3 = b; // ... while the reference is fine
    std::cout << b.m() << " " << b2.m() << " " << b3.m();
}

void test_raii()
{
    auto sp = shared_file_ptr("raii.cpp", "r");

    char buf[100];
    fread(buf, sizeof(char), sizeof(buf) / sizeof(char), sp.get());

    // here fclose() is called by sp deleter
}

int main()
{   
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
   
    test_RuleOf5();   
    test_RuleOf4Half();
 
    D d;
    test_slicing(d);

    test_raii();

    //  int arr[10];           // warning C26494
    //  int* p = arr;          // warning C26485

    ////  [[gsl::suppress(bounds.1)]] // This attribute suppresses Bounds rule #1
    //  {
    //      int* q = p + 1;    // warning C26481 (suppressed)
    //      p = q++;           // warning C26481 (suppressed)
    //  }

    return 0;
}
