#include <iostream>
#include "budget_manager.h"
#include "date.h"

using namespace std::literals;

const Date BudgetManager::START_DATE = Date("2000-01-01"s);
const Date BudgetManager::END_DATE = Date("2100-01-01"s);

void BudgetManager::ProcessQuery(const Query &query) {
    if (query.operation_name_ == "Earn") {
        size_t first_day_index = Date::ComputeDistance(START_DATE, query.start_date_);
        size_t days = Date::ComputeDistance(query.start_date_, query.end_date_ + 1);
        double income_per_day = query.income_/days;
        for (size_t i = first_day_index; i < first_day_index + days; ++i) {
            budget_[i].second += income_per_day;
        }
    }else if (query.operation_name_ == "ComputeIncome") {
        size_t first_day_index = Date::ComputeDistance(START_DATE, query.start_date_);
        size_t days = Date::ComputeDistance(query.start_date_, query.end_date_ + 1);
        double income_summ = 0;
        for (size_t i = first_day_index; i < first_day_index + days; ++i) {
            income_summ += budget_[i].second;
        }
        std::cout << income_summ << std::endl;
    }else if (query.operation_name_ == "PayTax") {
        size_t first_day_index = Date::ComputeDistance(START_DATE, query.start_date_);
        size_t days = Date::ComputeDistance(query.start_date_, query.end_date_ + 1);
        for (size_t i = first_day_index; i < first_day_index + days; ++i) {
            budget_[i].second *= 0.87;
        }
    }
}
