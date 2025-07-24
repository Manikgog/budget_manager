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
        auto* earnQuery = dynamic_cast<EarnQuery*>(query.get());
        double income_per_day = earnQuery->GetIncome()/days;
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
        auto* payTaxQuery = dynamic_cast<PayTaxQuery*>(query.get());
        for (size_t i = first_day_index; i < first_day_index + days; ++i) {
            if (budget_[i].second > 0) {
                budget_[i].second *= (1.0 - (payTaxQuery->GetTax()/100.0));
            }
        }
    }else if (query->GetOperationName() == "Spend") {
        size_t first_day_index = Date::ComputeDistance(START_DATE, query->GetStartDate());
        size_t days = Date::ComputeDistance(query->GetStartDate(), query->GetEndDate() + 1);
        auto* spendQuery = dynamic_cast<SpendQuery*>(query.get());
        double spend_per_day = spendQuery->GetSpend()/days;
        for (size_t i = first_day_index; i < first_day_index + days; ++i) {
            budget_[i].second -= spend_per_day;
        }
    }
}
