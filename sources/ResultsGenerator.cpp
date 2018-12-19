#include <utility>

#include <utility>
#include <algorithm>

#include "../headers/ResultsGenerator.h"

namespace zmote::countdown {
    ResultsGenerator::ResultsGenerator(int p_target, IntVector p_initial_numbers) {
        generate_for(p_target, std::move(p_initial_numbers));
    }

    PermutationResultVector ResultsGenerator::get_results() {
        return results;
    }

    void ResultsGenerator::generate_for(int p_target, IntVector p_initial_numbers) {
        clear();
        permutation_calculator.init(p_initial_numbers);
        for (StringVector const &permutation: permutation_calculator.get_permutations()) {
            auto pair = expression_evaluator.evaluate(permutation);
            if (pair.second >= 0) {
                results.emplace_back(PermutationResult{pair.first, pair.second, p_target, abs(pair.second - p_target)});
            }
        }
        std::sort(results.begin(), results.end(), [](PermutationResult const &first, PermutationResult const &second) {
            return first.diff > second.diff;
        });
    }

    void ResultsGenerator::clear() {
        results = PermutationResultVector{};
    }
}