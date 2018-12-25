#ifndef COUNTDOWNNUMBERSEARCH_PERMUTATIONLIST_H
#define COUNTDOWNNUMBERSEARCH_PERMUTATIONLIST_H

#include "Permutation.h"

namespace zmote::countdown {
    template<class T>
    class PermutationList {
        std::vector<Permutation<T>> list;
        using iterator = typename std::vector<Permutation<T>>::iterator;
        using const_iterator = typename std::vector<Permutation<T>>::const_iterator;
    public:
        PermutationList() = default;

        explicit PermutationList(std::vector<Permutation<T>> const &p_list)
                : list{p_list} {}

        PermutationList(std::initializer_list<Permutation<T>> list_of_permutations)
                : list{list_of_permutations} {

        }

        PermutationList(size_t n_times, Permutation<T> const &p_value)
                : list(n_times, p_value) {
        }

        iterator begin() {
            return list.begin();
        }

        const_iterator begin() const {
            return list.cbegin();
        }

        iterator end() {
            return list.end();
        }

        const_iterator end() const {
            return list.cend();
        }

        void add(Permutation<T> const &p_entry) {
            list.emplace_back(p_entry);
        }

        void add(PermutationList<T> const &p_list){
            std::copy(p_list.begin(), p_list.end(), std::back_inserter(list));
        }

        void clear() {
            list.clear();
        }

        size_t size() const {
            return list.size();
        }

        Permutation<T> &operator[](int const &index) {
            return list[index];
        }

        Permutation<T> const &operator[](int const &index) const {
            return list[index];
        }
    };

}

#endif //COUNTDOWNNUMBERSEARCH_PERMUTATIONLIST_H
