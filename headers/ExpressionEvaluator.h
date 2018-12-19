#ifndef COUNTDOWNNUMBERSEARCH_EXPRESSIONEVALUATOR_H
#define COUNTDOWNNUMBERSEARCH_EXPRESSIONEVALUATOR_H

#include "CountdownAliases.h"

namespace zmote::countdown {
    class ExpressionEvaluator {
    public:
        ExpressionEvaluator() = default;

        StringIntPair evaluate(StringVector const &expression);
    };
}

#endif //COUNTDOWNNUMBERSEARCH_EXPRESSIONEVALUATOR_H
