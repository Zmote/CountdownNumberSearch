#include "../headers/ExpressionEvaluator.h"
#include "../headers/SimpleMathOps.h"

namespace zmote::countdown {
    StringIntPair ExpressionEvaluator::evaluate(StringVector const &expression) {
        using namespace zmote::countdown;
        String operation{};
        for (String const &val: expression) {
            operation += val;
        }
        int result{std::stoi(expression[0])};
        for (int i = 1; i < expression.size(); i++) {
            if (expression[i] == "*") {
                result = SimpleMathOps::multiply(result, std::stoi(expression[i + 1]));
            }
            if (expression[i] == "/") {
                try {
                    result = SimpleMathOps::divide(result, std::stoi(expression[i + 1]));
                } catch (std::exception const &ex) {
                    return StringIntPair{operation + ", Failed: " + ex.what(), -1};
                }
            }
            if (expression[i] == "+") {
                result = SimpleMathOps::add(result, std::stoi(expression[i + 1]));
            }
            if (expression[i] == "-") {
                result = SimpleMathOps::subtract(result, std::stoi(expression[i + 1]));
            }
        }
        return StringIntPair{operation, result};
    }
}