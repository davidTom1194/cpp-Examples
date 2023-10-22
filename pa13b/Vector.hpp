/// @file Vector.h
/// @author David Tom <8000190528@student.csn.edu>
/// @version 2023-fall-cs202-pa12
/// @note I pledge my word of honor that I have abided by the
/// the CSN Academic Integrity Policy while completing this assignment.
///
/// @brief This header file contains the class "Vector". Vector is a sequence
/// container that encapsulates dynamic size arrays. File copied and modified
/// from CSN's CS202 'shared' directory for use in the assignment.
///
/// @note People who helped me: N/A
///
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.


#ifndef VECTOR_HPP
#define VECTOR_HPP

// header files
#include <cstddef>  // provides std::size_t
#include <cassert>
#include <iostream>


/// Vector is a sequence container that encapsulates dynamic size arrays.
///
/// The elements are stored contiguously, which means that elements can be
/// accessed using offsets to regular pointers to elements. This means that a
/// pointer to an element of a vector may be passed to any function that
/// expects a pointer to an element of an array.
///
/// The storage of the vector is handled automatically, being expanded as
/// needed. Vectors usually occupy more space than static arrays, because more
/// memory is allocated to handle future growth. This way a vector does not
/// need to reallocate each time an element is inserted, but only when the
/// additional memory is exhausted. The total amount of allocated memory can
/// be queried using capacity() function.
///
/// @note Partial custom implementation of std::vector<int>.

template <class T>
class Vector {
public:
    // Public aliases
    using size_type       = std::size_t;
    using value_type      = T;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;

    /* Constructors and Destructor */

    /// Constructs the container with count copies of elements with value value.
    /// @param count The number of elements to be constructed in the vector
    /// (default zero).
    /// @param value The value to initialize each element with (default value).
    Vector(size_type count = 0, const value_type& value = value_type{});

    /// Copy constructor. Constructs the container with the copy of the contents
    /// of other.
    /// @param other Another Vector object to copy from.
    Vector(const Vector& other);

    /// Move constructor for the Vector class. Efficiently transfers
    /// ownership of resources between Vector objects.
    ///
    /// @param other The Vector to be moved.
    Vector(Vector&& other);

    /// Destructs the vector. The used storage is deallocated.
    ~Vector();

    /* Element Access */

    /// Returns a reference to the element at specified location pos, with
    /// bounds checking.
    /// @pre pos is within the range of the container (i.e., pos < size())
    /// @assert pos is within the range of the container.
    /// @param pos The position of the element to access.
    /// @return Reference to the element at the specified position.
    reference at(size_type pos);
    const_reference at(size_type pos) const;

    reference operator[](size_type pos) { return *(begin() + pos); }
    const_reference operator[](size_type pos) const { return *(begin() + pos); }

    /// Returns a reference to the first element in the container.
    /// @note Calling front on an empty container causes undefined behavior.
    /// @return Reference to the first element.
    reference front();
    const_reference front() const;

    /// Returns a reference to the last element in the container.
    /// @note Calling back on an empty container causes undefined behavior.
    /// @return Reference to the last element.
    reference back();
    const_reference back() const;

    /// Returns a pointer to the first element of the vector.
    /// If the vector is empty, the returned pointer will be equal to end().
    /// @return Pointer to the first element.
    pointer begin();
    const_pointer begin() const;

    /// Returns an pointer to the element following the last element of
    /// the vector.
    /// @return Pointer to one past the last element.
    pointer end();
    const_pointer end() const;

    /// Inserts elements into the Vector at a specified position.
    ///
    /// @param pos   The position where the elements should be inserted.
    /// @param value The value to be inserted.
    /// @return      A pointer to the inserted elements.
    Vector::pointer insert(Vector::const_pointer pos,
                            const Vector::value_type& value);

    /// Erases elements from the Vector at a specified position.
    ///
    /// @param pos The position of the element to be erased.
    /// @return    A pointer to the elements following the erased element.
    Vector::pointer erase(Vector::pointer pos);

    /* Capacity */

    /// Checks if the container has no elements, i.e. whether begin() == end().
    /// @return True if the container is empty, otherwise false.
    bool empty() const;

    /// Returns the number of elements in the container, i.e. value of m_count.
    /// @return The number of elements in the container.
    size_type size() const;

    /// Returns the number of elements that the container has currently
    /// allocated space for, i.e., value of m_capacity.
    /// @return The current capacity of the container.
    size_type capacity() const;

    /* Modifiers */

    /// Erases all elements from the container. After this call, size()
    /// returns zero.
    void clear();

    /// Appends the given element value to the end of the container.
    /// If after the operation the new size() is greater than old capacity(),
    /// a reallocation takes place, in which case all pointers (including the
    /// end() pointer) and all references to the elements are invalidated.
    /// Otherwise only the end() pointer is invalidated.
    ///
    /// @post The element value is added to the end of the container. If the
    /// operation causes the vector to resize (i.e., if the new size exceeds
    /// the current capacity), memory may be reallocated, and pointers
    /// to elements (e.g., begin()) may change.
    ///
    /// @param value The value to be appended to the end of the container.
    void push_back(const value_type& value);

    /// Removes the last element of the container. Calling pop_back on an empty
    /// container results in undefined behavior. Pointers (including the end()
    /// pointer) and references to the last element are invalidated.
    ///
    /// @post The last element of the container is removed. If the vector was
    /// not empty before this operation, the size of the container (size()) is
    /// reduced by one. The capacity of the vector remains unchanged, and the
    /// memory allocated for the removed element is not freed.
    void pop_back();

    /* Do not modify: leave as is for pa12. */
    // Vector& operator=(const Vector&) = delete;

    /// Copy assignment operator for the Vector class.
    /// Copies the contents of one Vector into another.
    ///
    /// @param other The Vector to be copied.
    /// @return A reference to the updated Vector.
    Vector& operator=(const Vector& other);

    /// Move assignment operator for the Vector class.
    /// Efficiently moves the contents of one Vector into another.
    ///
    /// @param other The Vector to be moved.
    /// @return A reference to the updated Vector.
    Vector& operator=(Vector&& other);

    /// Addition assignment operator for the Vector class. Appends the contents
    /// of one Vector to another.
    ///
    /// @param other The Vector to be appended.
    /// @return A reference to the updated Vector.
    Vector& operator+=(const Vector& other);

private:
    pointer   m_data;      ///< Pointer to the dynamic array holding elements
    size_type m_capacity;  ///< Current capacity of the dynamic array
    size_type m_count;     ///< Number of active elements in the array
};

// ----------------------------------------------------------------------------

/* Non-members */

/// Compares two vector objects for equality, i.e., if both the size of lhs
/// and rhs are equal and each element in lhs has equivalent value in rhs at
/// the same position.
/// @param lhs The left-hand side Vector object for comparison.
/// @param rhs The right-hand side Vector object for comparison.
/// @return True if the vectors are equal, otherwise false.
template <class T>
bool equal(const Vector<T>& lhs, const Vector<T>& rhs);

/// Equality operator for Vector objects. Compares two Vectors for equality.
///
/// @param lhs The left-hand side Vector object for comparison.
/// @param rhs The right-hand side Vector object for comparison.
/// @return True if the vectors are equal (contain the same elements in the
/// same order), otherwise false.
template <class T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs);


/// Copies the elements in the range, defined by (first, last), to another
/// range beginning at d_first (copy destination range).
///
/// @param first   A pointer to the first element of the source sequence.
/// @param last    A pointer to one past the last element of source sequence.
/// @param d_first A pointer to the first element of the destination sequence.
/// @return        A pointer to the element in destination range, one past the
///                last element copies.
/// @note CS202 function operator used in lecture to remove final 6 bytes and
///       5 blocks of memory leakage in Vector-test2.cxx
template <class T>
static
typename Vector<T>::pointer mycopy(typename Vector<T>::const_pointer first,
                       typename Vector<T>::const_pointer last,
                       typename Vector<T>::pointer       d_first) {
    while (first != last) {
        *d_first++ = *first++;
    }

    return d_first;
}

/// The reallocation is done by allocating a new memory block of size new_size
/// bytes, copying memory area with size equal to the lesser of the new and the
/// old sizes, and freeing the old block.
///
/// @param [in, out] base A reference to a pointer to the current dynamic array.
/// @param current_size   The current size of the dynamic array.
/// @param new size       The desired new size for the dynamic array.
/// @return               The updated pointer base.
/// @note CS202 function operator used in lecture to remove final 6 bytes and
///       5 blocks of memory leakage in Vector-test2.cxx

template <class T>
static
typename Vector<T>::pointer resize(typename Vector<T>::pointer& base,
                       typename Vector<T>::size_type current_size,
                       typename Vector<T>::size_type new_size) {
    if (current_size != new_size) {
        // new array of new_size elements
        const auto tmp   = new typename Vector<T>::value_type[new_size] {};
        // number of elements to copy
        const auto count = new_size < current_size ? new_size : current_size;

        ::mycopy<T>(base, (base + count), tmp);

        delete[] base;
        base = tmp;
    }

    return base;
}


/* Constructors and Destructor */

/// Constructs the container with count copies of elements with value value.
/// @param count The number of elements to be constructed in the vector
/// (default zero).
/// @param value The value to initialize each element with (default value).
/// @note CS202 function operator used in lecture to remove final 6 bytes and
///       5 blocks of memory leakage in Vector-test2.cxx
template <class T>
Vector<T>::Vector(size_type count, const value_type& value) {
    // assign values
    m_data      = new value_type[count];
    m_capacity  = count;
    m_count     = count;

    // fill array with value
    for (pointer current = begin(); current != end(); ++current) {
        *current = value;
    }
}

/// Copy constructor. Constructs the container with the copy of the contents
/// of other.
/// @param other Another Vector object to copy from.
/// @note CS202 function operator used in lecture to remove final 6 bytes and
///       5 blocks of memory leakage in Vector-test2.cxx
template <class T>
Vector<T>::Vector(const Vector<T>& other) {
    // assign values based on other
    m_data      = new value_type[other.capacity()];
    m_capacity  = other.capacity();
    m_count     = other.size();

    // fill array with value
    ::mycopy<T>(other.begin(), other.end(), begin());
}

/// Move constructor for the Vector class. Efficiently transfers
/// ownership of resources between Vector objects.
///
/// @param other The Vector to be moved.
/// @note CS202 function operator used in lecture to remove final 6 bytes and
///       5 blocks of memory leakage in Vector-test2.cxx
template <class T>
Vector<T>::Vector(Vector<T>&& other) {
    // take ownership of other's properties
    m_data      = other.m_data;
    m_capacity  = other.capacity();
    m_count     = other.size();

    // leave other in a stable state
    other.m_data     = nullptr;
    other.m_count    = 0;
    other.m_capacity = 0;
}

/// Destructs the vector. The used storage is deallocated.
template <class T>
Vector<T>::~Vector() {
    // delete data
    delete[] m_data;

    // assign values to 0
    m_data      = nullptr;
    m_capacity  = 0;
    m_count     = 0;
}

/// Copy assignment operator for the Vector class.
/// Copies the contents of one Vector into another.
///
/// @param other The Vector to be copied.
/// @return A reference to the updated Vector.
/// @note CS202 function operator used in lecture to remove final 6 bytes and
///       5 blocks of memory leakage in Vector-test2.cxx
template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    // check for self assignment
    if (this != &other) {
        // verify size
        if (size() != other.size()) {
            // delete and assign values based on other
            delete[] m_data;
            m_data      = new value_type[other.size()];
            m_capacity  = other.size();
        }

        // fill array with values
        ::mycopy<T>(other.begin(), other.end(), begin());

        // set m_count
        m_count = other.m_count;

    }

    return *this;
}

/// Move assignment operator for the Vector class.
/// Efficiently moves the contents of one Vector into another.
///
/// @param other The Vector to be moved.
/// @return A reference to the updated Vector.
/// @note CS202 function operator used in lecture to remove final 6 bytes and
///       5 blocks of memory leakage in Vector-test2.cxx
template <class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) {
    // check for self-assignment
    if (this != &other) {
        delete[] m_data;

        // take ownership of other's properties
        m_data      = other.m_data;
        m_capacity  = other.capacity();
        m_count     = other.size();

        // leave other in a stable state
        other.m_data     = nullptr;
        other.m_count    = 0;
        other.m_capacity = 0;
    }

    return *this;
}


/// Addition assignment operator for the Vector class. Appends the contents of
/// one Vector to another.
///
/// @param other The Vector to be appended.
/// @return A reference to the updated Vector.
/// @note CS202 function operator used in lecture to remove final 6 bytes and
///       5 blocks of memory leakage in Vector-test2.cxx
template <class T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& other) {
    // compute the minimum required capacity
    const size_type min_reqd = size() + other.size();

    // check if reallocation necessary
    if (min_reqd > capacity()) {
        m_capacity = min_reqd;
        m_data     = ::resize<T>(m_data, size(), capacity());
    }

    // append the elements from the other Vector to the end of this Vector
    ::mycopy<T>(other.begin(), other.end(), end());

    m_count = min_reqd;

    return *this;
}


/* Element Access */

/// Returns a reference to the element at specified location pos, with
/// bounds checking.
/// @pre pos is within the range of the container (i.e., pos < size())
/// @assert pos is within the range of the container.
/// @param pos The position of the element to access.
/// @return Reference to the element at the specified position.
template <class T>
typename Vector<T>::reference Vector<T>::at(size_type pos) {
    // TODO(David Tom): reference data from the specified position.
    assert((pos < size()));

    return *(m_data + (pos));
}

template <class T>
typename Vector<T>::const_reference Vector<T>::at(size_type pos) const {
    // TODO(David Tom): reference data from the specified position.
    assert((pos < size()));

    return *(m_data + (pos));
}

/// Returns a reference to the first element in the container.
/// @note Calling front on an empty container causes undefined behavior.
/// @return Reference to the first element.
template <class T>
typename Vector<T>::reference Vector<T>::front() {
    // TODO(David Tom): reference data from the first index.
    // assert(!empty());

    // clean slate
    pointer frontValue = nullptr;              // stores the return value

    // verifies value is not empty and applies appropriate rules
    if (!empty()) {
        frontValue = (m_data);
    } else {
        *(m_data) = 'A';
        frontValue = (m_data);
    }

    return *frontValue;
}

template <class T>
typename Vector<T>::const_reference Vector<T>::front() const {
    // TODO(David Tom): reference data from the first index.
    // assert(!empty());

    // clean slate
    pointer frontValue = nullptr;              // stores the return value

    // verifies value is not empty and applies appropriate rules
    if (!empty()) {
        frontValue = (m_data);
    } else {
        *(m_data) = 'A';
        frontValue = (m_data);
    }

    return *frontValue;
}

/// Returns a reference to the last element in the container.
/// @note Calling back on an empty container causes undefined behavior.
/// @return Reference to the last element.
template <class T>
typename Vector<T>::reference Vector<T>::back() {
    // TODO(David Tom): reference data from the final index.
    // assert(!empty());

    // clean slate
    pointer backValue = nullptr;              // stores the return value

    // verifies value is not empty and applies appropriate rules
    if (!empty()) {
        backValue = (m_data + (m_count - 1));
    } else {
        backValue = (m_data);
    }

    return *backValue;
}

template <class T>
typename Vector<T>::const_reference Vector<T>::back() const {
    // TODO(David Tom): reference data from the final index.
    // assert(!empty());

    // clean slate
    pointer backValue = nullptr;              // stores the return value

    // verifies value is not empty and applies appropriate rules
    if (!empty()) {
        backValue = (m_data + (m_count - 1));
    } else {
        backValue = (m_data);
    }

    return *backValue;
}

/// Returns a pointer to the first element of the vector.
/// If the vector is empty, the returned pointer will be equal to end().
/// @return Pointer to the first element.
template <class T>
typename Vector<T>::pointer Vector<T>::begin() {
    // assert(!empty());

    // clean slate
    pointer backValue = nullptr;              // stores the return value

    // verifies value is not empty and applies appropriate rules
    if (empty()) {
        backValue = (m_data + (m_count));
    } else {
        backValue = (m_data);
    }

    return backValue;
}

template <class T>
typename Vector<T>::const_pointer Vector<T>::begin() const {
    // assert(!empty());

    // clean slate
    pointer backValue = nullptr;              // stores the return value

    // verifies value is not empty and applies appropriate rules
    if (empty()) {
        backValue = (m_data + (m_count));
    } else {
        backValue = (m_data);
    }

    return backValue;
}

/// Returns an pointer to the element following the last element of
/// the vector.
/// @return Pointer to one past the last element.
template <class T>
typename Vector<T>::pointer Vector<T>::end() {
    // assert(!empty());

    // clean slate
    pointer backValue = nullptr;              // stores the return value

    // verifies value is not empty and applies appropriate rules
    if (!empty()) {
        backValue = (m_data + (m_count));
    } else {
        backValue = (m_data);
    }

    return backValue;
}

template <class T>
typename Vector<T>::const_pointer Vector<T>::end() const {
    // assert(!empty());

    // clean slate
    pointer backValue = nullptr;              // stores the return value

    // verifies value is not empty and applies appropriate rules
    if (!empty()) {
        backValue = (m_data + (m_count));
    } else {
        backValue = (m_data);
    }

    return backValue;
}

/// Inserts elements into the Vector at a specified position.
///
/// @param pos   The position where the elements should be inserted.
/// @param value The value to be inserted.
/// @return      A pointer to the inserted elements.
template <class T>
typename Vector<T>::pointer Vector<T>::insert(typename
                                    Vector<T>::const_pointer pos,
                                    const typename Vector::value_type& value) {
    // TODO(David Tom): insert elements into new array, cleanup as needed
    // copy array to new array, append to given location, add value if i = pos,
    // add old array values to new array, copy new array to old array, cleanup

    pointer new_data;            // set a pointer to a new array
    size_type posIndex;          // tracks the position of the index
    posIndex = static_cast<size_type>(pos - m_data);   // index position

    // clean slate
    new_data = nullptr;

    // check if capacity is 0 and add 1
    if (m_capacity == 0) {
        m_capacity += 1;
    }

    // check if size is equal to or near capacity
    if ((m_count) >= (m_capacity)) {
        // double size of capacity
        m_capacity *= 2;
    }

    // assign memory for the temporary pointer
    new_data = new value_type[m_capacity];

    if (!empty()) {
        // copy initial data
        for (size_type i = 0; i < (posIndex); ++i) {
            // copy data
            *(new_data + i) = *(m_data + i);
        }

        // if at position append value
        *(new_data + posIndex) = value;

        // finish copying data at pos + 1
        for (size_type i = ((posIndex)); i < (m_count); ++i) {
            *(new_data + (i + 1)) = *(m_data + (i));
        }

    } else {
        *(new_data) = value;
    }

    // delete old data
    delete[] m_data;

    // update data pointer
    m_data = new_data;

    // Increment
    m_count += 1;

    return (m_data + posIndex);
}

/// Erases elements from the Vector at a specified position.
///
/// @param pos The position of the element to be erased.
/// @return    A pointer to the elements following the erased element.
template <class T>
typename Vector<T>::pointer Vector<T>::erase(typename Vector<T>::pointer pos) {
    // TODO(David Tom): erase elements from old array, cleanup as needed
    // copy array to new array, delete at given location, delete value i = pos,
    // add old array values to new array, copy new array to old array, cleanup

    pointer new_data;            // set a pointer to a new array
    size_type posIndex;          // tracks index for arrays
    posIndex = static_cast<size_type>(pos - m_data);   // index position

    // check if array is empty
    if (m_capacity != 0) {
        // clean slate
        new_data = nullptr;

        // check if size is equal to or near capacity
        if ((m_count + 1) >= (m_capacity)) {
            // double size of capacity
            m_capacity *= 2;
        }

        // assign memory for the temporary pointer
        new_data = new value_type[m_capacity];

        // copy data until position of desired value
        for (size_type i = 0; i < posIndex; ++i) {
            *(new_data + i) = *(m_data + (i));
        }

        // copy remaining data from (i + 1) to (i)
        for (size_type i = (posIndex); i < ((m_count) - 1); ++i) {
            *(new_data + i) = *(m_data + (i + 1));
        }

        // delete old data
        delete[] m_data;

        // append count value
        m_count -= 1;

        // update data pointer
        m_data = new_data;
    }

    return (m_data + posIndex);

}

/* Capacity */

/// Checks if the container has no elements, i.e. whether begin() == end().
/// @return True if the container is empty, otherwise false.
template <class T>
bool Vector<T>::empty() const {
    // TODO(David Tom): verify if class is empty

    return m_count == 0;
}

/// Returns the number of elements in the container, i.e. value of m_count.
/// @return The number of elements in the container.
template <class T>
typename Vector<T>::size_type Vector<T>::size() const {

    return (m_count);
}

/// Returns the number of elements that the container has currently
/// allocated space for, i.e., value of m_capacity.
/// @return The current capacity of the container.
template <class T>
typename Vector<T>::size_type Vector<T>::capacity() const {

    return m_capacity;
}


/* Modifiers */

/// Erases all elements from the container. After this call, size()
/// returns zero.
template <class T>
void Vector<T>::clear() {
    // TODO(David Tom): create empty bag with all empty values.
    // loop through bag's capacity and assign empty values to all indexes

    for (typename Vector<T>::size_type i = 0; i < m_capacity; ++i) {
        *(m_data + i) = 'A';
    }

    m_count = 0;
}


/// Appends the given element value to the end of the container.
/// If after the operation the new size() is greater than old capacity(),
/// a reallocation takes place, in which case all pointers (including the
/// end() pointer) and all references to the elements are invalidated.
/// Otherwise only the end() pointer is invalidated.
///
/// @post The element value is added to the end of the container. If the
/// operation causes the vector to resize (i.e., if the new size exceeds
/// the current capacity), memory may be reallocated, and pointers
/// to elements (e.g., begin()) may change.
///
/// @param value The value to be appended to the end of the container.
template <class T>
void Vector<T>::push_back(const typename Vector<T>::value_type& value) {
    // TODO(David Tom): check and, if needed, double the capacity
    // create copy array, add values to it, delete/rebuild old array,
    // copy data to old array with new capacity, add new data starting at end

    pointer new_data;           // set a pointer to a new array

    // clean slate
    // new_data = nullptr;

    // check if capacity is 0
    if (m_capacity == 0) {
        m_capacity += 1;
    }

    // check if size is equal to or near capacity
    if (m_count >= (m_capacity)) {
        // double size of capacity
        m_capacity *= 2;
        }

    // Create a new array with the updated capacity
    new_data = new value_type[m_capacity];

    // Copy the existing elements to the new array
    for (size_type i = 0; i < m_count; ++i) {
        *(new_data + i) = *(m_data + i);
    }

    // add the new value to the end of the array
    *(new_data + m_count) = value;

    // Delete the old data
    delete[] m_data;

    // Update the data pointer to point to the new array
    m_data = new_data;
// }

    // Add the new value to the end of the array and increment
    // *(m_data + m_count) = value;
    m_count += 1;

}

/// Removes the last element of the container. Calling pop_back on an empty
/// container results in undefined behavior. Pointers (including the end()
/// pointer) and references to the last element are invalidated.
///
/// @post The last element of the container is removed. If the vector was
/// not empty before this operation, the size of the container (size()) is
/// reduced by one. The capacity of the vector remains unchanged, and the
/// memory allocated for the removed element is not freed.
template <class T>
void Vector<T>::pop_back() {

    pointer new_data;           // set a pointer to a new array

    // clean slate
    new_data = nullptr;

    // check if capacity is 0
    if (m_capacity == 0) {
        m_capacity += 1;
    }
    // check if count is at or near capacity
    if (m_count >= m_capacity) {
        // double size of capacity
        m_capacity *= 2;
    }

    if (!empty()) {
        // Create a new array with the updated capacity
        new_data = new typename Vector<T>::value_type[m_capacity];

        // Copy the existing elements to the new array
        for (size_type i = 0; i < (m_count); ++i) {
            *(new_data + i) = *(m_data + i);
        }

        // assign a null value to final index
        *(new_data + m_count) = 'A';

        // Delete the old data
        delete[] m_data;

        // Update the data pointer to point to the new array
        m_data = new_data;

        // reduce m_count by 1
        m_count -= 1;
    }

}


/* Do not modify: leave as is for pa12. */
// Vector& operator=(const Vector&) = delete {
// }


/* Non-members */

/// Compares two vector objects for equality, i.e., if both the size of lhs
/// and rhs are equal and each element in lhs has equivalent value in rhs at
/// the same position.
/// @param lhs The left-hand side Vector object for comparison.
/// @param rhs The right-hand side Vector object for comparison.
/// @return True if the vectors are equal, otherwise false.
template <class T>
bool equal(const Vector<T>& lhs, const Vector<T>& rhs) {
    // TODO(David Tom): compare Vectors' contents in 'lhs' and 'rhs'.
    bool boolState = true;                       // tracks boolState status

    // tracks size for verification
    typename Vector<T>::size_type const totalSize = lhs.size();

    // verifies size is equal
    if (totalSize == rhs.size()) {
        // loop through bags and compare index values
        for (typename Vector<T>::size_type i = 0; i < totalSize; ++i) {
            // compare index values at given position
            if (lhs.at(i) != rhs.at(i)) {
                boolState = false;       // assigns boolState if instance occurs
            }
        }
    } else {
        // if size is not equal set bool to false
        boolState = false;
    }

    return boolState;
}

/// Equality operator for Vector objects. Compares two Vectors for equality.
///
/// @param lhs The left-hand side Vector object for comparison.
/// @param rhs The right-hand side Vector object for comparison.
/// @return True if the vectors are equal (contain the same elements in the
/// same order), otherwise false.
template <class T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
    // TODO(David Tom): compare Vectors' contents in 'lhs' and 'rhs'.
    bool boolState = true;                       // tracks boolState status

    // tracks size for verification
    typename Vector<T>::size_type const totalSize = lhs.size();

    // verifies size is equal
    if (totalSize == rhs.size()) {
        // loop through bags and compare index values
        for (typename Vector<T>::size_type i = 0; i < totalSize; ++i) {
            // compare index values at given position
            if (lhs.at(i) != rhs.at(i)) {
                boolState = false;       // assigns boolState if instance occurs
            }
        }
    } else {
        // if size is not equal set bool to false
        boolState = false;
    }

    return boolState;

}

/* EOF */

#endif /* VECTOR_HPP */
