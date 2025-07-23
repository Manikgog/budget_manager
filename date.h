#pragma once

#include <chrono>
#include <sstream>
#include <string>
#include <string_view>

class Date {
public:
    // explicit Date(const std::string& str) {
    //     std::istringstream input(str);
    //     std::chrono::from_stream(input, "%Y-%m-%d", ymd_);
    // }
    explicit Date(const std::string& str) {
        std::istringstream iss(str);
        int year, month, day;
        char sep;

        if (!(iss >> year >> sep >> month >> sep >> day) || sep != '-') {
            throw std::runtime_error("Invalid date format");
        }

        ymd_ = std::chrono::year{year}/std::chrono::month{static_cast<unsigned>(month)}/std::chrono::day{static_cast<unsigned>(day)};
        if (!ymd_.ok()) {
            throw std::runtime_error("Invalid date");
        }
    }

    explicit Date(std::string_view str)
        : Date(std::string(str)) {
    }

    explicit Date(const std::chrono::year_month_day& ymd)
        : ymd_(ymd) {}

    static int ComputeDistance(const Date& from, const Date& to) {
        return static_cast<int>(
            (std::chrono::sys_days(to.ymd_) - std::chrono::sys_days(from.ymd_)).count());
    }

    [[nodiscard]] Date operator+(size_t n) const {
        std::chrono::days days_to_add = std::chrono::days{n};
        std::chrono::year_month_day ymd = std::chrono::sys_days{ymd_} + days_to_add;
        Date date(ymd);
        return date;
    }

    [[nodiscard]] std::string ToString() const {
        return std::format("{:%Y-%m-%d}", ymd_);
    }

private:
    std::chrono::year_month_day ymd_{};
};