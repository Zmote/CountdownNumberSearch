#ifndef COUNTDOWNNUMBERSEARCH_PERMUTATIONRESULT_H
#define COUNTDOWNNUMBERSEARCH_PERMUTATIONRESULT_H

#include <string>
#include <boost/operators.hpp>

namespace zmote::countdown {
    struct EvaluationResult
            : boost::less_than_comparable<EvaluationResult>,
              boost::equality_comparable<EvaluationResult> {
        int target;
        int diff;
        int result;
        std::string operation;
    public:
        EvaluationResult(std::string p_operation, int p_result, int p_target, int p_diff);

        bool operator==(EvaluationResult const &right) const;

        bool operator<(EvaluationResult const &right) const;
    };
}

#endif //COUNTDOWNNUMBERSEARCH_PERMUTATIONRESULT_H
