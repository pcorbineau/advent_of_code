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
    "2-4,6-8",
    "2-3,4-5",
    "5-7,7-9",
    "2-8,3-7",
    "6-6,4-6",
    "2-6,4-8",
});
#endif
#include "stoi.h"

struct Range {
    int begin;
    int end;
};

constexpr bool is_subrange(const Range& r1, const Range& r2) {
    if (r1.begin >= r2.begin && r1.end <= r2.end) {
        return true;
    } else if (r2.begin >= r1.begin && r2.end <= r1.end) {
        return true;
    }
    else {
        return false;
    }
}

constexpr bool is_overlap(const Range& r1, const Range& r2) {
    // one of r1 is in r2
    if (r1.begin >= r2.begin && r1.begin <= r2.end) {
        return true;
    } else if (r1.end >= r2.begin && r1.end <= r2.end) {
        return true;
    }

    // one of r2 is in r1
    if (r2.begin >= r1.begin && r2.begin <= r1.end) {
        return true;
    } else if (r2.end >= r1.begin && r2.end <= r1.end) {
        return true;
    }

    return false;
}

auto part1(std::span<const std::string_view> lines)
{
    auto view = 
      lines
      | std::views::transform([](auto&& line) {
            auto v = line | std::views::split(',') | std::views::transform([](auto&& range) {
                auto r = range | std::views::split('-') | std::views::transform([](auto&& s) {
                    std::string str(s.begin(), s.end());
                    return stoi(str);
                }) | std::views::take(2) | std::views::common;
                return Range{ *r.begin(), *std::next(r.begin()) };
            }) | std::views::take(2) | std::views::common;
            return std::pair{ *v.begin(), *std::next(v.begin()) };
        })
      | std::views::filter([](auto&& pair) {
            return is_subrange(pair.first, pair.second);
        });

    return std::ranges::distance(view);
}

auto part2(std::span<const std::string_view> lines)
{
    auto view = 
      lines
      | std::views::transform([](auto&& line) {
            auto v = line | std::views::split(',') | std::views::transform([](auto&& range) {
                auto r = range | std::views::split('-') | std::views::transform([](auto&& s) {
                    std::string str(s.begin(), s.end());
                    return stoi(str);
                }) | std::views::take(2) | std::views::common;
                return Range{ *r.begin(), *std::next(r.begin()) };
            }) | std::views::take(2) | std::views::common;
            return std::pair{ *v.begin(), *std::next(v.begin()) };
        })
      | std::views::filter([](auto&& pair) {
            return is_overlap(pair.first, pair.second);
        });

    return std::ranges::distance(view);
}

int main()
{
    auto res1 = part1(data);
    std::cout << "part 1 : " << res1 << '\n';

    auto res2 = part2(data);
    std::cout << "part 2 : " << res2 << '\n';
}