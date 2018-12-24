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

    int map_num_index_to_iteration_range(int const &index) {
        if (index % 2 != 0) throw std::invalid_argument{"Param must be even index."};
        return index / 2;
    }

    PermutationList<std::string> calculate_precedences(Permutation<std::string> const &expression) {
        PermutationList<std::string> precedences{};
        std::string expr{};
        int rounds(((expression.size() - 1) / 2) + 1);
        for (int i = 0; i < rounds; i++) {
            expr.clear();
            bool paranthesisOpened{false};
            for (int j = 0; j < expression.size(); j++) {
                try {
                    if (j % 2 == 0) {
                        if (map_num_index_to_iteration_range(j) >= i) {
                            if (!paranthesisOpened) {
                                expr += "(";
                                expr += expression[j];
                                paranthesisOpened = !paranthesisOpened;
                            } else {
                                expr += expression[j];
                                expr += ")";
                                paranthesisOpened = !paranthesisOpened;
                            }

                        } else {
                            expr += expression[j];
                        }
                    } else {
                        expr += expression[j];
                    }
                    precedences.add(Permutation<std::string>{expr});
                } catch (std::invalid_argument const &ex) {
                    return precedences;
                }
            }
        }

        for (int i = 0; i < rounds; i++) {
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