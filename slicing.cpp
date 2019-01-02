
// C.67: A polymorphic class should suppress copying

// C.130: For making deep copies of polymorphic classes prefer a virtual clone 
// function instead of copy construction / assignment

#include "pch.h"

#include "gsl/pointers"

// polymorphic class suppresses copying
class B {
public:
    virtual char m() { return 'B'; }

    // supress copying
    B(const B&) = delete;
    B& operator=(const B&) = delete;

    // provide clone()
    virtual gsl::owner<B*> clone() = 0;
    virtual ~B() = 0;
};

class D : public B {
public:
    char m() override { return 'D'; }

    gsl::owner<D*> clone() override { /* ... */ }
    virtual ~D() override { /* ... */ }
};

void f(B& b) {
/* compile error:
    auto b2 = b; // ok, compiler will detect inadvertent copying, and protest
*/
}

//D d;
//f(d);