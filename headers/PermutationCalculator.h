#ifndef COUNTDOWNNUMBERSEARCH_PERMUTATIONGENERATOR_H
#define COUNTDOWNNUMBERSEARCH_PERMUTATIONGENERATOR_H

#include <string>
#include <vector>
#include "types/EvaluationResult.h"
#include "types/PermutationList.h"

namespace zmote::countdown {
    class PermutationCalculator {
        Permutation<std::string> const operators{"+", "-", "*", "/"};
        PermutationList<int> number_permutations{};
        PermutationList<std::string> operand_permutations{};
        PermutationList<std::string> permutations{};
        Permutation<int> initial_numbers;
    public:
        PermutationCalculator() = default;

        explicit PermutationCalculator(Permutation<int> const &p_initial_numbers);

        void init(Permutation<int> const &p_initial_numbers);

        PermutationList<std::string> get_permutations();

    private:
        void calculate_expression_permutations(Permutation<int> const &numbers);

        void calculate_numbers_permutations(Permutation<int> a, int size, int n);

        void calculate_operator_permutations();

        void clear();
    };
}

#endif //COUNTDOWNNUMBERSEARCH_PERMUTATIONGENERATOR_H
