#include <span>
#include <string_view>
#include <ranges>
#include <numeric>
#include <algorithm>
#include <vector>
#include <iostream>

#include "stoi.h"
#include "data.h"

constexpr auto part1(std::span<const std::string_view> lines)
{
    return std::ranges::max(lines |
                            std::views::split(std::string_view{}) |
                            std::views::transform([](auto &&rng)
                                                  {
        auto view = rng | std::views::transform(stoi) | std::views::common;
        return std::accumulate(view.begin(), view.end(), 0); }));
}

constexpr auto part2(std::span<const std::string_view> lines)
{
    auto accumulated_view = lines |
                            std::views::split(std::string_view{}) |
                            std::views::transform([](auto &&rng)
                                                  {
        auto view = rng | std::views::transform(stoi) | std::views::common;
        return std::accumulate(view.begin(), view.end(), 0); });
    std::vector<std::ranges::range_value_t<decltype(accumulated_view)>> accumulated(accumulated_view.begin(), accumulated_view.end());
    std::ranges::sort(accumulated, std::greater{});
    auto top3 = accumulated | std::views::take(3);
    return std::accumulate(top3.begin(), top3.end(), 0);
}

int main()
{
    static constexpr auto res1 = part1(data);
    std::cout << "part 1 : " << res1 << '\n';

    static constexpr auto res2 = part2(data);
    std::cout << "part 2 : " << res2 << '\n';
}