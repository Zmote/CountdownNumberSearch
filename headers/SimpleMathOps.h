#ifndef COUNTDOWNNUMBERSEARCH_SIMPLEMATHOPS_H
#define COUNTDOWNNUMBERSEARCH_SIMPLEMATHOPS_H

#include <stdexcept>

namespace zmote::countdown {
    struct SimpleMathOps {
        static int add(int first, int second);

        static int subtract(int first, int second);

        static int multiply(int first, int second);

        static int divide(int first, int second);

    };
}

#endif //COUNTDOWNNUMBERSEARCH_SIMPLEMATHOPS_H
