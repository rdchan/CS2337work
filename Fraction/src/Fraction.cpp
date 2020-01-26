#include "Fraction.h"

Fraction::Fraction()
{
    this->numerator = 0;
    this->denominator = 1;
}

Fraction::Fraction(int n)
{
    this->numerator = n;
    this->denominator = 1;
}

Fraction::Fraction(int n, int d)
{
    this->numerator = n;
    this->denominator = d;
}

Fraction::Fraction(const Fraction& frac) {
    this->numerator = frac.getNumerator();
    this->denominator = frac.getDenominator();
}

void Fraction::setNumerator(int n)
{
    this->numerator = n;
    this->simplify();
}

void Fraction::setDenominator(int d)
{
    this->denominator = d;
    this->simplify();
}



int Fraction::gcd(int a, int b)
{
    int t;
    while(b != 0) {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}

bool Fraction::operator==(const Fraction& rhs)
{
    return (this->numerator == rhs.getNumerator()) && (this->denominator == rhs.getDenominator());
}

void Fraction::simplify()
{
    int the_gcd = gcd(this->numerator, this->denominator);
    this->numerator /= the_gcd;
    this->denominator /= the_gcd;
}

bool Fraction::operator>(const Fraction& rhs)
{
    //TODO: prevent div by 0
    double left = (double)this->getNumerator() / this->getDenominator();
    double right = (double)rhs.getNumerator() / rhs.getDenominator();
    return left > right;
}

bool Fraction::operator<(const Fraction& rhs)
{
    //TODO: prevent div by 0
    double left = (double)this->getNumerator() / this->getDenominator();
    double right = (double)rhs.getNumerator() / rhs.getDenominator();
    return left < right;
}

Fraction& Fraction::operator/(const Fraction& rhs)
{
    Fraction tmp(this->getNumerator() * rhs.getDenominator(), this->getDenominator() * rhs.getNumerator());
    tmp.simplify();
    return *new Fraction(tmp);
}

Fraction& Fraction::operator*(const Fraction& rhs)
{
    Fraction tmp(this->getNumerator() * rhs.getNumerator(), this->getDenominator() * rhs.getDenominator());
    tmp.simplify();
    return *new Fraction(tmp);
}

/*Fraction Fraction::operator*(int c)
{
    this->setNumerator(this->getNumerator() * c);
    this->simplify();
    return *this;
}
*/
Fraction& Fraction::operator-(const Fraction& rhs)
{
    //numerator is this->getNumerator()*rhs.getDenominator() - rhs.getNumerator()*this->getDenominator()
    //denominator is this->getDenominator()*rhs.getDenominator()

    return *new Fraction(this->getNumerator()*rhs.getDenominator() - rhs.getNumerator()*this->getDenominator(),\
                          this->getDenominator()*rhs.getDenominator());
}

Fraction& Fraction::operator+(const Fraction& rhs)
{
    //numerator is this->getNumerator()*rhs.getDenominator() + rhs.getNumerator()*this->getDenominator()
    //denominator is this->getDenominator()*rhs.getDenominator()

    return *new Fraction(this->getNumerator()*rhs.getDenominator() + rhs.getNumerator()*this->getDenominator(),\
                          this->getDenominator()*rhs.getDenominator());
}

std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
    os << frac.getNumerator() << "/" << frac.getDenominator();
    return os;
}

std::istream& operator>>(std::istream& is, Fraction& frac) {
    int input;
    is >> input;
    frac.setNumerator(input);
    is >> input;
    frac.setDenominator(input);
    return is;
}

