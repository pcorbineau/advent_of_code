#include <span>
#include <string_view>
#include <numeric>
#include <ranges>
#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

#include "interleave.h"

#if 0
#include "data.h"
static constexpr auto BITSET_SIZE = 12;
#else
static constexpr auto BITSET_SIZE = 5;
#include <array>
static constexpr auto data = std::to_array<std::string_view>({
    "00100",
    "11110",
    "10110",
    "10111",
    "10101",
    "01111",
    "00111",
    "11100",
    "10000",
    "11001",
    "00010",
    "01010",
});
#endif
#include "stoi.h"

constexpr auto to_bool(const char c)
{
    switch (c) {
        case '0': return false;
        case '1': return true;
    }
}

template <std::size_t bitset_size>
constexpr auto part1(std::span<const std::string_view> lines)
{
    std::bitset<bitset_size> gamma{};
    std::bitset<bitset_size> epsilon{};
    for (size_t i = 0; i < bitset_size; ++i) {
        size_t count_1 = 0;
        size_t count_0 = 0;
        for (size_t j = 0; j < lines.size(); ++j) {
            if (to_bool(lines[j][i])) {
                ++count_1;
            } else {
                ++count_0;
            }
        }
        if (count_1 > count_0) {
            gamma.set(bitset_size - i - 1, true);
            epsilon.set(bitset_size - i - 1, false);
        } else {
            gamma.set(bitset_size - i - 1, false);
            epsilon.set(bitset_size -i - 1, true);
        }
    }
    return gamma.to_ulong() * epsilon.to_ulong();
}

auto part2(std::span<const std::string_view> lines)
{
    return 0;
}

int main()
{
    static constexpr auto res1 = part1<BITSET_SIZE>(data);
    std::cout << "part 1 : " << res1 << '\n';

     auto res2 = part2(data);
    std::cout << "part 2 : " << res2 << '\n';
}