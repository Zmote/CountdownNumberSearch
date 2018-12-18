#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

using String = std::string;
using StringVector = std::vector<String>;
using VectorOfStringVectors = std::vector<StringVector>;
using IntVector = std::vector<int>;
using VectorOfIntVectors = std::vector<IntVector>;
using StringIntPair = std::pair<String, int>;

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

VectorOfStringVectors calculate_permutations(IntVector const &numbers) {
    StringVector operators{"+", "-", "*", "/"};
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

    VectorOfStringVectors permutations{};
    for (StringVector const &_operands: operandPermutations) {
        StringVector numPermutation{};
        for (int i = 0; i < numbers.size(); i++) {
            if (i == (numbers.size() - 1)) {
                numPermutation.emplace_back(std::to_string(numbers[i]));
            } else {
                numPermutation.emplace_back(std::to_string(numbers[i]));
                numPermutation.emplace_back(_operands[i]);
            }
        }
        permutations.emplace_back(numPermutation);
    }

    return permutations;
};

void append(VectorOfStringVectors &first, VectorOfStringVectors const &second) {
    std::copy(second.begin(), second.end(), std::back_inserter(first));
}

void numbers_permutation(IntVector a, int size, int n, VectorOfIntVectors &collected) {
    if (size == 1) {
        collected.emplace_back(a);
        return;
    }

    for (int i = 0; i < size; i++) {
        numbers_permutation(a, size - 1, n, collected);
        if (size % 2 == 1) {
            std::swap(a[0], a[size - 1]);
        } else {
            std::swap(a[i], a[size - 1]);
        }

    }
}

StringIntPair evaluate_expression(StringVector const &expression) {
    String operation{};
    for (String const &val: expression) {
        operation += val;
    }
    int result{std::stoi(expression[0])};
    for (int i = 1; i < expression.size(); i++) {
        if (expression[i] == "*") {
            result = multiply(result, std::stoi(expression[i + 1]));
        }
        if (expression[i] == "/") {
            try {
                result = divide(result, std::stoi(expression[i + 1]));
            } catch (std::exception const &ex) {
                return StringIntPair{operation + ", Failed: " + ex.what(), -1};
            }
        }
        if (expression[i] == "+") {
            result = add(result, std::stoi(expression[i + 1]));
        }
        if (expression[i] == "-") {
            result = subtract(result, std::stoi(expression[i + 1]));
        }
    }
    return StringIntPair{operation, result};
}

int main() {
    int target = 272;
    IntVector initialNumbers{1, 4, 10, 8, 25, 50};
    int size = static_cast<int>(initialNumbers.size());
    VectorOfIntVectors numberPermutations{};
    numbers_permutation(initialNumbers, size, size, numberPermutations);
    VectorOfStringVectors permutations{};
    for (IntVector const &numbers: numberPermutations) {
        append(permutations, calculate_permutations(numbers));
    }

    for (StringVector const &permutation: permutations) {
        auto pair = evaluate_expression(permutation);
        int diff = abs(pair.second - target);
        if (diff < 8) {
            std::cout << pair.first << ": " << pair.second << ", Target: "
                      << target << ", Diff: " << diff << "\n";
        }
    }
}
