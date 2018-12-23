#include "../headers/VectorUtil.h"

namespace zmote::countdown::util {
    void append(vector_vectors<string>  &first, vector_vectors<string>  const &second) {
        std::copy(second.begin(), second.end(), std::back_inserter(first));
    }
}