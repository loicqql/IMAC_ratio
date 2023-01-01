#include <iostream>

#include "Ratio.hpp"


int main() {

    //contructors
    Ratio rat(3, 2);
	Ratio rat2(1, 2);

    //osstream
    std::cout << "ratio : " << rat << std::endl;

    //operator *
    std::cout << rat << " * " << rat2 << " = " << rat * rat2 << std::endl;

    //operator +
    std::cout << rat << " + " << rat2 << " = " << rat + rat2 << std::endl;

    //operator -
    std::cout << rat << " - " << rat2 << " = " << rat - rat2 << std::endl;

    Ratio rat5(2);
    std::cout << rat5 << std::endl;

    //floor et abs
    Ratio rat6(-1.5);
    std::cout << rat6 << std::endl;
    rat6=Ratio::floor(rat6);
    std::cout << rat6 << std::endl;
    rat6=Ratio::abs(rat6);
    std::cout << rat6 << std::endl;

    Ratio ratPow(2,5);
    ratPow=Ratio::pow<int>(ratPow,-2);
    std::cout << ratPow << std::endl;

    Ratio ratSqrt(9,25);
    ratSqrt=Ratio::sqrt(ratSqrt);
    std::cout << ratSqrt << std::endl;

    return 0;
}
