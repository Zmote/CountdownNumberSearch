#ifndef COUNTDOWNNUMBERSEARCH_PERMUTATIONLIST_H
#define COUNTDOWNNUMBERSEARCH_PERMUTATIONLIST_H

#include "Permutation.h"

namespace zmote::countdown {
    template<class T>
    class PermutationList {
        vector<Permutation<T>> list_;
        using iterator = typename vector<Permutation<T>>::iterator;
        using const_iterator = typename vector<Permutation<T>>::const_iterator;
    public:
        PermutationList() = default;

        explicit PermutationList(vector<Permutation<T>> const &p_list);

        PermutationList(std::initializer_list<Permutation<T>> list_of_permutations);

        void add(Permutation<T> const &p_entry);

        iterator begin();

        const_iterator begin() const;

        iterator end();

        const_iterator end() const;
    };

}

#endif //COUNTDOWNNUMBERSEARCH_PERMUTATIONLIST_H
