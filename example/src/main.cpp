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

    Ratio rat5 = Ratio(0.14112);
    std::cout << rat5 << std::endl;

    Ratio rat6 = Ratio(-1.5);
    std::cout << rat6 << std::endl;
    rat6=Ratio::floor(rat6);
    std::cout << rat6 << std::endl;
    rat6=Ratio::abs(rat6);
    std::cout << rat6 << std::endl;

    return 0;
}
