#include "../headers/PermutationCalculator.h"
#include "../headers/VectorUtil.h"

namespace zmote::countdown {

    PermutationCalculator::PermutationCalculator(std::vector<int> const &p_initial_numbers) {
        init(p_initial_numbers);
    }

    void PermutationCalculator::init(std::vector<int> const &p_initial_numbers) {
        clear();
        initial_numbers = p_initial_numbers;
        int size{static_cast<int>(initial_numbers.size())};
        calculate_numbers_permutations(initial_numbers, size, size);
        calculate_operator_permutations();
        for (std::vector<int> const &num_permutations: number_permutations) {
            calculate_expression_permutations(num_permutations);
        }
    }

    void PermutationCalculator::calculate_expression_permutations(std::vector<int> const &numbers) {
        for (std::vector<std::string> const &operands: operand_permutations) {
            std::vector<std::string> numPermutation{};
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
        std::vector<std::vector<std::string>> operands(initial_numbers.size() - 1, operators);
        std::vector<int> slots(initial_numbers.size() - 1, 0);
        while (slots[0] < operators.size()) {
            std::vector<std::string> permutation{};
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

    void PermutationCalculator::calculate_numbers_permutations(std::vector<int> a, int size, int n) {
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

    std::vector<std::vector<std::string>> PermutationCalculator::get_permutations() {
        return permutations;
    }

    void PermutationCalculator::clear() {
        number_permutations.clear();
        operand_permutations.clear();
        permutations.clear();
    }
}
