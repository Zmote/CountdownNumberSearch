#ifndef COUNTDOWNNUMBERSEARCH_COUNTDOWNALIASES_H
#define COUNTDOWNNUMBERSEARCH_COUNTDOWNALIASES_H

#include <string>
#include <vector>

namespace zmote::countdown {
    using string = std::string;
    template<class T>
    using vector = std::vector<T>;
    template<class T>
    using vector_vectors = vector<vector<T>>;
    template<class FIRST, class SECOND>
    using pair = std::pair<FIRST, SECOND>;
}

#endif //COUNTDOWNNUMBERSEARCH_COUNTDOWNALIASES_H
