#include "list.h"

template<typename T>
list<T>::Node::Node(const value_type& val) : data{val}, next{nullptr}, prev{nullptr} {}

template<typename T>
list<T>::Node::~Node() {
    next = nullptr;
    prev = nullptr;
    data = 0;
}

template<typename T>
list<T>::const_iterator::const_iterator(Node* ptr) : ptr{ptr} {}

template<typename T>
list<T>::const_iterator::const_iterator() : ptr{nullptr} {}

template<typename T>
list<T>::const_iterator::const_iterator(const const_iterator& rhv) : ptr{rhv.ptr} {}

template<typename T>
list<T>::const_iterator::const_iterator(const_iterator&& rhv) noexcept : ptr{std::move(rhv.ptr)} {}

template<typename T>
const typename list<T>::const_iterator list<T>::const_iterator::operator=(const const_iterator& rhv) {
        ptr = rhv.ptr;
        return *this;
}

template<typename T>
const typename list<T>::const_iterator list<T>::const_iterator::operator=(const_iterator&& rhv) {
    ptr = std::move(rhv.ptr);
    rhv.ptr = nullptr;
    return *this; 
}

template<typename T>
list<T>::const_reference list<T>::const_iterator::operator*() const {
    return ptr->data;
}

template<typename T>
const list<T>::Node* list<T>::const_iterator::operator->() const {
    return ptr;
}

template<typename T>
typename list<T>::const_iterator& list<T>::const_iterator::operator++() {
    if (ptr != nullptr) {
        ptr = ptr->next;
    }
    return *this;
}

template<typename T>
typename list<T>::const_iterator& list<T>::const_iterator::operator++(int) {
    const_iterator tmp = *this;
    if (ptr != nullptr) {
        ++(*this);
    }
    return tmp;
}

template<typename T>
typename list<T>::const_iterator& list<T>::const_iterator::operator--() {
    if (ptr != nullptr) {
        ptr = ptr->next;
    }
    return *this;
}

template<typename T>
typename list<T>::const_iterator& list<T>::const_iterator::operator--(int) {
    const_iterator tmp = *this;
    if (ptr != nullptr) {
        --(*this);
    }
    return tmp;
}

template<typename T>
typename list<T>::const_iterator& list<T>::const_iterator::operator+(size_t offset) {
    while (offset && ptr != nullptr) {
        ptr = ptr->next;
        --offset;
    }
    return *this;
}

template<typename T>
typename list<T>::const_iterator& list<T>::const_iterator::operator-(size_t offset) {
    while (offset && ptr != nullptr) {
        ptr = ptr->prev;
        --offset;
    }
    return *this;
}

template<typename T>
typename list<T>::const_iterator& list<T>::const_iterator::operator-(const_iterator& rhv) {
    return ptr - rhv.ptr;
}

template<typename T>
typename list<T>::const_iterator& list<T>::const_iterator::operator+=(size_t offset) {
    return *this + offset;
}

template<typename T>
typename list<T>::const_iterator& list<T>::const_iterator::operator-=(size_t offset) {
    return *this - offset;
}

template<typename T>
bool list<T>::const_iterator::operator==(const const_iterator& rhv) const {
    return ptr == rhv.ptr;
}

template<typename T>
bool list<T>::const_iterator::operator!=(const const_iterator& rhv) const {
    return !(*this == rhv);
}

template<typename T>
bool list<T>::const_iterator::operator<(const const_iterator& rhv) const {
    return ptr < rhv.ptr;
}

template<typename T>
bool list<T>::const_iterator::operator<=(const const_iterator& rhv) const {
    return (*this < rhv) || (*this == rhv);
}

template<typename T>
bool list<T>::const_iterator::operator>(const const_iterator& rhv) const {
    return ptr > rhv.ptr;
}

template<typename T>
bool list<T>::const_iterator::operator>=(const const_iterator& rhv) const {
    return (*this > rhv) || (*this == rhv);
}

template<typename T>
list<T>::iterator::iterator() : const_iterator() {}

template<typename T>
list<T>::iterator::iterator(Node* ptr) : const_iterator(ptr) {}

template<typename T>
list<T>::iterator::iterator(const iterator& rhv) : const_iterator(rhv) {}

template<typename T>
list<T>::iterator::iterator(iterator&& rhv) : const_iterator(std::move(rhv)) {}

template<typename T>
typename list<T>::iterator list<T>::iterator::operator=(const iterator& rhv) {
    this->ptr = rhv.ptr;
    return *this;
}

template<typename T>
typename list<T>::iterator list<T>::iterator::operator=(iterator&& rhv) {
    this->ptr = rhv.ptr;
    rhv.ptr == nullptr;
    return *this;
}
template<typename T>
T& list<T>::iterator::operator*() {
    return this->ptr->data;
}

template<typename T>
list<T>::Node* list<T>::iterator::operator->() {
    return this->ptr;
}

template<typename T>
list<T>::list() : head{nullptr}, tail{nullptr}, listsize{0} {}

template<typename T>
list<T>::list(size_type count, const_reference val) {
    Node* node = new Node(val);
    head = tail = node;
    listsize = count;
    for (int i = 1; i < count; ++i) {
        node = new Node(val);
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
}

template<typename T>
list<T>::list(size_type count) : list(count, 0) {}

template<typename T>
list<T>::list(const list& rhv) {
    Node* cur = rhv.head;
    listsize = rhv.listsize;
    while (cur != nullptr) {
        push_back(cur->data);
        cur = cur->next;
    }
}

template<typename T>
list<T>::list(list&& rhv) : listsize{rhv.listsize}, head{rhv.head}, tail{rhv.tail} {
    rhv.head = nullptr;
    rhv.tail = nullptr;
    rhv.listsize = 0;
}

template<typename T>
list<T>::list(std::initializer_list<value_type> elems) {
    listsize = elems.size();
    for (const auto& elem : elems) {
        push_back(elem);
    }
}

template<typename T>
list<T>::~list() {
    clear();
}

template<typename T>
list<T>& list<T>::operator=(const list& rhv) {
    if (this != &rhv) {
        clear();
        Node* cur = rhv.head;
        while(cur) {
            push_back(cur->data);
            cur = cur->next;
        }
        listsize = rhv.listsize;
    }
    return *this;
}

template<typename T>
list<T>& list<T>::operator=(list&& rhv) {
    if (this != &rhv) {
        clear();
        listsize = rhv.listsize;
        head = rhv.head;
        tail = rhv.tail;
        rhv.head = nullptr;
        rhv.tail = nullptr;
        rhv.listsize = 0;
    }
    return *this;
}

template<typename T>
list<T>& list<T>::operator=(std::initializer_list<value_type> elems) {
    clear();
    listsize = elems.size();
    for (const auto& elem : elems) {
        push_back(elem);
    }
    return *this;
} 

template<typename T>
bool list<T>::operator==(const list& rhv) {
    Node* cur1 = head;
    Node* cur2 = rhv.head;
    while (cur1 && cur2) {
        if (cur1->data != cur2->data) {
            return false;
        }
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    if (cur2) {
        return false;
    }
    if (cur1) {
        return false;
    }
    return true;
}

template<typename T>
bool list<T>::operator!=(const list& rhv) {
    return !(*this == rhv);
}

template<typename T>
bool list<T>::operator<(const list& rhv) {
    Node* cur1 = head;
    Node* cur2 = rhv.head;
    while (cur1 && cur2) {
        if (cur1->data >= cur2->data) {
            return false;
        }
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    if (cur2) {
        return false;
    }
    return true;
}

template<typename T>
bool list<T>::operator<=(const list& rhv) {
    return (*this < rhv || *this == rhv);
}

template<typename T>
bool list<T>::operator>(const list& rhv) {
    return !(*this <= rhv);
}

template<typename T>
bool list<T>::operator>=(const list& rhv) {
    return !(*this < rhv);
}

template<typename T>
void list<T>::assign(size_type count, const_reference val) {
    if (head == nullptr) {
        return;
    }
    listsize = count;
    Node* cur = head;
    while (count && cur) {
        cur->data = val;
        cur = cur->next;
        --count;
    }
    listsize -= count;
}

template<typename T>
void list<T>::assign(std::initializer_list<value_type> elems) {
    if (head == nullptr) {
        return;
    }
    Node* cur = head;
    for (const auto& elem : elems) {
        if (cur == nullptr) {
            return;
        }
        cur->data = elem;
        cur = cur->next;
        ++listsize;
    }
}

template<typename T>
list<T>::reference list<T>::front() {
    return head->data;
}

template<typename T>
list<T>::reference list<T>::back() {
    return tail->data;
}
template<typename T>
bool list<T>::empty() {
    return head == nullptr;
}

template<typename T>
list<T>::size_type list<T>::size() {
    return listsize;
}

template<typename T>
void list<T>::clear() {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }

    listsize = 0;
}

template<typename T>
typename list<T>::iterator list<T>::insert(const_iterator pos, const_reference val) {
    Node* tmp = new Node(val);
    if (pos == end()) {
        push_back(val);
    } else if (pos == begin()) {
        push_front(val);
    } else {
        Node* prevnode = head;
        while (const_iterator(prevnode->next) != pos) {
            prevnode = prevnode->next;
        }
        tmp->next = prevnode->next;
        tmp->prev = prevnode;
        prevnode->next->prev = tmp;
        prevnode->next = tmp;
        ++listsize;
    }
    return iterator(tmp->next);
}

template<typename T>
typename list<T>::iterator list<T>::insert(const_iterator pos, T&& val) {
    Node* tmp = new Node(val);
    if (pos == end()) {
        push_back(val);
    } else if (pos == begin()) {
        push_front(val);
    } else {
        Node* prevnode = head;
        while (const_iterator(prevnode->next) != pos) {
            prevnode = prevnode->next;
        }
        tmp->next = prevnode->next;
        tmp->prev = prevnode;
        prevnode->next->prev = tmp;
        prevnode->next = tmp;
        ++listsize;
    }
    return iterator(tmp->next);
}

template<typename T>
typename list<T>::iterator list<T>::insert(const_iterator pos, size_type count, const_reference val) {
    while (count) {
        pos = insert(pos, val);
        --count;
    }
    ++listsize;
    return pos;
}

template<typename T>
typename list<T>::iterator list<T>::insert(const_iterator pos, std::initializer_list<value_type> elems) {
    for (const auto& elem : elems) {
        pos = insert(pos, elem);
    }
    ++listsize;
    return pos;
}

template<typename T>
template<typename... Ts>
typename list<T>::iterator list<T>::emplace(const_iterator pos, Ts&&... args) {
    return insert(pos, value_type(std::forward<Ts>(args)...));
}

template<typename T>
template<typename... Ts>
void list<T>::emplace_back(Ts&&... args) {
    push_back(value_type(std::forward<Ts>(args)...));
}

template<typename T>
typename list<T>::iterator list<T>::erase(const_iterator pos) {
    Node* prevnode = head;
    if (head == nullptr) {
        return nullptr;
    } else if (pos == begin()) {
        pop_front();
    } else if (pos == iterator(tail)) {
        pop_back();
    } else {
        while (iterator(prevnode->next) != pos) {
            prevnode = prevnode->next;
        }
        if (!prevnode->next->next) {
            delete prevnode->next;
        } else {
            Node* tmp = prevnode->next;
            prevnode->next->next->prev = prevnode;
            prevnode->next = prevnode->next->next;
            delete tmp;
        }
        --listsize;
    }
    return iterator(prevnode->next);
}
template<typename T>
typename list<T>::const_iterator list<T>::erase(const_iterator first, const_iterator last) {
    if (first < begin() || last > iterator(tail)) {
        return const_iterator(nullptr);
    }
    while (first != last) {
        first = erase(first);
    }
    return first;
}

template<typename T>
void list<T>::push_back(const_reference val) {
    if (head == nullptr) {
        head = new Node(val);
        tail = head;
    } else {
        Node* tmp = new Node(val);
        tail->next = tmp;
        tmp->prev = tail;
        tail = tmp;
    }
    ++listsize;
}

template<typename T>
void list<T>::pop_back() {
    if (head == nullptr) {
        return;
    }
    Node* tmp = tail;
    if (head == tail) {
        head = nullptr;
        tail == nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    --listsize;
    delete tmp;
}

template<typename T>
void list<T>::push_front(const_reference val) {
    Node* tmp = new Node(val);
    if (head == nullptr) {
        head = tmp;
        tail = tmp;
    } else {
        tmp->next = head;
        head->prev = tmp;
        head = tmp;
        ++listsize;
    } 
}

template<typename T>
template<typename... Ts>
void list<T>::emplace_front(Ts&&... args){
    push_front(value_type(std::forward<Ts>(args)...));
    ++listsize;
}

template<typename T>
void list<T>::pop_front() {
    if (head == nullptr) {
        return;
    }
    Node* tmp = head;
    if (head == tail) {
        head = nullptr;
        tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }
    --listsize;
    delete tmp;
}

template<typename T>
void list<T>::resize(size_type count) {
    if (count < listsize) { 
        erase(begin() + count, end());
    }    
}

template<typename T>
void list<T>::resize(size_type count, const_reference val) {
    if (count > listsize) { 
        count = count - listsize;
        listsize += count;
        while (count) {
            push_back(val);
            --count;
        }
    } 
}

template<typename T>
void list<T>::swap(list& rhv) {
    Node* tmp1 = head;
    Node* tmp2 = tail;
    head = rhv.head;
    tail = rhv.tail;
    rhv.head = tmp1;
    rhv.tail = tmp2;
}

template<typename T>
void list<T>::merge(list& rhv) {
    if (head == nullptr) {
        return;
    }
    if (this == &rhv) {
        return;
    }
    tail->next = rhv.head;
    tail = rhv.tail; 
    rhv.head = nullptr;
    rhv.tail = nullptr;
}

template<typename T>
void list<T>::splice(const_iterator pos, list& rhv) {
    Node* cur = rhv.head;
    while (cur) {
        pos = insert(pos - 1, cur->data);
        cur = cur->next;
    }
}

template<typename T>
void list<T>::remove(const_reference val) {
    Node* cur = head;
    while (cur) {
        if (cur->data == val) {
            erase(iterator(cur));
            --listsize;
        }
        cur = cur->next;
    }
}

template<typename T>
template<typename unarypredicat>
void list<T>::remove_if(unarypredicat p) {
    Node* cur = head;
    while(cur) {
        if (p(cur->data)) {
            erase(iterator(cur));
            --listsize;
        }
        cur = cur->next;
    }
}

template<typename T>
void list<T>::reverse() {
    Node* tmp1 = head;
    Node* tmp2 = tail;
    while (tmp1 != tmp2 && tmp1->prev != tmp2) {
        value_type val = tmp1->data;
        tmp1->data = tmp2->data;
        tmp2->data = val;
        tmp1 = tmp1->next;
        tmp2 = tmp2->prev;
    }
}

template<typename T>
void list<T>::unique() {
    if (head == nullptr) {
        return;
    }
    Node* cur = head;
    while (cur && cur->next) {
        Node* runner = cur->next;
        while (runner != nullptr) {
            if (cur->data == runner->data) {
                Node* tmp = runner;
                runner->prev->next = runner->next;
                if (runner->next != nullptr){
                    runner->next->prev = runner->prev;
                } else {
                    tail = runner->prev;
                }
                runner = runner->next;
                delete tmp; 
           } else {
                runner = runner->next;
           }
        }
        cur = cur->next;
    }
}


template<typename T>
void list<T>::sort() {
    if (head == nullptr || head->next == nullptr) {
        return;
    }
    Node* cur = nullptr;
    Node* ptr = nullptr;
    bool swapped;
    do {
        cur = head;
        swapped = false;
        while (cur->next != ptr) {
            if (cur->data > cur->next->data) {
                value_type val = cur->data;
                cur->data = cur->next->data;
                cur->next->data = val;
                swapped = true;
            }
            cur = cur->next;
        }
        ptr = cur;
    } while (!swapped);
}

template<typename T>
typename list<T>::iterator list<T>::begin() {
    return iterator(head);
}

template<typename T>
typename list<T>::const_iterator list<T>::begin() const {
    return const_iterator(head);
}

template<typename T>
typename list<T>::const_iterator list<T>::end() const {
    return const_iterator();
}

template<typename T>
typename list<T>::iterator list<T>::end() {
    return iterator();
}

#include <iostream>
#include <string>

// Assuming the class list is already defined, as per your previous code...

int main() {
    // 1. Default constructor and basic list operations
    list<int> myList;

    std::cout << "List created. Empty: " << myList.empty() << std::endl;;

    // 2. Push elements at the back and front
    myList.push_back(10);
    myList.push_back(20);
    myList.push_front(5);

    std::cout << "List after push_back and push_front: ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 3. Front and back
    std::cout << "Front element: " << myList.front() << std::endl;
    std::cout << "Back element: " << myList.back() << std::endl;

    // 4. Test pop_back and pop_front
    myList.pop_back();
    myList.pop_front();
    std::cout << "List after pop_back and pop_front: ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 5. Test insert and erase
    myList.push_back(30);
    myList.push_back(40);
    myList.push_back(50);
    auto it = myList.begin();
    ++it; // Move to the second position
    myList.insert(it, 25);  // Insert before 30

    std::cout << "List after insert: ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    it = myList.begin();
    ++it; // Move to the second position
    myList.erase(it);  // Erase 25

    std::cout << "List after erase: ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 7. Test reverse
    myList.reverse();
    std::cout << "List after reverse: ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 6. Resize the list
    myList.resize(5, 100);
    std::cout << "List after resize (to 5 elements with 100): ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

   

    // 8. Test unique (should remove consecutive duplicates)
    myList.push_back(100);
    myList.push_back(100);
    myList.push_back(200);
    std::cout << "List before unique: ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    myList.unique();
    std::cout << "List after unique: ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 9. Test emplace (inserting element in place)
    myList.emplace(myList.begin(), 500);
    std::cout << "List after emplace (500 at beginning): ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 10. Test assign
    myList.assign(3, 42);
    std::cout << "List after assign (3 elements with value 42): ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 11. Test initializer list constructor
    list<int> newList = {1, 2, 3, 4, 5};
    std::cout << "New list created with initializer list: ";
    for (auto it = newList.begin(); it != newList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 12. Test comparison operators
    list<int> anotherList = {1, 2, 3, 4, 5};
    if (newList == anotherList) {
        std::cout << "Lists are equal" << std::endl;
    } else {
        std::cout << "Lists are not equal" << std::endl;
    }

    // 13. Test emplace_back
    anotherList.emplace_back(10);
    std::cout << "List after emplace_back (10 added to the end): ";
    for (auto it = anotherList.begin(); it != anotherList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 14. Test clear
    newList.clear();
    std::cout << "New list after clear: ";
    std::cout << "Size: " << newList.size() << " Is empty: " << newList.empty() << std::endl;

    return 0;
}
