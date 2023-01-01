#include <iostream>

#include <math.h>

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
    class Ratio {

    public :

        /// \brief defaultConstructor equal to 0
        constexpr Ratio() : m_numerator(0), m_denominator(1) {};

        /// \brief constructor from a numerator and a denominator
        /// \param numerator : int : the numerator of the requested rational
        /// \param denominator : unsigned int : the denominator of the requested rational
        Ratio(const int &numerator, const uint &denominator);

        /// \brief copyConstructor
        /// \param rat : Ratio copied
        constexpr Ratio(const Ratio &rat) : m_numerator(rat.m_numerator), m_denominator(rat.m_denominator) {};

        /// @brief Constructor which transforms a real into a Ratio
        /// @param real : a number to convert into a ratio
        /// @return a ratio equal to the real
        template <typename T>
        constexpr Ratio(const T &real);

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
        void irreducible();

        /// \brief transforms a Ratio into its invert
        void inverse();

        /// \brief operator =
        /// \param the rational
        void operator=(const Ratio &r);

        /// \brief operator *
        /// \param the rational
        Ratio operator*(const Ratio &r) const;

        /// \brief operator +
        /// \param the rational
        Ratio operator+(const Ratio &r) const;

        /// \brief operator -
        /// \param the rational
        Ratio operator-(const Ratio &r) const;

        /// \brief operator /
        /// \param the rational
        Ratio operator/(Ratio r) const;

        
        bool operator<=(const Ratio& rat) const;
        bool operator>=(const Ratio& rat) const;
        bool operator<(const Ratio& rat) const;
        bool operator>(const Ratio& rat) const;
        bool operator==(const Ratio& rat) const;
        bool operator!=(const Ratio& rat) const;


        template <typename T>
        constexpr friend Ratio operator*(const Ratio &rat, const T &value); 

        template <typename T>
        constexpr friend Ratio operator/(const Ratio &rat, const T &value);

        template <typename T>
        constexpr friend Ratio operator+(const Ratio &rat, const T &value);

        template <typename T>
        constexpr friend Ratio operator-(const Ratio &rat, const T &value);

        /// \brief unary minus
        inline friend Ratio operator-(const Ratio &rat) {return Ratio(-rat.m_numerator,rat.m_denominator);}

        //mathematical fonctions
        friend Ratio abs(const Ratio & rat)
        {
            return Ratio(std::abs(rat.m_numerator),rat.m_denominator);
        }

        friend Ratio floor(const Ratio & rat)
        {
            return Ratio(rat.m_numerator-rat.m_numerator%int(rat.m_denominator),rat.m_denominator);
        }

        //optionnal
        friend Ratio sin(const Ratio & rat)
        {
            double value=std::sin(double(rat.m_numerator)/double(rat.m_denominator));
            Ratio result(value);
            return result;
        }

        friend Ratio cos(const Ratio & rat)
        {
            double value=std::cos(double(rat.m_numerator)/double(rat.m_denominator));
            Ratio result(value);
            return result;
        }

        friend Ratio tan(const Ratio & rat)
        {
            return sin(rat)/cos(rat);
        }

        friend Ratio exp(const Ratio & rat)
        {
            double value=std::exp(rat.m_numerator/rat.m_denominator);
            return Ratio(value);
        }

        friend Ratio log(const Ratio & rat)
        {
            return Ratio(std::log(double(rat.m_numerator))-std::log(double(rat.m_denominator)));
        }

        friend Ratio sqrt(const Ratio & rat)
        {
            return Ratio(std::sqrt(rat.m_numerator),std::sqrt(rat.m_denominator));
        }

        template <typename T>
        constexpr static Ratio pow(Ratio rat, T n);


        // Utilities 

        /// \brief overload the operator << for Ratio
        /// \param stream : input stream
        /// \param v : the ratio to output
        /// \return the output stream containing the ratio data
        friend std::ostream& operator<<(std::ostream& stream, const Ratio& r)
        {
            stream << "(" << r.numerator() << "/" << r.denominator() << ")";
            return stream;
        }

    };

    //Utilities
    template <typename T>
    constexpr rto::Ratio convertRealToRatio(T real, uint nb_iter)
    {
        //1st stopping condition : return 0/1
        if(real==static_cast<T>(0)){return rto::Ratio();}

        //2nd stopping condition : return 0/1
        if(nb_iter==0){return rto::Ratio();}

        //case |real|<1
        if(real < static_cast<T>(1))
        {
            rto::Ratio rat=convertRealToRatio<T>(static_cast<T>(1)/real,nb_iter);
            rat.inverse();
            return rat;
        }

        //case |real|>=1
        else
        {
            int q=floor(real);
            return (rto::Ratio(q,1) + convertRealToRatio<T>(real-q, nb_iter-1));
        }
    }

    // Template functions
    template <typename T>
    constexpr Ratio::Ratio(const T &real)
    {
        static_assert(std::is_arithmetic_v<T>, "Invalid type; should be a number");
        uint nb_iter=100;
        int sign = real < static_cast<T>(0) ? -1 : 1;
        *this = Ratio(sign,1) * convertRealToRatio<T>(std::abs(real),nb_iter);
        this->irreducible();
    }


    //operators

    template <typename T>
    constexpr Ratio operator*(const rto::Ratio &rat, const T &value) 
    {
        static_assert(std::is_arithmetic_v<T>, "Invalid type; should be a number");
        rto::Ratio val(value);
        return rat*val;
    }

    template <typename T>
    constexpr Ratio operator/(const rto::Ratio &rat, const T &value) 
    {
        static_assert(std::is_arithmetic_v<T>, "Invalid type; should be a number");
        rto::Ratio val(value);
        return rat/val;
    }

    template <typename T>
    constexpr Ratio operator+(const rto::Ratio &rat, const T &value) 
    {
        static_assert(std::is_arithmetic_v<T>, "Invalid type; should be a number");
        rto::Ratio val(value);
        return rat+val;
    }

    template <typename T>
    constexpr Ratio operator-(const rto::Ratio &rat, const T &value) 
    {
        static_assert(std::is_arithmetic_v<T>, "Invalid type; should be a number");
        rto::Ratio val(value);
        return rat-val;
    }

    //pow
    template <typename T>
    constexpr Ratio pow(rto::Ratio rat, T n)
    {
        static_assert(std::is_arithmetic_v<T>, "Invalid type; should be a number");
        if(n<static_cast<T>(0))
        {
            rat.inverse();
            n=-n;
        }
        return Ratio(std::pow(rat.m_numerator,n),std::pow(rat.m_denominator,n));
    }

}
