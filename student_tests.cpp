#define CATCH_CONFIG_MAIN

#include "Polynomial.hpp"
#include "catch.hpp"
#include <sstream>

TEST_CASE("tougher cases")
{
    Polynomial threex;
    threex.insert_term(Term(3,2));
    Polynomial twox;
    twox.insert_term(Term(-2,2));
    std::cout<<"3x^2 + -2x^2 = " <<threex+twox<<std::endl;

    Polynomial x4;
    x4.insert_term(Term(1,4));
    x4.insert_term(Term(1,2));
    Polynomial x2;
    x2.insert_term(Term(1,2));
    std::cout<<x4<<" - "<<x2<<" = "<<x4-x2<<std::endl;

    Polynomial longLeft;
    longLeft.insert_term(Term(5,3));
    longLeft.insert_term(Term(-7,2));
    longLeft.insert_term(Term(3,1));
    longLeft.insert_term(Term(-4,0));
    Polynomial longRight;
    longRight.insert_term(Term(8,3));
    longRight.insert_term(Term(2,2));
    longRight.insert_term(Term(3,1));
    longRight.insert_term(Term(-7,0));
    std::cout<<longLeft<<" - "<<longRight << " = "<<longLeft-longRight<<std::endl;
}

TEST_CASE("Polynomial testing")
{

    Polynomial zero;
    zero.insert_term(Term());
    Polynomial xsquared;
    xsquared.insert_term(Term(1,2));

    //std::cout<<xsquared<<std::endl;
    Polynomial x;
    x.insert_term(Term(1,1));
    std::cout<<x<<std::endl;
    Polynomial x3;
    x3.insert_term(Term(1,3));
    Polynomial x4;
    x4.insert_term(Term(1,4));
    Polynomial threex;
    threex.insert_term(Term(3,1));
    //x4.insert_term(Term(2,2));
    //std::cout<<"x Polynomial: "<<x<<std::endl;
    // zero = zero + x;
    //std::cout<<"After adding x to 0, it became "<<zero<<std::endl;

    //std::cout<<"x*x = "<<x*x<<std::endl;
    std::cout<<xsquared<< " + "<<x<<" = " << x+xsquared<<std::endl;
    std::cout<<xsquared<< " - "<<x<<" = " << xsquared-x<<std::endl;
    std::cout<<xsquared<< " - "<<x4<<" - "<<x3 <<" = "<<xsquared-x4-x3<<std::endl;
    std::cout<<x<<" - "<< threex<<" = "<<x-threex<<std::endl;
    std::cout<<xsquared<<" / "<<x << " = " << xsquared/x<<std::endl;
    std::cout<<x<<" - "<<xsquared<<" = "<<x-xsquared<<std::endl;
    std::cout<<zero<<" - "<<x<<" = "<<zero-x<<std::endl;
    std::cout<<x<<" - "<<zero<<" = "<<x-zero<<std::endl;

    REQUIRE(1==1);
}


TEST_CASE("Testing using stringstream", "[Polynomial]")
{

    std::stringstream output_checker = std::stringstream();
    Polynomial poly;
    poly.insert_term(Term(2, 3));

    output_checker << poly;
    REQUIRE(output_checker.str() == "2x^3");

    output_checker = std::stringstream();

    Polynomial xsquared;
    xsquared.insert_term(Term(1,2));
    Polynomial xsquared2;
    xsquared2.insert_term(Term(2,2));
    output_checker <<xsquared - xsquared2;
    REQUIRE(output_checker.str() == "-x^2");

    output_checker = std::stringstream();
}

