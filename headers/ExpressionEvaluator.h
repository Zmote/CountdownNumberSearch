#ifndef COUNTDOWNNUMBERSEARCH_EXPRESSIONEVALUATOR_H
#define COUNTDOWNNUMBERSEARCH_EXPRESSIONEVALUATOR_H

#include "CountdownAliases.h"
#include "../headers/util/CMathParser.h"

namespace zmote::countdown {
    class ExpressionEvaluator {
        CMathParser parser{};
    public:
        ExpressionEvaluator() = default;

        StringIntPair evaluate(StringVector const &expression, int target);
    };
}

#endif //COUNTDOWNNUMBERSEARCH_EXPRESSIONEVALUATOR_H
