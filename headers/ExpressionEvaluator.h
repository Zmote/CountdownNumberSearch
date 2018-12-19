#ifndef COUNTDOWNNUMBERSEARCH_EXPRESSIONEVALUATOR_H
#define COUNTDOWNNUMBERSEARCH_EXPRESSIONEVALUATOR_H

#include "CountdownAliases.h"

namespace zmote::countdown {
    class ExpressionEvaluator {
    public:
        ExpressionEvaluator() = default;

        StringIntPair evaluate(StringVector const &expression, int target);
    private:
        void appendOperands(String &operation, const StringVector &expression, int i) const;
    };
}

#endif //COUNTDOWNNUMBERSEARCH_EXPRESSIONEVALUATOR_H
