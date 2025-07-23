#include "budget_manager.h"

#include <iostream>
#include <string_view>


void ParseAndProcessQuery(BudgetManager& manager, std::string_view line) {
    // Разработайте функцию чтения и обработки запроса.
    Parser parser;
    if (std::optional<Query> op_query = parser.ParseLine(line); op_query.has_value()) {
        const Query& query = op_query.value();
        manager.ProcessQuery(query);
    }
}

int ReadNumberOnLine(std::istream& input) {
    std::string line;
    std::getline(input, line);
    return std::stoi(line);
}

int main() {
    BudgetManager manager;

    const int query_count = ReadNumberOnLine(std::cin);

    for (int i = 0; i < query_count; ++i) {
        std::string line;
        std::getline(std::cin, line);
        ParseAndProcessQuery(manager, line);
    }
}