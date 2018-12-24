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
        std::vector<T> parts;
    public:
        Permutation() = default;

        explicit Permutation(std::vector<T> const &p_content)
                : parts{p_content} {}

        Permutation(std::initializer_list<T> p_list)
                : parts{p_list} {}

        std::vector<T> get_parts() const {
            return parts;
        }

        void add(T const &p_value) {
            parts.emplace_back(p_value);
        }

        T join() const {
            T joined{};
            for (T const &part : parts) {
                joined += part;
            }
            return joined;
        }

        size_t size() const {
            return parts.size();
        }

        bool operator<(Permutation<T> const &rhs) const {
            return size() < rhs.size();
        }

        T &operator[](int const index) {
            return parts[index];
        }

        T const &operator[](int const index) const {
            return parts[index];
        }

        template<class B = T>
        typename std::enable_if_t<std::is_same<B, std::string>::value, std::vector<B>>
        ::iterator begin() {
            return parts.begin();
        }

        template<class B = T>
        typename std::enable_if_t<std::is_same<B, std::string>::value, std::vector<B>>
        ::const_iterator begin() const {
            return parts.cbegin();
        }

        template<class B = T>
        typename std::enable_if_t<std::is_same<B, std::string>::value, std::vector<B>>
        ::iterator end() {
            return parts.end();
        }

        template<class B = T>
        typename std::enable_if_t<std::is_same<B, std::string>::value, std::vector<B>>
        ::const_iterator end() const {
            return parts.cend();
        }
    };
}

#endif //COUNTDOWNNUMBERSEARCH_PERMUTATION_H
