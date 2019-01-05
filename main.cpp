// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "RuleOf5.h"
#include "copy-and-swap.h"
#include "slicing.h"
#include "raii.h"
#include "overload.h"
#include "span.h"

#include <iostream>
// detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>  
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

void test_raii()
{
    auto sp = shared_file_ptr("raii.cpp", "r");

    char buf[100];
    fread(&buf[0], sizeof(char), sizeof(buf) / sizeof(char), sp.get());

    // here fclose() is called by sp deleter
}

void test_finally()
{
    try
    {
        FILE *f = nullptr;
        fopen_s(&f, "raii.cpp", "r");
        auto _ = gsl::finally([&f]() { if (f) fclose(f); cout << "file closed\n"; });

        char buf[100];
        fread(&buf[0], sizeof(char), sizeof(buf) / sizeof(char), f);

        throw std::exception("test finally\n");
    }
    catch (const std::exception &e)
    {
        cout << e.what();
    }
}

struct ArrayByVal
{
    char data[10];
};

void f(ArrayByVal v)
{
    cout << v.data[2];
    v.data[2] = 'x';
}

int main()
{   
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
   
    ArrayByVal v;
    strcpy_s(v.data, "abcdef");
    f(v);

    // * undefined:  if you read a variable twice in an expression 
    // where you also write it, the result is undefined
    int a[2]{ 3, 5 };
    int i = 0;
    a[i] = i++; // ???

    // * undefined: Between the previous and next sequence point a scalar 
    // object shall have its stored value modified at most once by the 
    // evaluation of an expression. Furthermore, the prior value shall be 
    // accessed only to determine the value to be stored.
    int j = ++i + i++;
    j;

    // *

    test_RuleOf5();   
    test_RuleOf4Half();
    test_raii();
    test_finally();

    slicing::test();
    overload::test();

    spantest::spantest();

    int arr[10];           // warning C26494
    int* p = arr;          // warning C26485

    //  [[gsl::suppress(bounds.1)]] // This attribute suppresses Bounds rule #1
    {
        int* q = p + 1;    // warning C26481 (suppressed)
        p = q++;           // warning C26481 (suppressed)
    }

    return 0;
}
