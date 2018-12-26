#include <chrono>
#include "../headers/PermutationCalculator.h"
#include "../headers/util/VectorUtil.h"

namespace zmote::countdown {

    PermutationCalculator::PermutationCalculator(Permutation<int> const &p_initial_numbers) {
        init(p_initial_numbers);
    }

    void PermutationCalculator::init(Permutation<int> const &p_initial_numbers) {
        clear();
        initial_numbers = p_initial_numbers;
        int size{static_cast<int>(initial_numbers.size())};
        calculate_numbers_permutations(initial_numbers, size, size);
        calculate_operator_permutations();

        for (Permutation<int> const &num_permutations: number_permutations) {
            calculate_expression_permutations(num_permutations);
        }
    }

    void PermutationCalculator::calculate_expression_permutations(Permutation<int> const &numbers) {
        int num_size = numbers.size();
        int last_index = num_size - 1;
        for (Permutation<std::string> const &operands: operand_permutations) {
            Permutation<std::string> num_permutation{};
            for (int i = 0; i < num_size; ++i) {
                if (i == last_index) {
                    num_permutation.add(std::to_string(numbers[i]));
                } else {
                    num_permutation.add(std::to_string(numbers[i]));
                    num_permutation.add(operands[i]);
                }
            }
            permutations.add(num_permutation);
        }
    }

    void PermutationCalculator::calculate_operator_permutations() {
        PermutationList<std::string> operands(initial_numbers.size() - 1, operators);
        std::vector<int> slots(initial_numbers.size() - 1, 0);
        while (slots[0] < operators.size()) {
            Permutation<std::string> permutation{};
            for (int i = 0; i < slots.size(); ++i) {
                permutation.add(operands[i][slots[i]]);
            }
            operand_permutations.add(permutation);
            ++slots[slots.size() - 1];
            for (int i = static_cast<int>(slots.size() - 1); i > 0; --i) {
                if (slots[i] >= operators.size()) {
                    slots[i] = 0;
                    ++slots[i - 1];
                }
            }
        }
    }

    void PermutationCalculator::calculate_numbers_permutations(Permutation<int> a, int size, int n) {
        if (size == 1) {
            number_permutations.add(a);
            return;
        }

        for (int i = 0; i < size; ++i) {
            calculate_numbers_permutations(a, size - 1, n);
            if (size % 2 == 1) {
                std::swap(a[0], a[size - 1]);
            } else {
                std::swap(a[i], a[size - 1]);
            }
        }
    }

    PermutationList<std::string> PermutationCalculator::get_permutations() {
        return permutations;
    }

    void PermutationCalculator::clear() {
        number_permutations.clear();
        operand_permutations.clear();
        permutations.clear();
        permutations.clear();
    }
}
