#include <gtest/gtest.h>

#include "Ratio.hpp"


/////////////////////////////////////////////////////
// constructors

TEST (RatioConstructor, defaultConstructor) { 
	Ratio<int> rat(5, 6);
	// ASSERT_EQ (vec.size(), 0);
}