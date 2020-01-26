//Rishi Chandna
//RDC180001
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "BinTree.h"
#include "Payload.h"
using namespace std;


string ExtractTerm(string line) {
    //given an expression, returns a substring leftmost term, whether it is an exponential or trig.

    //go through the expression,
    for(unsigned int i = 1; i < line.length(); i++) {
        //split at all + and - signs
        if(line.at(i) == '+' || line.at(i) == '-') {
            //but allow the negative from a trig term inner coeff and a negative exponent to pass through
            //  since those are included in the term
            if(line.at(i-1) != 's' && line.at(i-1) != 'n' && line.at(i-1) != '^') {
                return line.substr(0, i);
            }
        }
    }
    //if there were no signs to split at, return the line given since it's a single term.
    return line;
}

double PrepareTree(string line, BinTree<Payload*>* terms, int lower, int upper) {
    int trig_rank = 0; //"order trig terms in the order they were encountered"
    double evaluation = 0; //keep track of what the definite integral would be as we put things into the tree
                            //this way we reduce the number of traversals
    //we will cut off each term from the line using extract term, removing it from the line after putting it in the tree
    //this means that after we've processed all terms, the line will be empty
    while(line != "") {

        string term = ExtractTerm(line); //take one term at a time
        line.erase(0, term.length()); //cut it out of the line so we know when to stop
        //regarding the term
        //it can either be ax^b, x^b, ax, or a, or acosbx or asinbx

        Payload* new_term; //payload*, but becomes expterm* or trigterm*. then gets added to the tree
        char outer_coeff_delimiter; //c means cosine, x means x, s means sine. determines how we create the new_term
        int outer_coeff = 0; //shared across all 3 types of terms. (cos, sin, exp)

        if(term.find("cos") != string::npos) { //if there is a cos in the string, use c
            outer_coeff_delimiter = 'c';
        } else if(term.find("sin") != string::npos) { //if there's a sin in the string, use s
            outer_coeff_delimiter = 's';
        } else { //no sin or cos, it's an exponential term. might have ^, might not. might not even have an x
            outer_coeff_delimiter = 'x';
        }

        //pull outer coeff first
        //if there is an x,
        if(term.find(outer_coeff_delimiter) != string::npos) {
            if(term.find(outer_coeff_delimiter) == 0) { //ex. x^7 or cos 4x or sin 4x no coefficient, x is leading. assume 1
                outer_coeff = 1;
            } else if(term.find(outer_coeff_delimiter) == 1) { //ex. +x^7 or +cos 4x. no coefficient, but x isn't leading. still + tho
                if(term.at(0) == '+') {
                    outer_coeff = 1;
                } else if(term.at(0) == '-') { //ex. -x^7. no coefficient, but - sign means assume -1
                    outer_coeff = -1;
                } else { //otherwise, the coefficient is actually there! we can pull it from the start to the delimiter
                    outer_coeff = stoi(term.substr(0, term.find(outer_coeff_delimiter)));
                }
            } else { //more than a single digit outer-coeff, still pull the number.
                outer_coeff = stoi(term.substr(0, term.find(outer_coeff_delimiter)));
            }
        } else {
            //no delimiter found means that it's just a scalar.  grab the whole term
            outer_coeff = stoi(term);
        }

        //if it is an exponential term, pull the exponent
        if(outer_coeff_delimiter == 'x') {
            int exponent = 0;
            //if there's a ^, just read after it
            if(term.find('^') != string::npos) {
                exponent = stoi(term.substr(term.find('^')+1,term.length()));
            } else if(term.find('x') != string::npos) {
                //if there isn't, see if there's an x. if so, it's 1. otherwise it's 0
                exponent = 1;
            } else {
                exponent = 0;
            }

            //we now have all components of the expterm. create the new_term.
            new_term = new ExpTerm(Fraction(outer_coeff, 1), exponent);
        } else if(outer_coeff_delimiter == 'c') { //for a cos, we have outer coeff, we know it's cos from c, just need
            //to pull the inner coeff from between the s and the
            //(also need the trig rank)
            int inner_coeff;
            //check if it's just cos x
            if( (term.find('x')-term.find('s')-1) == 0) {
                inner_coeff = 1;
            } else if ( ((term.find('x')-term.find('s')-1) == 1) && ( term.at(term.find('s')+1) == '+') ) { //check if length is 1 and it's a + or -
                //checks for like cos+x. not necessary really.
                inner_coeff = 1;
            } else if ( ((term.find('x')-term.find('s')-1) == 1) && ( term.at(term.find('s')+1) == '-') ) {
                //checks for like cos-x. plausible
                inner_coeff = -1;
            } else { //otherwise, just a number we can pull. cos4x
                inner_coeff = stoi(term.substr(term.find('s')+1,term.find('x')-term.find('s')-1));
            }

            trig_rank++;

            //we now have everything we need to create new_term with cos.
            new_term = new TrigTerm(Fraction(outer_coeff,1), TrigTerm::Function::COS, inner_coeff, trig_rank);
        }  else if(outer_coeff_delimiter == 's') {
            //if it's a sine, pull the inner coefficient from between the n and the x

            int inner_coeff;
            //check if length is 0 (just x)
            if( (term.find('x')-term.find('n')-1) == 0) {
                inner_coeff = 1;
            } else if ( ((term.find('x')-term.find('n')-1) == 1) && ( term.at(term.find('n')+1) == '+') ) { //check if length is 1 and it's a + or -
               //checks like sin+x. not really necessary
                inner_coeff = 1;
            } else if ( ((term.find('x')-term.find('n')-1) == 1) && ( term.at(term.find('n')+1) == '-') ) {
                //checks something like sin-x. plausible
                inner_coeff = -1;
            } else { //otherwise, just a number we can pull. sin10x
                inner_coeff = stoi(term.substr(term.find('n')+1,term.find('x')-term.find('n')-1));
            }
            trig_rank++;

            //we now have everything we need to create new_term with cos.
            new_term = new TrigTerm(Fraction(outer_coeff,1),TrigTerm::Function::SIN, inner_coeff, trig_rank);

        }

        //we've examined cases for expterm, cos, and sin.
        //before we add it to the tree and lose it, integrate and then evaluate that term at the bounds

        new_term->IntegrateTerm(); //reduces number of traversals
        evaluation += (new_term->EvaluateAt(upper, lower)); //reduces number of traversals

        //check if it can be combined with an existing term in the tree
        auto existing = terms->Search(new_term); //search returns true for exp terms with exponent matching, and trigterms with inner coeff matching
        if(existing == nullptr) {
            terms->Insert(new_term); //if search came up empty, throw it in the tree
        } else {
            existing->getPayload()->Combine(new_term); //if search had something, edit the existing term.
        }

    }

    //return the integrated expression at bounds
    return evaluation;
}

//going to be recursive, friend function. uses getparity and payload prints
void PrintTerms(BinTree<Payload*>* terms, const Node<Payload*>* curr) {
    //recursive function, inorder traversal
    //print left, then this, then right, base case is null
    if(curr == nullptr) { return; } //don't print anything if we're past a leaf

    //print the left subtree
    PrintTerms(terms, curr->getLeft());

    //print this node.
    //if this node is the first one to be printed (equal to tree's leftmost value)
    if((terms->MinValue()->getPayload() == curr->getPayload())) {
        //print it, passing in firstterm is true. this puts the sign inside the fraction/ignores +1 coefficient etc.
        curr->getPayload()->Print(true);
    } else {
        //if it isn't the first term, print the parity separate from the term to get proper spacing
        cout << curr->getPayload()->GetParity();
        curr->getPayload()->Print(false);
    }

    //print the right subtree
    PrintTerms(terms, curr->getRight());
}


void PrintTerms(BinTree<Payload*>* terms) {
    PrintTerms(terms, terms->getRoot());
}



void ParseLine(string line) {
    BinTree<Payload*>* terms = new BinTree<Payload*>; //holds the integrated terms, in order of printing

    //first check if we are dealing with a definite or an indefinite integral

    //if it's a definite integral, grab the bounds
    int upper_limit = 0;
    int lower_limit = 0;
    if(line.at(0) != '|') {
            //lower bound is from the beginning to the pipe
        lower_limit = stoi(line.substr(0, line.find('|')));
            //upper bound is from the pipe to the first space
        upper_limit = stoi(line.substr(line.find('|')+1, line.find(' ', line.find('|'))-line.find('|')));
        //remove the bounds and pipe to make parsing easier later
        line.erase(0, line.find(' ', line.find('|')+1));
    }


    //remove all whitespace from the line for consistency
    for(unsigned int i = 0; i < line.length(); i++) {
        if(line.at(i) == ' ') {
            line.erase(i, 1);
            i--; //don't need to go to next index since the string condenses
        }
    }

    //at this point the line no longer has whitespace
    //if the line still has a pipe, that means it didn't have bounds (we removed the pipe after getting bounds)
    if(line.at(0) == '|') { //do the indefinite integral

        //take out the pipe and the dx
        line.erase(0,1);
        line.erase(line.find('d'),2);

        //call to prepare tree will fill the tree with the integrated terms
        //prepare tree returns the integrated expression evaluated at bounds, but we don't have to do anything with that
        PrepareTree(line, terms, upper_limit, lower_limit);

        //now that the tree has the integrated expression, we need to print it out
        PrintTerms(terms);
        cout << " + C" << endl;
    } else { //do the definite integral
        //take out the dx (pipe was already removed)
        line.erase(line.find('d'),2);

        //this time we call prepare tree but store the evaluation it gives back
        double definite_result = PrepareTree(line, terms, upper_limit, lower_limit);

        //print terms like normal
        PrintTerms(terms);

        //also print the evaluation to 3 decimal places
        cout << fixed << setprecision(3);
        cout << ", " << lower_limit << "|" << upper_limit << " = " << definite_result << endl;
    }

    //make sure to deallocate the tree!
    delete terms;
    terms = nullptr;
}

int main()
{

    //prompt for input filename
    string line;
    cin >> line;
    ifstream input(line);

    //assert that it is valid
    if(!input.is_open()) {
        cerr << "couldn't open file";
        return -1;
    }

    //call ParseLine (which will print to console) on each line
    while(getline(input, line)) {
        ParseLine(line);
    }

    //close the input file
    input.close();
    return 0;


}
