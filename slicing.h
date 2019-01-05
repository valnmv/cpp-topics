
// C.67: A polymorphic class should suppress copying

// C.130: For making deep copies of polymorphic classes prefer a virtual clone 
// function instead of copy construction / assignment

#include "pch.h"
#include "gsl-lite.hpp"
#include <iostream>

namespace slicing
{
    // In order to fix slicing suppress copying in polymorphic classes as in
    // the commented out lines and implement clone() instead
    class B
    {
    public:
        virtual char m() noexcept { return 'B'; }

        //B() = default;
        //virtual ~B() = default;

        // suppress copying
        //B(const B&) = delete;
        //B& operator=(const B&) = delete;

        // provide clone()
        //virtual gsl::owner<B*> clone() = 0;    
    };

    class D : public B
    {
    public:
        char m() noexcept override { return 'D'; }

        //~D() { /* ... */ }

        // implement clone()
    //    gsl::owner<D*> clone() override { /* ... */ return nullptr; }
    };

    void test()
    {
        using std::cout;

        // object attributes are sliced when assigning derived-to-base
        D d;
        B b1 = d;  // D::f() is sliced
        auto &b2 = d; // ... while the reference is fine
        cout << d.m() << " " << b1.m() << " " << b2.m();
    }
}

