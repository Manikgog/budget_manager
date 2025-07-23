#pragma once

#include <optional>
#include <string>
#include "date.h"

struct Query {
    std::string operation_name_;
    Date start_date_;
    Date end_date_;
    double income_ = 0;
};


// Напишите в этом файле код, ответственный за чтение запросов.
class Parser {
public:
    std::optional<Query> ParseLine(std::string_view line);
};

