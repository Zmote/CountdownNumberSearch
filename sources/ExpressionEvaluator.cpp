#include <algorithm>
#include <cctype>
#include "../headers/ExpressionEvaluator.h"
#include "../headers/SimpleMathOps.h"

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

    StringIntPair ExpressionEvaluator::evaluate(StringVector const &expression, int target) {
        int result{-1};
        int closest{result};
        std::string closest_expr{};
        std::string expr{};
        std::for_each(expression.begin(), expression.end(), [&](std::string const &elem) {
            expr += elem;
            if (is_digit(elem)) {
                expr = encase_in_brackets(expr);
            }
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
        return StringIntPair{closest_expr, closest};
    }
}