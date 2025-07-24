#pragma once

#include <optional>
#include <string>
#include "date.h"

class Query {
    std::string operation_name_;
    Date start_date_;
    Date end_date_;
public:
    Query(const std::string& operation_name, const Date& start_date, const Date& end_date)
        : operation_name_(operation_name)
        , start_date_(start_date)
        , end_date_(end_date) {}

    virtual ~Query() = default;

    [[nodiscard]] const std::string& GetOperationName() const {
        return operation_name_;
    }

    [[nodiscard]] const Date& GetStartDate() const {
        return start_date_;
    }

    [[nodiscard]] const Date& GetEndDate() const {
        return end_date_;
    }
};

class EarnQuery : public Query {
    double income_;
public:
    EarnQuery(const std::string& operation_name, const Date& start_date, const Date& end_date, double income)
        : Query(operation_name, start_date, end_date)
        , income_(income) {}

    [[nodiscard]] double GetIncome() const {
        return income_;
    }
};


class PayTaxQuery : public Query {
    double tax_;
public:
    PayTaxQuery(const std::string& operation_name, const Date& start_date, const Date& end_date, double tax)
        : Query(operation_name, start_date, end_date)
        , tax_(tax) {}

    [[nodiscard]] double GetTax() const {
        return tax_;
    }
};


class SpendQuery : public Query {
    double spend_;
public:
    SpendQuery(const std::string& operation_name, const Date& start_date, const Date& end_date, double spend)
        : Query(operation_name, start_date, end_date)
        , spend_(spend) {}

    [[nodiscard]] double GetSpend() const {
        return spend_;
    }
};

// Напишите в этом файле код, ответственный за чтение запросов.
class Parser {
public:
    static std::unique_ptr<Query> ParseLine(std::string_view line);
private:
    static std::pair<std::string, std::string> ParseFirstWord(std::string_view line);
};
