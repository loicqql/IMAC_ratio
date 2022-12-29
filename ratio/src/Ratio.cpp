#include <iostream>
#include <numeric>
#include <cassert>
#include <math.h>

#include "Ratio.hpp"

// Utilities 
template <typename R>
Ratio convertRealToRatio(R real, uint nb_iter)
{
    //1st stopping condition : return 0/1
    if(real==0){return Ratio();}

    //2nd stopping condition : return 0/1
    if(nb_iter==0){return Ratio();}
    
    //sign gestion
    int sign = 1;
    if(real<0){ sign=-1; real=-real;}

    //case |real|<1
    if(real<1)
    {
        Ratio rat=convertRealToRatio(1/real,nb_iter);
        rat.inverse();
        return sign*rat;
    }

    //case |real|>=1
    else
    {
        int q=floor(real);
        return sign*(Ratio(q,1) + convertRealToRatio(real-q, nb_iter-1));
    }
}

template <typename R>
Ratio::Ratio(const R &real)
{
    uint nb_iter=100;
    *this = convertRealToRatio(real,nb_iter);
}

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
    this->m_numerator=this->m_numerator/pgcd;
    this->m_denominator=this->m_denominator/pgcd;
}

void Ratio::inverse()
{   
    assert(this->m_denominator!=0 && "Can't invert infinite numbers"); 

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

Ratio Ratio::operator/(Ratio rat) const 
{
    assert(rat.m_numerator!=0 && "Can't divide by 0"); 
    rat.inverse();
    return *this*rat;
}

//mathematical fonctions

Ratio Ratio::sin(const Ratio & rat){
    float value=std::sin(rat.m_numerator/rat.m_denominator);
    Ratio result(value);
    return result;
}

Ratio Ratio::cos(const Ratio & rat){
    float value=std::cos(rat.m_numerator/rat.m_denominator);
    Ratio result(value);
    return result;
}

Ratio Ratio::tan(const Ratio & rat){
    return Ratio::sin(rat)/Ratio::cos(rat);
}

// Ratio Ratio::exp(const Ratio & rat){
//     return Ratio(std::exp(rat.m_numerator),rat.m_numerator*std::exp(rat.m_numerator));
// }

// Ratio Ratio::log(const Ratio & rat){
//     return Ratio(std::log(rat.m_numerator),rat.m_numerator/rat.m_numerator);
// }

// Ratio Ratio::abs(const Ratio & rat){
//     return Ratio(std::abs(rat.m_numerator),rat.m_numerator*sign(rat.m_numerator));
// }

// Ratio Ratio::pow(const Ratio & rat, const T &n){
//     return Ratio(std::pow(rat.m_numerator,n),n*rat.m_numerator*std::pow(rat.m_numerator,n-1));
// }

// Ratio Ratio::sqrt(const Ratio & rat){
//     return Ratio(std::sqrt(rat.m_numerator),rat.m_numerator/(2*std::sqrt(rat.m_numerator)));
// }
