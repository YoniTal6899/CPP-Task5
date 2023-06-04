#include "doctest.h"
#include "sources/MagicalContainer.h"
#include <stdexcept>

using namespace ariel;
using namespace std;

// Test case for adding elements to the MagicalContainer
TEST_CASE("Adding elements to MagicalContainer") {
    MagicalContainer container;

    SUBCASE("Adding a single element") {
        container.addElement(10);
        CHECK(container.size() == 1);
    }

    SUBCASE("Adding multiple elements") {
        container.addElement(10);
        container.addElement(20);
        container.addElement(30);
        CHECK(container.size() == 3);
    }
}

// Add more test cases...

// Test case for removing elements from the MagicalContainer
TEST_CASE("Removing elements from MagicalContainer") {
    MagicalContainer container;

    SUBCASE("Removing an existing element") {
        container.addElement(10);
        container.addElement(20);
        CHECK_NOTHROW(container.removeElement(10));
        CHECK(container.size() == 1);
    }

    SUBCASE("Removing a non-existing element") {
        container.addElement(10);
        container.addElement(20);
        CHECK_THROWS_AS(container.removeElement(30), runtime_error);
        CHECK(container.size() == 2);
    }
}

// Test case for the AscendingIterator
TEST_CASE("AscendingIterator") {
    MagicalContainer container;
    container.addElement(10);
    container.addElement(20);
    container.addElement(30);
    container.addElement(15);
    container.addElement(25);

    SUBCASE("Iterating over elements") {
        AscendingIterator it(container);
        CHECK(*it == 10);
        ++it;
        CHECK(*it == 15);
        ++it;
        CHECK(*it == 20);
        ++it;
        CHECK(*it == 25);
        ++it;
        CHECK(*it == 30);
        ++it;
        CHECK(it == it.end());
    }
}

// Test case for comparing iterators from the same container
TEST_CASE("Comparing iterators from the same container") {
    MagicalContainer container;
    for (int i = 1; i <= 10; ++i) {
        container.addElement(i * 10);
    }

    SUBCASE("Comparing AscendingIterator with itself") {
        AscendingIterator it1(container);
        AscendingIterator it2(container);
        CHECK(it1 == it2);
        CHECK(!(it1 != it2));
        CHECK(!(it1 < it2));
        CHECK(!(it1 > it2));
    }
}

// Test case for an empty container
TEST_CASE("Empty Container") {
    MagicalContainer container;

    SUBCASE("Size of an empty container should be zero") {
        CHECK(container.size() == 0);
    }
    AscendingIterator ai1(container);
    SUBCASE("Iterating through an empty container should not enter the loop") {
        for (auto it = ai1.begin(); it != ai1.end(); ++it) {
            CHECK(false); // Fail the test if the loop is entered
        }
        CHECK(true); // If the loop is not entered, the test passes
    }
}

// Test case for adding and removing elements
TEST_CASE("Adding and Removing Elements") {
    MagicalContainer container;

    SUBCASE("Adding elements should increase the container size") {
        container.addElement(10);
        CHECK(container.size() == 1);
        container.addElement(20);
        CHECK(container.size() == 2);
    }

    SUBCASE("Removing elements should decrease the container size") {
        container.addElement(10);
        container.addElement(20);
        container.addElement(30);
        container.removeElement(20);
        CHECK(container.size() == 2);
        container.removeElement(10);
        CHECK(container.size() == 1);
    }
}

// Test case for iterating through all elements in the container
TEST_CASE("Iterating through All Elements") {
    MagicalContainer container;
    container.addElement(10);
    container.addElement(20);
    container.addElement(30);

    SUBCASE("Iterating through all elements should return all elements in the container") {
        vector<int> expected{10, 20, 30};
        vector<int> result;
        AscendingIterator ai(container);
        for (auto it = ai.begin(); it != ai.end(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }
}
