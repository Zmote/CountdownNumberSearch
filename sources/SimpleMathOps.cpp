#include "../headers/SimpleMathOps.h"

namespace zmote::countdown {
    int SimpleMathOps::add(int first, int second) {
        return first + second;
    }

    int SimpleMathOps::subtract(int first, int second) {
        return first - second;
    }

    int SimpleMathOps::multiply(int first, int second) {
        return first * second;
    }

    int SimpleMathOps::divide(int first, int second) {
        if (second == 0) throw std::invalid_argument{"Can't divide through zero"};
        if (first % second != 0) throw std::invalid_argument{"Can't have fractions!"};
        return first / second;
    }
}