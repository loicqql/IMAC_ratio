#include <gtest/gtest.h>

#include <numeric>

#include "Ratio.hpp"


/////////////////////////////////////////////////////
// constructors

TEST (RatioConstructor, constructorByValueAndIrreducibility)
{ 
	rto::Ratio rat(24, 2);
	uint pgcd=std::__detail::__gcd(uint(rat.numerator()),rat.denominator());
	ASSERT_EQ(pgcd, uint(1));
}

TEST (RatioConstructor, constructorWithReal)
{ 
	rto::Ratio rat((double)1.5);
	ASSERT_DOUBLE_EQ((double)rat.numerator() / rat.denominator(), 1.5);

	rto::Ratio rat2((float)3.5);
	ASSERT_FLOAT_EQ((float)rat2.numerator() / rat2.denominator(), 3.5);

	rto::Ratio rat3(2);
	ASSERT_FLOAT_EQ(rat3.numerator() / rat3.denominator(), 2);
}

/////////////////////////////////////////////////////
// transformation

/// irreducible
TEST (transformation, irreducible)
{ 
	rto::Ratio rat(6, 4);
	ASSERT_EQ((double)rat.numerator() / rat.denominator(), 3.0/2);
}

/// inverse
TEST (transformation, inverse)
{ 
	rto::Ratio rat(3, 2);
	rat.inverse();
	ASSERT_EQ((double)rat.numerator() / rat.denominator(), 2.0/3);
}

/////////////////////////////////////////////////////
// operators
// operatorsInteger (the result is an integer)

/// multiplication

TEST (operators, multiplication)
{ 
	rto::Ratio rat(5, 2);
	rto::Ratio rat2(7, 3);
	rto::Ratio res = rat * rat2;
	ASSERT_DOUBLE_EQ((double)res.numerator() / res.denominator(), (5.0/2.0) * (7.0/3.0));
}

TEST (operatorsInteger, multiplication)
{ 
	rto::Ratio rat(3, 2);
	rto::Ratio rat2(2, 1);
	rto::Ratio res = rat * rat2;
	ASSERT_DOUBLE_EQ((double)res.numerator() / res.denominator(), 3.0);
}

/// division

TEST (operators, division)
{ 
	rto::Ratio rat(5, 2);
	rto::Ratio rat2(7, 3);
	rto::Ratio res = rat / rat2;
	ASSERT_DOUBLE_EQ((double)res.numerator() / res.denominator(), (5.0/2.0) / (7.0/3.0));
}

TEST (operatorsInteger, division)
{ 
	rto::Ratio rat(3, 2);
	rto::Ratio rat2(1, 2);
	rto::Ratio res = rat / rat2;
	ASSERT_DOUBLE_EQ((double)res.numerator() / res.denominator(), 3.0);
}

/// addition

TEST (operators, addition)
{ 
	rto::Ratio rat(5, 2);
	rto::Ratio rat2(7, 3);
	rto::Ratio res = rat + rat2;
	ASSERT_DOUBLE_EQ((double)res.numerator() / res.denominator(), (5.0/2.0) + (7.0/3.0));
}

TEST (operatorsInteger, addition)
{ 
	rto::Ratio rat(7, 2);
	rto::Ratio rat2(1, 2);
	rto::Ratio res = rat + rat2;
	ASSERT_DOUBLE_EQ((double)res.numerator() / res.denominator(), 4.0);
}

/// subtraction

TEST (operators, subtraction)
{ 
	rto::Ratio rat(5, 2);
	rto::Ratio rat2(7, 3);
	rto::Ratio res = rat - rat2;
	ASSERT_NEAR((double)res.numerator() / res.denominator(), (5.0/2.0) - (7.0/3.0), 0.001);
}

TEST (operatorsInteger, subtraction)
{ 
	rto::Ratio rat(3, 2);
	rto::Ratio rat2(1, 2);
	rto::Ratio res = rat - rat2;
	ASSERT_DOUBLE_EQ((double)res.numerator() / res.denominator(), 1.0);
}

/// copy assignment

TEST (operators, assignment)
{ 
	rto::Ratio rat(5, 2);
	rto::Ratio rat2 = rat;
	ASSERT_EQ(rat.numerator(), rat2.numerator());
	ASSERT_EQ(rat.denominator(), rat2.denominator());
}

/// multiplication with number

TEST (operators, multiplicationWnumber)
{ 
	rto::Ratio rat(5, 2);
	rat = rat * 2.5; 
	ASSERT_DOUBLE_EQ((double)rat.numerator() / rat.denominator(), 5.0/2.0 * 2.5);
}

/// division with number

TEST (operators, divisionWnumber)
{ 
	rto::Ratio rat(5, 2);
	rat = rat / 2.5; 
	ASSERT_DOUBLE_EQ((double)rat.numerator() / rat.denominator(), 5.0/2.0 / 2.5);
}

/// addition with number

TEST (operators, additionWnumber)
{ 
	rto::Ratio rat(5, 2);
	rat = rat + 2.5; 
	ASSERT_DOUBLE_EQ((double)rat.numerator() / rat.denominator(), 5.0/2.0 + 2.5);
}

/// subtraction with number

TEST (operators, subtractionWnumber)
{ 
	rto::Ratio rat(5, 2);
	rat = rat - 2.5; 
	ASSERT_DOUBLE_EQ((double)rat.numerator() / rat.denominator(), 5.0/2.0 - 2.5);
}

/// unary minus

TEST (operators, unary_minus)
{ 
	rto::Ratio rat(5, 2);
	rat = -rat;
	ASSERT_DOUBLE_EQ((double)rat.numerator() / rat.denominator(), -5.0/2.0);
}

/////////////////////////////////////////////////////
// comparison functions

/// less_or_equal

TEST (comparison, less_or_equal)
{ 
	rto::Ratio rat(3, 2);
	rto::Ratio rat2(1, 2);
	ASSERT_EQ(rat <= rat2, false);

	rat2 = rat2 + 1;
	ASSERT_EQ(rat <= rat2, true);
}

/// greater_or_equal

TEST (comparison, greater_or_equal)
{ 
	rto::Ratio rat(1, 2);
	rto::Ratio rat2(3, 2);
	ASSERT_EQ(rat >= rat2, false);

	rat = rat + 1;
	ASSERT_EQ(rat >= rat2, true);
}

/// less

TEST (comparison, less)
{ 
	rto::Ratio rat(3, 2);
	rto::Ratio rat2(1, 2);
	ASSERT_EQ(rat < rat2, false);

	rat2 = rat2 + 1;
	ASSERT_EQ(rat < rat2, false);
}

/// greater

TEST (comparison, greater)
{ 
	rto::Ratio rat(1, 2);
	rto::Ratio rat2(3, 2);
	ASSERT_EQ(rat > rat2, false);

	rat = rat + 1;
	ASSERT_EQ(rat > rat2, false);
}

/// equal

TEST (comparison, equal)
{ 
	rto::Ratio rat(1, 2);
	rto::Ratio rat2(3, 2);
	ASSERT_EQ(rat == rat2, false);

	rat = rat + 1;
	ASSERT_EQ(rat == rat2, true);
}

/// not_equal

TEST (comparison, not_equal)
{ 
	rto::Ratio rat(1, 2);
	rto::Ratio rat2(3, 2);
	ASSERT_EQ(rat != rat2, true);

	rat = rat + 1;
	ASSERT_EQ(rat != rat2, false);
}

/////////////////////////////////////////////////////
// mathematical functions

/// abs

TEST (math_functions, abs)
{ 
	rto::Ratio rat(-5, 2);
	rat = abs(rat);
	ASSERT_DOUBLE_EQ((double)rat.numerator() / rat.denominator(), 5.0/2.0);
}

/// floor

TEST (math_functions, floor)
{ 
	rto::Ratio rat(5, 2);
	rat = floor(rat);
	ASSERT_DOUBLE_EQ((double)rat.numerator() / rat.denominator(), 2.0);
}

/// sin

TEST (math_functions, sin)
{ 
	rto::Ratio rat(M_PI);
	rat = sin(rat);
	ASSERT_NEAR((double)rat.numerator() / rat.denominator(), std::sin(M_PI), 0.1);
}

/// cos

TEST (math_functions, cos)
{ 
	rto::Ratio rat(M_PI);
	rat = cos(rat);
	ASSERT_NEAR((double)rat.numerator() / rat.denominator(), std::cos(M_PI), 0.1);
}

/// tan

TEST (math_functions, tan)
{ 
	rto::Ratio rat(M_PI);
	rat = tan(rat);
	ASSERT_NEAR((double)rat.numerator() / rat.denominator(), std::tan(M_PI), 0.1);
}

/// exp

TEST (math_functions, exp)
{ 
	rto::Ratio rat(5,2);
	rat = exp(rat);
	ASSERT_NEAR((double)rat.numerator() / rat.denominator(), std::exp(5.0/2.0), 0.1);
}

/// log

TEST (math_functions, log)
{ 
	rto::Ratio rat(5,2);
	rat = log(rat);
	ASSERT_NEAR((double)rat.numerator() / rat.denominator(), std::log(5.0/2.0), 0.1);
}

/// sqrt

TEST (math_functions, sqrt)
{ 
	rto::Ratio rat(5,2);
	rat = sqrt(rat);
	ASSERT_NEAR((double)rat.numerator() / rat.denominator(), std::sqrt(5.0/2.0), 0.1);
}