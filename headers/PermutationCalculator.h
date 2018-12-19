#ifndef COUNTDOWNNUMBERSEARCH_PERMUTATIONGENERATOR_H
#define COUNTDOWNNUMBERSEARCH_PERMUTATIONGENERATOR_H

#include <string>
#include <vector>
#include "PermutationResult.h"
#include "CountdownAliases.h"

namespace zmote::countdown {
    class PermutationCalculator {
        StringVector const operators{"+", "-", "*", "/"};
        VectorOfIntVectors number_permutations{};
        VectorOfStringVectors operand_permutations{};
        VectorOfStringVectors permutations{};
        IntVector initial_numbers;
    public:
        PermutationCalculator() = default;
        explicit PermutationCalculator(IntVector const &p_initial_numbers);
        void init(IntVector const &p_initial_numbers);
        VectorOfStringVectors get_permutations();

    private:
        void calculate_expression_permutations(IntVector const &numbers);

        void calculate_numbers_permutations(IntVector a, int size, int n);

        void calculate_operator_permutations();

        void clear();
    };
}

#endif //COUNTDOWNNUMBERSEARCH_PERMUTATIONGENERATOR_H
