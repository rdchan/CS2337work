//Rishi Chandna
//RDC180001
#ifndef PAYLOAD_H
#define PAYLOAD_H

#include <iostream> //for printing functions
#include <cmath> //for evaluating exp terms to get definite integral

class Fraction
{
    public:
        Fraction();
        Fraction(int, int);
        virtual ~Fraction();
        void Print(bool);
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

class Payload
{
public:
    Payload();
    Payload(Fraction);
    virtual ~Payload(); //no pointer members, nothing to delete or cleanup
    virtual void IntegrateTerm() = 0; //implemented in child classes because it differs for each
    virtual void Print(bool) = 0;
    virtual double EvaluateAt(int, int) = 0; //used for keeping track of evaluation for definite integrals
    virtual bool operator<(const Payload*) = 0; //used for comparing for insertion. only need either < or >. I chose <
    virtual bool operator==(const Payload*) = 0; //used for comparing for combining like terms
    Fraction getCoefficient() const { return outer_coeff; }
    void Combine(const Payload*);
    std::string GetParity(); //helps with stable printing
protected:
    Fraction outer_coeff;


private:

};

class ExpTerm : public Payload
{

public:
    ExpTerm();
    ExpTerm(Fraction, int);
    ~ExpTerm();
    virtual void IntegrateTerm(); //reverse power rule
    virtual void Print(bool); //check Payload.cpp for more details on these functions
    virtual double EvaluateAt(int, int);
    virtual bool operator<(const Payload*);
    virtual bool operator==(const Payload*);
    int getExponent() const { return exponent; }
    void setExponent(int exp) { exponent = exp; }
protected:

private:
    int exponent;

};

class TrigTerm : public Payload //see Payload.cpp for more information
{

public:
    enum Function {SIN, COS}; //keep track of what function it is. it'll swap when integrating.
    Function func;
    TrigTerm();
    TrigTerm(Fraction, Function, int, int);
    ~TrigTerm();
    int inner_coeff;
    virtual void IntegrateTerm();
    virtual void Print(bool);
    virtual double EvaluateAt(int, int);
    virtual bool operator<(const Payload*);
    virtual bool operator==(const Payload*);
    int getRank() const { return rank; }
    void setRank(int _rank) { rank = _rank; }
    int getInnerCoeff() const { return inner_coeff; }
    void setInnerCoeff(int _inner) { inner_coeff = _inner;}
protected:

private:
    int rank;

};
#endif // PAYLOAD_H
