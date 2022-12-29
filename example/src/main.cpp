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

    return 0;
}
