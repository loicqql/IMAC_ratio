#include <iostream>
#include <numeric>
#include <cassert>
#include <math.h>

#include "Ratio.hpp"

std::ostream& operator<<(std::ostream& stream, const Ratio& r)
{
    stream << "(" << r.m_numerator << "/" << r.m_denominator << ")";
    return stream;
}

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

//mathematical fonctions

Ratio abs(const Ratio & rat)
{
    return Ratio(std::abs(rat.m_numerator),rat.m_denominator);
}

Ratio floor(const Ratio & rat)
{
    return Ratio(rat.m_numerator-rat.m_numerator%int(rat.m_denominator),rat.m_denominator);
}

//optionnal
Ratio sin(const Ratio & rat)
{
    double value=std::sin(double(rat.m_numerator)/double(rat.m_denominator));
    Ratio result(value);
    return result;
}

Ratio cos(const Ratio & rat)
{
    double value=std::cos(double(rat.m_numerator)/double(rat.m_denominator));
    Ratio result(value);
    return result;
}

Ratio tan(const Ratio & rat)
{
    return sin(rat)/cos(rat);
}

Ratio exp(const Ratio & rat)
{
    double value=std::exp(rat.m_numerator/rat.m_denominator);
    return Ratio(value);
}

Ratio log(const Ratio & rat)
{
    return Ratio(std::log(double(rat.m_numerator))-std::log(double(rat.m_denominator)));
}

Ratio sqrt(const Ratio & rat)
{
    return Ratio(std::sqrt(rat.m_numerator),std::sqrt(rat.m_denominator));
}
