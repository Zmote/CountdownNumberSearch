#ifndef COUNTDOWNNUMBERSEARCH_RESULTSAGGREGATOR_H
#define COUNTDOWNNUMBERSEARCH_RESULTSAGGREGATOR_H

#include <set>
#include <future>
#include <thread>
#include "CountdownAliases.h"
#include "PermutationCalculator.h"
#include "ExpressionEvaluator.h"

namespace zmote::countdown {
    using PermutationResultSet = std::set<EvaluationResult>;
    using PermutationResultVector = std::vector<EvaluationResult>;

    class ResultsGenerator {
        int const PARTITION_SIZE{61400};
        PermutationResultSet results{};
        PermutationCalculator permutation_calculator{};

    public:
        ResultsGenerator(int p_target, vector<int> p_initial_numbers);

        void generate_for(int p_target, vector<int> p_initial_numbers);

        PermutationResultVector get_results();

    private:
        void clear();

        void run_evaluation_threads(int p_target, const vector<vector_vectors<string>> &parts,
                                    vector<std::future<std::set<EvaluationResult>>> &partial_results,
                                    vector<std::thread> &threads) const;

        void populate_results_from_futures(vector<std::future<std::set<EvaluationResult>>> &partial_results);

        void join_evaluation_threads(vector<std::thread> &threads);

        void split_permutations_into_ranges(const vector_vectors<string> &permutations,
                                            vector_vectors<string> &sub_permutations,
                                            vector<vector_vectors<string>> &parts, int permutations_limit) const;

        void run_evaluation(int p_target, const vector_vectors<string> &sub_perms,
                            std::set<EvaluationResult> &sub_results) const;
    };
}


#endif //COUNTDOWNNUMBERSEARCH_RESULTSAGGREGATOR_H
