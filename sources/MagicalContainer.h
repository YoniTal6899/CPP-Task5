#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

namespace ariel
{
    class MagicalContainer
    {
        private:
        vector<int> elements;

        public:
        void addElement(int element) {elements.push_back(element);}

        vector<int> getElements() const{
            return this->elements;
        }

        void removeElement(int element)
        {
            for (auto it = elements.begin(); it != elements.end(); ++it)
            {
                if (*it == element)
                {
                    elements.erase(it);
                    break;
                }
            }
        }

        int size() const {return elements.size();}

        friend class AscendingIterator;
        friend class PrimeIterator;
        friend class SideCrossIterator;
    };

 
    class AscendingIterator 
    {
        private:
            const MagicalContainer& container;
            size_t index;

        public:
            AscendingIterator(const MagicalContainer& cont, size_t idx = 0)
                : container(cont), index(idx) {}

            bool operator==(const AscendingIterator& other) const {
                return &container == &other.container && index == other.index;
            }

            bool operator!=(const AscendingIterator& other) const {
                return !(*this == other);
            }

            bool operator>(const AscendingIterator& other) const {
                return index > other.index;
            }

            bool operator<(const AscendingIterator& other) const {
                return index < other.index;
            }

            int operator*() const {
                return container.elements[index];
            }

            AscendingIterator& operator++() {
                ++index;
                return *this;
            }

            AscendingIterator begin() const {
                return AscendingIterator(*this);
            }

            AscendingIterator end() const {
                return AscendingIterator(this->container, container.getElements().size());
            }
    };


    class PrimeIterator
    {
        private:
            const MagicalContainer& container;
            size_t index;

            bool isPrime(int number) const {
                if (number < 2)
                    return false;
                for (int i = 2; i <= std::sqrt(number); ++i) {
                    if (number % i == 0)
                        return false;
                }
                return true;
            }

        public:
            PrimeIterator(const MagicalContainer& cont, size_t idx = 0)
                : container(cont), index(idx) {
                while (index < container.elements.size() && !isPrime(container.elements[index]))
                    ++index;
            }

            bool operator==(const PrimeIterator& other) const {
                return &container == &other.container && index == other.index;
            }

            bool operator!=(const PrimeIterator& other) const {
                return !(*this == other);
            }

            bool operator>(const PrimeIterator& other) const {
                return index > other.index;
            }

            bool operator<(const PrimeIterator& other) const {
                return index < other.index;
            }

            int operator*() const {
                return container.elements[index];
            }

            PrimeIterator& operator++() {
                ++index;
                while (index < container.elements.size() && !isPrime(container.elements[index]))
                    ++index;
                return *this;
            }

            PrimeIterator begin() const {
                return PrimeIterator(*this);
            }

            PrimeIterator end() const {
                return PrimeIterator(this->container, container.getElements().size());
            }
    };

    class SideCrossIterator
    {
        private:
            const MagicalContainer& container;
            size_t forwardIndex;
            size_t backwardIndex;

        public:
            SideCrossIterator(const MagicalContainer& cont)
                : container(cont), forwardIndex(0), backwardIndex(cont.elements.size() - 1) {}

            bool operator==(const SideCrossIterator& other) const {
                return &container == &other.container && forwardIndex == other.forwardIndex &&
                    backwardIndex == other.backwardIndex;
            }

            bool operator!=(const SideCrossIterator& other) const {
                return !(*this == other);
            }

            bool operator>(const SideCrossIterator& other) const {
                return forwardIndex > other.forwardIndex || backwardIndex > other.backwardIndex;
            }

            bool operator<(const SideCrossIterator& other) const {
                return forwardIndex < other.forwardIndex || backwardIndex < other.backwardIndex;
            }

            int operator*() const {
                if (forwardIndex <= backwardIndex)
                    return container.elements[forwardIndex];
                else
                    return container.elements[backwardIndex];
            }

            SideCrossIterator& operator++() {
                if (forwardIndex <= backwardIndex)
                    ++forwardIndex;
                else
                    --backwardIndex;
                return *this;
            }

            
            SideCrossIterator begin() const {
                return SideCrossIterator(*this);
            }

            SideCrossIterator end() const {
                SideCrossIterator endIterator(*this);
                endIterator.forwardIndex = container.getElements().size();
                endIterator.backwardIndex = container.getElements().size() - 1;
                return endIterator;
            }
        };

}