#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

using String = std::string;
using StringVector = std::vector<String>;
using VectorOfStringVectors = std::vector<StringVector>;
using IntVector = std::vector<int>;

int add(int first, int second) {
    return first + second;
}

int subtract(int first, int second) {
    return first - second;
}

int multiply(int first, int second) {
    return first * second;
}

int divide(int first, int second) {
    if (second == 0) throw std::invalid_argument{"Can't divide through zero"};
    if (first % second != 0) throw std::invalid_argument{"Can't have fractions!"};
    return first / second;
}

StringVector calculate_permutations(IntVector const &numbers,
                                    StringVector const &operators) {
    auto permutations = StringVector{};
    VectorOfStringVectors operands =
            VectorOfStringVectors(numbers.size() - 1, operators);
    VectorOfStringVectors operandPermutations{};
    std::vector<int> slots(numbers.size() - 1, 0);
    while (slots[0] < operators.size()) {
        StringVector permutation{};
        for (int i = 0; i < slots.size(); i++) {
            permutation.emplace_back(operands[i][slots[i]]);
        }
        operandPermutations.emplace_back(permutation);
        ++slots[slots.size() - 1];
        for (int i = static_cast<int>(slots.size() - 1); i > 0; i--) {
            if (slots[i] >= operators.size()) {
                slots[i] = 0;
                slots[i - 1]++;
            }
        }
    }

    for (StringVector const &_operands: operandPermutations) {
        String numPermutation{};
        for (int i = 0; i < numbers.size(); i++) {
            if (i == (numbers.size() - 1)) {
                numPermutation += std::to_string(numbers[i]);
            } else {
                numPermutation += std::to_string(numbers[i]);
                numPermutation += _operands[i];
            }
        }
        permutations.emplace_back(numPermutation);
    }

    return permutations;
};

int main() {
    int target = 271;
    IntVector numbers{1, 4, 10, 8, 25, 50};
    StringVector operators{"+", "-", "*", "/"};
    StringVector permutations{calculate_permutations(numbers, operators)};
    for (String const &permutation: permutations) {
        std::cout << permutation << "\n";
    }
}