#include "pch.h"
#include "RuleOf5.h"

#include <memory.h>

RuleOf5::RuleOf5() noexcept
{
    // nothing to do here, members are default-initialized with brace-or-equal-initialization
}

RuleOf5::RuleOf5(uint8_t *d, size_t len)
{
    length = len;
    data = new uint8_t[length];
    memcpy(data, d, length);
}

// Note: if not needed, delete copy assignment op to avoid slicing
RuleOf5::RuleOf5(const RuleOf5 &other) : length{other.length}, 
    data{new uint8_t[length]}
{   
    memcpy(data, other.data, length);
}

// Note: if not needed, delete copy assignment op to avoid slicing
RuleOf5& RuleOf5::operator=(const RuleOf5 &other)
{
    if (this == &other)
        return *this;

    delete[]data;

    length = other.length;
    data = new uint8_t[length];
    memcpy(data, other.data, length);

    return *this;
}

// Note: if it is a derived class, first move-construct the base using std::move(other)
RuleOf5::RuleOf5(RuleOf5 &&other) noexcept
{
    length = other.length;
    data = other.data;
    other.data = nullptr;
    other.length = 0;
}

// Note: if it is a derived class, first move-assign the base using std::move(other)
RuleOf5& RuleOf5::operator=(RuleOf5 &&other) noexcept
{
    if (this == &other)
        return *this;

    delete[]data;

    length = other.length;
    data = other.data;
    other.data = nullptr;
    other.length = 0;

    return *this;
}

// must be virtual for base classes, but then delete copy construction and assignment
// to avoid slicing
RuleOf5::~RuleOf5()
{
    // use delete[] for pointers allocated with new[]
    delete []data;
}
