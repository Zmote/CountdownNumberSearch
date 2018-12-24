#ifndef COUNTDOWNNUMBERSEARCH_RESULTSAGGREGATOR_H
#define COUNTDOWNNUMBERSEARCH_RESULTSAGGREGATOR_H

#include <set>
#include <future>
#include <thread>
#include "PermutationCalculator.h"
#include "ExpressionEvaluator.h"

namespace zmote::countdown {

    class ResultsGenerator {
        int const PARTITION_SIZE{61400};
        std::set<EvaluationResult> results{};
        PermutationCalculator permutation_calculator{};

    public:
        ResultsGenerator(int p_target, Permutation<int> p_initial_numbers);

        void generate_for(int p_target, Permutation<int> p_initial_numbers);

        std::vector<EvaluationResult> get_results();

    private:
        void clear();

        std::vector<std::thread>
        instantiate_evaluation_threads(int p_target, std::vector<PermutationList<std::string>> const &parts,
                                       std::vector<std::future<std::set<EvaluationResult>>> &partial_results) const;

        void populate_results_from_futures(std::vector<std::future<std::set<EvaluationResult>>> &partial_results);

        void join_evaluation_threads(std::vector<std::thread> &&threads);

        std::vector<PermutationList<std::string>>
        split_permutations_into_ranges(PermutationList<std::string> const &permutations,
                                       int const &permutations_limit) const;

        void run_evaluation(int p_target, const PermutationList<std::string> &sub_perms,
                            std::set<EvaluationResult> &sub_results) const;
    };
}


#endif //COUNTDOWNNUMBERSEARCH_RESULTSAGGREGATOR_H
