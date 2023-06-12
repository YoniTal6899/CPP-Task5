#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
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
            bool deleated=false;
            for (auto it = elements.begin(); it != elements.end(); ++it)
            {
                if (*it == element)
                {
                    elements.erase(it);
                    deleated=true;
                    break;
                }
            }
            if(!deleated){__throw_runtime_error("Element was not found!");}
        }

        int size() const {return elements.size();}

        class AscendingIterator;
        class PrimeIterator;
        class SideCrossIterator;
    };

 
    class MagicalContainer::AscendingIterator 
    {
        private:
            MagicalContainer& container;
            size_t index;
            void sortVectorAscending(vector<int>& vec) {sort(vec.begin(), vec.end());}

        public:
            AscendingIterator(MagicalContainer& cont, size_t idx = 0)
                : container(cont), index(idx) {sortVectorAscending(this->container.elements);}

            AscendingIterator& operator=(const AscendingIterator& other)
            {
                if (&this->container != &other.container) {throw std::runtime_error("Iterators are pointing at different containers");}
                this->index=other.index;
                return *this;                
            }

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
                sortVectorAscending(this->container.elements);
                if(index>=container.elements.size()){throw std::runtime_error("Iterator reached the end");}
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


    class MagicalContainer::PrimeIterator
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

            PrimeIterator& operator=(const PrimeIterator& other)
            {
                if (&this->container != &other.container) {throw std::runtime_error("Iterators are pointing at different containers");}
                this->index=other.index;
                return *this;                
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
                if(index>=container.elements.size()){throw std::runtime_error("Iterator reached the end");}
                ++index;
                while (index < container.elements.size() && !isPrime(container.elements[index])){
                    ++index;
                }
                   
                return *this;
            }

            PrimeIterator begin() const {
                return PrimeIterator(*this);
            }

            PrimeIterator end() const {
                return PrimeIterator(this->container, container.getElements().size());
            }
    };

    class MagicalContainer::SideCrossIterator {
        private:
            int up;
            int down;
            MagicalContainer container;
            void stillAlive(){ if (!(up+down < container.size())){throw std::runtime_error("Iterator reached the end");}}
        public:
            SideCrossIterator(const MagicalContainer& container,int start=0, int finish =0) : container(container), up(start), down(finish) {}
            SideCrossIterator(const SideCrossIterator& other) : container(other.container), up(other.up), down(other.down) {}
            SideCrossIterator(){}

            SideCrossIterator& operator=(const SideCrossIterator& other) //Assignment operator
            {
                if (&this->container != &other.container) {throw std::runtime_error("Iterators are pointing at different containers");}
                up = other.up;
                down = other.down;
                return *this;
            }
            //Compare operators
            bool operator==(const SideCrossIterator& other) const {return (up == other.up && down == other.down);}
            bool operator!=(const SideCrossIterator& other) const {return !(*this==other);}
            bool operator>(const SideCrossIterator& other) const { return (up > other.up || down > other.down);}
            bool operator<(const SideCrossIterator& other) const { return (up < other.up || down < other.down);}

            int operator*() const
            {
                if(up != down){return container.elements[(vector<int>::size_type)(container.size()-down)];}                           
                return container.elements[(vector<int>::size_type)up];
            }

            SideCrossIterator& operator++() // Inc the right index
            {
                stillAlive();
                if (up != down) {++up;}
                else {++down;}
                return *this;
            }

            SideCrossIterator begin() const { return SideCrossIterator(this->container);}
            SideCrossIterator end() const 
            {
                int half= this->container.size()/2; //End Situation for the iterator. Both of indexes are in the middle
                if(this->container.size()%2 !=0){return SideCrossIterator(this->container, half, half+1);}
                return SideCrossIterator(this->container, half,half);
            }
};    


}



//static_cast<size_t>(container.size() - 1)