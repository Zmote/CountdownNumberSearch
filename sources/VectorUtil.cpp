#include "../headers/VectorUtil.h"

namespace zmote::countdown::util {
    void append(VectorOfStringVectors &first, VectorOfStringVectors const &second) {
        std::copy(second.begin(), second.end(), std::back_inserter(first));
    }
}