#include <utility>

#include "../../headers/types/EvaluationResult.h"

namespace zmote::countdown {
    EvaluationResult::EvaluationResult(std::string p_operation, int p_result, int p_target, int p_diff)
            : operation{std::move(p_operation)}, result{p_result}, target{p_target}, diff{p_diff} {}

    bool EvaluationResult::operator==(EvaluationResult const &right) const {
        return operation == right.operation;
    }

    bool EvaluationResult::operator<(EvaluationResult const &right) const {
        return operation < right.operation;
    }
}