#include <algorithm>
#include <cctype>
#include <iostream>
#include "../headers/ExpressionEvaluator.h"
#include "../headers/types/PermutationList.h"

namespace zmote::countdown {

    std::string encase_in_brackets(std::string const &p_input) {
        return "(" + p_input + ")";
    }

    bool is_digit(std::string const &p_input) {
        for (char const &character: p_input) {
            if (!std::isdigit(character)) {
                return false;
            }
        }
        return true;
    }

    int map_num_index_to_iteration_range(int const &index, int const &range) {
        if (index % range != 0) return -1;
        return index / range;
    }

    bool has_parenthesis_index(int const &string_index, int const &round_index,
                               int const &end_index, int const &range) {
        int mapped_index{map_num_index_to_iteration_range(string_index, range)};
        return mapped_index != -1
               && mapped_index >= round_index
               && string_index != end_index;
    }

    void add_parenthesis(bool &parenthesis_open, std::string &original, std::string const &appended) {
        if (!parenthesis_open) {
            original += "(";
            original += appended;
            parenthesis_open = !parenthesis_open;
        } else {
            original += appended;
            original += ")";
            parenthesis_open = !parenthesis_open;
        }
    }

    void ExpressionEvaluator::try_simple_ltr_precedences(Permutation<std::string> const &expression) {
        std::string expr{};
        int number_count(((expression.size() - 1) / 2) + 1);
        for (int i = 0; i < number_count; ++i) {
            expr.clear();
            for (int j = 0; j < expression.size(); ++j) {
                expr += expression[j];
                if (is_digit(expression[j])) {
                    expr = encase_in_brackets(expr);
                }
                process_evaluation(Permutation<std::string>{expr});
            }
        }
    }

    void ExpressionEvaluator::process_expression(Permutation<std::string> const &expression, int const &round_index,
                                                 int const &range) {
        bool parenthesis_open{false};
        int expression_last_index = expression.size() - 1;
        std::string expr{};
        for (int string_index = 0; string_index < expression.size(); ++string_index) {
            bool is_digit_value{is_digit(expression[string_index])};
            if (is_digit_value) {
                if (has_parenthesis_index(string_index, round_index, expression_last_index, range)) {
                    add_parenthesis(parenthesis_open, expr, expression[string_index]);
                } else {
                    expr += expression[string_index];
                }
            } else {
                expr += expression[string_index];
                if (string_index == expression_last_index
                    && parenthesis_open) {
                    expr += ")";
                }
            }
            if (is_digit_value && !parenthesis_open) {
                process_evaluation(Permutation<std::string>{expr});
            }
        }
    }

    void ExpressionEvaluator::try_grouped_precedences(Permutation<std::string> const &expression) {
        std::string expr{};
        int number_count(((expression.size() - 1) / 2) + 1);
        for (int range = 2; range < number_count; ++range) {
            for (int round_index = 0; round_index < number_count; ++round_index) {
                expr.clear();
                if (round_index + range <= number_count) {
                    process_expression(expression, round_index, range);
                }
            }
        }
    }

    void ExpressionEvaluator::try_precedences(Permutation<std::string> const &expression) {
        try_grouped_precedences(expression);
        try_simple_ltr_precedences(expression);
    }

    bool
    ExpressionEvaluator::process_evaluation(Permutation<std::string> const &process_expr) {
        std::string && expr{process_expr.join()};
        if (parser.Calculate(expr.c_str(), &result) == CMathParser::ResultOk) {
            int closest_diff{abs(target - closest_result)};
            int current_diff{abs(target - result)};
            if (current_diff < closest_diff) {
                std::swap(result, closest_result);
                std::swap(expr, closest_expr);
            }
        }
        return closest_result == target;
    }

    std::pair<std::string, int>
    ExpressionEvaluator::evaluate(Permutation<std::string> const &expression, int p_target) {
        reset();
        target = p_target;
        try_precedences(expression);
        return std::pair<std::string, int>{closest_expr, closest_result};
    }

    void ExpressionEvaluator::reset() {
        target = -1;
        result = -1;
        closest_result = -1;
        closest_expr.clear();
    }
}