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
/// Ratio is a library using rationals to remplace floating-point arithmetic.
/// \section install_bigsec How to install
/// \subsection dependencies_sec Dependecies
/// \li Cmake (>=3.13)
/// \li libgtest-dev (google test)
/// \li Doxygen (if you want the documentation)
/// \subsection install_sec Install with cmake (Linux / Mac)
/// \li go to main dir
/// \li mkdir build
/// \li cd build
/// \li cmake ..
/// \li make
/// \li ./example/example (run example)
/// \li ./UnitTest/UnitTests (run tests)
/// \li if Doxygen installed: make html
/// \li The documentation is located in :
/// 	- [path to build]/INTERFACE/doc/doc-doxygen/html/index.html


/// \class Ratio
/// \brief class using rationals to remplace floating-point arithmetic.

namespace rto {
    template <typename T = int>
    class Ratio {

    public :

        /// \brief defaultConstructor equal to 0
        /// @return a ratio (0/1)
        constexpr Ratio() {
            static_assert(std::is_integral_v<T>, "Invalid type; should be a number");
            m_numerator = static_cast<T>(0);
            m_denominator = static_cast<T>(1);
        };

        /// \brief constructor from a numerator and a denominator
        /// \param numerator : the numerator of the requested rational
        /// \param denominator : the denominator of the requested rational
        /// @return a ratio (numerator/denominator)
        constexpr Ratio(const T &numerator, const T &denominator) {
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
        /// @return the ratio
        constexpr Ratio(const Ratio &rat) {
            static_assert(std::is_integral_v<T>, "Invalid type; should be a number");
            m_numerator = rat.m_numerator;
            m_denominator = rat.m_denominator;
        };

        /// \brief destructor
        ~Ratio() = default;

    private :
    
        T m_numerator;
        T m_denominator;

    public :

        /// \brief get numerator
        /// @return the numerator
        constexpr inline T & numerator() {return m_numerator;};

        /// \brief get denominator
        /// @return the denominator
        constexpr inline T & denominator() {return m_denominator;};

        /// \brief get numerator
        /// @return the numerator
        constexpr inline const T & numerator() const {return m_numerator;};

        /// \brief get denominator
        /// @return the denominator
        constexpr inline const T & denominator() const {return m_denominator;};

        /// \brief transforms a Ratio into an irreducible fraction
        /// @return void
        constexpr void irreducible() {
            T pgcd = std::gcd(this->m_numerator,this->m_denominator);
            this->m_numerator=this->m_numerator/pgcd;
            this->m_denominator=this->m_denominator/pgcd;
        }

        /// \brief transforms a Ratio into its invert
        /// @return void
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
        /// \param rat : the rational
        /// @return void
        constexpr void operator=(const Ratio &rat) {
            this->m_numerator=rat.m_numerator;
            this->m_denominator=rat.m_denominator;
        }

        /// \brief operator *
        /// \param rat : the rational
        /// @return the ratio
        constexpr Ratio operator*(const Ratio &rat) const {
            T num = this->m_numerator * rat.m_numerator;
            T den = this->m_denominator * rat.m_denominator;
            return Ratio(num, den);
        }

        /// \brief operator +
        /// \param rat : the rational
        /// @return the ratio
        constexpr Ratio operator+(const Ratio &rat) const {
            T num = this->m_numerator * rat.m_denominator + this->m_denominator * rat.m_numerator;
            T den = this->m_denominator * rat.m_denominator;
            return Ratio(num, den);
        }

        /// \brief operator -
        /// \param r : the rational
        /// @return the ratio
        constexpr Ratio operator-(const Ratio &rat) const {
            T num = this->m_numerator * rat.m_denominator - this->m_denominator * rat.m_numerator;
            T den = this->m_denominator * rat.m_denominator;
            return Ratio(num, den);
        }

        /// \brief operator /
        /// \param rat : the rational
        /// @return the ratio
        constexpr Ratio operator/(Ratio rat) const {
            assert(rat.m_numerator!=0 && "Can't divide by 0"); 
            rat.inverse();
            return *this*rat;
        }

        /// \brief operator <=
        /// \param rat : the rational
        /// @return result
        constexpr bool operator<=(const Ratio& rat) const {
            return (this->m_numerator / this->m_denominator) <= (rat.m_numerator / rat.m_denominator);
        }

        /// \brief operator >=
        /// \param rat : the rational
        /// @return result
        constexpr bool operator>=(const Ratio& rat) const {
            return (this->m_numerator / this->m_denominator) >= (rat.m_numerator / rat.m_denominator);
        }

        /// \brief operator <
        /// \param rat : the rational
        /// @return result
        constexpr bool operator<(const Ratio& rat) const {
            return (this->m_numerator / this->m_denominator) < (rat.m_numerator / rat.m_denominator);
        }

        /// \brief operator >
        /// \param rat : the rational
        /// @return result
        constexpr bool operator>(const Ratio& rat) const {
            return (this->m_numerator / this->m_denominator) > (rat.m_numerator / rat.m_denominator);
        }

        /// \brief operator ==
        /// \param rat : the rational
        /// @return result
        constexpr bool operator==(const Ratio& rat) const {
            return (this->m_numerator == rat.m_numerator) && (this->m_denominator == rat.m_denominator);
        }

        /// \brief operator !=
        /// \param rat : the rational
        /// @return result
        constexpr bool operator!=(const Ratio& rat) const {
            return (this->m_numerator / this->m_denominator) != (rat.m_numerator / rat.m_denominator);
        }


        /// \brief operator * with a number
        /// \param rat : the rational
        /// \param value : the number
        /// @return a ratio
        template <typename U>
        constexpr friend Ratio operator*(const Ratio &rat, const U &value) {
            static_assert(std::is_arithmetic_v<U>, "Invalid type; should be a number");
            rto::Ratio val(value);
            return rat*val;
        }

        /// \brief operator / with a number
        /// \param rat : the rational
        /// \param value : the number
        /// @return a ratio
        template <typename U>
        constexpr friend Ratio operator/(const Ratio &rat, const U &value) {
            static_assert(std::is_arithmetic_v<U>, "Invalid type; should be a number");
            rto::Ratio val(value);
            return rat/val;
        }

        /// \brief operator + with a number
        /// \param rat : the rational
        /// \param value : the number
        /// @return a ratio
        template <typename U>
        constexpr friend Ratio operator+(const Ratio &rat, const U &value) {
            static_assert(std::is_arithmetic_v<U>, "Invalid type; should be a number");
            rto::Ratio val(value);
            return rat+val;
        }

        /// \brief operator - with a number
        /// \param rat : the rational
        /// \param value : the number
        /// @return a ratio
        template <typename U>
        constexpr friend Ratio operator-(const Ratio &rat, const U &value) {
            static_assert(std::is_arithmetic_v<U>, "Invalid type; should be a number");
            rto::Ratio val(value);
            return rat-val;
        }

        /// \brief unary minus
        /// \param rat : ratio
        /// @return -ratio
        inline friend Ratio operator-(const Ratio &rat) {return Ratio(-rat.m_numerator,rat.m_denominator);}

        //mathematical fonctions

        /// \brief abs
        /// \param rat : the rational
        /// @return abs of the rational
        constexpr friend Ratio abs(const Ratio & rat) {
            return Ratio(std::abs(rat.m_numerator),rat.m_denominator);
        }

        /// \brief floor
        /// \param rat : the rational
        /// @return floor of the rational
        constexpr friend Ratio floor(const Ratio & rat) {
            return Ratio(rat.m_numerator-rat.m_numerator%rat.m_denominator,rat.m_denominator);
        }

        //optionnal

        /// \brief sin
        /// \param rat : the rational
        /// @return sin of the rational
        constexpr friend Ratio sin(const Ratio & rat) {
            double value=std::sin(double(rat.m_numerator)/double(rat.m_denominator));
            Ratio result(value);
            return result;
        }

        /// \brief cos
        /// \param rat : the rational
        /// @return cos of the rational
        constexpr friend Ratio cos(const Ratio & rat) {
            double value=std::cos(double(rat.m_numerator)/double(rat.m_denominator));
            Ratio result(value);
            return result;
        }

        /// \brief tan
        /// \param rat : the rational
        /// @return tan of the rational
        constexpr friend Ratio tan(const Ratio & rat) {
            return sin(rat)/cos(rat);
        }

        /// \brief exp
        /// \param rat : the rational
        /// @return exp of the rational
        constexpr friend Ratio exp(const Ratio & rat) {
            double value=std::exp(rat.m_numerator/rat.m_denominator);
            return Ratio(value);
        }

        /// \brief log
        /// \param rat : the rational
        /// @return log of the rational
        constexpr friend Ratio log(const Ratio & rat) {
            return Ratio(std::log(double(rat.m_numerator))-std::log(double(rat.m_denominator)));
        }

        /// \brief square_root
        /// \param rat : the rational
        /// @return sqrt of the rational
        constexpr friend Ratio sqrt(const Ratio & rat) {
            return Ratio(pow(rat, 0.5));
        }

        /// \brief pow
        /// \param rat : the rational
        /// \param n : a number
        /// @return pow of the rational
        template <typename U>
        constexpr friend Ratio pow(Ratio rat, U n) {
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
