#include <span>
#include <string_view>
#include <numeric>
#include <ranges>
#include <iostream>
#include <vector>
#include <algorithm>

#if 1
#include "data.h"
#else
#include <array>
static constexpr auto data = std::to_array<std::string_view>({
    "forward 5",
    "down 5",
    "forward 8",
    "up 3",
    "down 8",
    "forward 2",
});
#endif
#include "stoi.h"

constexpr auto part1(std::span<const std::string_view> lines)
{
    return 0;
}

constexpr auto part2(std::span<const std::string_view> lines)
{
    return 0;
}

int main()
{
    static constexpr auto res1 = part1(data);
    std::cout << "part 1 : " << res1 << '\n';

    static constexpr auto res2 = part2(data);
    std::cout << "part 2 : " << res2 << '\n';
}