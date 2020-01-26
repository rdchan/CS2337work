#ifndef TEMOCTEMPLATE_H
#define TEMOCTEMPLATE_H

#include <vector> //used for the vector
#include <iostream> //used for simplistic print function, as opposed to operator<< overload

template<typename T>
class TemocTemplate
{
    public:
        TemocTemplate(){};
        ~TemocTemplate(){};

        //uses selection sort
        void SortMe() {
            //outer loop pass to go through each element
            for(unsigned int i = 0; i < MyVector.size()-1; i++) {
                int minIndex = i;
                //find the minimum element past the outer loop
                for(unsigned int j = i+1; j < MyVector.size(); j++) {
                    if(MyVector[j] < MyVector[minIndex]) {
                        minIndex = j;
                    }
                }
                //bring the minimum element to the sorted side of the vector
                T tmp = MyVector[i];
                MyVector[i] = MyVector[minIndex];
                MyVector[minIndex] = tmp;
            }
        }

        //call the recursive find function with bounds of the vector size
        bool Find(const T& val) {
            return Find(val, 0, MyVector.size()-1);
        }

        //recursive binary search algorithm. returns true if the value is in the vector, false otherwise
        bool Find(const T& val, int _lower_bound, int _upper_bound) {
            //if the previous midpoint passes through a bound, we've gone through the whole vector and haven't found it
            if(_upper_bound < _lower_bound) { return false; }
            //find a new midpoint given the current bounds
            unsigned int midpoint = ((_upper_bound - _lower_bound)/2) + _lower_bound;
            //check if we've found the value
            if(MyVector[midpoint] == val) { return true;}
            //if the value is higher than our midpoint, check the half above what we just checked
            if(val > MyVector[midpoint]) {
                return Find(val, midpoint+1, _upper_bound);
            } else { //otherwise it's lower and we should check the half below
                return Find(val, _lower_bound, midpoint-1);
            }
        }
        void add(T newVal) { MyVector.push_back(newVal);}

        void print() {
            //print out all the elements except for the last one with a comma
            for(auto it = MyVector.begin(); it != --MyVector.end(); ++it) {
                std::cout << *it << ", ";
            }
            //then print the last one
            std::cout << *(--MyVector.end()) << std::endl;
        }

    private:
        std::vector<T> MyVector;
};

#endif // TEMOCTEMPLATE_H
