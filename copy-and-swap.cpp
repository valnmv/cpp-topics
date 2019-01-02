#include "pch.h"
#include "copy-and-swap.h"

RuleOf4Half::RuleOf4Half() noexcept
{
}

RuleOf4Half::RuleOf4Half(uint8_t *d, size_t len)
{
    length = len;
    data = new uint8_t[length];
    memcpy(data, d, length);
}

RuleOf4Half::RuleOf4Half(const RuleOf4Half &other)
{
    length = other.length;
    data = new uint8_t[length];
    memcpy(data, other.data, length); 
}

// Note: if it is a derived class, first move-assign the base using std::move(other)
RuleOf4Half::RuleOf4Half(RuleOf4Half &&other) noexcept
{
    length = other.length;
    data = other.data;
    other.data = nullptr;
    other.length = 0;
}

RuleOf4Half& RuleOf4Half::operator=(RuleOf4Half other) noexcept
{
    swap(*this, other);
    return *this;
}

RuleOf4Half::~RuleOf4Half()
{
    delete[]data;
}

void swap(RuleOf4Half &first, RuleOf4Half &second) noexcept
{
    // enable ADL (not necessary in our case, but good practice)
    using std::swap;
    swap(first.length, second.length);
    swap(first.data, second.data);
}
