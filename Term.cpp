#include <ostream>
#include "Polynomial.hpp"

Term::Term (double coeff, int pow)
{
    coefficient = coeff;
    power = pow;
}
double Term::get_coefficient () const
{
    return coefficient ;
}
int Term::get_power () const
{
    return power;
}

//friend function.
std::ostream& operator<< (
    std::ostream & out,
    const Term & t )
{
    if (t.get_coefficient()!=0)
    {    if (t.get_power()==0)
        {
            out<<t.get_coefficient();
        }
        else
        {
            //output coefficient if not zero or one
            if (t.get_coefficient()!=1.0)
            {
                if (t.get_coefficient()==-1.0)
                {
                    //if it's -1, then just output negative
                    out<<"-";
                }
                else
                {
                    out<<t.get_coefficient();
                }
            }
            out<<"x";
            if(t.get_power()>1 || t.get_power()<0)
            {
                out<<"^"<<t.get_power();
            }
        }
    }
    return out;
}
