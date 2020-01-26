#include <iostream>

#include "TemocTemplate.h"

using namespace std;

int main()
{

    cout << boolalpha; //set flag to print true and false instead of 1 and 0 for the find function

    //add some integers and print the unsorted and sorted
    TemocTemplate<int> myIntVec;
    myIntVec.add(10);
    myIntVec.add(5);
    myIntVec.add(15);
    cout << "before sort: ";
    myIntVec.print();
    myIntVec.SortMe();
    cout << "after sort: ";
    myIntVec.print();
    //find an element in the vector, and one not.
    cout << "myIntVec.Find(15): " << myIntVec.Find(15) << endl;
    cout << "myIntVec.Find(0): " << myIntVec.Find(0) << endl << endl;

    //add some doubles in, then print unsorted and sorted
    TemocTemplate<double> myDoubleVec;
    myDoubleVec.add(3.6);
    myDoubleVec.add(-13.5);
    myDoubleVec.add(17.333);
    myDoubleVec.add(0.4);
    cout << "before sort: ";
    myDoubleVec.print();
    myDoubleVec.SortMe();
    cout << "after sort: ";
    myDoubleVec.print();
    //try finding something that exists, and something that doesn't
    cout << "myDoubleVec.Find(3.6): " << myDoubleVec.Find(3.6) << endl;
    cout << "myDoubleVec.Find(2.9): " << myDoubleVec.Find(2.9) << endl << endl;

    //add in different types of strings and print unsorted and sorted
    TemocTemplate<string> myStrings;
    myStrings.add("cheese");
    myStrings.add("fishing");
    myStrings.add("spaghetti");
    myStrings.add("shoe");
    myStrings.add("instruments");
    myStrings.add("lights");
    cout << "before sort: ";
    myStrings.print();
    myStrings.SortMe();
    cout << "after sort: ";
    myStrings.print();
    //find shoestrings and don't find a yoyo string
    cout << "myStrings.Find(shoe): " << myStrings.Find("shoe") << endl;
    cout << "myStrings.Find(yoyo): " << myStrings.Find("yoyo") << endl;


    return 0;
}
