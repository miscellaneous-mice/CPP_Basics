#include <iostream>
#include<algorithm>
#include <sstream>
#include <memory>


template<typename T>
class Node {
public:
    std::shared_ptr<Node<T>> next;
    std::shared_ptr<Node<T>> prev;
    T value;
    Node(T value) : value(value), next(nullptr), prev(nullptr) {};
};

template <typename LinkedList>
struct LLIterator {
    using ValueType = typename LinkedList::Type;
    using PointerType = std::shared_ptr<Node<ValueType>>;
    using ReferenceType = Node<ValueType>&;
    LLIterator(PointerType ptr) : m_Node(ptr) {};

    // PreFix operator
    LLIterator operator++() const {
        m_Node = m_Node->next;
        return *this;
    }

    // PostFix operator
    LLIterator operator++(int) const {
        LLIterator iterator = *this; 
        ++(*this);
        return iterator;
    }

    LLIterator operator--() const {
        m_Node = m_Node->prev;
        return *this;
    }

    LLIterator operator--(int) const {
        LLIterator iterator = *this; 
        --(*this);
        return iterator;
    }

    PointerType operator->() const {
        return m_Node;
    }

    ReferenceType operator*() const {
        return *m_Node;
    }

    bool operator==(const LLIterator& other) const {
        return m_Node == other.m_Node; // Just checks if the nodes have the same memory addresses (0x023487832 == 0x023487832)
    }

    bool operator!=(const LLIterator& other) const {
        return !(*this == other);
    }

private:
    mutable PointerType m_Node;
};

template<typename T>
class LinkedList {
public:
    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> tail;
    using Type = T;
    using Iterator = LLIterator<LinkedList<T>>;
    using constIterator = const LLIterator<LinkedList<T>>;
    size_t length;
    
    LinkedList() : head(nullptr), tail(nullptr), length(0) {}
    LinkedList(const LinkedList& other) {
        this->length = other.length;
        std::shared_ptr<Node<T>> other_current = other.head;
        while(other_current != nullptr) {
            this->append(other_current->value);
            other_current = other_current->next;
        }
    }

    LinkedList(LinkedList&& other) {
        this->length = other.length;
        this->head = std::move(other.head);
        this->tail = std::move(other.tail);
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            this->length = 0;
            this->head = nullptr;
            this->tail = nullptr;
            this->length = other.length;
            std::shared_ptr<Node<T>> other_current = other.head;
            while(other_current != nullptr) {
                this->append(other_current->value);
                other_current = other_current->next;
            }
        }
        return *this;
    }

    LinkedList& operator=(LinkedList&& other) {
        if (this != &other) {
            this->length = other.length;
            this->head = std::move(other.head);
            this->tail = std::move(other.tail);
        }
        return *this;
    }

    LinkedList& operator<<(const LinkedList& other) {
        if (this != &other) {
            this->length += other.length;
            std::shared_ptr<Node<T>> other_current = other.head;
            while(other_current != nullptr) {
                this->append(other_current->value);
                other_current = other_current->next;
            }
        }
        return *this;
    }

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(tail->next);
    }

    constIterator being() const {
        return Iterator(head);
    }

    constIterator end() const {
        return Iterator(tail->next);
    }

    ~LinkedList() = default;
    
    T& operator[](size_t index) const {
        if (index >= length) {
            std::cerr<<"Indexing Error"<<std::endl;
            throw std::exception();
        }
        bool iter = (index < int(length / 2));
        std::shared_ptr<Node<T>> current = iter ? this->head : this->tail;
        size_t m_range = iter ? index : length - index - 1;
        for(size_t i = 0; i < m_range ; i++) {
            current = iter ? current->next : current->prev;
        }
        return current->value;
    }

    void append(const T& value) {
        std::shared_ptr<Node<T>> new_node = std::make_shared<Node<T>>(value);
        if (head == nullptr) {
            this->head = new_node;
            this->tail = new_node;
        }
        else {
            new_node->prev = this->tail;
            this->tail->next = new_node;
            this->tail = this->tail->next; 
        }
        length++;
    }

    void pop() {
        if (this->head != nullptr){
            std::shared_ptr<Node<T>> prev_tail = this->tail->prev;
            this->tail = this->tail->prev;
            this->tail->next = nullptr;
            length--;
            return;
        }
        std::cerr<<"Linked List is empty"<<std::endl;
        throw std::exception();
    }

    void clear() {
        std::shared_ptr<Node<T>> current_node = this->head, next_node = nullptr;
        while(current_node != nullptr) {
            next_node = current_node->next;
            current_node->next = nullptr;
            current_node->prev = nullptr;
            current_node = next_node;
        }
        this->head = nullptr;
        this->tail = nullptr;
        length = 0;
    }
    
    std::string Print(bool reverse=false) const {
        std::stringstream result;
        std::shared_ptr<Node<T>> current = reverse ? this->tail : this->head;
        while(current != nullptr) {
            result << current->value;
            if((reverse ? current->prev : current->next) != nullptr) {
                result << (reverse ? " <- " : " -> ");
            }
            current = reverse ? current->prev : current->next;
        }
        return result.str();
    }

    void reverse(){
        std::shared_ptr<Node<T>> current_node = this->head;
        std::shared_ptr<Node<T>> prev_node = nullptr, next_node = nullptr;
        std::shared_ptr<Node<T>> temp_tail = this->tail;
        this->tail = this->head;
        this->head = temp_tail;
        while (current_node != nullptr){
            next_node = current_node->next;
            current_node->next = prev_node;
            current_node->prev = next_node;
            prev_node = current_node;
            current_node = next_node;
        }
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& stream, const LinkedList<T>& ll) {
    stream<<ll.Print();
    return stream;
}

int main() {
    LinkedList<int> ll1;
    ll1.append(1);
    ll1.append(2);
    ll1.append(3);
    ll1.append(4);
    ll1.append(5);
    std::cout << ll1 << std::endl;
    ll1.pop();
    ll1.pop();
    std::cout << ll1 << std::endl;
    ll1.append(4);
    ll1.append(5);
    std::cout<<"Element 1 : "<<ll1[1]<<", Element 4 : "<<ll1[4]<<std::endl;

    LinkedList<int> ll2 = ll1;
    // LinkedList<int> ll2 = std::move(ll1);
    ll2.append(10);
    ll2.append(20);
    ll2.append(30);
    std::cout << ll2 << std::endl;
    ll2.pop();
    ll2.pop();
    ll2.pop();
    std::cout << ll2 << std::endl;

    LinkedList<int> ll3;
    ll3.append(99);
    ll3.append(88);
    ll3.append(77);
    std::cout << ll3 << std::endl;
    ll3 = ll1;
    std::cout << ll3 << std::endl;
    ll3 << ll2;
    std::cout << ll3 << std::endl;
    ll3.reverse();
    std::cout << ll3 << std::endl;
    ll3.clear();
    ll3.append(1);
    ll3.append(2);
    ll3.append(3);
    std::cout << ll3 << std::endl;

    LinkedList<int>::Iterator it = ll3.begin();
    it++;
    std::cout<<it->value<<std::endl;

    for (LinkedList<int>::constIterator it = ll2.begin(); it != ll2.end(); it++) {
        std::cout<<it->value<<" -> ";
    }
    std::cout<<std::endl;

    for (const auto& it : ll2) {
        std::cout<<it.value<<" -> ";
    }
    std::cout<<std::endl;

    return 0;
}