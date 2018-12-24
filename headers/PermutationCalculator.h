#ifndef COUNTDOWNNUMBERSEARCH_PERMUTATIONGENERATOR_H
#define COUNTDOWNNUMBERSEARCH_PERMUTATIONGENERATOR_H

#include <string>
#include <vector>
#include "types/EvaluationResult.h"

namespace zmote::countdown {
    class PermutationCalculator {
        std::vector<std::string> const operators{"+", "-", "*", "/"};
        std::vector<std::vector<int>> number_permutations{};
        std::vector<std::vector<std::string>> operand_permutations{};
        std::vector<std::vector<std::string>> permutations{};
        std::vector<int> initial_numbers;
    public:
        PermutationCalculator() = default;

        explicit PermutationCalculator(std::vector<int> const &p_initial_numbers);

        void init(std::vector<int> const &p_initial_numbers);

        std::vector<std::vector<std::string>> get_permutations();

    private:
        void calculate_expression_permutations(std::vector<int> const &numbers);

        void calculate_numbers_permutations(std::vector<int> a, int size, int n);

        void calculate_operator_permutations();

        void clear();
    };
}

#endif //COUNTDOWNNUMBERSEARCH_PERMUTATIONGENERATOR_H
