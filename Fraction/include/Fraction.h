#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>

class Fraction
{
    public:
        Fraction();
        Fraction(int);
        Fraction(int, int);
        Fraction(const Fraction&);
        Fraction& operator+(const Fraction&);
        Fraction& operator-(const Fraction&);
        Fraction& operator*(const Fraction&);
        Fraction& operator/(const Fraction&);
        bool operator<(const Fraction&);
        bool operator>(const Fraction&);
        bool operator==(const Fraction&);
        int getNumerator() const { return numerator;}
        int getDenominator() const { return denominator;}
        void setNumerator(int);
        void setDenominator(int);
        friend std::ostream& operator<<(std::ostream&, const Fraction&);
        friend std::istream& operator>>(std::istream&, Fraction&);
    private:
        void simplify();
        int numerator;
        int denominator;
        int gcd(int, int);

};
#endif // FRACTION_H
