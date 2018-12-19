#ifndef COUNTDOWNNUMBERSEARCH_PERMUTATIONRESULT_H
#define COUNTDOWNNUMBERSEARCH_PERMUTATIONRESULT_H

#include <string>

namespace zmote::countdown {
    struct PermutationResult {
        int target;
        int diff;
        int result;
        std::string operation;
    public:
        PermutationResult(std::string p_operation, int p_result, int p_target, int p_diff);
    };
}

#endif //COUNTDOWNNUMBERSEARCH_PERMUTATIONRESULT_H
