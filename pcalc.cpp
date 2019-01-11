#include <iostream>
#include <fstream>
#include <string>
#include "Polynomial.hpp"

using std::cout;
using std::endl;
void output(Polynomial &temp1, Polynomial &temp2, std::string op)
{
    std::cout<<temp1<<" "<<op<<" "<<temp2;
    if (op == "+")
    {
        std::cout<<" = "<<temp1+temp2<<std::endl;
    }
    else if (op=="-")
    {
        std::cout<<" = "<<temp1-temp2<<std::endl;
    }
    else if (op=="*")
    {
        std::cout<<" = "<<temp1*temp2<<std::endl;
    }
    else if (op=="/")
    {   Polynomial ans = temp1/temp2;
        std::cout<<" = "<<ans<<std::endl;
    }
    else if (op=="%")
    {    Polynomial ans = temp1%temp2;
        std::cout<<" = "<<ans<<std::endl;
    }
    Polynomial brandnew;
    temp1 = brandnew;
    temp2 = brandnew;
}
void addPolynomial(std::string &line, Polynomial &temp)
{
    int count = 0;
    //std::cout<<"Adding polynomial "<<std::endl;
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == ',')
        {
            count++;
        }
    }
    // the amount of commas is even, which is invalid
    if (count%2==0 && count!=0)
    {
        throw(std::logic_error("Error: Invalid polynomial"));
    }

    int coeff = 0;
    int power = 0;
    // std::cout<<"Before adding, poly was "<<temp<<std::endl;
    while(true)
    {
        std::size_t found = line.find(",");
        if (found!=std::string::npos)
        {
            //found coefficient
            coeff= std::stoi(line.substr(0, found));
            // std::cout<<"coeff was "<<coeff<<std::endl;
            line = line.substr(found+1);
        }

        std::size_t found2 = line.find(",");
        if (found2!=std::string::npos)
        {
            //found power
            power = std::stoi(line.substr(0, found2));
            temp.insert_term(Term(coeff, power));
            //  std::cout<<"Pow was "<<power<<std::endl;
            line = line.substr(found2+1);
        }
        else
        {
            //std::cout<<"Found last power. Coeff was "<<coeff<<std::endl;
            break;
        }
    }
    //line's last term is missed due the condition, and is the final power
    temp.insert_term(Term(coeff, std::stoi(line)));
}
int main( int argc, char* argv[] )
{
    if (argc!=2&& argc!=3&&argc!=4)
    {
        std::cout<<"Error: invalid amount of arguments.";
        return EXIT_FAILURE;
    }
    // std::cout<<"Executing main..."<<std::endl;
    std::fstream source;
    Polynomial temp1;
    Polynomial temp2;
    std::string op;
    // std::cout<<argc<<" arguments. "<<std::endl;
    if( argc ==2)
    {
        //in both 2/3, we must open the input file and add the polynomials
        std::string line;
        source.open(argv[1]);
        while (!source.eof())
        {
            std::getline(source, line, ' ');
            if (line.size()<=1)
            {
                break;
            }
            try
            {
                addPolynomial(line, temp1);
            }
            catch(std::logic_error())
            {
                std::cout<<"Error: error occurred"<<std::endl;
                return EXIT_FAILURE;
            }
            // read operation
            std::getline(source, op, ' ');
            // read other polynomial;
            std::getline(source, line, '\n');
            try
            {
                addPolynomial(line, temp2);
            }
            catch(std::logic_error())
            {
               std::cout<<"Error: error occurred"<<std::endl;
                return EXIT_FAILURE;
            }
            try
            {
                output(temp1, temp2, op);
            }
            catch(std::logic_error())
            {
               std::cout<<"\nError: error occurred"<<std::endl;
                return EXIT_FAILURE;
            }
        }

        return EXIT_SUCCESS;
        // std::cout<<"Got out of the loop."<<std::endl;
    }
    if (argc==3)
        {
            // std::cout<<"There were two arguments."<<std::endl;
            //open output
        std::string line;
        source.open(argv[1]);
            std::streambuf *backup;
            std::ofstream out(argv[2]);
            out.open(argv[2]);
            backup = std::cout.rdbuf();     // back up cout's streambuf
            std::cout.rdbuf(out.rdbuf());  //redirect cout to go to file
              while (!source.eof())
        {   std::getline(source, line, ' ');
            if (line.size()<=1)
            {
                break;
            }
            try
            {
                addPolynomial(line, temp1);
            }
            catch(std::logic_error())
            {
               std::cout<<"Error: error occurred"<<std::endl;
                return EXIT_FAILURE;
            }
            // read operation
            std::getline(source, op, ' ');
            // read other polynomial;
            std::getline(source, line, '\n');
            try
            {
                addPolynomial(line, temp2);
            }
            catch(std::logic_error())
            {
               std::cout<<"Error: error occurred"<<std::endl;
                return EXIT_FAILURE;
            }
            try
            {
                output(temp1, temp2, op);
            }
            catch(std::logic_error())
            {
               std::cout<<"\nError: error occurred"<<std::endl;
                return EXIT_FAILURE;
            }
        }
            return EXIT_SUCCESS;
        }

    if(argc==4)
    {
        //std::cout<<"There were three arguments."<<std::endl;
        //polynomial, operation, polynomial
        //represented in coeff, pow, coef, pow, etc.
        std::string str(argv[1]);
        op = argv[2];
        std::string str2(argv[3]);
        try
        {
            addPolynomial(str, temp1);
        }
        catch(std::logic_error())
        {
             std::cout<<"Error: error occurred"<<std::endl;
            return EXIT_FAILURE;
        }
        try
        {
            addPolynomial(str2, temp2);
        }
        catch(std::logic_error())
        {
             std::cout<<"Error: error occurred"<<std::endl;
            return EXIT_FAILURE;
        }
        try
        {
            output(temp1, temp2, op);
        }
        catch(std::logic_error())
        {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }
}
