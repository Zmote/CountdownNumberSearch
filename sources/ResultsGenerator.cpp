#include <utility>

#include <utility>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <thread>
#include <future>

#include "../headers/ResultsGenerator.h"

namespace zmote::countdown {
    ResultsGenerator::ResultsGenerator(int p_target, std::vector<int> p_initial_numbers) {
        generate_for(p_target, std::move(p_initial_numbers));
    }

    std::vector<EvaluationResult> ResultsGenerator::get_results() {
        std::vector<EvaluationResult> sorted_results{results.begin(), results.end()};
        std::sort(sorted_results.begin(), sorted_results.end(),
                  [](EvaluationResult const &first, EvaluationResult const &second) {
                      return first.diff > second.diff;
                  });
        return sorted_results;
    }

    void ResultsGenerator::generate_for(int p_target, std::vector<int> p_initial_numbers) {
        clear();
        permutation_calculator.init(p_initial_numbers);

        std::vector<std::vector<std::string>> const &permutations{permutation_calculator.get_permutations()};

        int thread_count = static_cast<int>(round(permutations.size() / PARTITION_SIZE));
        int permutations_limit = static_cast<int>(round(permutations.size() / thread_count));

        std::vector<std::vector<std::vector<std::string>>> parts{
                split_permutations_into_ranges(permutations, permutations_limit)};
        std::vector<std::future<std::set<EvaluationResult>>> partial_results{};
        join_evaluation_threads(instantiate_evaluation_threads(p_target, parts, partial_results));
        populate_results_from_futures(partial_results);
    }

    std::vector<std::vector<std::vector<std::string>>>
    ResultsGenerator::split_permutations_into_ranges(std::vector<std::vector<std::string>> const &permutations,
                                                     int const &permutations_limit) const {
        std::vector<std::vector<std::vector<std::string>>> parts{};
        std::vector<std::vector<std::string>> sub_permutations{};
        for (int i = 0; i < permutations.size(); i++) {
            sub_permutations.emplace_back(permutations[i]);
            if (i > 0 && i % permutations_limit == 0) {
                parts.emplace_back(sub_permutations);
                sub_permutations.clear();
            }
        }
        return parts;
    }

    void ResultsGenerator::join_evaluation_threads(std::vector<std::thread> &&threads) {
        for (std::thread &a_thread: threads) {
            a_thread.join();
        }
    }

    void ResultsGenerator::populate_results_from_futures(
            std::vector<std::future<std::set<EvaluationResult>>> &partial_results) {
        for (std::future<std::set<EvaluationResult>> &sub_res_future: partial_results) {
            for (EvaluationResult const &res: sub_res_future.get()) {
                results.emplace(res);
            }
        }
    }

    std::vector<std::thread>
    ResultsGenerator::instantiate_evaluation_threads(int p_target,
                                                     std::vector<std::vector<std::vector<std::string>>> const &parts,
                                                     std::vector<std::future<std::set<EvaluationResult>>> &partial_results) const {
        std::vector<std::thread> threads{};
        for (std::vector<std::vector<std::string>> const &sub_perms: parts) {
            std::promise<std::set<EvaluationResult>> promise{};
            partial_results.emplace_back(promise.get_future());
            threads.emplace_back(std::thread{[&](std::promise<std::set<EvaluationResult>> &&p_promise) {
                std::set<EvaluationResult> sub_results{};
                run_evaluation(p_target, sub_perms, sub_results);
                p_promise.set_value(sub_results);
            }, std::move(promise)});
        }
        return threads;
    }

    void ResultsGenerator::run_evaluation(int p_target, const std::vector<std::vector<std::string>> &sub_perms,
                                          std::set<EvaluationResult> &sub_results) const {
        ExpressionEvaluator expression_evaluator{};
        for (std::vector<std::string> const &permutation : sub_perms) {
            auto const pair = expression_evaluator.evaluate(permutation, p_target);
            if (pair.second >= 0) {
                sub_results.insert(
                        EvaluationResult{pair.first, pair.second, p_target, abs(pair.second - p_target)});
            }
        }
    }

    void ResultsGenerator::clear() {
        results = std::set<EvaluationResult>{};
    }
}