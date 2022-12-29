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

    // std::cout << rat << std::endl;

    Ratio rat5 = Ratio(1.5);
    std::cout << rat5 << std::endl;

    Ratio rat6 = Ratio(-1.5);
    std::cout << rat6 << std::endl;

    Ratio ratSin(M_PI,1);
    ratSin=Ratio::sin(ratSin);
    std::cout << ratSin << std::endl;

    return 0;
}
