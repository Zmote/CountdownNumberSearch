#include <iostream>
#include <algorithm>
#include "headers/ResultsGenerator.h"

void start_calculation() {
    using namespace zmote::countdown;
    std::cout << "Please enter your TARGET number:";
    int target{};
    std::cin >> target;
    std::cout << "\nPlease enter 6 numbers from the set of numbers\n"
                 "[100, 75, 50, 25, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1],\n"
                 "use spaces to separate (duplicates allowed): ";
    IntVector const number_set{100, 75, 50, 25, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    IntVector initial_numbers{};
    for (int i = 0; i < 6; i++) {
        int number{};
        std::cin >> number;
        if (find(number_set.begin(), number_set.end(), number) != number_set.end()) {
            initial_numbers.emplace_back(number);
        } else {
            throw std::invalid_argument{"Number " + std::to_string(number) + " not allowed, aborting..."};
        }
    }
    int limit{};
    std::cout << "Please enter a limit( show results with certain difference to target): ";
    std::cin >> limit;
    std::cout << "Calculating results... please be patient... \n";
    ResultsGenerator results_generator{target, initial_numbers};
    std::cout << "\n-------------- Results Start -------------------- \n\n";
    int id{0};
    for (PermutationResult const &result: results_generator.get_results()) {
        if (result.diff <= limit) {
            std::cout << std::to_string(++id)<< ") Operation: ";
            for (char const &op: result.operation) {
                if (op == '+' || op == '-' || op == '/' || op == '*') {
                    std::cout << "\n";
                    std::cout << op << " ";
                } else {
                    std::cout << op;
                }
            }
            std::cout << "\n";
            std::cout << "Result: " << result.result << ", Target: " << result.target
                      << ", Diff: " << result.diff << "\n\n";
        }
    }
    std::cout << "\n-------------- Results End ---------------------- \n\n";
}

int main() {
    std::cout << R"(
******************************************
* WELCOME TO THE COUNTDOWN NUMBERS TOOL  *
* Follow the instructiosn below the      *
* calculate all possible results         *
******************************************
)" << "\n";
    while (true) {
        try {
            start_calculation();
        } catch (std::invalid_argument const &ex) {
            std::cout << ex.what();
            return 0;
        }
        std::cout << "Do you want to continue with another round? [Y/N]: ";
        std::string response{};
        std::cin >> response;
        if (response == "N" || response == "n" || response == "NO" || response == "no" || response == "No") {
            return 0;
        } else {
            std::cout << "\n";
        }
    }
}
