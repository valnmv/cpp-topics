#pragma once

#include <stdint.h>
#include "gsl/pointers"

class RuleOf4Half
{
public:
    RuleOf4Half() noexcept;
    RuleOf4Half(uint8_t *, size_t);
    RuleOf4Half(const RuleOf4Half &other);
    RuleOf4Half(RuleOf4Half &&other) noexcept;
    RuleOf4Half& operator=(RuleOf4Half other) noexcept;
    ~RuleOf4Half();
    friend void swap(RuleOf4Half &first, RuleOf4Half &second) noexcept;

private:
    gsl::owner<uint8_t *> data = nullptr; // raw pointer for the example; otherwise use smart pointers
    size_t length{ 0 }; // brace-or-equal initialization
};

