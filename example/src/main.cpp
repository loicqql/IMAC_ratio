/*
 ________   ________   _________   ___   ________     
|\   __  \ |\   __  \ |\___   ___\|\  \ |\   __  \    
\ \  \|\  \\ \  \|\  \\|___ \  \_|\ \  \\ \  \|\  \   
 \ \   _  _\\ \   __  \    \ \  \  \ \  \\ \  \\\  \  
  \ \  \\  \|\ \  \ \  \    \ \  \  \ \  \\ \  \\\  \ 
   \ \__\\ _\ \ \__\ \__\    \ \__\  \ \__\\ \_______\
    \|__|\|__| \|__|\|__|     \|__|   \|__| \|_______|

*/ 

#include <iostream>

#include "Ratio.hpp"

using namespace rto;

//https://stackoverflow.com/questions/29997096/bold-output-in-c
class bold {
    std::string_view const &s;
public:
    bold(std::string_view const &s) : s(s) {}

    friend std::ostream &operator<<(std::ostream &os, bold const &b) {
        os << "\x1b[7m" << b.s << "\x1b[0m";
        return os;
    }
};

void title();


int main()
{

    title();

    std::cout << "\x1b[1m" << bold("--EXAMPLES--") << std::endl << std::endl;

    /////////////////////////////////////////////////////
    // constructors
    {
        std::cout << bold("-constructors") << std::endl;
        std::cout << "Ratio rat(1,2) = " << Ratio(1,2) << std::endl;
        std::cout << "Ratio rat(3.5) = " << Ratio(3.5) << std::endl;
        std::cout << "Ratio rat(4) = " << Ratio(4) << std::endl;
        std::cout << std::endl;
    }

    /////////////////////////////////////////////////////
    // inverse
    {
        std::cout << bold("-inverse") << std::endl;
        Ratio rat(1,2);
        rat.inverse();
        std::cout << "Ratio rat(1,2)" << std::endl;
        std::cout << "rat.inverse() = " << rat << std::endl;
        std::cout << std::endl;
    }

    /////////////////////////////////////////////////////
    // operators
    {
        std::cout << bold("-operators") << std::endl;
        Ratio rat(0.5);
        Ratio rat2(3.5);
        std::cout << "Ratio rat(0.5)" << std::endl;
        std::cout << "Ratio rat2(3.5)" << std::endl;
        std::cout << "rat + rat2 = " << rat + rat2 << std::endl;
        std::cout << "rat - rat2 = " << rat - rat2 << std::endl;
        std::cout << "rat * rat2 = " << rat * rat2 << std::endl;
        std::cout << "rat / rat2 = " << rat / rat2 << std::endl;
        std::cout << std::endl;
    }

    /////////////////////////////////////////////////////
    // copy assignment
    {
        std::cout << bold("-copy assignment") << std::endl;
        Ratio rat(0.5);
        Ratio rat2 = rat;
        std::cout << "Ratio rat(0.5)" << std::endl;
        std::cout << "Ratio rat2 = rat" << std::endl;
        std::cout << "rat2 = " << rat2 << std::endl;
        std::cout << std::endl;
    }

    /////////////////////////////////////////////////////
    // operations with number
    {
        std::cout << bold("-operations with number") << std::endl;
        Ratio rat(0.5);
        std::cout << "Ratio rat(0.5)" << std::endl;
        std::cout << "rat + 2 = " << rat + 2 << std::endl;
        std::cout << "rat - 2 = " << rat - 2 << std::endl;
        std::cout << "rat * 2 = " << rat * 2 << std::endl;
        std::cout << "rat / 2 = " << rat / 2 << std::endl;
        std::cout << std::endl;
    }

    /////////////////////////////////////////////////////
    // unary minus
    {
        std::cout << bold("-unary minus") << std::endl;
        Ratio rat(0.5);
        std::cout << "Ratio rat(0.5)" << std::endl;
        std::cout << "-rat = " << -rat<< std::endl;
        std::cout << std::endl;
    }

    /////////////////////////////////////////////////////
    // comparison functions
    {
        std::cout << bold("-comparison functions") << std::endl;
        Ratio rat(0.5);
        Ratio rat2(2.5);
        std::cout << "Ratio rat(0.5)" << std::endl;
        std::cout << "Ratio rat2(2.5)" << std::endl;
        std::cout << "rat < rat2 = " << (rat < rat2 ? "true" : "false") << std::endl;
        std::cout << "rat > rat2 = " << (rat > rat2 ? "true" : "false") << std::endl;
        std::cout << "rat <= rat2 = " << (rat <= rat2 ? "true" : "false") << std::endl;
        std::cout << "rat >= rat2 = " << (rat >= rat2 ? "true" : "false") << std::endl;
        std::cout << "rat == rat2 = " << (rat == rat2 ? "true" : "false") << std::endl;
        std::cout << "rat != rat2 = " << (rat != rat2 ? "true" : "false") << std::endl;
        std::cout << std::endl;
    }                                                                               

    /////////////////////////////////////////////////////
    // mathematical functions
    {
        std::cout << bold("-mathematical functions") << std::endl;
        Ratio rat(0.5);
        std::cout << "Ratio rat(0.5)" << std::endl;
        std::cout << "Ratio::abs(-rat) = " << abs(-rat) << std::endl;
        std::cout << "Ratio::floor(rat) = " << floor(rat) << std::endl;
        std::cout << "Ratio::sin(rat) = " << sin(rat) << " = " << (double)sin(rat).numerator() /  sin(rat).denominator() << " (not recommended)" << std::endl;
        std::cout << "Ratio::cos(rat) = " << cos(rat) << " = " << (double)cos(rat).numerator() /  cos(rat).denominator() << " (not recommended)" << std::endl;
        std::cout << "Ratio::tan(rat) = " << tan(rat) << " = " << (double)tan(rat).numerator() /  tan(rat).denominator() << " (not recommended)" << std::endl;
        std::cout << "Ratio::log(rat) = " << log(rat) << " = " << (double)log(rat).numerator() /  log(rat).denominator() << " (not recommended)" << std::endl;
        std::cout << "Ratio::sqrt(rat) = " << sqrt(rat) << std::endl;
        std::cout << std::endl;
    }

    return 0;
}

void title()
{
    printf(R"EOF(
 ________   ________   _________   ___   ________     
|\   __  \ |\   __  \ |\___   ___\|\  \ |\   __  \    
\ \  \|\  \\ \  \|\  \\|___ \  \_|\ \  \\ \  \|\  \   
 \ \   _  _\\ \   __  \    \ \  \  \ \  \\ \  \\\  \  
  \ \  \\  \|\ \  \ \  \    \ \  \  \ \  \\ \  \\\  \ 
   \ \__\\ _\ \ \__\ \__\    \ \__\  \ \__\\ \_______\
    \|__|\|__| \|__|\|__|     \|__|   \|__| \|_______|
    )EOF");

    std::cout << std::endl << std::endl;
}


//00101000 11001011 10110101 00100000 11001101 10100001 11000010 10110000 00100000 11001101 10011100 11001010 10010110 00100000 11001101 10100001 11000010 10110000 11001011 10110101 00101001