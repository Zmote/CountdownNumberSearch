#include <utility>

#include <utility>
#include <algorithm>

#include "../headers/ResultsGenerator.h"

namespace zmote::countdown {
    ResultsGenerator::ResultsGenerator(int p_target, IntVector p_initial_numbers) {
        generate_for(p_target, std::move(p_initial_numbers));
    }

    PermutationResultVector ResultsGenerator::get_results() {
        PermutationResultVector sorted_results{results.begin(), results.end()};
        std::sort(sorted_results.begin(), sorted_results.end(), [](PermutationResult const &first, PermutationResult const &second) {
            return first.diff > second.diff;
        });
        return sorted_results;
    }

    void ResultsGenerator::generate_for(int p_target, IntVector p_initial_numbers) {
        clear();
        permutation_calculator.init(p_initial_numbers);
        for (StringVector const &permutation: permutation_calculator.get_permutations()) {
            auto pair = expression_evaluator.evaluate(permutation, p_target);
            if (pair.second >= 0) {
                results.insert(PermutationResult{pair.first, pair.second, p_target, abs(pair.second - p_target)});
            }
        }
    }

    void ResultsGenerator::clear() {
        results = PermutationResultSet{};
    }
}