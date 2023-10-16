/// @file Vector.cpp
/// @author David Tom <8000190528@student.csn.edu>
/// @date 2023-fall-cs202-pa12-Vector
/// @note I pledge my word of honor that I have abided by the
/// the CSN Academic Integrity Policy while completing this assignment.
///
/// @brief This header file contains the class "Vector". Vector is a sequence
/// container that encapsulates dynamic size arrays.
///
/// @note People who helped me: N/A
///
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.

// header files
#include "Vector.h"
#include <cassert>
#include <iostream>

/* Constructors and Destructor */

/// Constructs the container with count copies of elements with value value.
/// @param count The number of elements to be constructed in the vector
/// (default zero).
/// @param value The value to initialize each element with (default value).
Vector::Vector(size_type count, const value_type& value) {
    // TODO(David Tom): create container with elements.
    // loop through vector's count and assign value to all indexes

    // clean slate
    m_data = nullptr;
    m_capacity = 0;
    m_count = 0;

    // set m_count and m_capacity
    m_count = count;
    m_capacity = (count);

    // memory allocate
    m_data = new value_type[m_capacity];

    //// initialize elements with value
    for (size_type i = 0; i < m_count; ++i) {
        *(m_data + i) = value;
    }
}

/// Copy constructor. Constructs the container with the copy of the contents
/// of other.
/// @param other Another Vector object to copy from.
Vector::Vector(const Vector& other) {
    // TODO(David Tom): copy vector from other

    // clean slate
    m_data = nullptr;
    m_capacity = 0;
    m_count = 0;

    // assign memory for the pointer
    m_data = new value_type[other.m_capacity];

    // assign values from previous array
    m_count = other.m_count;
    m_capacity = other.m_capacity;

    // copy data
    for (size_type i = 0; i < other.m_count; ++i) {
        *(m_data + i) = *(other.m_data + i);
    }

}

/// Move constructor for the Vector class. Efficiently transfers
/// ownership of resources between Vector objects.
///
/// @param other The Vector to be moved.
Vector::Vector(Vector&& other) {
    // TODO(David Tom): move vector from other

    // clean slate
    m_data = nullptr;
    m_capacity = 0;
    m_count = 0;

    // assign memory for the temporary pointer
    m_data = new value_type[other.m_capacity];

    // assign values from previous array
    m_count = other.m_count;
    m_capacity = other.m_capacity;

    // copy data
    for (size_type i = 0; i < other.m_count; ++i) {
        *(m_data + i) = *(other.m_data + i);
    }

    // delete other's data
    other.clear();
    other.m_data = nullptr;
    other.m_count = 0;
    other.m_capacity = 0;

}

/// Destructs the vector. The used storage is deallocated.
Vector::~Vector() {
    // TODO(David Tom): deletes vector
    // delete data
    delete[] m_data;

    // assign values to 0
    m_data = nullptr;
    m_capacity = 0;
    m_count = 0;
}

/* Element Access */

/// Returns a reference to the element at specified location pos, with
/// bounds checking.
/// @pre pos is within the range of the container (i.e., pos < size())
/// @assert pos is within the range of the container.
/// @param pos The position of the element to access.
/// @return Reference to the element at the specified position.
Vector::reference Vector::at(size_type pos) {
    // TODO(David Tom): reference data from the specified position.
    assert((pos < size()));

    return *(m_data + (pos));
}

Vector::const_reference Vector::at(size_type pos) const {
    // TODO(David Tom): reference data from the specified position.
    assert((pos < size()));

    return *(m_data + (pos));
}

/// Returns a reference to the first element in the container.
/// @note Calling front on an empty container causes undefined behavior.
/// @return Reference to the first element.
Vector::reference Vector::front() {
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

Vector::const_reference Vector::front() const {
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
Vector::reference Vector::back() {
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

Vector::const_reference Vector::back() const {
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
Vector::pointer Vector::begin() {
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

Vector::const_pointer Vector::begin() const {
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
Vector::pointer Vector::end() {
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

Vector::const_pointer Vector::end() const {
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
Vector::pointer Vector::insert(Vector::const_pointer pos,
                        const Vector::value_type& value) {
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
Vector::pointer Vector::erase(Vector::pointer pos) {
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
bool Vector::empty() const {
    // TODO(David Tom): verify if class is empty

    return m_count == 0;
}

/// Returns the number of elements in the container, i.e. value of m_count.
/// @return The number of elements in the container.
Vector::size_type Vector::size() const {

    return (m_count);
}

/// Returns the number of elements that the container has currently
/// allocated space for, i.e., value of m_capacity.
/// @return The current capacity of the container.
Vector::size_type Vector::capacity() const {

    return m_capacity;
}


/* Modifiers */

/// Erases all elements from the container. After this call, size()
/// returns zero.
void Vector::clear() {
    // TODO(David Tom): create empty bag with all empty values.
    // loop through bag's capacity and assign empty values to all indexes

    for (Vector::size_type i = 0; i < m_capacity; ++i) {
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
void Vector::push_back(const value_type& value) {
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
void Vector::pop_back() {

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
        new_data = new value_type[m_capacity];

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

/// Copy assignment operator for the Vector class.
/// Copies the contents of one Vector into another.
///
/// @param other The Vector to be copied.
/// @return A reference to the updated Vector.
Vector& Vector::operator=(const Vector& other) {
    // TODO(David Tom): copy vector from other
    if (this != &other) {
        // clean slate
        m_data = nullptr;
        m_capacity = 0;
        m_count = 0;

        // assign memory for the temporary pointer
        m_data = new value_type[other.m_capacity];

        // assign values from previous array
        m_count = other.m_count;
        m_capacity = other.m_capacity;

        // copy data
        for (size_type i = 0; i < other.m_count; ++i) {
            *(m_data + i) = *(other.m_data + i);
        }
    }

    return *this;
}

/// Move assignment operator for the Vector class.
/// Efficiently moves the contents of one Vector into another.
///
/// @param other The Vector to be moved.
/// @return A reference to the updated Vector.
Vector& Vector::operator=(Vector&& other) {

    if (this != &other) {
        // clean slate
        m_data = nullptr;
        m_capacity = 0;
        m_count = 0;

        // assign memory for the temporary pointer
        m_data = new value_type[other.m_capacity];

        // assign values from previous array
        m_count = other.m_count;
        m_capacity = other.m_capacity;

        // copy data
        for (size_type i = 0; i < other.m_count; ++i) {
            *(m_data + i) = *(other.m_data + i);
        }

        // delete other's data
        other.clear();
        other.m_data = nullptr;
        other.m_count = 0;
        other.m_capacity = 0;
    }

    return *this;
}


/// Addition assignment operator for the Vector class. Appends the contents of
/// one Vector to another.
///
/// @param other The Vector to be appended.
/// @return A reference to the updated Vector.
Vector& Vector::operator+=(const Vector& other) {
    // TODO(David Tom): appends contents of vector to another
    // push back with value being other's
    // create copy array, add values to it, delete/rebuild old array,
    // copy data to old array with new capacity, add new data starting at end

    pointer new_data;           // set a pointer to a new array
    size_type j = 0;            // used to track index for array2

    // clean slate
    new_data = nullptr;

    // set new capacity value
    m_capacity = (m_capacity + other.m_capacity);

    if (this != &other) {
        // check if size is equal to or near capacity
        if ((m_count + other.m_count) >= (m_capacity)) {
            // double size of capacity
            m_capacity *= 2;
        }

        // assign memory for the temporary pointer
        new_data = new value_type[m_capacity];

        // copy data from array1
        for (size_type i = 0; i < m_count; ++i) {
            *(new_data + i) = *(m_data + i);
        }

        // append data from array2
        // start from end of array1 and beginning of array2 (j = 0)
        for (size_type i = m_count; i < (m_count + other.m_count); ++i) {
            *(new_data + i) = *(other.m_data + j);
            ++j;
        }

        // delete old data
        delete[] m_data;

        // update data pointer
        m_data = new_data;

        // increment m_count
        m_count = (m_count + other.m_count);
    }

    return *this;
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
bool equal(const Vector& lhs, const Vector& rhs) {
    // TODO(David Tom): compare Vectors' contents in 'lhs' and 'rhs'.
    bool boolState = true;                       // tracks boolState status

    // tracks size for verification
    Vector::size_type const totalSize = lhs.size();

    // verifies size is equal
    if (totalSize == rhs.size()) {
        // loop through bags and compare index values
        for (Vector::size_type i = 0; i < totalSize; ++i) {
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
bool operator==(const Vector& lhs, const Vector& rhs) {
    // TODO(David Tom): compare Vectors' contents in 'lhs' and 'rhs'.
    bool boolState = true;                       // tracks boolState status

    // tracks size for verification
    Vector::size_type const totalSize = lhs.size();

    // verifies size is equal
    if (totalSize == rhs.size()) {
        // loop through bags and compare index values
        for (Vector::size_type i = 0; i < totalSize; ++i) {
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
