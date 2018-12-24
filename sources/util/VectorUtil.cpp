#include "../../headers/util/VectorUtil.h"

namespace zmote::countdown::util {
    void append(std::vector<std::vector<std::string>> &first,
                std::vector<std::vector<std::string>> const &second) {
        std::copy(second.begin(), second.end(), std::back_inserter(first));
    }
}