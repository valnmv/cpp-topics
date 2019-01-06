#include "pch.h"
#include "gsl-lite.hpp"
#include "span.h"

#include <chrono>
#include <thread>
#include <iostream>

namespace spantest
{
    void increment(gsl::span<int> s)
    {
        //using namespace std::chrono_literals;
        //std::this_thread::sleep_for(1us);

        for (int &x : s) ++x;
    }

    void spantest()
    {
        const int n = 10;
        int a[n] = {};

        increment(a);
        increment({a, 10});
    }
}

