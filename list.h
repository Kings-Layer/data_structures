#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <initializer_list>

template<typename T>
class list {
    public:
        using value_type = T;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using reference = value_type&;
        using const_reference = const value_type&;
        using size_type = size_t;

    private:
        struct Node {
            value_type data;
            Node* next;
            Node* prev;

            Node(const value_type& val);
            ~Node();
        };

    public:
        class const_iterator {
            friend class list;
            protected:
                explicit const_iterator(Node* ptr);
            public:
                const_iterator();
                const_iterator(const const_iterator& rhv);
                const_iterator(const_iterator&& rhv) noexcept;

            public:
                const const_iterator operator=(const const_iterator& rhv);
                const const_iterator operator=(const_iterator&& rhv);
                const_reference operator*() const;
                const Node* operator->() const;
                const_iterator& operator++();
                const_iterator& operator++(int);
                const_iterator& operator--();
                const_iterator& operator--(int);
                const_iterator& operator+(size_type offset);
                const_iterator& operator-(size_type offset);
                const_iterator& operator-(const_iterator& rhv);
                const_iterator& operator+=(size_type offset);
                const_iterator& operator-=(size_type offset);
                bool operator==(const const_iterator& rhv) const;
                bool operator!=(const const_iterator& rhv) const;
                bool operator<(const const_iterator& rhv) const;
                bool operator<=(const const_iterator& rhv) const;
                bool operator>(const const_iterator& rhv) const;
                bool operator>=(const const_iterator& rhv) const;

            private:
                Node* ptr;
        };


        class iterator : public const_iterator {
            public:
                iterator();
                iterator(Node* ptr);
                iterator(const iterator& rhv);
                iterator(iterator&& rhv);

            public:
                iterator operator=(const iterator& rhv);
                iterator operator=(iterator&& rhv);
                reference operator*();
                Node* operator->();
        };

    public:
        list();
        list(size_type count, const_reference val);
        list(size_type count);
        list(const list& rhv);
        list(list&& rhv);
        list(std::initializer_list<value_type> elems);
        ~list();

    public:
        list& operator=(const list& rhv);
        list& operator=(list&& rhv);
        list& operator=(std::initializer_list<value_type> elems);
        bool operator==(const list& rhv);
        bool operator!=(const list& rhv);
        bool operator<(const list& rhv);
        bool operator>(const list& rhv);
        bool operator<=(const list& rhv);
        bool operator>=(const list& rhv);

    public:
        void assign(size_type count, const_reference val);
        void assign(std::initializer_list<value_type> elems);
        reference front();
        reference back();
        bool empty();
        size_type size();
        void clear();
        iterator insert(const_iterator pos, const_reference val);
        iterator insert(const_iterator pos, T&& val);
        iterator insert(const_iterator pos, size_type count, const_reference val);
        iterator insert(const_iterator pos, std::initializer_list<value_type> elems);
        template<typename... Ts>
        iterator emplace(const_iterator pos, Ts&&... args);
        template<typename... Ts>
        void emplace_back(Ts&&... args);
        iterator erase(const_iterator pos);
        const_iterator erase(const_iterator first, const_iterator last);
        void push_back(const_reference val);
        void pop_back();
        void push_front(const_reference val);
        template<typename... Ts>
        void emplace_front(Ts&&... args);
        void pop_front();
        void resize(size_type count);
        void resize(size_type count, const_reference val);
        void swap(list& rhv);
        void merge(list& rhv);
        void splice(const_iterator pos, list& rhv);
        void remove(const_reference val);
        template<typename unarypredicat>
        void remove_if(unarypredicat p);
        void reverse();
        void unique();
        void sort();

        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;

    private:
        Node* head;
        Node* tail; 
        size_type listsize;
};

#endif