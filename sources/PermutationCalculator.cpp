#include "../headers/PermutationCalculator.h"
#include "../headers/VectorUtil.h"

namespace zmote::countdown {

    PermutationCalculator::PermutationCalculator(vector<int> const &p_initial_numbers) {
        init(p_initial_numbers);
    }

    void PermutationCalculator::init(vector<int> const &p_initial_numbers) {
        clear();
        initial_numbers = p_initial_numbers;
        int size{static_cast<int>(initial_numbers.size())};
        calculate_numbers_permutations(initial_numbers, size, size);
        calculate_operator_permutations();
        for (vector<int> const &num_permutations: number_permutations) {
            calculate_expression_permutations(num_permutations);
        }
    }

    void PermutationCalculator::calculate_expression_permutations(vector<int> const &numbers) {
        for (vector<string> const &operands: operand_permutations) {
            vector<string> numPermutation{};
            for (int i = 0; i < numbers.size(); i++) {
                if (i == (numbers.size() - 1)) {
                    numPermutation.emplace_back(std::to_string(numbers[i]));
                } else {
                    numPermutation.emplace_back(std::to_string(numbers[i]));
                    numPermutation.emplace_back(operands[i]);
                }
            }
            permutations.emplace_back(numPermutation);
        }
    }

    void PermutationCalculator::calculate_operator_permutations() {
        vector_vectors<string> operands(initial_numbers.size() - 1, operators);
        vector<int> slots(initial_numbers.size() - 1, 0);
        while (slots[0] < operators.size()) {
            vector<string> permutation{};
            for (int i = 0; i < slots.size(); i++) {
                permutation.emplace_back(operands[i][slots[i]]);
            }
            operand_permutations.emplace_back(permutation);
            ++slots[slots.size() - 1];
            for (int i = static_cast<int>(slots.size() - 1); i > 0; i--) {
                if (slots[i] >= operators.size()) {
                    slots[i] = 0;
                    slots[i - 1]++;
                }
            }
        }
    }

    void PermutationCalculator::calculate_numbers_permutations(vector<int> a, int size, int n) {
        if (size == 1) {
            number_permutations.emplace_back(a);
            return;
        }

        for (int i = 0; i < size; i++) {
            calculate_numbers_permutations(a, size - 1, n);
            if (size % 2 == 1) {
                std::swap(a[0], a[size - 1]);
            } else {
                std::swap(a[i], a[size - 1]);
            }
        }
    }

    vector_vectors<string> PermutationCalculator::get_permutations() {
        return permutations;
    }

    void PermutationCalculator::clear() {
        number_permutations = vector_vectors<int>{};
        operand_permutations = vector_vectors<string>{};
        permutations = vector_vectors<string>{};
    }
}
