#ifndef COUNTDOWNNUMBERSEARCH_PERMUTATIONGENERATOR_H
#define COUNTDOWNNUMBERSEARCH_PERMUTATIONGENERATOR_H

#include <string>
#include <vector>
#include "types/EvaluationResult.h"
#include "CountdownAliases.h"

namespace zmote::countdown {
    class PermutationCalculator {
        vector<string> const operators{"+", "-", "*", "/"};
        vector_vectors<int> number_permutations{};
        vector_vectors<string> operand_permutations{};
        vector_vectors<string> permutations{};
        vector<int> initial_numbers;
    public:
        PermutationCalculator() = default;
        explicit PermutationCalculator(vector<int> const &p_initial_numbers);
        void init(vector<int> const &p_initial_numbers);
        vector_vectors<string> get_permutations();

    private:
        void calculate_expression_permutations(vector<int> const &numbers);

        void calculate_numbers_permutations(vector<int> a, int size, int n);

        void calculate_operator_permutations();

        void clear();
    };
}

#endif //COUNTDOWNNUMBERSEARCH_PERMUTATIONGENERATOR_H
