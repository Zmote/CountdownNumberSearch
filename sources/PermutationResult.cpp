#include <utility>

#include "../headers/PermutationResult.h"

namespace zmote::countdown {
    PermutationResult::PermutationResult(std::string p_operation, int p_result, int p_target, int p_diff)
            : operation{std::move(p_operation)}, result{p_result}, target{p_target}, diff{p_diff} {}
}