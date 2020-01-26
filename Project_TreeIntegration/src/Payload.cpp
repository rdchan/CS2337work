//Rishi Chandna
//RDC180001
#include "Payload.h"

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

    //just euclid's algo
    int t;
    while(b != 0) {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void Fraction::simplify() {
    //divide top and bottom by the gcd
    int the_gcd = gcd(numer, denom);
    numer /= the_gcd;
    denom /= the_gcd;

    //force negative sign to the numerator to make printing stable
    if (denom < 0) {
        denom *= -1;
        numer *= -1;
    }
}
void Fraction::Print(bool isFirstTerm) {
    //if it evaluates to positive 1, no need to print the fraction. specific to this project
    if(numer == 1 && denom == 1) {
        //don't print anything
    } else if (numer == -1 && denom == 1) {
        //if it evaluates to negative one, just print a negative sign. specific to this project
        std::cout << "-";
    } else if (denom == 1) { //denom ==1 means that the numerator holds all the information. no need for (numer/denom)
        //with the first term, the sign goes with it
        if(isFirstTerm) {
            std::cout << numer;
        } else {
            //with all other terms, getParity will take care of printing the sign. just worry about magnitude for these
            std::cout << std::abs(numer);
        }
    } else {
        //need numer and denom
        if(isFirstTerm) {
            //get that sign in there for first term
            std::cout << "(" << numer << "/" << denom << ")";
        } else {
            //let GetParity print sign, just worry about magnitude
            std::cout << "(" << std::abs(numer) << "/" << denom << ")";
        }
    }
}

double Fraction::toDouble() {
    return (double)((double)numer/(double)denom);
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

Payload::Payload()
{
    outer_coeff = Fraction(1, 1);
}

Payload::Payload(Fraction input) : Payload() {
    outer_coeff = input;
}

Payload::~Payload()
{
    //dtor
}

//used to print terms
std::string Payload::GetParity() {
    if(outer_coeff.toDouble() == -1) {
        //get the space, but the fraction print will get the sign.
        return " ";
    } else if (outer_coeff.toDouble() < 0) {
        //if the outer coeff is negative, use a negative sign
        return " - ";
    } else {
        return " + ";
    }

}

void Payload::Combine(const Payload* input) {
    //for expterm, cos and sin, this is what is needed when two like-terms are combined.
    outer_coeff = outer_coeff + input->getCoefficient();
}

ExpTerm::ExpTerm() : Payload() {
    exponent = 0;
}

ExpTerm::ExpTerm(Fraction coeff, int exp) : Payload(coeff){
    exponent = exp;
}

ExpTerm::~ExpTerm() {

}

void ExpTerm::IntegrateTerm() {
    //reverse power rule. straight forward with outer_coeff being a fraction.
    exponent++;
    outer_coeff = outer_coeff/exponent; //overloaded fraction / operator with fraction and int!
}

void ExpTerm::Print(bool isFirstTerm) {
    //just gotta follow the guidelines on how it should be printed

    //special cases
    if(outer_coeff.toDouble() == 1) {

    } else if (outer_coeff.toDouble() == -1) {
        if(isFirstTerm) {
            std::cout << "-";
        } else {
            std::cout << "- ";
        }
    } else {
        //typically just print the outer coeff though
        outer_coeff.Print(isFirstTerm);
    }

    //special cases
    if(exponent == 0) {
        //no x value, just a scalar
    } else if (outer_coeff.getNumer() == 0) {
        //has no value, 0*x = 0.
    } else if(exponent == 1) {
        std::cout << "x";
    } else {
        //normal case
        std::cout << "x^" << exponent;
    }
}

double ExpTerm::EvaluateAt(int lower, int upper) {
    //at upper minus at lower.
    return outer_coeff.toDouble() * (double)((double)(pow(upper, exponent)) - (double)(pow(lower, exponent)));
}

bool ExpTerm::operator<(const Payload* rhs) {
    //used for ordering in the tree. ***higher exponents go to the left side***

    //check if we are comparing against an expterm
    const ExpTerm* rhs_exp = dynamic_cast<const ExpTerm*>(rhs);
    if(rhs_exp) {
        //if so, check the exponents
        if(exponent > rhs_exp->getExponent()) {
            return true;
        } else {
            return false;
        }
    } else {
        //if the dynamic cast gave a null pointer, it's because rhs is a trig term. trig terms are always greater than exp terms
        return true;
    }
}

bool ExpTerm::operator==(const Payload* rhs) {

    //used to see if we can combine. needs exponent to be the same

    const ExpTerm* rhs_exp = dynamic_cast<const ExpTerm*>(rhs);
    //check if it is an expterm
    if(rhs_exp) {
            //if so, compare exponents
        if(exponent == rhs_exp->getExponent()) {
            return true;
        } else {
            return false;
        }
    } else {
        //if the dynamic cast gave a null pointer, it's because rhs is a trig term. trig terms are always greater than exp terms
        return false;
    }
}

TrigTerm::TrigTerm() : Payload(){
    func = Function::COS;
    inner_coeff = 0;
    rank = 0;
}

TrigTerm::TrigTerm(Fraction outer, Function fun, int inner, int rank) : Payload(outer) {
    func = fun;
    inner_coeff = inner;
    this->rank = rank;
}

TrigTerm::~TrigTerm() {

}

void TrigTerm::IntegrateTerm() {
    //definition of integration for these functions. flip signs and function switching. easy to understand
    if(func == Function::COS) {
        outer_coeff = outer_coeff/inner_coeff; //fraction operator / overload!
        func = Function::SIN;
    } else {
        outer_coeff = outer_coeff/inner_coeff;
        outer_coeff = outer_coeff*-1;
        func = Function::COS;
    }
}

void TrigTerm::Print(bool isFirstTerm) {
    if(outer_coeff.toDouble() == 1) {

    } else if (outer_coeff.toDouble() == -1) {
        if(isFirstTerm) {
            std::cout << "-";
        } else {
            std::cout << "- ";
        }
    } else {
        outer_coeff.Print(isFirstTerm);
    }
    //special cases for cos
    if(func == Function::COS) {
        if(outer_coeff.getNumer() == 0) {

        } else if(inner_coeff == 1) {
            std::cout << "cos x";
        } else {
            //standard
            std::cout << "cos " << inner_coeff << "x";
        }
    } else {
    //special cases for sin
        if(outer_coeff.getNumer() == 0) {

        } else if(inner_coeff == 1) {
            std::cout << "sin x";
        } else {
            //standard
            std::cout << "sin " << inner_coeff << "x";
        }
    }

}

double TrigTerm::EvaluateAt(int, int) {
    //trig terms are only subject to indefinite integrals
    return 0;
}

bool TrigTerm::operator<(const Payload* rhs) {
    //used to determine tree insert order. compare the "rank" which is order encountered

    const TrigTerm* rhs_trig = dynamic_cast<const TrigTerm*>(rhs);
    //can only check rank against other trig terms
    if(rhs_trig) {
        if(rank < rhs_trig->getRank()) {
            return true;
        } else {
            return false;
        }
    } else {
        //if the dynamic cast gave a null pointer, it's because rhs is an exp term. exp terms are always less
        return false;
    }
}

bool TrigTerm::operator==(const Payload* rhs) {
    //used to check if we can combine. can only combine if the function is the same (cos and cos or sin and sin)
                                                        //and the inner coeff is the same
    const TrigTerm* rhs_trig = dynamic_cast<const TrigTerm*>(rhs);
    //make sure it's a trig term
    if(rhs_trig) {
            //if so, check function (cos or sin) and inner coeff
        if(func == rhs_trig->func && inner_coeff == rhs_trig->getInnerCoeff()) {
            return true;
        } else {
            return false;
        }
    } else {
        //if the dynamic cast gave a null pointer, it's because rhs is an exp term. exp terms won't be equal
        return false;
    }
}
