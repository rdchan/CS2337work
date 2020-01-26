/*#ifndef FRACTION_H
#define FRACTION_H


class Fraction
{
    public:
        Fraction();
        Fraction(int, int);
        virtual ~Fraction();
        void Print();
        double toDouble();
        Fraction& operator+(const Fraction&);
        Fraction& operator-(const Fraction&);
        Fraction& operator*(const Fraction&);
        Fraction& operator/(const Fraction&);
        Fraction& operator+(const int&);
        Fraction& operator-(const int&);
        Fraction& operator*(const int&);
        Fraction& operator/(const int&);
        int getNumer() const{ return numer;}
        int getDenom () const{ return denom;}

    protected:

    private:
        int numer;
        int denom;
        int gcd(int, int);
        void simplify();

};

#endif // FRACTION_H
*/
