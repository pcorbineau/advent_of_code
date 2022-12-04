#pragma once

#include <string_view>

constexpr bool is_digit(char c)
{
    return c <= '9' && c >= '0';
}

constexpr int stoi_impl(const char *str, int value = 0)
{
    return *str ? is_digit(*str) ? stoi_impl(str + 1, (*str - '0') + value * 10)
                                 : throw "compile-time-error: not a digit"
                : value;
}

constexpr int stoi(const char c) {
    return is_digit(c) ? c - '0' : throw "compile-time-error: not a digit";
}

constexpr int stoi(std::string_view str)
{
    return stoi_impl(str.data());
}