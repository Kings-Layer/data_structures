#include "dinamic_array.h"
 


#ifndef ARR
#define ARR

template<typename T>
dinamic_array<T>::const_iterator::const_iterator(T* ptr) : ptr{ptr} {}

template<typename T>
dinamic_array<T>::const_iterator::const_iterator() : ptr{nullptr} {}

template<typename T>
dinamic_array<T>::const_iterator::const_iterator(const const_iterator& rhv) : ptr{rhv.ptr} {}

template<typename T>
dinamic_array<T>::const_iterator::const_iterator(const_iterator&& rhv) noexcept : ptr{std::move(rhv.ptr)}{
    rhv.ptr = nullptr;
}

template<typename T>
const typename dinamic_array<T>::const_iterator dinamic_array<T>::const_iterator::operator=(const const_iterator& rhv) {
        ptr = rhv.ptr;
}

template<typename T>
const typename dinamic_array<T>::const_iterator dinamic_array<T>::const_iterator::operator=(const_iterator&& rhv) {
    ptr = std::move(rhv.ptr);
    rhv.ptr = nullptr;
}

template<typename T>
const T& dinamic_array<T>::const_iterator::operator*() const {
    return *ptr;
}

template<typename T>
const T* dinamic_array<T>::const_iterator::operator->() const {
    return ptr;
}

template<typename T>
typename dinamic_array<T>::const_iterator& dinamic_array<T>::const_iterator::operator++() {
    ++ptr;
    return *this;
}

template<typename T>
typename dinamic_array<T>::const_iterator& dinamic_array<T>::const_iterator::operator++(int) {
    const_iterator tmp = *this;
    ++(*this);
    return tmp;
}

template<typename T>
typename dinamic_array<T>::const_iterator& dinamic_array<T>::const_iterator::operator--() {
    --ptr;
    return *this;
}

template<typename T>
typename dinamic_array<T>::const_iterator& dinamic_array<T>::const_iterator::operator--(int) {
    const_iterator tmp = *this;
    --(*this);
    return tmp;
}

template<typename T>
typename dinamic_array<T>::const_iterator& dinamic_array<T>::const_iterator::operator+(size_t offset) {
    return (ptr + offset);
}

template<typename T>
typename dinamic_array<T>::const_iterator& dinamic_array<T>::const_iterator::operator-(size_t offset) {
    return (ptr - offset);
}

template<typename T>
typename dinamic_array<T>::const_iterator& dinamic_array<T>::const_iterator::operator+=(size_t offset) {
    ptr += offset;
    return *this;
}

template<typename T>
typename dinamic_array<T>::const_iterator& dinamic_array<T>::const_iterator::operator-=(size_t offset) {
    ptr -= offset;
    return *this;
}

template<typename T>
const T& dinamic_array<T>::const_iterator::operator[](size_t pos) const {
    return ptr[pos];
}

template<typename T>
bool dinamic_array<T>::const_iterator::operator==(const const_iterator& rhv) const {
    return ptr == rhv.ptr;
}

template<typename T>
bool dinamic_array<T>::const_iterator::operator!=(const const_iterator& rhv) const {
    return !(*this == rhv);
}

template<typename T>
bool dinamic_array<T>::const_iterator::operator<(const const_iterator& rhv) const {
    return ptr < rhv.ptr;
}

template<typename T>
bool dinamic_array<T>::const_iterator::operator<=(const const_iterator& rhv) const {
    return (*this < rhv) || (*this == rhv);
}

template<typename T>
bool dinamic_array<T>::const_iterator::operator>(const const_iterator& rhv) const {
    return ptr > rhv.ptr;
}

template<typename T>
bool dinamic_array<T>::const_iterator::operator>=(const const_iterator& rhv) const {
    return (*this > rhv) || (*this == rhv);
}

template<typename T>
dinamic_array<T>::iterator::iterator() : const_iterator() {}

template<typename T>
dinamic_array<T>::iterator::iterator(T* ptr) : const_iterator(ptr) {}

template<typename T>
dinamic_array<T>::iterator::iterator(const iterator& rhv) : const_iterator(rhv) {}

template<typename T>
dinamic_array<T>::iterator::iterator(iterator&& rhv) : const_iterator(std::move(rhv)) {}

template<typename T>
T& dinamic_array<T>::iterator::operator*() {
    return *(this->ptr);
}

template<typename T>
T* dinamic_array<T>::iterator::operator->() {
    return this->ptr;
}

template<typename T>
T& dinamic_array<T>::iterator::operator[](size_t pos) {
    return this->ptr[pos];
}

template<typename T>
dinamic_array<T>::dinamic_array() : size{0}, capacity{0}, arr{nullptr} {}


template<typename T>
dinamic_array<T>::dinamic_array(size_t n) : capacity{n}, size{0} {
    arr = new T[capacity];
}

template<typename T>
dinamic_array<T>::dinamic_array(size_t n, const T& value) : size{n}, capacity{n} {
    arr = new T[capacity];
    for (int i = 0; i < size; ++i) {
        arr[i] = value;
    }
}

template<typename T>
dinamic_array<T>::dinamic_array(const dinamic_array& rhv) : capacity{rhv.capacity}, size{rhv.size} {
    arr = new T[capacity];
    for (int i = 0; i < size; ++i) {
        arr[i] = rhv.arr[i];
    }
}

template<typename T>
dinamic_array<T>::dinamic_array(dinamic_array&& rhv) noexcept : size{rhv.size}, capacity{rhv.capacity} {
    arr = new T[capacity];
    for (int i = 0; i < size; ++i) {
        arr[i] = rhv.arr[i];
    }
    delete[] rhv.arr;
    rhv.size = 0;
    rhv.capacity = 0;
}

template<typename T>
dinamic_array<T>::dinamic_array(std::initializer_list<T> list) {
    capacity = list.size();
    size = capacity;
    arr = new T[capacity];
    int i = 0;
    for (auto& elem : list) {
        arr[i] = elem;
        ++i;
    }
}

template<typename T>
dinamic_array<T>::~dinamic_array() {
    clear();
}

template<typename T>
dinamic_array<T>& dinamic_array<T>::dinamic_array::operator=(const dinamic_array& rhv) {
    if(this != &rhv) {
        if (capacity < rhv.capacity) {
            reserve(rhv.capacity);
            capacity = rhv.capacity;
        }
        size = rhv.size;
        for (int i = 0; i < size; ++i) {
            arr[i] = rhv.arr[i];
        }
    }
    return *this;
}

template<typename T>
dinamic_array<T>& dinamic_array<T>::operator=(dinamic_array&& rhv) noexcept {
     if(this != &rhv) {
        if (capacity < rhv.capacity) {
            reserve(rhv.capacity);
            capacity = rhv.capacity;
        }
        size = rhv.size;
        for (int i = 0; i < size; ++i) {
            arr[i] = rhv.arr[i];
        }
    }
    rhv.size = 0;
    rhv.capacity = 0;
    delete[] rhv.arr;
    return *this;
}

template<typename T>
const T& dinamic_array<T>::operator[](size_t pos) const {
    return arr[pos];
}

template<typename T>
T& dinamic_array<T>::operator[](size_t pos) {
    return arr[pos];
}

template<typename T>
bool dinamic_array<T>::operator==(const dinamic_array& rhv) const {
    if (size != rhv.size)
        return false;
    for (int i = 0; i < size; ++i) {
        if (arr[i] != rhv.arr[i]) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool dinamic_array<T>::operator!=(const dinamic_array& rhv) const {
    return !(*this == rhv);
}

template<typename T>
bool dinamic_array<T>::operator<(const dinamic_array& rhv) const {
    for (int i = 0; i < size; ++i) {
        if (arr[i] < rhv.arr[i]) {
            return true;
        } else if (arr[i] > rhv.arr[i]) {
            return false;
        }
    }
    return false;
}

template<typename T>
bool dinamic_array<T>::operator<=(const dinamic_array& rhv) const {
    return (*this < rhv) || (*this == rhv);
}

template<typename T>
bool dinamic_array<T>::operator>(const dinamic_array& rhv) const {
    return !(*this <= rhv);
}

template<typename T>
bool dinamic_array<T>::operator>=(const dinamic_array& rhv) const {
    return !(*this < rhv);
}

template<typename T>
void dinamic_array<T>::reserve(size_t cap) {
    capacity = cap;
    T* ptr = new T[cap];
    for (int i = 0; i < size; ++i) {
        ptr[i] = arr[i];
    }
    delete[] arr;
    arr = ptr;
}

template<typename T>
size_t dinamic_array<T>::get_capacity() {
    return capacity;
}

template<typename T>
bool dinamic_array<T>::include(const_reference target) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == target) {
            return true;
        }
    }
    return false;
}

template<typename T>
typename dinamic_array<T>::iterator dinamic_array<T>::insert(const_iterator pos, const_reference val) {
    if (size == capacity) {
        reserve(2 * capacity + 1);
    }
    for (auto& it = end(); it != pos; --it) {
        *it = *(it - 1);
    }
    *pos = val;
    ++size;
    return ++pos;
}

template<typename T>
typename dinamic_array<T>::iterator dinamic_array<T>::insert(const_iterator pos, size_type count, const_reference val) {
    if ((size + count) >= capacity) {
        reserve(capacity + count);
    }
    auto& it2 = end() + count - 1;
    for (auto& it1 = end() - 1; it1 != pos + count; --it1) {
        *it2 = *it1;
        --it2;
    }
    it2 = pos;
    while(it2 != pos + count) {
        *it2 = val;
        ++it2;
    }
    size += count;
    return ++it2;
}

template<typename T>
typename dinamic_array<T>::iterator dinamic_array<T>::insert(const_iterator pos, std::initializer_list<T> list) {
    size_type count = list.size();
    if ((size + count) >= capacity) {
        reserve(capacity + count);
    }
    auto& it2 = end() + count - 1;
    for (auto& it1 = end() - 1; it1 != pos + count; --it1) {
        *it2 = *it1;
        --it2;
    }
    it2 = pos;
    for (auto& elem : list) {
        *it2 = elem;
        ++it2;
    }
    size += list.size();
    return ++it2;
}

template<typename T>
size_t dinamic_array<T>::insert(size_t pos, const_reference val) {
    if (size == capacity) {
        reserve(capacity * 2 + 1);
    }
    for (int i = size; i > pos; --i) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = val;
    ++size;
    return ++pos;
}

template<typename T>
void dinamic_array<T>::push_back(const_reference val) {
    if (size == capacity) {
        reserve(capacity * 2 + 1);
    }
    arr[size] = val;
    ++size;    
}

template<typename T>
void dinamic_array<T>::pop_back() {
    if (size == 0)
        return;
    --size;
}

template<typename T>
void dinamic_array<T>::remove(size_t pos) {
    if (size == 0)
        return;
    for (int i = pos; i < size; ++i) {
        arr[i] = arr[i + 1];
    }
    --size;
}

template<typename T>
void dinamic_array<T>::remove(const_iterator pos) {
    for (auto& it = pos; it != end() - 1; ++it) {
        *it = *(it + 1);
    }
    --size;
}

template<typename T>
void dinamic_array<T>::clear() {
    size = 0;
    capacity = 0;
    delete[] arr;
}

template<typename T>
size_t dinamic_array<T>::get_size() {
    return size;
}

template<typename T>
bool dinamic_array<T>::is_empty() {
    return size == 0;
}

template<typename T>
void dinamic_array<T>::shrink_to_fit() {
    int* ptr = new value_type[size];
    for (int i = 0; i < size; ++i) {
        ptr[i] = arr[i];
    }
    delete[] arr;
    arr = ptr;
}

template<typename T>
void dinamic_array<T>::assign(size_type count, const_reference val) {
    size = count;
    for (int i = 0; i < size; ++i) {
        arr[i] = val;
    }
}

template<typename T>
T& dinamic_array<T>::at(size_type pos) {
    if (pos < 0 || pos > size) {
        throw std::out_of_range("index is out of range");
    }
    return arr[pos];
}

template<typename T>
typename dinamic_array<T>::iterator dinamic_array<T>::erase(const_iterator pos) {
    for (auto& it = pos; it != end() - 1; ++it) {
        *it = *(it + 1);
    }
    --size;
    return pos;
} 

template<typename T>
typename dinamic_array<T>::iterator dinamic_array<T>::erase(const_iterator first, const_iterator last) {
    size_type index1 = last - begin() + 1;
    size_type index2 = first - begin();
    size_type count = last - first;
    while (index2 < size - count) {
        arr[index2] = arr[index1];
        ++index2;
        ++index1;
    } 
    size = size - count;
    return ++last;
}

template<typename T>
T& dinamic_array<T>::front() {
    return arr[0];
}

template<typename T>
T& dinamic_array<T>::back() {
    return arr[size - 1];
}

template<typename T>
T* dinamic_array<T>::data() {
    return arr;
}

template<typename T>
void dinamic_array<T>::swap(dinamic_array& rhv) {
    pointer ptr = arr;
    arr = rhv.arr;
    rhv.arr = ptr;
}

template<typename T>
void dinamic_array<T>::resize(size_type count) {
    if (size >= count)
        size -= count;
} 

template<typename T>
void dinamic_array<T>::resize(size_type count, const_reference val) {
    if (size >= count) {
        size -= count;
        for (int i = 0; i < size; ++i) {
            arr[i] = val;
        }
    }
}

template<typename T>
typename dinamic_array<T>::iterator dinamic_array<T>::begin() {
    return iterator(arr);
}

template<typename T>
typename dinamic_array<T>::const_iterator dinamic_array<T>::begin() const {
    return const_iterator(arr);
}

template<typename T>
typename dinamic_array<T>::iterator dinamic_array<T>::end() {
    return iterator(&arr[size]);
}

template<typename T>
typename dinamic_array<T>::const_iterator dinamic_array<T>::end() const {
    return iterator(&arr[size]);
}

template<typename T>
template<typename... Ts>
typename dinamic_array<T>::iterator dinamic_array<T>::emplace(const_iterator pos, Ts&&... args) {
    value_type elem(args...);
    return insert(pos, elem);
}

template<typename T>
template<typename... Ts>
T& dinamic_array<T>::emplace_back(Ts&&... args) {
    value_type elem(args...);
    push_back(elem);
    return arr[size - 1];
}

template<typename T>
std::ostream& operator<<(std::ostream& out, dinamic_array<T> arr) {
    for (auto& elem : arr) {
        out << elem << "  ";
    }
    return out;
}

#endif

int main() {
    dinamic_array<int> arr;
}