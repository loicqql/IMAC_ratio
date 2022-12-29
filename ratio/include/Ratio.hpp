#include <iostream>

#include <numeric>

#pragma once


// Doxygen menu
/// \version 0.1
/// \mainpage
/// \tableofcontents
/// \section instroduction_sec What for?
/// Ratio is a super tool :).
/// \section install_bigsec How to install
/// \subsection depen


/////////////////////////////////////////////////////
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

    /// \brief destructor
    ~Ratio() = default;

    /// \brief get numerator
    inline int & numerator() {return m_numerator;};

    /// \brief get denominator
    inline uint & denominator() {return m_denominator;};

    /// \brief transforms a Ratio into an irreducible fraction
    void irreducible();

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
    Ratio operator/(const Ratio &r) const;

    /// \brief overload the operator << for Ratio
    /// \param stream : input stream
    /// \param v : the ratio to output
    /// \return the output stream containing the ratio data
    friend std::ostream& operator<<(std::ostream& stream, const Ratio& r);

};