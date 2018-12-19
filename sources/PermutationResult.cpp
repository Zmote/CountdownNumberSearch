#include <utility>

#include "../headers/PermutationResult.h"

namespace zmote::countdown {
    PermutationResult::PermutationResult(std::string p_operation, int p_result, int p_target, int p_diff)
            : operation{std::move(p_operation)}, result{p_result}, target{p_target}, diff{p_diff} {}

    bool PermutationResult::operator==(PermutationResult const &right) const{
        return operation == right.operation;
    }

    bool PermutationResult::operator!=(PermutationResult const &right) const{
        return !(*this == right);
    }

    bool PermutationResult::operator<(PermutationResult const &right) const{
        return operation < right.operation;
    }

    bool PermutationResult::operator<=(PermutationResult const &right) const{
        return operation <= right.operation;
    }

    bool PermutationResult::operator>(PermutationResult const &right) const{
        return operation > right.operation;
    }

    bool PermutationResult::operator>=(PermutationResult const &right) const{
        return operation >= right.operation;;
    }
}