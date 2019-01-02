#pragma once

// An example of managing raw pointer, hence the need for rule-of-5.
// Prefer implementeing RAII, Rule-of-0 and use span<>

#include <stdint.h>
#include "gsl-lite.hpp"

class RuleOf5
{
public:
    RuleOf5() noexcept;
    RuleOf5(uint8_t *, size_t);
    RuleOf5(const RuleOf5 &other);
    RuleOf5& operator=(const RuleOf5 &other);
    RuleOf5(RuleOf5 &&other) noexcept;
    RuleOf5& operator=(RuleOf5 &&other) noexcept;
    ~RuleOf5();
private:
    gsl::owner<uint8_t *> data = nullptr; // raw pointer for the example; otherwise use smart pointers
    size_t length{ 0 }; // brace-or-equal initialization
};

