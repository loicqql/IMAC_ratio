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

    /// \brief getter / setter
    inline int & numerator() {return m_numerator;};
    inline uint & denominator() {return m_denominator;};

    /// \brief transforms a Ratio into an irreducible fraction
    void irreducible();
};

	/// \brief overload the operator << for Ratio
    /// \param stream : input stream
    /// \param v : the vector to output
    /// \return the output stream containing the vector data
    std::ostream& operator<< (std::ostream& stream, const Ratio& v);

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
