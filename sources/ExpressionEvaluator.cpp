#include "../headers/ExpressionEvaluator.h"
#include "../headers/SimpleMathOps.h"

namespace zmote::countdown {
    StringIntPair ExpressionEvaluator::evaluate(StringVector const &expression, int target) {
        using namespace zmote::countdown;
        int result{std::stoi(expression[0])};
        String operation{expression[0]};
        for (int i = 1; i < expression.size(); i++) {
            if (result == target) return StringIntPair{operation, result};
            if (expression[i] == "*") {
                appendOperands(operation, expression, i);
                result = SimpleMathOps::multiply(result, std::stoi(expression[i + 1]));
            }
            if (expression[i] == "/") {
                try {
                    appendOperands(operation, expression, i);
                    result = SimpleMathOps::divide(result, std::stoi(expression[i + 1]));
                } catch (std::exception const &ex) {
                    return StringIntPair{operation + ", Failed: " + ex.what(), -1};
                }
            }
            if (expression[i] == "+") {
                appendOperands(operation, expression, i);
                result = SimpleMathOps::add(result, std::stoi(expression[i + 1]));
            }
            if (expression[i] == "-") {
                appendOperands(operation, expression, i);
                result = SimpleMathOps::subtract(result, std::stoi(expression[i + 1]));
            }
        }
        return StringIntPair{operation, result};
    }

    void ExpressionEvaluator::appendOperands(String &operation, const StringVector &expression, int i) const {
        operation += expression[i];
        operation += expression[i+1];
    }
}