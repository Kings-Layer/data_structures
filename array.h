#ifndef ARRAY
#define ARRAY

#include <iostream>
#include <string>
#include <initializer_list>
#include <stdexcept>


template<typename T, int N>
class array {
public:
using value_type = T;
using reference = value_type&;
using const_reference = const value_type&;
using pointer = value_type*;
using const_pointer = const value_type*;
    
    private:
        
        bool b;
        value_type arr[N];    

    public:
    
        array();
        array(std::initializer_list<value_type> list);
        array(const array& rhv);
        array(array&& rhv) noexcept;
        ~array();

    public:

        const array& operator=(const array& rhv);
        const array& operator=(array&& rhv);

        bool operator==(const array& rhv) const;
        bool operator!=(const array& rhv) const;
        bool operator<(const array& rhv) const;
        bool operator<=(const array& rhv) const;
        bool operator>(const array& rhv) const;
        bool operator>=(const array& rhv) const;

        reference operator[](size_t pos);
        const_reference operator[](size_t pos) const;

    public:

        reference get(size_t pos);
        const_reference get(size_t pos) const;
        reference at(size_t pos);
        const_reference at(size_t pos) const;
        reference front();
        const_reference front() const;
        reference back();
        const_reference back() const;
        pointer data() noexcept;
        const_pointer data() const noexcept;

        bool empty();
        size_t size();

    public:
        class const_iterator {
            friend class array;
            private:
            
                pointer ptr;
            
            protected:

                const_iterator(pointer p) : ptr{p} {}

            public:

                const_iterator() : ptr{nullptr} {}
                const_iterator(const const_iterator& rhv) : ptr{rhv.ptr} {}
                const_iterator(const_iterator&& rhv) noexcept : ptr(rhv.ptr) {
                    rhv.ptr = nullptr;
                }
                ~const_iterator() {
                    ptr = nullptr;
                }

            public:

                const const_iterator& operator=(const const_iterator& rhv) {
                    ptr = rhv.ptr; 
                    return *this;
                }
                
                const const_iterator& operator=(const_iterator&& rhv) {
                    ptr = rhv.ptr; 
                    rhv.ptr = nullptr; 
                    return *this;
                }
                const_reference operator*() const { 
                    return *ptr;
                }
                
                const_pointer operator->() const {
                    return ptr;
                }

                const_iterator& operator++() { 
                    ++ptr; 
                    return *this;
                }
                
                const_iterator& operator++(int) {
                    const_iterator tmp = this; 
                    ++(*this); 
                    return tmp;
                }
                
                const_iterator& operator--() {
                    --ptr; 
                    return *this;
                }

                const_iterator& operator--(int) {
                    const_iterator tmp = *this; 
                    --(*this); 
                    return tmp;
                }

                const_iterator& operator+(size_t dif) {
                    ptr += dif; 
                    return *this;
                }
                
                const_iterator& operator-(size_t dif) {
                    ptr -= dif; 
                    return *this;
                }

                const_reference operator[](size_t pos) const {
                    return ptr[pos];
                }

                bool operator==(const const_iterator& rhv) const {
                    return ptr == rhv.ptr;
                }

                bool operator!=(const const_iterator& rhv) const {
                    return ptr != rhv.ptr;
                }
                
                bool operator<(const const_iterator& rhv) const {
                    return ptr < rhv.ptr;
                }
                
                bool operator<=(const const_iterator& rhv) const {
                    return ((ptr < rhv.ptr) || (ptr == rhv.ptr));
                }

                bool operator>(const const_iterator& rhv) const {
                    return ptr > rhv.ptr;
                }

                bool operator>=(const const_iterator& rhv) const {
                    return ((ptr > rhv.ptr) || (ptr == rhv.ptr));
                }

        };

        public:
            class iterator : public const_iterator {

                public:

                    iterator() : const_iterator() {}
                    iterator(pointer p) : const_iterator(p) {}
                    iterator(const const_iterator& rhv) : const_iterator(rhv) {}
                    iterator(const_iterator&& rhv) noexcept : const_iterator(rhv) {}
                    ~iterator() {this->ptr = nullptr;}
                
                public:

                    reference operator[](size_t pos) {
                        
                        return this->ptr[pos];
                    
                    }
                    const_reference operator[] (size_t pos) const {
                        return this->ptr[pos];
                    }

                    reference operator*() {
                        return *(this->ptr);
                    }

                    const_reference operator*() const {
                        return *(this->ptr);
                    }

                    pointer operator->() {
                        return this->ptr;
                    }

                    const_pointer operator->() const {
                        return this->ptr;
                    }
            };

            public:

                const_iterator cbegin() const {
                    return arr;
                }

                iterator begin() {
                    return arr;
                }

                const_iterator cend() const {
                    return (arr + N);
                }
                
                iterator end() {
                    return (arr + N);
                }

                const_iterator crbegin() const {
                    return (arr + N - 1);
                }

                iterator rbegin() {
                    return (arr + N - 1);
                }

                const_iterator crend() const {
                    return (arr - 1);
                }

                iterator rend() {
                    return (arr - 1);
                }

};



#endif