/*#include "Fraction.h"
#include <iostream> //for printing to console
#include <cmath> //abs to get the sign out of there

Fraction::Fraction()
{
    numer = 1;
    denom = 1;
    simplify();
}

Fraction::Fraction(int num, int den) {
    numer = num;
    denom = den;
    simplify();
}

Fraction::~Fraction()
{
    //dtor
}

int Fraction::gcd(int a, int b) {
    int t;
    while(b != 0) {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void Fraction::simplify() {
    int the_gcd = gcd(numer, denom);
    numer /= the_gcd;
    denom /= the_gcd;
    if (denom < 0) {
        denom *= -1;
        numer *= -1;
    }
}
void Fraction::Print() {
    if(numer == 1 && denom == 1) {
        //don't print anything
    } else if (denom == 1) {
        std::cout << std::abs(numer);
    } else {
        std::cout << "(" << std::abs(numer) << "/" << denom << ")";
    }
}

double Fraction::toDouble() {
    return numer/denom;
}
Fraction& Fraction::operator+(const Fraction& rhs) {
    return *new Fraction(numer * rhs.getDenom() + rhs.getNumer() * denom, denom*rhs.getDenom());
}

Fraction& Fraction::operator-(const Fraction& rhs) {
    return *new Fraction(numer * rhs.getDenom() - rhs.getNumer() * denom, denom*rhs.getDenom());
}

Fraction& Fraction::operator*(const Fraction& rhs) {
    return *new Fraction(numer * rhs.getNumer(), denom * rhs.getDenom());
}

Fraction& Fraction::operator/(const Fraction& rhs) {
    return *new Fraction(numer * rhs.getDenom(), denom * rhs.getNumer());
}

Fraction& Fraction::operator+(const int& rhs) {
    return *new Fraction(numer + rhs * denom, denom);
}

Fraction& Fraction::operator-(const int& rhs) {
    return *new Fraction(numer - rhs * denom, denom);
}

Fraction& Fraction::operator*(const int& rhs) {
    return *new Fraction(numer * rhs, denom);
}

Fraction& Fraction::operator/(const int& rhs) {
    return *new Fraction(numer, rhs*denom);
}
*/
