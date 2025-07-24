#include "parser.h"

#include <iostream>
#include <unordered_map>

namespace queries {

class ComputeIncome : public ComputeQuery {
public:
    using ComputeQuery::ComputeQuery;

    [[nodiscard]] ReadResult Process(const BudgetManager &budget) const override {
        const int idx_from = BudgetManager::GetDayIndex(GetFrom());
        const int idx_to = BudgetManager::GetDayIndex(GetTo());

        double income = 0;

        for (int i = idx_from; i <= idx_to; ++i) {
            income += budget.GetDayState(i).income - budget.GetDayState(i).spend;
            //std::cout << "income = budget.GetDayState(i).income - budget.GetDayState(i).spend = " << income << std::endl;
        }

        return {income};
    }

    class Factory : public QueryFactory {
    public:
        [[nodiscard]] std::unique_ptr<Query> Construct(std::string_view config) const override {
            auto parts = Split(config, ' ');
            return std::make_unique<ComputeIncome>(Date(parts[0]), Date(parts[1]));
        }
    };
};

class Alter : public ModifyQuery {
public:
    Alter(Date from, Date to, double amount)
        : ModifyQuery(from, to), amount_(amount) {
    }

    void Process(BudgetManager& budget) const override {
        const int idx_from = BudgetManager::GetDayIndex(GetFrom());
        const int idx_to = BudgetManager::GetDayIndex(GetTo());

        double day_income = amount_ / (idx_to - idx_from + 1);

        for (int i = idx_from; i <= idx_to; ++i) {
            budget.GetDayState(i).income += day_income;
        }
    }

    class Factory : public QueryFactory {
    public:
        [[nodiscard]] std::unique_ptr<Query> Construct(std::string_view config) const override {
            auto parts = Split(config, ' ');
            double payload = std::stod(std::string(parts[2]));
            return std::make_unique<Alter>(Date(parts[0]), Date(parts[1]), payload);
        }
    };

private:
    double amount_;
};

class PayTax : public ModifyQuery {
public:
    PayTax(Date from, Date to, int tax)
        : ModifyQuery(from, to), tax_(tax) {}

    void Process(BudgetManager& budget) const override {
        const int idx_from = BudgetManager::GetDayIndex(GetFrom());
        const int idx_to = BudgetManager::GetDayIndex(GetTo());
        for (int i = idx_from; i <= idx_to; ++i) {
            if (budget.GetDayState(i).income > 0) {
                budget.GetDayState(i).income *= 1.0 - (tax_/100.0);
                std::cout << "budget.GetDayState(i).income = " << budget.GetDayState(i).income << "budget.GetDayState(i).spend = " << budget.GetDayState(i).spend << std::endl;
            }
        }
    }

    class Factory : public QueryFactory {
    public:
        [[nodiscard]] std::unique_ptr<Query> Construct(std::string_view config) const override {
            auto parts = Split(config, ' ');
            int payload = std::stoi(std::string(parts[2]));
            return std::make_unique<PayTax>(Date(parts[0]), Date(parts[1]), payload);
        }
    };
private:
    int tax_;
};

class Spend : public ModifyQuery {
public:
    Spend(Date from, Date to, double amount)
        : ModifyQuery(from, to), amount_(amount) {
    }

    void Process(BudgetManager& budget) const override {
        const int idx_from = BudgetManager::GetDayIndex(GetFrom());
        const int idx_to = BudgetManager::GetDayIndex(GetTo());
        double day_spend = amount_ / (idx_to - idx_from + 1);
        for (int i = idx_from; i <= idx_to; ++i) {
            budget.GetDayState(i).spend += day_spend;
        }
    }

    class Factory : public QueryFactory {
    public:
        [[nodiscard]] std::unique_ptr<Query> Construct(std::string_view config) const override {
            auto parts = Split(config, ' ');
            double payload = std::stod(std::string(parts[2]));
            return std::make_unique<Spend>(Date(parts[0]), Date(parts[1]), payload);
        }
    };

private:
    double amount_;
};

}  // namespace queries

const QueryFactory& QueryFactory::GetFactory(std::string_view id) {
    using namespace std::literals;

    static queries::ComputeIncome::Factory compute_income;
    static queries::Alter::Factory alter;
    static queries::PayTax::Factory pay_tax;
    static queries::Spend::Factory spend;
    static std::unordered_map<std::string_view, const QueryFactory &> factories
            = {{"ComputeIncome"sv, compute_income},
               {"Earn"sv,          alter},
               {"PayTax"sv,        pay_tax},
                {"Spend"sv, spend}};

    return factories.at(id);
}
