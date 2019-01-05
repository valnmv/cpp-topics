#include "pch.h"
#include "gsl-lite.hpp"
#include "span.h"

namespace spantest
{
    void increment(gsl::span<int> s)
    {
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