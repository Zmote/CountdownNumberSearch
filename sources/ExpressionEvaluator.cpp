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

    bool has_paranthesis_index(int const &string_index, int const &round_index,
                               int const &end_index, int const &range) {
        int mapped_index{map_num_index_to_iteration_range(string_index, range)};
        return mapped_index != -1
               && mapped_index >= round_index
               && string_index != end_index;
    }

    void add_paranthesis(bool &paranthesis_open, std::string &original, std::string const &appended) {
        if (!paranthesis_open) {
            original += "(";
            original += appended;
            paranthesis_open = !paranthesis_open;
        } else {
            original += appended;
            original += ")";
            paranthesis_open = !paranthesis_open;
        }
    }

    PermutationList<std::string> calculate_simple_ltr_precedences(Permutation<std::string> const &expression) {
        PermutationList<std::string> precedences{};
        std::string expr{};
        int number_count(((expression.size() - 1) / 2) + 1);
        for (int i = 0; i < number_count; i++) {
            expr.clear();
            for (int j = 0; j < expression.size(); j++) {
                expr += expression[j];
                if (is_digit(expression[j])) {
                    expr = encase_in_brackets(expr);
                }
                precedences.add(Permutation<std::string>{expr});
            }
        }
        return precedences;
    }

    PermutationList<std::string> calculate_grouped_precedences(Permutation<std::string> const &expression) {
        PermutationList<std::string> precedences{};
        std::string expr{};
        int number_count(((expression.size() - 1) / 2) + 1);
        int const expression_last_index = expression.size() - 1;
        for (int range = 2; range < number_count; range++) {
            for (int round_index = 0; round_index < number_count; round_index++) {
                expr.clear();
                if (round_index + range <= number_count) {
                    bool paranthesis_open{false};
                    for (int string_index = 0; string_index < expression.size(); string_index++) {
                        bool is_digit_value{is_digit(expression[string_index])};
                        if (is_digit_value) {
                            if (has_paranthesis_index(string_index, round_index, expression_last_index, range)) {
                                add_paranthesis(paranthesis_open, expr, expression[string_index]);
                            } else {
                                expr += expression[string_index];
                            }
                        } else {
                            expr += expression[string_index];
                            if (string_index == expression_last_index
                                && paranthesis_open) {
                                expr += ")";
                            }
                        }
                        if (is_digit_value && !paranthesis_open) {
                            precedences.add(Permutation<std::string>{expr});
                        }
                    }
                }
            }
        }
        return precedences;
    }

    PermutationList<std::string> calculate_precedences(Permutation<std::string> const &expression) {
        PermutationList<std::string> precedences{};
        precedences.add(calculate_grouped_precedences(expression));
        precedences.add(calculate_simple_ltr_precedences(expression));
        return precedences;
    }

    std::pair<std::string, int> ExpressionEvaluator::evaluate(Permutation<std::string> const &expression, int target) {
        int result{-1};
        int closest{result};
        std::string closest_expr{};
        PermutationList<std::string> precedence_permutations{calculate_precedences(expression)};
        std::for_each(precedence_permutations.begin(), precedence_permutations.end(),
                      [&](Permutation<std::string> const &elem) {
                          std::string expr{elem.join()};
                          if (parser.Calculate(expr.c_str(), &result) == CMathParser::ResultOk) {
                              int closest_diff{abs(target - closest)};
                              int current_diff{abs(target - result)};
                              if (current_diff < closest_diff) {
                                  closest = result;
                                  closest_expr = expr;
                                  if (current_diff == 0) return;
                              }
                          }
                      });
        return std::pair<std::string, int>{closest_expr, closest};
    }
}