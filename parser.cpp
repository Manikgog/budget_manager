// Напишите в этом файле код, ответственный за чтение запросов.
#include "parser.h"

std::optional<Query> Parser::ParseLine(std::string_view line) {
    std::string line_str{line};
    size_t first_space_index = line.find_first_of(' ');
    std::string operation_name = line_str.substr(0, first_space_index);
    size_t second_space_index = line.find(' ', first_space_index + 1);
    std::string start_date = line_str.substr(first_space_index + 1, second_space_index - 1 - first_space_index);
    if (operation_name == "ComputeIncome" || operation_name == "PayTax") {
        std::string end_date = line_str.substr(second_space_index + 1, line_str.size() - second_space_index);
        return std::optional<Query>({operation_name, Date(start_date), Date(end_date)});
    }
    size_t third_space_index = line.find(' ', second_space_index + 1);
    std::string end_date = line_str.substr(second_space_index + 1, third_space_index - 1 - second_space_index);
    std::string income = line_str.substr(third_space_index + 1, line_str.size() - third_space_index);
    return std::optional<Query>({operation_name, Date(start_date), Date(end_date), std::stod(income)});
 }