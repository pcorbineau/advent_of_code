#include <iostream>
#include <numeric>
#include <span>
#include <string_view>
#include <tuple>
#include <ranges>

#include "data.h"

enum class Hand
{
    Rock,
    Paper,
    Scissor,
};

enum class Result
{
    LOSE,
    WIN,
    DRAW
};

constexpr auto beat(const Hand &h)
{
    switch (h)
    {
    case Hand::Rock:
        return Hand::Scissor;
    case Hand::Paper:
        return Hand::Rock;
    case Hand::Scissor:
        return Hand::Paper;
    }
}

constexpr auto lose(const Hand &h)
{
    switch (h)
    {
    case Hand::Rock:
        return Hand::Paper;
    case Hand::Paper:
        return Hand::Scissor;
    case Hand::Scissor:
        return Hand::Rock;
    }
}

constexpr auto to_points(const Hand &h)
{
    switch (h)
    {
    case Hand::Rock:
        return 1;
    case Hand::Paper:
        return 2;
    case Hand::Scissor:
        return 3;
    }
}

constexpr auto to_points(const Result &r)
{
    switch (r)
    {
    case Result::LOSE:
        return 0;
    case Result::WIN:
        return 6;
    case Result::DRAW:
        return 3;
    }
}

constexpr auto to_hand(const char c)
{
    switch (c)
    {
    case 'A':
        return Hand::Rock;
    case 'B':
        return Hand::Paper;
    case 'C':
        return Hand::Scissor;
    case 'X':
        return Hand::Rock;
    case 'Y':
        return Hand::Paper;
    case 'Z':
        return Hand::Scissor;
    }
    return Hand{};
}

constexpr auto to_result(const char c)
{
    switch (c)
    {
    case 'X':
        return Result::LOSE;
    case 'Y':
        return Result::DRAW;
    case 'Z':
        return Result::WIN;
    }
    return Result{};
}

constexpr auto fight(const Hand &opponent, const Hand &me)
{
    if (opponent == me)
    {
        return Result::DRAW;
    }
    else if (beat(opponent) == me)
    {
        return Result::LOSE;
    }
    else
    {
        return Result::WIN;
    }
}

constexpr auto hand_from_result(const Hand &opponent, const Result &result)
{
    switch (result)
    {
    case Result::LOSE:
        return beat(opponent);
    case Result::WIN:
        return lose(opponent);
    case Result::DRAW:
        return opponent;
    }
}

constexpr auto parse(std::string_view line)
{
    return std::make_tuple(line[0], line[2]);
}

// line is 'O M'
constexpr auto parse1(std::string_view line)
{
    const auto &[opponent, me] = parse(line);
    return std::make_tuple(to_hand(opponent), to_hand(me));
}

// line is 'O R'
constexpr auto parse2(std::string_view line)
{
    const auto &[opponent, result] = parse(line);
    return std::make_tuple(to_hand(opponent), to_result(result));
}

constexpr auto part1(std::span<const std::string_view> lines)
{
    return std::accumulate(
        lines.begin(),
        lines.end(),
        0,
        [](const auto acc, const auto line)
        {
            const auto [opponent, me] = parse1(line);
            return acc + to_points(me) + to_points(fight(opponent, me));
        });
}

constexpr auto part2(std::span<const std::string_view> lines)
{
    return std::accumulate(lines.begin(), lines.end(), 0,
                           [](const auto &res, const auto &line)
                           {
                               const auto [opponent, result] = parse2(line);
                               const auto me = hand_from_result(opponent, result);
                               return res + to_points(me) + to_points(result);
                           });
}

int main()
{
    static constexpr auto res1 = part1(data);
    std::cout << "part 1 : " << res1 << std::endl;

    static constexpr auto res2 = part2(data);
    std::cout << "part 2 : " << res2 << std::endl;

    return 0;
}