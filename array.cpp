#include "std::array.h"

#ifndef ARR
#define ARR

template<typename T, int N>
array<T,N>::array() : b{true}, arr{} {}

template<typename T, int N>
array<T,N>::array(std::initializer_list<T> list) : b{false} {
    int i = 0;
    for (auto& elem : list) {
        arr[i] = elem;
        ++i;
    }
}

template<typename T, int N>
array<T,N>::array(const array& rhv) : b{false} {
    for (int i = 0; i < N; ++i) {
        arr[i] = rhv.arr[i];
    }
}

template<typename T, int N>
array<T,N>::array(array&& rhv) noexcept : b{false} {
    for (int i = 0; i < N; ++i) {
        arr[i] = std::move(rhv.arr[i]);
        rhv.arr[i].~T();
    }
}

template<typename T, int N>
array<T, N>::~array() {
    for (int i = 0; i < N; ++i) {
        arr[i].~T();
    }
}

template<typename T, int N>
const array<T,N>& array<T,N>::operator=(const array& rhv) {
    if (this != &rhv) {
        for (int i = 0; i < N; ++i) {
            arr[i] = rhv.arr[i];
        }
    }
    return *this;
}

template<typename T, int N>
const array<T,N>& array<T,N>::operator=(array&& rhv) {
    if (this != &rhv) {
        for (int i = 0; i < N; ++i) {
            arr[i] = std::move(rhv.arr[i]);
            rhv.arr[i].~T();
        }
    }
    return *this;
}


template<typename T, int N>
bool array<T,N>::operator==(const array& rhv) const {
    for (int i = 0; i < N; ++i) {
        if (arr[i] != rhv.arr[i]) {
            return false;
        }
    }
    return true;
}

template<typename T, int N>
bool array<T,N>::operator!=(const array& rhv) const {
    return !(*this == rhv);
}


template<typename T, int N>
bool array<T, N>::operator<(const array& rhv) const {
    for (int i = 0; i < N; ++i) {
        if (arr[i] < rhv.arr[i]) {
            return true;
        }
        else if (arr[i] > rhv.arr[i]) {
            return false;
        }
    }
    return false;
}

template<typename T, int N>
bool array<T,N>::operator<=(const array& rhv) const {
    return (*this < rhv) || (*this == rhv);
}

template<typename T, int N>
bool array<T,N>::operator>(const array& rhv) const {
    return !(*this <= rhv);
}

template<typename T, int N>
bool array<T, N>::operator>=(const array& rhv) const {
    return !(*this < rhv);
}

template<typename T, int N>
T& array<T,N>::operator[](size_t pos) {
    return arr[pos];
}

template<typename T, int N>
const T& array<T,N>::operator[](size_t pos) const {
    return arr[pos];
}

template<typename T, int N>
T& array<T, N>::get(size_t pos) {
    return arr[pos];
}

template<typename T, int N>
const T& array<T,N>::get(size_t pos) const {
    return arr[pos];
}

template<typename T, int N>
T& array<T,N>::at(size_t pos) {
    if (pos < N && pos >= 0) {
        return arr[pos];
    }
    throw std::out_of_range("position is out of range");
}

template<typename T, int N>
const T& array<T,N>::at(size_t pos) const {
    if (pos < N && pos >= 0) {
        return arr[pos];
    }
    throw std::out_of_range("position is out of range");
}

template<typename T, int N>
T& array<T,N>::front() {
    return arr[0];
}

template<typename T, int N>
const T& array<T,N>::front() const {
    return arr[0];
}

template<typename T, int N>
T& array<T,N>::back() {
    return arr[N - 1];
}

template<typename T, int N>
const T& array<T,N>::back() const {
    return arr[N - 1];
}

template<typename T, int N>
T* array<T,N>::data() noexcept {
    return arr;
}

template<typename T, int N>
const T* array<T,N>::data() const noexcept {
    return arr;
}

template<typename T, int N>
bool array<T,N>::empty() {
    return b;
}

template<typename T, int N>
size_t array<T,N>::size() {
    return N;
}


#endif



