#ifndef COUNTDOWNNUMBERSEARCH_EXPRESSIONEVALUATOR_H
#define COUNTDOWNNUMBERSEARCH_EXPRESSIONEVALUATOR_H

#include <string>
#include <vector>
#include "../headers/util/CMathParser.h"
#include "types/Permutation.h"

namespace zmote::countdown {
    class ExpressionEvaluator {
        CMathParser parser{};
    public:
        ExpressionEvaluator() = default;

        std::pair<std::string, int> evaluate(Permutation<std::string> const &expression, int target);
    };
}

#endif //COUNTDOWNNUMBERSEARCH_EXPRESSIONEVALUATOR_H
