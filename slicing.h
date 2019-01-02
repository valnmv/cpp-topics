
// C.67: A polymorphic class should suppress copying

// C.130: For making deep copies of polymorphic classes prefer a virtual clone 
// function instead of copy construction / assignment

#include "pch.h"

#include "gsl-lite.hpp"

// polymorphic class suppresses copying
class B 
{
public:
    //virtual char m() { return 'B'; }

    B() = default;
    virtual ~B() = default;

    // suppress copying
    B(const B&) = delete;
    B& operator=(const B&) = delete;

    // provide clone()
    virtual gsl::owner<B*> clone() = 0;    
};

class D : public B 
{
public:
    //char m() override { return 'D'; }

    ~D() { /* ... */ }

    // implement clone()
    gsl::owner<D*> clone() override { /* ... */ return nullptr; }
};

