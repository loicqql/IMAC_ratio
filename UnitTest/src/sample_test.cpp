#include <gtest/gtest.h>

#include <numeric>

#include "Ratio.hpp"


/////////////////////////////////////////////////////
// constructors

TEST (RatioConstructor, constructorByValueAndIrreducibility) { 
	Ratio rat(24, 2);
	uint pgcd=std::__detail::__gcd(uint(rat.numerator()),rat.denominator());
	ASSERT_EQ(pgcd, uint(1));
}