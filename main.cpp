#include <iostream>
#include <algorithm>
#include <chrono>
#include "headers/ResultsGenerator.h"

void start_calculation() {
    using namespace zmote::countdown;
    std::cout << "Please enter your TARGET number:";
    int target{};
    std::cin >> target;
    std::cout << "\nPlease enter 6 numbers from the set of numbers\n"
                 "[100, 75, 50, 25, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1],\n"
                 "use spaces to separate (duplicates allowed): ";
    std::vector<int> const number_set{100, 75, 50, 25, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    Permutation<int> initial_numbers{};
    for (int i = 0; i < 6; i++) {
        int number{};
        std::cin >> number;
        if (find(number_set.begin(), number_set.end(), number) != number_set.end()) {
            initial_numbers.add(number);
        } else {
            throw std::invalid_argument{"Number " + std::to_string(number) + " not allowed, aborting..."};
        }
    }
    int limit{};
    std::cout << "Please enter a limit( show results with certain difference to target): ";
    std::cin >> limit;
    std::cout << "Calculating results... please be patient... \n";
    auto start = std::chrono::high_resolution_clock::now();
    ResultsGenerator results_generator{target, initial_numbers};
    std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - start;
    std::cout << "Calculation took: " << std::to_string(elapsed.count()) << "s\n";
    std::cout << "\n-------------- Results Start -------------------- \n\n";
    int id{0};
    for (EvaluationResult const &result: results_generator.get_results()) {
        if (result.diff <= limit) {
            std::cout << std::to_string(++id) << ") Operation: " << result.operation << ", Result: "
                      << result.result << ", Target: " << result.target << ", Diff: " << result.diff << "\n";
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
