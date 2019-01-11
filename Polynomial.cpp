#include "Polynomial.hpp"
#include <iostream>
Polynomial::Polynomial () {}

void Polynomial::insert_term (Term term_to_insert)
{
    int pow = term_to_insert.get_power();
    bool added = false;
    for(int i=1; i<= terms.getLength(); i++)
    {
        // std::cout<<"Executing loop"<<std::endl;
        Term currTerm= terms.getEntry(i);
        if(pow == currTerm.get_power())
        {
            Term result(term_to_insert.get_coefficient() + currTerm.get_coefficient(), pow);
            //    std::cout<<"Replacing entry "<<i<<" with "<<result<<std::endl;
            if(result.get_coefficient()==0 && terms.getLength()>1)
            {
                terms.remove(i);
            }
            else
            {
                terms.replace(i, result);
            }
            added = true;
            break;
        }
        else if (pow> currTerm.get_power())
        {
            //if this term's power is greater, then add it in front
            //  std::cout<<"Inserting " <<term_to_insert<<" at "<< i<<std::endl;
            terms.insert(i, term_to_insert);
            added = true;
            break;
        }
    }
    if (!added)
    {
        //   std::cout<<"Inserting " <<term_to_insert<<" at end of list "<<std::endl;
        terms.insert(terms.getLength()+1, term_to_insert);
    }
}

Polynomial Polynomial::operator+ (const Polynomial &rhs)
{
    Polynomial result;
    for (int i=1; i<=terms.getLength(); i++)
    {
        result.insert_term(terms.getEntry(i));
    }
    for (int j=1; j<=rhs.terms.getLength(); j++)
    {
        Term otherTerm = rhs.terms.getEntry(j);
        result.insert_term(otherTerm);
    }
    return result;
}
Polynomial Polynomial::operator* (const Polynomial &rhs)
{
    Polynomial result;
    for (int i=1; i<=terms.getLength(); i++)
    {
        Term currTerm = terms.getEntry(i);
        for (int j=1; j<=rhs.terms.getLength(); j++)
        {
            Term otherTerm = rhs.terms.getEntry(j);
            Term res(currTerm.get_coefficient()*otherTerm.get_coefficient(), currTerm.get_power()+otherTerm.get_power());
            result.insert_term(res);
        }
    }
    return result;
}
Polynomial Polynomial::operator- (const Polynomial &rhs)
{
    Polynomial result;
    for (int i=1; i<=terms.getLength(); i++)
    {
        result.insert_term(terms.getEntry(i));
    }
    for (int j=1; j<=rhs.terms.getLength(); j++)
    {
        Term otherTerm = rhs.terms.getEntry(j);
        Term neg(otherTerm.get_coefficient()*-1, otherTerm.get_power());
        result.insert_term(neg);
    }
    return result;
}
Polynomial Polynomial::operator/ (const Polynomial &rhs)
{
    for (int i=1;i<=rhs.terms.getLength();i++)
    {
    if (rhs.terms.getEntry(i).get_power()<0)
    {
        for(int i=1;i<=terms.getLength();i++){
        std::cout<<terms.getEntry(i)<<std::endl;
        }
        std::cout<<" / "<<rhs<<std::endl;
        std::cout<<"\nError: Power was less then 0"<<std::endl;
        throw std::logic_error("Error: Power was less than 0");
    }
    }
    // the quotient
    Polynomial q;
    q.insert_term(Term());
    // std::cout<<"Q begun as "<<q<<std::endl;
    // the remainder
    Polynomial rem;
    for (int i=1; i<=terms.getLength(); i++)
    {
        rem.insert_term(terms.getEntry(i));
    }
    int count = 0;
    while (rem.terms.getEntry(1).get_coefficient()!=0  && rem.terms.getEntry(1).get_power()>=rhs.terms.getEntry(1).get_power())
    {
        Polynomial temp;
        Term leading = rem.terms.getEntry(1);
        Term otherlead = rhs.terms.getEntry(1);
        Term result(leading.get_coefficient()/otherlead.get_coefficient(),leading.get_power()-otherlead.get_power());
        temp.insert_term(result);
        q= q+temp;
        //std::cout<<"\nCount "<< count<<" Q: "<<q;
        rem= rem - (temp*rhs);
        //std::cout<<"rhs was "<<rhs<<std::endl;
        //std::cout<<"Temp*rhs: "<<temp*rhs<<std::endl;
       // std::cout<<"Rem " << rem<<std::endl;
        count++;
    }
    //std::cout<<"Polynomial q is "<<q<<std::endl;
    return q;
}

Polynomial Polynomial::operator% (const Polynomial &rhs)
{

    for (int i=1;i<=rhs.terms.getLength();i++)
    {
    if (rhs.terms.getEntry(i).get_power()<0)
    {for(int i=1;i<=terms.getLength();i++){
        std::cout<<terms.getEntry(i)<<std::endl;
        }
        std::cout<<" % "<<rhs<<std::endl;
        std::cout<<"\nError: Power was less then 0"<<std::endl;
        throw std::logic_error("Error: Power was less than 0");
    }
    }
    // the quotient
    Polynomial q;
    // the remainder
    q.insert_term(Term());
    Polynomial rem;
    for (int i=1; i<=terms.getLength(); i++)
    {
        rem.insert_term(terms.getEntry(i));
    }
    while (rem.terms.getEntry(1).get_coefficient()!=0 && rem.terms.getEntry(1).get_power()>=rhs.terms.getEntry(1).get_power())
    {
        Polynomial temp;
        Term leading = rem.terms.getEntry(1);
        Term otherlead = rhs.terms.getEntry(1);
        Term result(leading.get_coefficient()/otherlead.get_coefficient(),leading.get_power()-otherlead.get_power());
        temp.insert_term(result);
        q= q+temp;
        rem= rem - (temp*rhs);
    }

    return rem;
}

std::ostream &operator<< (std::ostream &out, const Polynomial &p)
{
    if (p.terms.getLength()==1)
    {
        out<<p.terms.getEntry(1);
        if (p.terms.getEntry(1).get_coefficient()==0)
        {
            out<<"0";
        }
        return out;
    }
    for (int i=1; i<=p.terms.getLength(); i++)
    {
        if (i>1 && p.terms.getEntry(i).get_coefficient()>0)
        {
            out<<"+";
        }
        out<<p.terms.getEntry(i);
    }
    if (p.terms.getLength()==0)
    {
        out<<"0";
    }
    return out;
}
