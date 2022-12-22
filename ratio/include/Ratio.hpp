#include <iostream>

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


template <typename T>

/// \class Ratio
/// \brief class using rationals to remplace floating-point arithmetic.
class Ratio {

private :
  
    T m_numerator;
    T m_denominator;

public :

	/// \brief constructor from a numerator and a denominator
	/// \param numerator : the numerator of the requested rational
    /// \param numerator : the denominator of the requested rational
    Ratio(const T &numerator, const T &denominator) : m_numerator(numerator), m_denominator(denominator) {};

    /// \brief destructor
    ~Ratio() = default;

};

    template<typename T>
	/// \brief overload the operator << for Ratio
    /// \param stream : input stream
    /// \param v : the vector to output
    /// \return the output stream containing the vector data
    std::ostream& operator<< (std::ostream& stream, const Ratio<T>& v);
