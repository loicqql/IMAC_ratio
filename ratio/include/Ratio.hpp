#include <iostream>
#include <numeric>
#include <cmath>
#include <cassert>

#pragma once


// Doxygen menu
/// \version 0.1
/// \mainpage
/// \tableofcontents
/// \section instroduction_sec What for?
/// Ratio is a super tool :).
/// \section install_bigsec How to install
/// \subsection dependencies_sec Dependecies
/// \li nothing
/// \li Doxygen (if you want the documentation)
/// \subsection install_sec Install with cmake (Linux / Mac)
/// \li go to main dir
/// \li mkdir build
/// \li cd build
/// \li cmake ..
/// \li make
/// \li if Doxygen installed: make html
/// \li The documentation is located in :
/// 	- [path to build]/doc/doc-doxygen/html/index.html or 
/// 	- or [path to build]/INTERFACE/doc/doc-doxygen/html/index.html


/// \class Ratio
/// \brief class using rationals to remplace floating-point arithmetic.

namespace rto {
    template <typename T = int>
    class Ratio {

    public :

        /// \brief defaultConstructor equal to 0
        constexpr Ratio() {
            static_assert(std::is_integral_v<T>, "Invalid type; should be a number");
            m_numerator = static_cast<T>(0);
            m_denominator = static_cast<T>(1);
        };

        /// \brief constructor from a numerator and a denominator
        /// \param numerator : int : the numerator of the requested rational
        /// \param denominator : unsigned int : the denominator of the requested rational
        constexpr Ratio(const int &numerator, const uint &denominator) {
            static_assert(std::is_integral_v<T>, "Invalid type; should be a number");
            this->m_numerator=numerator;
            this->m_denominator=denominator;
            this->irreducible();
        }

        /// @brief Constructor which transforms a real into a Ratio
        /// @param real : a number to convert into a ratio
        /// @return a ratio equal to the real
        template <typename U>
        constexpr Ratio(const U &real) {
            static_assert(std::is_arithmetic_v<T>, "Invalid type; should be a number");
            uint nb_iter=100;
            int sign = real < static_cast<U>(0) ? -1 : 1;
            *this = Ratio(sign,1) * convertRealToRatio<U>(std::abs(real),nb_iter);
            this->irreducible();
        }

        /// \brief copyConstructor
        /// \param rat : Ratio copied
        constexpr Ratio(const Ratio &rat) {
            static_assert(std::is_integral_v<T>, "Invalid type; should be a number");
            m_numerator = rat.m_numerator;
            m_denominator = rat.m_denominator;
        };

        /// \brief destructor
        ~Ratio() = default;

    private :
    
        int m_numerator;
        uint m_denominator;

    public :

        /// \brief get numerator
        constexpr inline int & numerator() {return m_numerator;};

        /// \brief get denominator
        constexpr inline uint & denominator() {return m_denominator;};

        /// \brief get numerator
        constexpr inline const int & numerator() const {return m_numerator;};

        /// \brief get denominator
        constexpr inline const uint & denominator() const {return m_denominator;};

        /// \brief transforms a Ratio into an irreducible fraction
        constexpr void irreducible() {
            T pgcd = std::gcd(this->m_numerator,this->m_denominator);
            this->m_numerator=this->m_numerator/pgcd;
            this->m_denominator=this->m_denominator/pgcd;
        }

        /// \brief transforms a Ratio into its invert
        constexpr void inverse() {
            T sign= static_cast<T>(1);
            if (this->m_numerator<0) {
                sign=-1; 
            }
            T temp= sign*this->m_numerator;
            this->m_numerator=sign*this->m_denominator;
            this->m_denominator=temp;
        }

        /// \brief operator =
        /// \param the rational
        constexpr void operator=(const Ratio &r) {
            this->m_numerator=r.m_numerator;
            this->m_denominator=r.m_denominator;
        }

        /// \brief operator *
        /// \param the rational
        constexpr Ratio operator*(const Ratio &r) const {
            T num = this->m_numerator * r.m_numerator;
            T den = this->m_denominator * r.m_denominator;
            return Ratio(num, den);
        }

        /// \brief operator +
        /// \param the rational
        constexpr Ratio operator+(const Ratio &r) const {
            T num = this->m_numerator * r.m_denominator + this->m_denominator * r.m_numerator;
            T den = this->m_denominator * r.m_denominator;
            return Ratio(num, den);
        }

        /// \brief operator -
        /// \param the rational
        constexpr Ratio operator-(const Ratio &r) const {
            T num = this->m_numerator * r.m_denominator - this->m_denominator * r.m_numerator;
            T den = this->m_denominator * r.m_denominator;
            return Ratio(num, den);
        }

        /// \brief operator /
        /// \param the rational
        constexpr Ratio operator/(Ratio rat) const {
            assert(rat.m_numerator!=0 && "Can't divide by 0"); 
            rat.inverse();
            return *this*rat;
        }

        
        constexpr bool operator<=(const Ratio& rat) const {
            return (this->m_numerator / this->m_denominator) <= (rat.m_numerator / rat.m_denominator);
        }
        constexpr bool operator>=(const Ratio& rat) const {
            return (this->m_numerator / this->m_denominator) >= (rat.m_numerator / rat.m_denominator);
        }
        constexpr bool operator<(const Ratio& rat) const {
            return (this->m_numerator / this->m_denominator) < (rat.m_numerator / rat.m_denominator);
        }
        constexpr bool operator>(const Ratio& rat) const {
            return (this->m_numerator / this->m_denominator) > (rat.m_numerator / rat.m_denominator);
        }
        constexpr bool operator==(const Ratio& rat) const {
            return (this->m_numerator == rat.m_numerator) && (this->m_denominator == rat.m_denominator);
        }
        constexpr bool operator!=(const Ratio& rat) const {
            return (this->m_numerator / this->m_denominator) != (rat.m_numerator / rat.m_denominator);
        }


        template <typename U>
        constexpr friend Ratio operator*(const Ratio &rat, const U &value) {
            static_assert(std::is_arithmetic_v<U>, "Invalid type; should be a number");
            rto::Ratio val(value);
            return rat*val;
        } 

        template <typename U>
        constexpr friend Ratio operator/(const Ratio &rat, const U &value) {
            static_assert(std::is_arithmetic_v<U>, "Invalid type; should be a number");
            rto::Ratio val(value);
            return rat/val;
        }

        template <typename U>
        constexpr friend Ratio operator+(const Ratio &rat, const U &value) {
            static_assert(std::is_arithmetic_v<U>, "Invalid type; should be a number");
            rto::Ratio val(value);
            return rat+val;
        }

        template <typename U>
        constexpr friend Ratio operator-(const Ratio &rat, const U &value) {
            static_assert(std::is_arithmetic_v<U>, "Invalid type; should be a number");
            rto::Ratio val(value);
            return rat-val;
        }

        /// \brief unary minus
        inline friend Ratio operator-(const Ratio &rat) {return Ratio(-rat.m_numerator,rat.m_denominator);}

        //mathematical fonctions
        constexpr friend Ratio abs(const Ratio & rat) {
            return Ratio(std::abs(rat.m_numerator),rat.m_denominator);
        }

        constexpr friend Ratio floor(const Ratio & rat) {
            return Ratio(rat.m_numerator-rat.m_numerator%int(rat.m_denominator),rat.m_denominator);
        }

        //optionnal
        constexpr friend Ratio sin(const Ratio & rat) {
            double value=std::sin(double(rat.m_numerator)/double(rat.m_denominator));
            Ratio result(value);
            return result;
        }

        constexpr friend Ratio cos(const Ratio & rat) {
            double value=std::cos(double(rat.m_numerator)/double(rat.m_denominator));
            Ratio result(value);
            return result;
        }

        constexpr friend Ratio tan(const Ratio & rat) {
            return sin(rat)/cos(rat);
        }

        constexpr friend Ratio exp(const Ratio & rat) {
            double value=std::exp(rat.m_numerator/rat.m_denominator);
            return Ratio(value);
        }

        constexpr friend Ratio log(const Ratio & rat) {
            return Ratio(std::log(double(rat.m_numerator))-std::log(double(rat.m_denominator)));
        }

        constexpr friend Ratio sqrt(const Ratio & rat) {
            return Ratio(std::sqrt(rat.m_numerator),std::sqrt(rat.m_denominator));
        }

        template <typename U>
        constexpr static Ratio<T> pow(Ratio rat, U n) {
            static_assert(std::is_arithmetic_v<U>, "Invalid type; should be a number");
            if(n<static_cast<U>(0)) {
                rat.inverse();
                n=-n;
            }
            return Ratio(std::pow(rat.m_numerator,n),std::pow(rat.m_denominator,n));
        }

        /// \brief overload the operator << for Ratio
        /// \param stream : input stream
        /// \param v : the ratio to output
        /// \return the output stream containing the ratio data
        constexpr friend std::ostream& operator<<(std::ostream& stream, const Ratio& r) {
            stream << "(" << r.numerator() << "/" << r.denominator() << ")";
            return stream;
        }


    private : //Utilities
        
        template <typename U>
        constexpr rto::Ratio<T> convertRealToRatio(U real, uint nb_iter) {
            //1st stopping condition : return 0/1
            if(real==static_cast<U>(0)){return rto::Ratio();}

            //2nd stopping condition : return 0/1
            if(nb_iter==0){return rto::Ratio();}

            //case |real|<1
            if(real < static_cast<U>(1)) {
                rto::Ratio rat=convertRealToRatio<U>(static_cast<U>(1)/real,nb_iter);
                rat.inverse();
                return rat;
            } else { //case |real|>=1
                int q=floor(real);
                return (rto::Ratio(q,1) + convertRealToRatio<U>(real-q, nb_iter-1));
            }
        }
    };
}
