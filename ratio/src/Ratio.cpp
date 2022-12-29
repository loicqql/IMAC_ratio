#include <iostream>
#include <numeric>
#include <cassert>
#include <math.h>

#include "Ratio.hpp"

// Utilities 
Ratio convertRealToRatio(double real, uint nb_iter)
{
    //1st stopping condition : return 0/1
    if(real==0){return Ratio();}

    //2nd stopping condition : return 0/1
    if(nb_iter==0){return Ratio();}

    //case |real|<1
    if(real<1)
    {
        Ratio rat=convertRealToRatio(1/real,nb_iter);
        rat.inverse();
        return rat;
    }

    //case |real|>=1
    else
    {
        int q=floor(real);
        return (Ratio(q,1) + convertRealToRatio(real-q, nb_iter-1));
    }
}

std::ostream& operator<<(std::ostream& stream, const Ratio& r)
{
    stream << "(" << r.m_numerator << "/" << r.m_denominator << ")";
    return stream;
}


// Ratio's functions

Ratio::Ratio(const double &real)
{
    uint nb_iter=100;
    int sign = real < 0 ? -1 : 1;
    *this = Ratio(sign,1) * convertRealToRatio(std::abs(real),nb_iter);
    this->irreducible();
}

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

//mathematical fonctions

Ratio Ratio::abs(const Ratio & rat){
    return Ratio(std::abs(rat.m_numerator),rat.m_denominator);
}

Ratio Ratio::floor(const Ratio & rat){
    return Ratio(rat.m_numerator-rat.m_numerator%int(rat.m_denominator),rat.m_denominator);
}

//optionnal
Ratio Ratio::sin(const Ratio & rat){
    double value=std::sin(double(rat.m_numerator)/double(rat.m_denominator));
    Ratio result(value);
    return result;
}

Ratio Ratio::cos(const Ratio & rat){
    double value=std::cos(double(rat.m_numerator)/double(rat.m_denominator));
    Ratio result(value);
    return result;
}

Ratio Ratio::tan(const Ratio & rat){
    return Ratio::sin(rat)/Ratio::cos(rat);
}

Ratio Ratio::exp(const Ratio & rat){
    double value=std::exp(rat.m_numerator/rat.m_denominator);
    return Ratio(value);
}

Ratio Ratio::log(const Ratio & rat){
    return Ratio(std::log(rat.m_numerator)-std::log(rat.m_denominator));
}

// Ratio Ratio::pow(const Ratio & rat, const T &tio::abs(const Ratio & rat){
//     return Ratio(std::abs(rat.m_numerator),rat.m_denominator);
// }n){
//     return Ratio(std::pow(rat.m_numerator,n),n*rat.m_numerator*std::pow(rat.m_numerator,n-1));
// }

// Ratio Ratio::sqrt(const Ratio & rat){
//     return Ratio(std::sqrt(rat.m_numerator),rat.m_numerator/(2*std::sqrt(rat.m_numerator)));
// }
