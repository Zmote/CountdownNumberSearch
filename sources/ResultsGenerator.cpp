#include <utility>

#include <utility>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <thread>
#include <future>

#include "../headers/ResultsGenerator.h"

namespace zmote::countdown {
    ResultsGenerator::ResultsGenerator(int p_target, IntVector p_initial_numbers) {
        generate_for(p_target, std::move(p_initial_numbers));
    }

    PermutationResultVector ResultsGenerator::get_results() {
        PermutationResultVector sorted_results{results.begin(), results.end()};
        std::sort(sorted_results.begin(), sorted_results.end(),
                  [](PermutationResult const &first, PermutationResult const &second) {
                      return first.diff > second.diff;
                  });
        return sorted_results;
    }

    // TODO: Refactor long ass function
    void ResultsGenerator::generate_for(int p_target, IntVector p_initial_numbers) {
        clear();
        permutation_calculator.init(p_initial_numbers);

        VectorOfStringVectors const &permutations{permutation_calculator.get_permutations()};
        VectorOfStringVectors sub_permutations{};
        std::vector<VectorOfStringVectors> parts{};
        int thread_count = static_cast<int>(round(permutations.size() / PARTITION_SIZE));
        int permutations_limit = static_cast<int>(round(permutations.size() / thread_count));

        split_permutations_into_ranges(permutations, sub_permutations, parts, permutations_limit);

        std::vector<std::future<std::set<PermutationResult>>> partial_results{};
        std::vector<std::thread> threads{};

        run_evaluation_threads(p_target, parts, partial_results, threads);
        join_evaluation_threads(threads);
        populate_results_from_futures(partial_results);
    }

    void ResultsGenerator::split_permutations_into_ranges(const VectorOfStringVectors &permutations,
                                                          VectorOfStringVectors &sub_permutations,
                                                          std::vector<VectorOfStringVectors> &parts,
                                                          int permutations_limit) const {
        for (int i = 0; i < permutations.size(); i++) {
            sub_permutations.emplace_back(permutations[i]);
            if (i > 0 && i % permutations_limit == 0) {
                parts.emplace_back(sub_permutations);
                sub_permutations.clear();
            }
        }
    }

    void ResultsGenerator::join_evaluation_threads(std::vector<std::thread> &threads) {
        for (std::thread &a_thread: threads) {
            a_thread.join();
        }
    }

    void ResultsGenerator::populate_results_from_futures(
            std::vector<std::future<std::set<PermutationResult>>> &partial_results) {
        for (std::future<std::set<PermutationResult>> &sub_res_future: partial_results) {
            for (PermutationResult const &res: sub_res_future.get()) {
                results.emplace(res);
            }
        }
    }

    void ResultsGenerator::run_evaluation_threads(int p_target, const std::vector<VectorOfStringVectors> &parts,
                                                  std::vector<std::future<std::set<PermutationResult>>> &partial_results,
                                                  std::vector<std::thread> &threads) const {
        for (VectorOfStringVectors const &sub_perms: parts) {
            using PermutationResultsPromise = std::promise<std::set<PermutationResult>>;
            PermutationResultsPromise promise{};
            partial_results.emplace_back(promise.get_future());
            threads.emplace_back(std::thread{[&](PermutationResultsPromise &&p_promise) {
                std::set<PermutationResult> sub_results{};
                run_evaluation(p_target, sub_perms, sub_results);
                p_promise.set_value(sub_results);
            }, move(promise)});
        }
    }

    void ResultsGenerator::run_evaluation(int p_target, const VectorOfStringVectors &sub_perms,
                                          std::set<PermutationResult> &sub_results) const {
        ExpressionEvaluator expression_evaluator{};
        for (StringVector const &permutation : sub_perms) {
            auto pair = expression_evaluator.evaluate(permutation, p_target);
            if (pair.second >= 0) {
                sub_results.insert(
                        PermutationResult{pair.first, pair.second, p_target, abs(pair.second - p_target)});
            }
        }
    }

    void ResultsGenerator::clear() {
        results = PermutationResultSet{};
    }
}