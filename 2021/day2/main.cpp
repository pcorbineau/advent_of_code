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

enum class Direction
{
    Forward,
    Down,
    Up
};

constexpr auto to_direction(std::string_view dir)
{
    if (dir == "forward") return Direction::Forward;
    else if (dir == "down") return Direction::Down;
    else if (dir == "up") return Direction::Up;
    else throw std::runtime_error("invalid direction");
}

constexpr auto offset(const Direction &dir, const int distance)
{
    switch (dir) {
        case Direction::Forward: return std::make_tuple(distance, 0);
        case Direction::Down: return std::make_tuple(0, distance);
        case Direction::Up: return std::make_tuple(0, -distance);
    }
    throw std::runtime_error("invalid direction");
    return std::make_tuple(0, 0);
}

constexpr auto offset2(const Direction &dir, const int distance, const int aim)
{
    switch (dir) {
        case Direction::Forward: return std::make_tuple(distance, aim * distance, aim);
        case Direction::Down: return std::make_tuple(0, 0, aim + distance);
        case Direction::Up: return std::make_tuple(0, 0, aim - distance);
    }
    throw std::runtime_error("invalid direction");
    return std::make_tuple(0, 0, 0);
}

constexpr auto split(std::string_view line, const char delim) {
    auto pos = line.find(delim);
    return std::make_tuple(line.substr(0, pos), line.substr(pos + 1));
}

constexpr auto part1(std::span<const std::string_view> lines)
{
    auto string_to_tuple = [](auto&& line) {
        auto [dir, distance] = split(line, ' ');
        return std::make_tuple(to_direction(dir), stoi(distance));
    };
    
    auto views = lines 
      | std::views::transform(string_to_tuple)
      | std::views::transform([](auto&& x) {return offset(std::get<0>(x), std::get<1>(x));});

    auto [x, y] = std::accumulate(views.begin(), views.end(), std::make_tuple(0, 0), [](auto&& acc, auto&& x) {
        return std::make_tuple(std::get<0>(acc) + std::get<0>(x), std::get<1>(acc) + std::get<1>(x));
    });
    return x * y;
}

constexpr auto part2(std::span<const std::string_view> lines)
{
    auto string_to_tuple = [](auto&& line) {
        auto [dir, distance] = split(line, ' ');
        return std::make_tuple(to_direction(dir), stoi(distance));
    };

    auto my_lambda = [aim = 0] (auto&& x) mutable {
        auto [h, y, a] = offset2(std::get<0>(x), std::get<1>(x), aim);
        aim = a;
        return std::make_tuple(h, y);
    };

    auto views = lines 
      | std::views::transform(string_to_tuple)
      | std::views::transform(my_lambda);

    auto [x, y] = std::accumulate(views.begin(), views.end(), std::make_tuple(0, 0), [](auto&& acc, auto&& x) {
        return std::make_tuple(std::get<0>(acc) + std::get<0>(x), std::get<1>(acc) + std::get<1>(x));
    });
    return x * y;
}

int main()
{
    static constexpr auto res1 = part1(data);
    std::cout << "part 1 : " << res1 << '\n';

    static constexpr auto res2 = part2(data);
    std::cout << "part 2 : " << res2 << '\n';
}