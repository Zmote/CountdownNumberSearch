#ifndef COUNTDOWNNUMBERSEARCH_RESULTSAGGREGATOR_H
#define COUNTDOWNNUMBERSEARCH_RESULTSAGGREGATOR_H

#include <set>
#include <future>
#include <thread>
#include "CountdownAliases.h"
#include "PermutationCalculator.h"
#include "ExpressionEvaluator.h"

namespace zmote::countdown {
    using PermutationResultSet = std::set<PermutationResult>;
    using PermutationResultVector = std::vector<PermutationResult>;

    class ResultsGenerator {
        int const PARTITION_SIZE{61400};
        PermutationResultSet results{};
        PermutationCalculator permutation_calculator{};

    public:
        ResultsGenerator(int p_target, IntVector p_initial_numbers);

        void generate_for(int p_target, IntVector p_initial_numbers);

        PermutationResultVector get_results();

    private:
        void clear();

        void run_evaluation_threads(int p_target, const std::vector<VectorOfStringVectors> &parts,
                                    std::vector<std::future<std::set<PermutationResult>>> &partial_results,
                                    std::vector<std::thread> &threads) const;

        void populate_results_from_futures(std::vector<std::future<std::set<PermutationResult>>> &partial_results);

        void join_evaluation_threads(std::vector<std::thread> &threads);

        void split_permutations_into_ranges(const VectorOfStringVectors &permutations,
                                            VectorOfStringVectors &sub_permutations,
                                            std::vector<VectorOfStringVectors> &parts, int permutations_limit) const;

        void run_evaluation(int p_target, const VectorOfStringVectors &sub_perms,
                            std::set<PermutationResult> &sub_results) const;
    };
}


#endif //COUNTDOWNNUMBERSEARCH_RESULTSAGGREGATOR_H
