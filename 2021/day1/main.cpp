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
    "199",
    "200",
    "208",
    "210",
    "200",
    "207",
    "240",
    "269",
    "260",
    "263",
});
#endif
#include "stoi.h"

constexpr auto common(auto&& rng) {
    return 
      std::ranges::count(
        rng 
        | std::views::slide(2)
        | std::views::transform([](auto&& x) {
            return x[0] < x[1];}),
      true);
}

constexpr auto part1(std::span<const std::string_view> lines)
{
    return common(lines | std::views::transform(stoi));
}

constexpr auto part2(std::span<const std::string_view> lines)
{
    auto sum_radar = [](const auto& x) {return std::accumulate(x.begin(), x.end(), 0);};
    return common(
        lines 
        | std::views::transform(stoi) 
        | std::views::slide(3) 
        | std::views::transform(sum_radar));
}

int main()
{
    auto res1 = part1(data);
    std::cout << "part 1 : " << res1 << '\n';

    auto res2 = part2(data);
    std::cout << "part 2 : " << res2 << '\n';
}