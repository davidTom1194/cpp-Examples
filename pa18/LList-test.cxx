/// @file 2023-fall-cs202-pa17a-LList::LList-test.cxx
/// @author Kevin Mess <kevin.mess@csn.edu>
///
/// @version 2023-11-11 Original
/// @version 2023-11-20 Added edge case tests for insert() and erase()
///
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.
///
/// @brief This file contains Catch2 unit tests for the Node struct,
/// BiDirectionalIterator struct, and LList class.
///
/// @note subject to change -- create a symbolic link to the source document.

#include <string>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "LList.hpp"
#include "LList.hpp"  // test include guard

TEMPLATE_TEST_CASE("Node struct is correctly initialized", "[Node]",
                   int, double, std::string) {
    TestType data = TestType{};
    Node<TestType> node(data);

    SECTION("Node is initialized with default data and null pointers") {
        CHECK(node.data == data);
        CHECK(node.prev == nullptr);
        CHECK(node.next == nullptr);
    }

    SECTION("Node can be initialized with specific data") {
        data = GENERATE(values<TestType>({TestType{1}, TestType{2}, TestType{3}}));
        Node<TestType> specificNode(data);
        CHECK(specificNode.data == data);
        CHECK(specificNode.prev == nullptr);
        CHECK(specificNode.next == nullptr);
    }

    SECTION("Node links to other nodes correctly") {
        Node<TestType> prevNode(data);
        Node<TestType> nextNode(data);
        Node<TestType> middleNode(data, &prevNode, &nextNode);

        CHECK(middleNode.prev == &prevNode);
        CHECK(middleNode.next == &nextNode);
        CHECK(prevNode.next == nullptr);
        CHECK(nextNode.prev == nullptr);
    }
}

TEMPLATE_TEST_CASE("Node struct handles different data types", "[Node]",
                   int, double, std::string) {
    SECTION("Node handles integer data") {
        Node<int> node(5);
        CHECK(node.data == 5);
    }

    SECTION("Node handles floating-point data") {
        Node<double> node(3.14);
        CHECK(node.data == Approx(3.14));
    }

    SECTION("Node handles string data") {
        Node<std::string> node("test");
        CHECK(node.data == "test");
    }
}

TEST_CASE("BiDirectionalIterator functionality", "[BiDirectionalIterator]") {
    Node<int> node1(1);
    Node<int> node2(2);
    Node<int> node3(3);

    // Manually linking nodes for testing
    node1.next = &node2;
    node2.prev = &node1;
    node2.next = &node3;
    node3.prev = &node2;

    LList<int>::BiDirectionalIterator it(&node1);

    SECTION("Iterator initialization and dereferencing") {
        CHECK(*it == 1);
    }

    SECTION("Iterator increment operations") {
        // prefix increment
        CHECK(*(++it) == 2);
        // postfix increment
        it++;
        CHECK(*it == 3);
    }

    SECTION("Iterator decrement operations") {
        // moving iterator to the end
        ++it; ++it;
        // prefix decrement
        CHECK(*(--it) == 2);
        // postfix decrement
        it--;
        CHECK(*it == 1);
    }

    SECTION("Iterator comparison operations") {
        LList<int>::BiDirectionalIterator it2(&node1);
        CHECK(it == it2);  // same position
        ++it2;
        CHECK(it != it2);  // different position
    }

    SECTION("Arrow operator access") {
        Node<std::string> strNode1("Test1");
        Node<std::string> strNode2("Test2");
        strNode1.next = &strNode2;
        strNode2.prev = &strNode1;

        LList<std::string>::BiDirectionalIterator strIt(&strNode1);
        CHECK(strIt->size() == 5);
    }
}

TEST_CASE("LList construction", "[LList]") {
    SECTION("Default constructor") {
        LList<int> list;
        CHECK(list.empty());
        CHECK(list.size() == 0);
        CHECK(list.begin() == list.end());
    }

    SECTION("Copy constructor") {
        // Prerequisite: push_back
        LList<int> original;
        original.push_back(1);
        original.push_back(2);
        original.push_back(3);

        LList<int> copy(original);
        CHECK(copy.size() == original.size());
        CHECK_FALSE(original.begin() == copy.begin());
        CHECK_FALSE(copy.empty());

        auto orig_it = original.begin();
        auto copy_it = copy.begin();
        while (orig_it != original.end() && copy_it != copy.end()) {
            CHECK(*orig_it == *copy_it);
            ++orig_it;
            ++copy_it;
        }
    }

    SECTION("Move constructor") {
        // Prerequisite: push_back
        LList<int> original;
        original.push_back(1);
        original.push_back(2);

        LList<int> moved(std::move(original));
        CHECK(moved.size() == 2);
        CHECK(original.empty());
        CHECK(*moved.begin() == 1);
        CHECK(*(++moved.begin()) == 2);
    }

    SECTION("Initializer list constructor") {
        LList<int> list({1, 2, 3});
        CHECK(list.size() == 3);
        CHECK_FALSE(list.empty());

        auto it = list.begin();
        CHECK(*it == 1);
        ++it;
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 3);
    }
}

TEST_CASE("LList assignment operations", "[LList]") {
    SECTION("Copy assignment operator") {
        // Prerequisite: push_back
        LList<int> original;
        original.push_back(1);
        original.push_back(2);

        LList<int> copy;
        copy = original;

        CHECK(copy.size() == original.size());
        CHECK_FALSE(copy.empty());

        auto orig_it = original.begin();
        auto copy_it = copy.begin();
        while (orig_it != original.end() && copy_it != copy.end()) {
            CHECK(*orig_it == *copy_it);
            ++orig_it;
            ++copy_it;
        }
    }

    SECTION("Move assignment operator") {
        // Prerequisite: push_back
        LList<int> original;
        original.push_back(1);
        original.push_back(2);

        LList<int> moved;
        moved = std::move(original);

        CHECK(moved.size() == 2);
        CHECK(original.empty());
        CHECK(*moved.begin() == 1);
        CHECK(*(++moved.begin()) == 2);
    }

    SECTION("Assignment from initializer list") {
        LList<int> list;
        list = {1, 2, 3};

        CHECK(list.size() == 3);
        CHECK_FALSE(list.empty());

        auto it = list.begin();
        CHECK(*it == 1);
        ++it;
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 3);
    }
}

TEST_CASE("LList iterator operations", "[LList]") {
    SECTION("Iterators on an empty list") {
        LList<int> list;
        CHECK(list.begin() == list.end());
        CHECK_NOTHROW(list.begin());
        CHECK_NOTHROW(list.end());
    }

    SECTION("Iterators on a non-empty list") {
        // Prerequisite: push_back
        LList<int> list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);

        CHECK(list.begin() != list.end());

        auto it = list.begin();
        CHECK(*it == 1);
        ++it;
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 3);
        ++it;
        CHECK(it == list.end());
    }

    SECTION("Const iterators on a non-empty list") {
        // Prerequisite: push_back, initializer_list ctor
        const LList<int> list = {1, 2, 3};

        auto it = list.begin();
        CHECK(*it == 1);
        ++it;
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 3);
        ++it;
        CHECK(it == list.end());
    }
}

TEST_CASE("LList capacity operations", "[LList]") {
    SECTION("Empty list") {
        LList<int> list;
        CHECK(list.empty());
        CHECK(list.size() == 0);
    }

    SECTION("List with one element") {
        // Prerequisite: push_back
        LList<int> list;
        list.push_back(1);
        CHECK_FALSE(list.empty());
        CHECK(list.size() == 1);
    }

    SECTION("List with multiple elements") {
        // Prerequisite: push_back
        LList<int> list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        CHECK_FALSE(list.empty());
        CHECK(list.size() == 3);
    }

    SECTION("Empty list after removing elements") {
        // Prerequisite: push_back and pop_back
        LList<int> list;
        list.push_back(1);
        list.pop_back();
        CHECK(list.empty());
        CHECK(list.size() == 0);
    }
}

TEST_CASE("LList element access operations", "[LList]") {
    SECTION("Accessing elements in a non-empty list") {
        // Prerequisite: push_back
        LList<int> list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);

        CHECK(list.front() == 1);
        CHECK(list.back() == 3);
    }

    SECTION("Accessing elements in a list with one element") {
        // Prerequisite: push_back
        LList<int> list;
        list.push_back(5);

        CHECK(list.front() == 5);
        CHECK(list.back() == 5); // front and back should be the same
    }

    SECTION("Accessing elements in an empty list") {
        LList<int> list;
        CHECK_THROWS_AS(list.front(), std::out_of_range);
        CHECK_THROWS_AS(list.back(), std::out_of_range);
    }
}

TEST_CASE("LList modifier operations", "[LList]") {
    SECTION("push_front on an empty and non-empty list") {
        LList<int> list;
        list.push_front(1);
        CHECK(list.size() == 1);
        CHECK(list.front() == 1);

        list.push_front(0);
        CHECK(list.size() == 2);
        CHECK(list.front() == 0);
    }

    SECTION("pop_front on a non-empty list") {
        // Prerequisite: push_front
        LList<int> list;
        list.push_front(1);
        list.pop_front();
        CHECK(list.empty());

        list.push_front(2);
        list.push_front(1);
        list.pop_front();
        CHECK(list.front() == 2);
    }

    SECTION("pop_front on an empty list") {
        LList<int> list;
        CHECK_NOTHROW(list.pop_front());
    }

    SECTION("push_back on an empty and non-empty list") {
        LList<int> list;
        list.push_back(1);
        CHECK(list.size() == 1);
        CHECK(list.back() == 1);

        list.push_back(2);
        CHECK(list.size() == 2);
        CHECK(list.back() == 2);
    }

    SECTION("pop_back on a non-empty list") {
        // Prerequisite: push_back
        LList<int> list;
        list.push_back(1);
        list.pop_back();
        CHECK(list.empty());

        list.push_back(1);
        list.push_back(2);
        list.pop_back();
        CHECK(list.back() == 1);
    }

    SECTION("pop_back on an empty list") {
        LList<int> list;
        CHECK_NOTHROW(list.pop_back());
    }

    SECTION("insert and erase operations") {
        LList<int> list;
        list.push_back(1);
        list.push_back(3);

        // Inserting at the beginning
        auto itBegin = list.insert(list.begin(), 0); // Inserting 0 at the beginning
        CAPTURE(list);
        CHECK(*itBegin == 0);
        CHECK(list.size() == 3);

        // Inserting in the middle
        auto itMiddle = list.insert(++list.begin(), 2); // Inserting 2 between 1 and 3
        CAPTURE(list);
        CHECK(*itMiddle == 2);
        CHECK(list.size() == 4);

        // Inserting at the end
        auto itEnd = list.insert(list.end(), 4); // Inserting 4 at the end
        CAPTURE(list);
        CHECK(*itEnd == 4);
        CHECK(list.size() == 5);

        // Erasing middle element (2)
        itMiddle = list.erase(itMiddle); // Erasing 2
        CAPTURE(list);
        CHECK(*itMiddle == 1);
        CHECK(list.size() == 4);

        // Erasing beginning element (0)
        itBegin = list.erase(itBegin); // Erasing 0
        CAPTURE(list);
        CHECK(*itBegin == 1);
        CHECK(list.size() == 3);

        // Erasing end element (4)
        list.erase(itEnd); // Erasing 4
        CAPTURE(list);
        CHECK(list.size() == 2);

        // Test erasing at end() throws exception
        CHECK_THROWS_AS(list.erase(list.end()), std::invalid_argument);
    }


    SECTION("swap operation") {
        // Prerequisite: push_back
        LList<int> list1;
        list1.push_back(1);
        list1.push_back(2);
        LList<int> list2;
        list2.push_back(2);

        list1.swap(list2);
        CHECK(list1.size() == 1);
        CHECK(list2.size() == 2);
        CHECK(list1.front() == 2);
        CHECK(list2.front() == 1);
    }

    SECTION("clear operation") {
        // Prerequisite: push_back or similar function for list population
        LList<int> list;
        list.push_back(1);
        list.push_back(2);
        list.clear();
        CHECK(list.empty());
    }
}

/* EOF */
