#ifndef _Polynomial_H
#define _Polynomial_H
//#include "Term.hpp"
#include "LinkedList.hpp"

class Term
{
private:
    double coefficient;
    int power;
public:
    Term (double coefficient=0.0, int power=0);
    double get_coefficient () const;
    int get_power () const;
    friend std::ostream& operator<< (std::ostream & out,const Term & t );
};
class Polynomial
{
private:
    LinkedList<Term> terms;
public:
    Polynomial ();
    void insert_term (Term term_to_insert);
    Polynomial operator+ (const Polynomial &rhs);
    Polynomial operator* (const Polynomial &rhs);
    Polynomial operator- (const Polynomial &rhs);
    Polynomial operator/ (const Polynomial &rhs);
    Polynomial operator% (const Polynomial &rhs);

    friend std::ostream &operator<< (std::ostream &out, const Polynomial &p);
};


#endif
