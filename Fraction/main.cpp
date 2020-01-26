/*
    Rishi Chandna
    rdc180001
*/

#include <iostream>
#include "Fraction.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    Fraction a(1,4);
    Fraction b;
    cout << "a is: " << a << endl << "enter b: " << endl;
    cin >> b;
    while(a == b) {
        cout << "please do not make them the same" << endl << "enter b: " << endl;
        cin >> b;
    }
    cout << "b is: " << b << endl;
    a = a+b;
    cout << "a is now" << a << endl;
    /*
    Create a driver program that uses the fraction class
Create two fraction objects
Use the stream extraction operator to modify one of the objects
Make sure that both objects represent different fractions
Use the stream insertion operator to display the results of each overloaded mathematical and relational operator
addition
subtraction
multiplication
division
less than
greater than
equals
    */
    cout << "(" << a << ") + (" << b << ") = " << a+b << endl;
    cout << "(" << a << ") - (" << b << ") = " << a-b << endl;
    cout << "(" << a << ") * (" << b << ") = " << a*b << endl;
    cout << "(" << a << ") / (" << b << ") = " << a/b << endl;
    cout << "(" << a << ") < (" << b << ") ? " << ((a<b) ? "true" : "false") << endl;
    cout << "(" << a << ") > (" << b << ") ? " << ((a>b) ? "true" : "false") << endl;
    cout << "(" << a << ") == (" << b << ") ? " << ((a==b) ? "true" : "false") << endl;
    return 0;
}
