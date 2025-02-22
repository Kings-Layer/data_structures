#ifndef DINAMIC_ARRAY
#define DINAMIC_ARRAY



#include <iostream>
#include <string>
#include <initializer_list>

template<typename T>
class dinamic_array {
    public:
        using value_type = T;
        using size_type = std::size_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;

    public:
        class const_iterator {
            friend class dinamic_array;
            protected:
                explicit const_iterator(pointer ptr);
            
            public:
                const_iterator();
                const_iterator(const const_iterator& rhv);
                const_iterator(const_iterator&& rhv) noexcept;

            public:
                const const_iterator operator=(const const_iterator& rhv);
                const const_iterator operator=(const_iterator&& rhv);
                const_reference operator*() const;
                const_pointer operator->() const;
                const_iterator& operator++();
                const_iterator& operator++(int);
                const_iterator& operator--();
                const_iterator& operator--(int);
                const_iterator& operator+(size_type offset);
                const_iterator& operator-(size_type offset);
                const_iterator& operator+=(size_type offset);
                const_iterator& operator-=(size_type offset);
                const_reference operator[](size_type pos) const;
                bool operator==(const const_iterator& rhv) const;
                bool operator!=(const const_iterator& rhv) const;
                bool operator<(const const_iterator& rhv) const;
                bool operator<=(const const_iterator& rhv) const;
                bool operator>(const const_iterator& rhv) const;
                bool operator>=(const const_iterator& rhv) const;

            private:
                pointer ptr;
        };

    public:
        class iterator : public const_iterator {
            public:
                iterator();
                iterator(pointer ptr);
                iterator(const iterator& rhv);
                iterator(iterator&& rhv);

            public:
                reference operator*();
                pointer operator->();
                reference operator[](size_type pos);
        };


    public:
        dinamic_array();
        dinamic_array(size_type n);
        dinamic_array(size_type n, const_reference value);
        dinamic_array(const dinamic_array& rhv);
        dinamic_array(dinamic_array&& rhv) noexcept;
        dinamic_array(std::initializer_list<value_type> list);
        ~dinamic_array();

    public:
        dinamic_array& operator=(const dinamic_array& rhv);
        dinamic_array& operator=(dinamic_array&& rhv) noexcept;
        const_reference operator[](size_type pos) const;
        reference operator[](size_type pos);
        bool operator==(const dinamic_array& rhv) const;
        bool operator!=(const dinamic_array& rhv) const;
        bool operator<(const dinamic_array& rhv) const;
        bool operator<=(const dinamic_array& rhv) const;
        bool operator>(const dinamic_array& rhv) const;
        bool operator>=(const dinamic_array& rhv) const;

    public:
        void reserve(size_type cap);
        size_type get_capacity();
        bool include(const_reference target);
        template<typename... Ts>
        iterator emplace(const_iterator pos, Ts&&... args);
        template<typename... Ts>
        reference emplace_back(Ts&&... args);
        iterator insert(const_iterator pos, const_reference val);
        iterator insert(const_iterator pos, size_type count, const_reference val);
        iterator insert(const_iterator pos, std::initializer_list<value_type> list);
        size_type insert(size_type pos, const_reference val);
        void push_back(const_reference val);
        void pop_back();
        void remove(size_type pos);
        void remove(const_iterator pos);
        void clear();
        size_type get_size();
        bool is_empty();
        void shrink_to_fit();
        void assign(size_type count, const_reference val);
        reference at(size_type pos);
        iterator erase(const_iterator pos);
        iterator erase(const_iterator first, const_iterator last);
        reference front();
        reference back();
        pointer data();
        void swap(dinamic_array& rhv);
        void resize(size_type count);
        void resize(size_type count, const_reference val);
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;


    private:
        size_type capacity;
        size_type size;
        pointer arr;

};
template<typename T>
std::ostream& operator<<(std::ostream& out, dinamic_array<T> arr);


#endif

