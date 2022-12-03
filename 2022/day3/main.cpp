#include <span>
#include <string_view>
#include <numeric>
#include <ranges>
#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>

#if 1
#include "data.h"
#else
#include <array>
static constexpr auto data = std::to_array<std::string_view>({
    "vJrwpWtwJgWrhcsFMMfFFhFp",
    "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL",
    "PmmdzqPrVvPwwTWBwg",
    "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn",
    "ttgJtRGJQctTZtZT",
    "CrZsJsPPZsGzwwsLwLmpwMDw",
});
#endif
#include "stoi.h"

constexpr auto to_points (const char c) -> int {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 1;
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 27;
    } else {
        throw std::runtime_error("Invalid character");
    }
};

constexpr auto part1(std::span<const std::string_view> lines)
{
    auto split_line = [](auto&& line) {
        return std::make_tuple(line.substr(0, line.size() / 2), line.substr(line.size() / 2));
    };
    auto find_common_char = [](auto&& rng) {
        auto [left, right] = rng;
        return *std::ranges::find_first_of(left, right);
    };


    auto view = 
      lines 
      | std::views::transform(split_line) 
      | std::views::transform(find_common_char) 
      | std::views::transform(to_points);
    return std::accumulate(view.begin(), view.end(), 0);
}

auto part2(std::span<const std::string_view> lines)
{
    auto sort_chunks_and_set_intersections = [](auto&& chunk) {
        std::vector<char> chunk1_sorted(chunk[0].begin(), chunk[0].end());
        std::vector<char> chunk2_sorted(chunk[1].begin(), chunk[1].end());
        std::vector<char> chunk3_sorted(chunk[2].begin(), chunk[2].end());

        std::sort(chunk1_sorted.begin(), chunk1_sorted.end());
        std::sort(chunk2_sorted.begin(), chunk2_sorted.end());
        std::sort(chunk3_sorted.begin(), chunk3_sorted.end());

        std::vector<char> common1;
        std::set_intersection(chunk1_sorted.begin(), chunk1_sorted.end(), chunk2_sorted.begin(), chunk2_sorted.end(), std::back_inserter(common1));
        std::vector<char> common2;
        std::set_intersection(common1.begin(), common1.end(), chunk3_sorted.begin(), chunk3_sorted.end(), std::back_inserter(common2));

        return common2.empty() ? ' ' : common2.front();
    };

    auto views = 
      lines 
      | std::views::chunk(3) 
      | std::views::transform(sort_chunks_and_set_intersections)
      | std::views::transform(to_points); 

    return std::accumulate(views.begin(), views.end(), 0);
}

int main()
{
    static constexpr auto res1 = part1(data);
    std::cout << "part 1 : " << res1 << '\n';

    auto res2 = part2(data);
    std::cout << "part 2 : " << res2 << '\n';
}