// Напишите в этом файле код, ответственный за чтение запросов.
#include "parser.h"
#include <memory>

std::unique_ptr<Query> Parser::ParseLine(std::string_view line) {
    std::pair<std::string, std::string> operation_and_text = ParseFirstWord(line);
    std::pair<std::string, std::string> first_date_and_text = ParseFirstWord(operation_and_text.second);
    std::pair<std::string, std::string> second_date_and_text = ParseFirstWord(first_date_and_text.second);
    Date first_date(first_date_and_text.first);
    Date second_date(second_date_and_text.first);
    if (operation_and_text.first == "Earn") {
        const double income = std::stod(second_date_and_text.second);
        return std::make_unique<EarnQuery>(operation_and_text.first, first_date, second_date, income);
    } else if (operation_and_text.first == "ComputeIncome") {
        return std::make_unique<Query>(operation_and_text.first, first_date, second_date);
    } else if (operation_and_text.first == "PayTax") {
        const int tax = std::stoi(second_date_and_text.second);
        return std::make_unique<PayTaxQuery>(operation_and_text.first, first_date, second_date, tax);
    } else if (operation_and_text.first == "Spend") {
        const double spend = std::stod(second_date_and_text.second);
        return std::make_unique<SpendQuery>(operation_and_text.first, first_date, second_date, spend);
    }
    return {};
 }

std::pair<std::string, std::string> Parser::ParseFirstWord(std::string_view line) {
    std::string line_str{line};
    size_t first_space_index = line.find_first_of(' ');
    std::string operation_name = line_str.substr(0, first_space_index);
    std::string text = line_str.substr(first_space_index + 1, line_str.size() - first_space_index);
    return std::pair<std::string, std::string>{operation_name, text};
}
