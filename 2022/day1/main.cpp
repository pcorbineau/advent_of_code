#include <span>
#include <string_view>
#include <ranges>
#include <numeric>
#include <algorithm>
#include <vector>
#include <iostream>

#include "stoi.h"
#include "data.h"

constexpr auto elves_sum_calories(std::span<const std::string_view> lines)
{
    auto string_to_int = [](auto &&rng)  { return std::ranges::transform_view(rng, stoi); };
    auto sum_calories  = [](auto &&view) { return std::accumulate(view.begin(), view.end(), 0); }; // sum calories

    return lines
      | std::views::split(std::string_view{}) // use empty line to split elves ingredients calories
      | std::views::transform([&](auto &&rng) {return sum_calories(string_to_int(rng));}); // for each elf compute sum of calories
}

constexpr auto part1(std::span<const std::string_view> lines)
{
    return std::ranges::max(elves_sum_calories(lines));
}

constexpr auto part2(std::span<const std::string_view> lines)
{
    auto elves_sum_calories_view = elves_sum_calories(lines);

    // copy into vector to be able to use std::ranges::sort
    std::vector<std::ranges::range_value_t<decltype(elves_sum_calories_view)>> accumulated(elves_sum_calories_view.begin(), elves_sum_calories_view.end());
    std::ranges::sort(accumulated, std::greater{});

    // select the first 3 elements
    auto top3 = accumulated | std::views::take(3);

    // return sum of the first 3 elements
    return std::accumulate(top3.begin(), top3.end(), 0);
}

int main()
{
    static constexpr auto res1 = part1(data);
    std::cout << "part 1 : " << res1 << '\n';

    static constexpr auto res2 = part2(data);
    std::cout << "part 2 : " << res2 << '\n';
}