#ifndef COUNTDOWNNUMBERSEARCH_COUNTDOWN_TRAITS_H
#define COUNTDOWNNUMBERSEARCH_COUNTDOWN_TRAITS_H

#include <type_traits>

namespace zmote::countdown {
    // Only make helper types available within this file
    namespace {
        struct No {
            char dummy;
        };

        //Defining it for the case += operator doesn't exist
        //and tempalte resolution resolves to false
        //rather than the compilation failing (ie. this prevents it from failing)
        //by providing an appropriate substitution
        template<typename T>
        No operator+=(const T &, const T &);

        struct Yes {
            //Ensuring that sizeof comparison is
            //definitely different sizes for No vs. Yes
            char dummy[2];
        };
    }

    template<class T>
    class has_size_method {
        template<typename C>
        static Yes test(decltype(&C::size));

        template<typename C>
        static No test(...);

    public:
        enum {
            value = sizeof(test<T>(0)) == sizeof(Yes)
        };
    };

    template<class T>
    struct has_operator_plus_equal {
        enum {
            value = !std::is_same<decltype(*(T *) (0) += *(T *) (0)), No>::value
        };
    };

}

#endif //COUNTDOWNNUMBERSEARCH_COUNTDOWN_TRAITS_H
