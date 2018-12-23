#include "../../headers/types/PermutationList.h"

namespace zmote::countdown {
    template<class T>
    PermutationList<T>::PermutationList(std::vector<Permutation<T>> const &p_list)
            : list_{p_list} {}

    template<class T>
    PermutationList<T>::PermutationList(std::initializer_list<Permutation<T>> list_of_permutations)
            : list_{list_of_permutations} {

    }

    template<class T>
    typename PermutationList<T>::iterator PermutationList<T>::begin() {
        return zmote::countdown::PermutationList<T>::iterator();
    }

    template<class T>
    typename PermutationList<T>::const_iterator PermutationList<T>::begin() const {
        return list_.cbegin();
    }

    template<class T>
    typename PermutationList<T>::iterator PermutationList<T>::end() {
        return list_.end();
    }

    template<class T>
    typename PermutationList<T>::const_iterator PermutationList<T>::end() const {
        return list_.cend();
    }

    template<class T>
    void PermutationList<T>::add(Permutation<T> const &p_entry) {
        list_.emplace_back(p_entry);
    }
}