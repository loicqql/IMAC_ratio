#include <iostream>
#include <numeric>
#include <cassert>
#include <math.h>

#include "Ratio.hpp"

using namespace rto;

// Ratio's functions

Ratio::Ratio(const int &numerator, const uint &denominator)
{
    this->m_numerator=numerator;
    this->m_denominator=denominator;
    this->irreducible();
}

void Ratio::irreducible()
{
    uint pgcd = std::__detail::__gcd(uint(this->m_numerator),this->m_denominator);
    this->m_numerator=this->m_numerator/int(pgcd);
    this->m_denominator=this->m_denominator/pgcd;
}

void Ratio::inverse()
{   
    int sign=1;
    if (this->m_numerator<0)
    {
        sign=-1; 
    }
    uint temp=uint(sign*this->m_numerator);
    this->m_numerator=sign*int(this->m_denominator);
    this->m_denominator=temp;
}

void Ratio::operator=(const Ratio &r)
{
    this->m_numerator=r.m_numerator;
    this->m_denominator=r.m_denominator;
}

Ratio Ratio::operator*(const Ratio &r) const
{
    int num = this->m_numerator * r.m_numerator;
    int den = this->m_denominator * r.m_denominator;
    return Ratio(num, den);
}

Ratio Ratio::operator+(const Ratio &r) const
{
    int num = this->m_numerator * r.m_denominator + this->m_denominator * r.m_numerator;
    int den = this->m_denominator * r.m_denominator;
    return Ratio(num, den);
}

Ratio Ratio::operator-(const Ratio &r) const
{
    int num = this->m_numerator * r.m_denominator - this->m_denominator * r.m_numerator;
    int den = this->m_denominator * r.m_denominator;
    return Ratio(num, den);
}

Ratio Ratio::operator/(Ratio rat) const 
{
    assert(rat.m_numerator!=0 && "Can't divide by 0"); 
    rat.inverse();
    return *this*rat;
}

//comparison operators

bool Ratio::operator<=(const Ratio& rat) const
{
    return (this->m_numerator / this->m_denominator) <= (rat.m_numerator / rat.m_denominator);
}

bool Ratio::operator>=(const Ratio& rat) const
{
    return (this->m_numerator / this->m_denominator) >= (rat.m_numerator / rat.m_denominator);
}

bool Ratio::operator<(const Ratio& rat) const
{
    return (this->m_numerator / this->m_denominator) < (rat.m_numerator / rat.m_denominator);
}

bool Ratio::operator>(const Ratio& rat) const
{
    return (this->m_numerator / this->m_denominator) > (rat.m_numerator / rat.m_denominator);
}

bool Ratio::operator==(const Ratio& rat) const
{
    return (this->m_numerator == rat.m_numerator) && (this->m_denominator == rat.m_denominator);
}

bool Ratio::operator!=(const Ratio& rat) const
{
    return (this->m_numerator / this->m_denominator) != (rat.m_numerator / rat.m_denominator);
}