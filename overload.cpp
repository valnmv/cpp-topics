// hiding-rule.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include<iostream>

namespace overload {
    using namespace std;

    class B {
    public:
        int x = 10;
        virtual int f(int i)
        {
            cout << "B::f(int): ";
            return i + x;
        }
    };

    class D : public B {
    public:
        int x = 20;
        int f(int i)
        {
            cout << "D::f(int): ";
            return i + x;
        }

        double f(double d)
        {
            cout << "D::f(double): ";
            return d + x;
        }
    };

    void test()
    {
        D d;
        cout << d.f(2) << '\n';
        cout << d.f(2.3) << '\n';

        B& b = d;
        cout << b.f(2) << '\n';
        cout << b.f(2.3) << '\n';
    }
}