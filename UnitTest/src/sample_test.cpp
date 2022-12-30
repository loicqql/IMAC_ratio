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

TEST (RatioConstructor, constructorWithReal) { 
	Ratio rat((double)1.5);
	ASSERT_DOUBLE_EQ((double)rat.numerator() / rat.denominator(), 1.5);

	Ratio rat2((float)3.5);
	ASSERT_FLOAT_EQ((float)rat2.numerator() / rat2.denominator(), 3.5);

	Ratio rat3(2);
	ASSERT_FLOAT_EQ(rat3.numerator() / rat3.denominator(), 2);
}

/////////////////////////////////////////////////////
// transformation

/// irreducible
TEST (transformation, irreducible) { 
	Ratio rat(6, 4);
	ASSERT_EQ((double)rat.numerator() / rat.denominator(), 3.0/2);
}

/// inverse
TEST (transformation, inverse) { 
	Ratio rat(3, 2);
	rat.inverse();
	ASSERT_EQ((double)rat.numerator() / rat.denominator(), 2.0/3);
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
	Ratio rat2(2, 1);
	Ratio res = rat * rat2;
	ASSERT_DOUBLE_EQ((double)res.numerator() / res.denominator(), 3.0);
}

/// division

TEST (operators, division) { 
	Ratio rat(5, 2);
	Ratio rat2(7, 3);
	Ratio res = rat / rat2;
	ASSERT_DOUBLE_EQ((double)res.numerator() / res.denominator(), (5.0/2.0) / (7.0/3.0));
}

TEST (operatorsInteger, division) { 
	Ratio rat(3, 2);
	Ratio rat2(1, 2);
	Ratio res = rat / rat2;
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
	ASSERT_NEAR((double)res.numerator() / res.denominator(), (5.0/2.0) - (7.0/3.0), 0.001);
}

TEST (operatorsInteger, subtraction) { 
	Ratio rat(3, 2);
	Ratio rat2(1, 2);
	Ratio res = rat - rat2;
	ASSERT_DOUBLE_EQ((double)res.numerator() / res.denominator(), 1.0);
}

/// copy assignment

TEST (operators, assignment) { 
	Ratio rat(5, 2);
	Ratio rat2 = rat;
	ASSERT_EQ(rat.numerator(), rat2.numerator());
	ASSERT_EQ(rat.denominator(), rat2.denominator());
}

/// multiplication with number

TEST (operators, multiplicationWnumber) { 
	Ratio rat(5, 2);
	rat = rat * 2.5; 
	ASSERT_DOUBLE_EQ((double)rat.numerator() / rat.denominator(), 5.0/2.0 * 2.5);
}

/// division with number

TEST (operators, divisionWnumber) { 
	Ratio rat(5, 2);
	rat = rat / 2.5; 
	ASSERT_DOUBLE_EQ((double)rat.numerator() / rat.denominator(), 5.0/2.0 / 2.5);
}

/// addition with number

TEST (operators, additionWnumber) { 
	Ratio rat(5, 2);
	rat = rat + 2.5; 
	ASSERT_DOUBLE_EQ((double)rat.numerator() / rat.denominator(), 5.0/2.0 + 2.5);
}

/// subtraction with number

TEST (operators, subtractionWnumber) { 
	Ratio rat(5, 2);
	rat = rat - 2.5; 
	ASSERT_DOUBLE_EQ((double)rat.numerator() / rat.denominator(), 5.0/2.0 - 2.5);
}

/// unary minus

TEST (operators, unary_minus) { 
	Ratio rat(5, 2);
	rat = -rat;
	ASSERT_DOUBLE_EQ((double)rat.numerator() / rat.denominator(), -5.0/2.0);
}

/////////////////////////////////////////////////////
// comparison functions

TEST (comparison, less_or_equal) { 
	Ratio rat(3, 2);
	Ratio rat2(1, 2);
	ASSERT_EQ(rat <= rat2, false);

	rat2 = rat2 + 1;
	ASSERT_EQ(rat <= rat2, true);
}

TEST (comparison, greater_or_equal) { 
	Ratio rat(1, 2);
	Ratio rat2(3, 2);
	ASSERT_EQ(rat >= rat2, false);

	rat = rat + 1;
	ASSERT_EQ(rat >= rat2, true);
}

TEST (comparison, less) { 
	Ratio rat(3, 2);
	Ratio rat2(1, 2);
	ASSERT_EQ(rat < rat2, false);

	rat2 = rat2 + 1;
	ASSERT_EQ(rat < rat2, false);
}

TEST (comparison, greater) { 
	Ratio rat(1, 2);
	Ratio rat2(3, 2);
	ASSERT_EQ(rat > rat2, false);

	rat = rat + 1;
	ASSERT_EQ(rat > rat2, false);
}

TEST (comparison, equal) { 
	Ratio rat(1, 2);
	Ratio rat2(3, 2);
	ASSERT_EQ(rat == rat2, false);

	rat = rat + 1;
	ASSERT_EQ(rat == rat2, true);
}

TEST (comparison, not_equal) { 
	Ratio rat(1, 2);
	Ratio rat2(3, 2);
	ASSERT_EQ(rat != rat2, true);

	rat = rat + 1;
	ASSERT_EQ(rat != rat2, false);
}

/////////////////////////////////////////////////////
// mathematical functions

/// abs

TEST (math_functions, abs) { 
	Ratio rat(-5, 2);
	rat = abs(rat);
	ASSERT_DOUBLE_EQ((double)rat.numerator() / rat.denominator(), 5.0/2.0);
}

/// floor

TEST (math_functions, floor) { 
	Ratio rat(5, 2);
	rat = floor(rat);
	ASSERT_DOUBLE_EQ((double)rat.numerator() / rat.denominator(), 2.0);
}

/// sin

TEST (math_functions, sin) { 
	Ratio rat(M_PI);
	rat = sin(rat);
	ASSERT_NEAR((double)rat.numerator() / rat.denominator(), std::sin(M_PI), 0.1);
}

/// cos

TEST (math_functions, cos) { 
	Ratio rat(M_PI);
	rat = cos(rat);
	ASSERT_NEAR((double)rat.numerator() / rat.denominator(), std::cos(M_PI), 0.1);
}

/// tan

TEST (math_functions, tan) { 
	Ratio rat(M_PI);
	rat = tan(rat);
	ASSERT_NEAR((double)rat.numerator() / rat.denominator(), std::tan(M_PI), 0.1);
}

/// exp

TEST (math_functions, exp) { 
	Ratio rat(5,2);
	rat = exp(rat);
	ASSERT_NEAR((double)rat.numerator() / rat.denominator(), std::exp(5.0/2.0), 0.1);
}

/// log

TEST (math_functions, log) { 
	Ratio rat(5,2);
	rat = log(rat);
	ASSERT_NEAR((double)rat.numerator() / rat.denominator(), std::log(5.0/2.0), 0.1);
}

/// sqrt

TEST (math_functions, sqrt) { 
	Ratio rat(5,2);
	rat = sqrt(rat);
	ASSERT_NEAR((double)rat.numerator() / rat.denominator(), std::sqrt(5.0/2.0), 0.1);
}