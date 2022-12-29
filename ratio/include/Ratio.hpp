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
class Ratio {

private :
  
    int m_numerator;
    uint m_denominator;

public :

    /// \brief defaultConstructor equal to 0
    Ratio() : m_numerator(0), m_denominator(1) {};

	/// \brief constructor from a numerator and a denominator
	/// \param numerator : int : the numerator of the requested rational
    /// \param denominator : unsigned int : the denominator of the requested rational
    Ratio(const int &numerator, const uint &denominator);

    /// \brief copyConstructor
    /// \param rat : Ratio copied
    Ratio(const Ratio &rat) : m_numerator(rat.m_numerator), m_denominator(rat.m_denominator) {};

    /// @brief Constructor which transforms a real into a Ratio
    /// @param real : a real to convert into a ratio
    /// @return a ratio equal to real
    template <typename R>
    Ratio(const R &real);

    /// \brief destructor
    ~Ratio() = default;

    /// \brief get numerator
    inline int & numerator() {return m_numerator;};

    /// \brief get denominator
    inline uint & denominator() {return m_denominator;};

    /// \brief get numerator
    inline const int & numerator() const {return m_numerator;};

    /// \brief get denominator
    inline const uint & denominator() const {return m_denominator;};

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



    template <typename T>
    inline friend Ratio operator*(const T &value, const Ratio &rat) 
    {
        Ratio val(value);
        return val*rat;
    }
    template <typename T>
    inline friend Ratio operator*(const Ratio &rat, const T &value) 
    {
        Ratio val(value);
        return val*rat;
    }

    template <typename T>
    inline friend Ratio operator/(const Ratio &rat, const T &value) 
    {
        Ratio val(value);
        return rat/val;
    }
    template <typename T>
    inline friend Ratio operator/(const T &value, const Ratio &rat) 
    {
        Ratio val(value);
        return val/rat;
    }

    /// \brief unary minus
    inline friend Ratio operator-(const Ratio &rat) {return Ratio(-rat.m_numerator,rat.m_denominator);}


    static Ratio sin(const Ratio & rat);
    static Ratio cos(const Ratio & rat);
    static Ratio tan(const Ratio & rat);
    static Ratio exp(const Ratio & rat);
    static Ratio log(const Ratio & rat);
    static Ratio abs(const Ratio & rat);
    static Ratio sqrt(const Ratio & rat);
    template <typename T>
    static Ratio pow(const Ratio & rat, const T &n);


    // Utilities 

    /// \brief overload the operator << for Ratio
    /// \param stream : input stream
    /// \param v : the ratio to output
    /// \return the output stream containing the ratio data
    friend std::ostream& operator<<(std::ostream& stream, const Ratio& r);

};