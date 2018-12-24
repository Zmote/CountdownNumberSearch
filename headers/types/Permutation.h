#ifndef COUNTDOWNNUMBERSEARCH_PERMUTATION_H
#define COUNTDOWNNUMBERSEARCH_PERMUTATION_H

#include <string>
#include <vector>
#include <type_traits>
#include <boost/operators.hpp>
#include <stdexcept>
#include "../typetraits/CountdownTraits.h"

namespace zmote::countdown {

    /**
     * Base declaration for all disallowed types
     * */
    template<class T, class Enable = void>
    class Permutation;

    template<class T>
    class Permutation<T, typename std::enable_if_t<has_operator_plus_equal<T>::value>>
            : boost::less_than_comparable<Permutation<T>> {
        std::vector<T> _parts;
    public:
        explicit Permutation(std::vector<T> const &p_content)
                : _parts{p_content} {}

        Permutation(std::initializer_list<T> p_list)
                : _parts{p_list} {}

        std::vector<T> get_parts() const {
            return _parts;
        }

        T join() {
            T joined{};
            for (T const &part : _parts) {
                joined += part;
            }
            return joined;
        }

        size_t size() const {
            return _parts.size();
        }

        bool operator<(Permutation<T> const &rhs) const {
            return size() < rhs.size();
        }
    };
}

#endif //COUNTDOWNNUMBERSEARCH_PERMUTATION_H
