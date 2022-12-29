#include "Ratio.hpp"

Ratio::Ratio(const int &numerator, const uint &denominator)
{
    this->m_numerator=numerator;
    this->m_denominator=denominator;
    this->irreducible();
}

void Ratio::irreducible()
{
    uint pgcd = std::__detail::__gcd(uint(this->m_numerator),this->m_denominator);
    this->m_numerator=this->m_numerator/pgcd;
    this->m_denominator=this->m_denominator/pgcd;
}

Ratio Ratio::operator*(const Ratio &r) const
{
    int num = this->m_numerator * r.m_numerator;
    int den = this->m_denominator * r.m_denominator;
    if(num == den) { // integer found
        num = this->m_denominator;
        den = 1;
    }
    return Ratio(num, den);
}

Ratio Ratio::operator+(const Ratio &r) const
{
    int num = this->m_numerator * r.m_denominator + this->m_denominator * r.m_numerator;
    int den = this->m_denominator * r.m_denominator;
    if(num == den) { // integer found
        num = this->m_denominator;
        den = 1;
    }
    return Ratio(num, den);
}

Ratio Ratio::operator-(const Ratio &r) const
{
    int num = this->m_numerator * r.m_denominator - this->m_denominator * r.m_numerator;
    int den = this->m_denominator * r.m_denominator;
    if(num == den) { // integer found
        num = this->m_denominator;
        den = 1;
    }
    return Ratio(num, den);
}

std::ostream& operator<<(std::ostream& stream, const Ratio& r)
{
    stream << "(" << r.m_numerator << "/" << r.m_denominator << ")";
    return stream;
}
