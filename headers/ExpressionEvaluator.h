#ifndef COUNTDOWNNUMBERSEARCH_EXPRESSIONEVALUATOR_H
#define COUNTDOWNNUMBERSEARCH_EXPRESSIONEVALUATOR_H

#include <string>
#include <vector>
#include "../headers/util/CMathParser.h"
#include "types/Permutation.h"

namespace zmote::countdown {
    class ExpressionEvaluator {
        CMathParser parser{};
        int result{-1};
        int closest_result{-1};
        int target{-1};
        std::string closest_expr{};
    public:
        ExpressionEvaluator() = default;

        std::pair<std::string, int> evaluate(Permutation<std::string> const &expression, int target);

    private:
        void try_grouped_precedences(Permutation<std::string> const &expression);
        void try_precedences(Permutation<std::string> const &expression);
        void try_simple_ltr_precedences(Permutation<std::string> const &expression);
        bool process_evaluation(Permutation<std::string> const &process_expr);
        void process_expression(Permutation<std::string> const &expression, int const &round_index, int const &range);
        void reset();
    };
}

#endif //COUNTDOWNNUMBERSEARCH_EXPRESSIONEVALUATOR_H
