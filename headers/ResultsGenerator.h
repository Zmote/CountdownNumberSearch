#ifndef COUNTDOWNNUMBERSEARCH_RESULTSAGGREGATOR_H
#define COUNTDOWNNUMBERSEARCH_RESULTSAGGREGATOR_H

#include <set>
#include "CountdownAliases.h"
#include "PermutationCalculator.h"
#include "ExpressionEvaluator.h"

namespace zmote::countdown {
    using PermutationResultSet = std::set<PermutationResult>;
    using PermutationResultVector = std::vector<PermutationResult>;

    class ResultsGenerator {
        PermutationResultSet results{};
        PermutationCalculator permutation_calculator{};
        ExpressionEvaluator expression_evaluator{};

    public:
        ResultsGenerator(int p_target, IntVector p_initial_numbers);

        void generate_for(int p_target, IntVector p_initial_numbers);

        PermutationResultVector get_results();

    private:
        void clear();
    };
}


#endif //COUNTDOWNNUMBERSEARCH_RESULTSAGGREGATOR_H
