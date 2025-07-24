#include <iostream>
#include "budget_manager.h"
#include "date.h"

using namespace std::literals;

const Date BudgetManager::START_DATE = Date("2000-01-01"s);
const Date BudgetManager::END_DATE = Date("2100-01-01"s);

void BudgetManager::ProcessQuery(std::unique_ptr<Query> query) {
    if (query->GetOperationName() == "Earn") {
        size_t first_day_index = Date::ComputeDistance(START_DATE, query->GetStartDate());
        size_t days = Date::ComputeDistance(query->GetStartDate(), query->GetEndDate() + 1);
        double income_per_day = query->/days;
        for (size_t i = first_day_index; i < first_day_index + days; ++i) {
            budget_[i].second += income_per_day;
        }
    }else if (query->GetOperationName() == "ComputeIncome") {
        size_t first_day_index = Date::ComputeDistance(START_DATE, query->GetStartDate());
        size_t days = Date::ComputeDistance(query->GetStartDate(), query->GetEndDate() + 1);
        double income_summ = 0;
        for (size_t i = first_day_index; i < first_day_index + days; ++i) {
            income_summ += budget_[i].second;
        }
        std::cout << income_summ << std::endl;
    }else if (query->GetOperationName() == "PayTax") {
        size_t first_day_index = Date::ComputeDistance(START_DATE, query->GetStartDate());
        size_t days = Date::ComputeDistance(query->GetStartDate(), query->GetEndDate() + 1);
        for (size_t i = first_day_index; i < first_day_index + days; ++i) {
            budget_[i].second *= 0.87;
        }
    }
}
