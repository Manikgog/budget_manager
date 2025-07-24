#pragma once

#include <vector>
#include "date.h"
#include "parser.h"

struct OneDayBudget {
    double income_ = 0;
    double spend_ = 0;
};

class BudgetManager {
public:
    static const Date START_DATE;
    static const Date END_DATE;

    BudgetManager()
        : budget_() {
        size_t days = Date::ComputeDistance(START_DATE, END_DATE);
        budget_.reserve(days);
        for (size_t i = 0; i < days; ++i) {
            budget_.emplace_back(START_DATE + i, 0.0);
        }
    }

    void ProcessQuery(std::unique_ptr<Query> query);

private:
    std::vector<std::pair<Date, OneDayBudget> > budget_;
};