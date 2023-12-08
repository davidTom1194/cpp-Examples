/// @file LList.hpp
/// @author David Tom <8000190528@student.csn.edu>
/// @version 2023-fall-cs202-pa17a
/// @note I pledge my word of honor that I have abided by the
/// the CSN Academic Integrity Policy while completing this assignment.
///
/// @brief This header file contains the class "LList". LList is a linked list
/// class emulating `std::list` containing a `bidirectional` struct and also the
/// `node`. File follows the standards for CSN's CS202 assignment criteria.
///
/// @note People who helped me: N/A
///
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.

// Definitions
#ifndef LLIST_HPP
#define LLIST_HPP

// Preprocessor Directive(s)
#include <initializer_list>
#include <iterator>

/* ========================================================================== */
/* ========== Class/Struct Definition(s) ========= */
/* ========================================================================== */
/// This starter code defines a template structure Node in C++. It's designed to
/// be a part of a doubly linked list, where each node contains data of a
/// generic type T, and pointers to the previous and next nodes in the list.
///
/// These instance variables work together to define the structure of each node
/// in a doubly linked list, allowing for efficient and flexible data
/// management. The data variable holds the content, while prev and next
/// pointers maintain the structural integrity of the list, enabling
/// bidirectional navigation.

template <class T>
struct Node {
    using value_type = T;

    // Constructor
    /// Step 1
    /// Constructor: Node
    /// Initializes the node with data and links to previous and next nodes.
    /// Foundation for creating nodes in the LList.
    explicit Node(const value_type& value, Node* prev_node = nullptr,
         Node* next_node = nullptr)
         : data(value), prev(prev_node), next(next_node) {};

    value_type  data;         ///< Data of the node, of type T
    Node*       prev;         ///< Pointer to the previous node
    Node*       next;         ///< Pointer to the next node
};  // End: struct Node


/// List is a container that supports constant time insertion and removal of
/// elements from anywhere in the container. Fast random access is not
/// supported. It is implemented as a doubly-linked list. This container
/// provides bidirectional iteration capability.
///
/// Adding, removing and moving the elements within the list or across several
/// lists does not invalidate the iterators or references. An iterator is
/// invalidated only when the corresponding element is deleted.

template <class T>
class LList {
public:
    /// The BiDirectionalIterator struct is designed to iterate over a
    /// collection of Node<T> elements in both forward and backward directions.
    ///
    /// These member functions collectively enable the BiDirectionalIterator to
    /// seamlessly navigate through a doubly linked list, providing a standard
    /// interface for iteration that's consistent with C++ iterator conventions.
    /// The struct adheres to the requirements of a bidirectional iterator,
    /// including the ability to iterate forwards and backwards, dereference the
    /// iterator to access node data, and compare iterators for equality or
    /// inequality.
    struct BiDirectionalIterator {
        // Iterator traits
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        // Constructor
        /// Step 2
        /// Constructor: BiDirectionalIterator
        /// Initializes the iterator.
        /// Sets current to the provided Node<T>* pointer, or nullptr (default).
        explicit BiDirectionalIterator(Node<T>* ptr = nullptr)
        : current(ptr) {};

        // Dereference operators
        reference operator*() const;
        pointer operator->() const;

        // Increment/decrement operators
        BiDirectionalIterator& operator++();
        BiDirectionalIterator operator++(int ignored);
        BiDirectionalIterator& operator--();
        BiDirectionalIterator operator--(int ignored);

        // Equality/Inequality comparison operators
        /// Step 6
        /// Checks if two iterators are/not pointing to the same node.
        bool operator==(const BiDirectionalIterator& other) const
        { return this->current == other.current; }
        bool operator!=(const BiDirectionalIterator& other) const
        { return this->current != other.current; }

        Node<T>* current;  ///< pointer to Node encapsulated by struct
    };  // End: struct BiDirectionalIterator

    // types
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using iterator = BiDirectionalIterator;
    using const_iterator = const iterator;

    // construct/copy/destroy
    /// Step 7
    /// Constructor: LList
    /// Initializes an empty list.
    /// Sets head and tail pointers to nullptr and count to 0.
    LList() : head(nullptr), tail(nullptr), count(0) {};
    LList(const LList& other);
    LList(LList&& other);
    LList(std::initializer_list<T> ilist);
    virtual ~LList();

    // assignment
    LList& operator=(const LList& other);
    LList& operator=(LList&& other);
    LList& operator=(std::initializer_list<T> ilist);

    // iterators
    /// Step 9
    /// Returns an iterator poiting to the first/last element (head/tail)
    iterator       begin() noexcept { return iterator(head); }
    const_iterator begin() const noexcept { return const_iterator(head); }
    iterator       end() noexcept { return iterator(nullptr); }
    const_iterator end() const noexcept { return const_iterator(nullptr); }

    // capacity
    /// Steps 10 & 11
    /// 10: Returns true if the list is empty (ie., head is nullptr),
    /// otherwise false.
    /// 11: Returns the number of elements in the list (value of count).
    bool empty() const noexcept { return head == nullptr ? true : false; }
    size_type size() const noexcept { return count; }

    // element access
    reference       front();
    const_reference front() const;
    reference       back();
    const_reference back() const;

    // modifiers
    void     push_front(const T& value);
    void     pop_front();
    void     push_back(const T& value);
    void     pop_back();
    iterator insert(const_iterator position, const T& value);
    iterator erase(const_iterator position);
    void     swap(LList& other);
    void     clear() noexcept;

private:
    Node<T>* head;
    Node<T>* tail;
    size_type count;
};  // End: class LList


/* ========================================================================== */
/* ========== Function Implementations ========== */
/* ========================================================================== */

/* ========== Constructor/Copy/Destructor: All ========== */
/// Step 15
/// Copy: LList
/// Initializes a new list by deep copying the nodes from other.
/// Iterates through other, creating new nodes and linking them accordingly.
template <class T>
LList<T>::LList(const LList& other)
    : head(nullptr), tail(nullptr), count(0) {
    // Set current to other's head
    Node<T>* current = other.head;

    // Iterate through other and push_back
    while (current != nullptr) {
        this->push_back(current->data);
        current = current->next;
    }
}

/// Step 16
/// Move: LList
/// Takes ownership of other's data, setting head, tail, and count to other's
/// values.
/// Sets other's head and tail to nullptr, and count to 0.
template <class T>
LList<T>::LList(LList&& other)
    : head(other.head), tail(other.tail), count(other.count) {
    // Set other's values to nullptr or 0
    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;
}

/// Step 23
/// Constructor: LList std::initializer_list<T>
/// Initializes the list with elements from the initializer list.
/// Iterates through ilist and inserts each element at the end of the list.
template <class T>
LList<T>::LList(std::initializer_list<T> ilist)
    : head(nullptr), tail(nullptr), count(0) {
    // Insert each item at the end of the list
    for (const T& item : ilist) {
        this->push_back(item);
    }
}

/// Step 8
/// Destructor: LList
/// Destroys the list and frees up resources.
/// Iterates through the list, deleting each node.
template <class T>
LList<T>::~LList() {
    // Set current to start
    Node<T>* current = head;

    // iterate through list, deleting each node
    while (current != nullptr) {
        Node<T>* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    // Set all values to nullptr or 0
    head = nullptr;
    tail = nullptr;
    count = 0;
}

/* ======== Dereference Operators (Overloads): BiDirectionalIterator ======== */
/// Step 3a
/// Reference Operator*(): BiDirectionalIterator
/// Returns a reference to the data stored in the current node.
template <class T>
typename LList<T>::BiDirectionalIterator::reference
                   LList<T>::BiDirectionalIterator::operator*() const {
    // Verify current is not a nullptr
    if (current == nullptr) {
        throw std::runtime_error("Dereferencing a null iterator");
    }

    return current->data;
}

/// Step 3b
/// Pointer Operator->(): BiDirectional Iterator
/// This provides access to the member functions or variables of the data stored
/// in the current node. It returns a pointer to the data member stored in
/// the node.
template <class T>
typename LList<T>::BiDirectionalIterator::pointer
                   LList<T>::BiDirectionalIterator::operator->() const {
    // Verify current is not a nullptr
    if (current == nullptr) {
        throw std::runtime_error("Dereferencing a null iterator");
    }

    return &(current->data);
}

/* ========== Increment/Decrement Operators: BiDirectionalIterator ========== */

/// Step 4a
/// Operator++(): BiDirectionalIterator&
/// Prefix increment. Advances the iterator to the next node and returns a
/// reference to the updated iterator.
template <class T>
typename LList<T>::BiDirectionalIterator&
                   LList<T>::BiDirectionalIterator::operator++() {

    // Verify current is not a nullptr and link to next
    if (current != nullptr) {
        current  = current->next;
    } else {
        throw std::runtime_error("Error: Attempt to increment null iterator.");
    }

    return *this;
}

/// Step 4b
/// Operator++(int ignored): BiDirectionalIterator
/// Postfix increment. Advances the iterator to the next node but returns the
/// iterator as it was before the increment.
template <class T>
typename LList<T>::BiDirectionalIterator
                   LList<T>::BiDirectionalIterator::operator++(int) {
    // Create a copy of the current iterator
    BiDirectionalIterator copy = *this;

    operator++();       // Advance the current iterator
    return copy;        // Return the copy
}

/// Step 5a
/// Operator--(): BiDirectionalIterator&
/// Prefix decrement. Moves the iterator to the previous node and returns a
/// reference to the updated iterator.
template <class T>
typename LList<T>::BiDirectionalIterator&
                   LList<T>::BiDirectionalIterator::operator--() {

    // Verify current is not a nullptr and link to next
    if (current != nullptr) {
        current  = current->prev;
    } else {
        throw std::runtime_error("Error: Attempt to increment null iterator.");
    }

    return *this;
}

/// Step 5b
/// Operator--(int ignored): BiDirectionalIterator
/// Postfix decrement. Moves the iterator to the previous node but returns the
/// iterator as it was before the decrement.
template <class T>
typename LList<T>::BiDirectionalIterator
                   LList<T>::BiDirectionalIterator::operator--(int) {
    // Create a copy of the current iterator
    BiDirectionalIterator copy = *this;

    operator--();       // Decrease the current iterator
    return copy;        // Return the copy
}

/* ========== Assignment: LList ========== */
/// Step 17
/// Operator=(const LList& other): LList
/// Copy assignment operator.
/// Clears the current list, then deep copies other into the list.
template <class T>
LList<T>& LList<T>::operator=(const LList& other) {
    // Check for self-assignment
    if (this != &other) {
        // Clear the current list
        this->clear();

        // Set current to other head
        Node<T>* current = other.head;

        // Iterate and copy all values
        while (current != nullptr) {
            this->push_back(current->data);
            current = current->next;
        }
    }

    return *this;
}

/// Step 18
/// Operator=(LList&& other): LList
/// Move assignment operator.
/// Swaps the contents of the list with other.
template <class T>
LList<T>& LList<T>::operator=(LList&& other) {
    // Check for self-assignment
    if (this != &other) {
        // Clear the current list
        this->clear();

        // Set values to other's
        this->head = other.head;
        this->tail = other.tail;
        this->count = other.count;

        // Set values to nullptr or 0
        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;
    }

    return *this;
}

/// Step 24
/// Operator=(std::initializer_list<T> ilist): LList
/// Assigns the elements of the initializer list to the list.
/// Clears the current list, then inserts each element from ilist.
template <class T>
LList<T>& LList<T>::operator=(std::initializer_list<T> ilist) {
    // Clear the current list
    this->clear();

    // Iterate and insert elements from initializer list
    for (const T& item : ilist) {
        this->push_back(item);
    }

    return *this;
}


/* ========== Element Access: LList ========== */
/// Step 13a
/// Reference front(): LList
/// Returns a reference to the first element in the list.
template <class T>
typename LList<T>::reference LList<T>::front() {
    // Verify if list is empty
    if (head == nullptr) {
        throw std::out_of_range("Accessing front on an empty list");
    }

    return head->data;
}

/// Step 13b
/// Const_reference front() const: LList
/// Returns a reference to the first element in the list.
template <class T>
typename LList<T>::const_reference LList<T>::front() const {
    // Verify if list is empty
    if (head == nullptr) {
        throw std::out_of_range("Accessing front on an empty list");
    }

    return head->data;
}

/// Step 13c
/// Reference back(): LList
/// Returns a reference to the last element in the list.
template <class T>
typename LList<T>::reference LList<T>::back() {
    // Verify if list is empty
    if (tail == nullptr) {
        throw std::out_of_range("Accessing back on an empty list");
    }

    return tail->data;
}

/// Step 13d
/// Const_reference back() const: LList
/// Returns a reference to the last element in the list.
template <class T>
typename LList<T>::const_reference LList<T>::back() const {
    // Verify if list is empty
    if (tail == nullptr) {
        throw std::out_of_range("Accessing back on an empty list");
    }

    return tail->data;
}

/* ========== Modifiers: LList ========== */
/// Step 12a
/// Void push_front(const T& value): LList
/// Inserts a new element at the front of the list.
/// Updates head and, if necessary, tail.
template <class T>
void LList<T>::push_front(const T& value) {
    // Create a new node
    Node<T>* newNode = new Node<T>(value);

    // Verify if list is empty
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    // Increment count
    ++count;
}

/// Step 14a
/// Void pop_front(): LList
/// Removes the first element of the list.
/// Updates head and, if necessary, tail.
template <class T>
void LList<T>::pop_front() {
    // Check if the list is empty
    if (head != nullptr) {
        // Remove the first element
        Node<T>* oldHead = head;
        head = head->next;

        // Verify if list has become empty
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }

        // Remove old head
        delete oldHead;

        // Decrement count
        --count;
    }

}

/// Step 12b
/// Void push_back(const T& value): LList
/// Adds a new element to the end of the list.
/// Updates tail and, if necessary, head.
template <class T>
void LList<T>::push_back(const T& value) {
    // Create a new node
    Node<T>* newNode = new Node<T>(value);

    // Verify if list is empty
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    // Increment count
    ++count;
}

/// Step 14b
/// Void pop_back(): LList
/// Removes the last element of the list.
/// Updates tail and, if necessary, head.
template <class T>
void LList<T>::pop_back() {
    // Check if list is empty
    if (head != nullptr) {
        // Remove the last element
        Node<T>* oldTail = tail;
        tail = tail->prev;

        // Verify if list is empty
        if (tail == nullptr) {
            head = nullptr;
        } else {
            tail->next = nullptr;
        }

        // Decrement count
        --count;

        // Remove old tail
        delete oldTail;
    }
}

/// Step 19
/// Iterator insert(const_iterator position, const T& value): LList
/// Inserts a new element before the element at the specified position.
/// Returns an iterator pointing to the newly inserted element.
template <class T>
typename LList<T>::iterator LList<T>::insert(typename LList<T>::const_iterator
                                             position, const T& value) {
    // Create a new node with the given value
    Node<T>* newNode = new Node<T>(value);

    // Verify if list is empty and position is valid
    if (head == nullptr) {
        // List is empty
        head = tail = newNode;
    } else if (position.current == nullptr) {
        // Position is past the end, insert at the end
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    } else if (position.current == head) {
        // Insert at the beginning
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    } else {
        // Insert in between
        Node<T>* prevNode = position.current->prev;
        prevNode->next = newNode;
        newNode->prev = prevNode;
        newNode->next = position.current;
        position.current->prev = newNode;
    }

    // Increment count
    ++count;

    return iterator(newNode);
}

/// Step 20
/// Iterator erase(const_iterator position): LList
/// Removes the element at position.
/// Returns the iterator following the last removed element.
template <class T>
typename LList<T>::iterator LList<T>::erase(typename
                                            LList<T>::const_iterator position) {
    // Verify if list is empty and position is valid
    if (head == nullptr || position.current == nullptr) {
        throw std::invalid_argument("Out of Range!");
    }

    // Set nodes for deletion
    Node<T>* nodeToDelete = position.current;
    Node<T>* nextNode = nodeToDelete->next;

    // Delete appropriate node
    if (nodeToDelete == head) {
        // Delete first element
        head = head->next;
        if (head) {
            head->prev = nullptr;
        }
    } else if (nodeToDelete == tail) {
        // Delete last element
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        }
    } else {
        // Delete in between
        Node<T>* prevNode = nodeToDelete->prev;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }

    // Free the memory of the node to be erased
    delete nodeToDelete;

    // Decrement count
    --count;

    return iterator(nextNode);
}

/// step 22
/// Void swap(LList& other): LList
/// Swaps the contents of the list with other.
template <class T>
void LList<T>::swap(LList& other) {
    // Swap the head pointers
    Node<T>* tempHead = this->head;
    this->head = other.head;
    other.head = tempHead;

    // Swap the tail pointers
    Node<T>* tempTail = this->tail;
    this->tail = other.tail;
    other.tail = tempTail;

    // Swap the counts
    size_t tempCount = this->count;
    this->count = other.count;
    other.count = tempCount;
}

/// Step 21
/// Void clear() noexcept: LList
/// Clears the list of all elements.
/// Sets head and tail to nullptr and count to 0.
template <class T>
void LList<T>::clear() noexcept {
    // Set current to head
    Node<T>* current = head;

    // Iterate and delete all elements
    while (current != nullptr) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }

    // Set values to nullptr or 0
    head = nullptr;
    tail = nullptr;
    count = 0;
}

#endif  // LLIST_HPP
