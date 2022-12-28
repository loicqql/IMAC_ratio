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

/////////////////////////////////////////////////////
// operators
// operatorsInteger (the result is an integer)

/// multiplication

TEST (operators, multiplication) { 
	Ratio rat(5, 2);
	Ratio rat2(7, 3);
	Ratio res = rat * rat2;
	ASSERT_DOUBLE_EQ((double)res.numerator() / res.denominator(), (5.0/2.0) * (7.0/3.0));
}

TEST (operatorsInteger, multiplication) { 
	Ratio rat(3, 2);
	Ratio rat2(2, 0);
	Ratio res = rat * rat2;
	ASSERT_DOUBLE_EQ((double)res.numerator() / res.denominator(), 3.0);
}

/// addition

TEST (operators, addition) { 
	Ratio rat(5, 2);
	Ratio rat2(7, 3);
	Ratio res = rat + rat2;
	ASSERT_DOUBLE_EQ((double)res.numerator() / res.denominator(), (5.0/2.0) + (7.0/3.0));
}

TEST (operatorsInteger, addition) { 
	Ratio rat(7, 2);
	Ratio rat2(1, 2);
	Ratio res = rat + rat2;
	ASSERT_DOUBLE_EQ((double)res.numerator() / res.denominator(), 4.0);
}

/// subtraction

TEST (operators, subtraction) { 
	Ratio rat(5, 2);
	Ratio rat2(7, 3);
	Ratio res = rat - rat2;
	ASSERT_DOUBLE_EQ((double)res.numerator() / res.denominator(), (5.0/2.0) - (7.0/3.0));
}

TEST (operatorsInteger, subtraction) { 
	Ratio rat(3, 2);
	Ratio rat2(1, 2);
	Ratio res = rat - rat2;
	ASSERT_DOUBLE_EQ((double)res.numerator() / res.denominator(), 1.0);
}
