/******************************************************************************
\File pa.hpp
\Author Timothy Lee Ke xin
\Par DP email: timothykexin.lee@digipen.edu.sg
\Par Course: RSE 1202
\Par Section: Problem Solving with vectors and strings 
\Par Programming Assignment #3
\Date 04-02-2022

  \Brief
  This program is used to declare header files for use and functions in the 
  pa.cpp file.
  
  - Ptr_Cmp_Func
      It is used for function pointer that takes in two parameters, both of 
      type read-only reference and returns a bool.
  
  - fill_vector_from_istream
      Reads a line of text, parse the line into a string specifying a country's 
      name and a long int specifying the country's population, and augment a 
      vector<CountryInfo> container with this information. Returns the name of
      the vector struct CountryInfo.

  - max_name_length
      This function returns the length of the longest country's name in the
      vector struct CountryInfo. Returns the value of type size_t.
      
  - sort
      Sorts all elements in vector struct CountryInfo object referenced by rv 
      using a sorting criterion specified by the comparison function pointed 
      to by cmp. Does not return any argument/s.

  - cmp_name_less
      Function cmp_name_less returns true if the country name referenced by 
      left is lexicographically less than the country name referenced by right; 
      Otherwise, the function returns false. 

  - cmp_name_greater
      Function cmp_name_less returns true if the country name referenced by 
      left is lexicographically more than the country name referenced by right; 
      Otherwise, the function returns false. 
 
  - cmp_pop_less
      Function name cmp_pop_less returns true if population of object 
      referenced by left is numerically less than population of object 
      referenced by right; Otherwise, the function returns false.
 
  - cmp_pop_greater
      Function name cmp_pop_less returns true if population of object 
      referenced by left is numerically more than population of object 
      referenced by right; Otherwise, the function returns false. 
 
  - write_to_ostream
      Writes the contents of the container referenced by v into the output 
      stream referenced by os. Each element of the container must be separated 
      by a newline. The two data members of CountryInfo must be left justified.
      To format using the setw function with width specified in the function
      parameter fw. Does not return any argument/s.

******************************************************************************/
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

#ifndef PA_HPP
#define PA_HPP
namespace HLP2 {
// structure to encapsulate a country's name and its population ...
struct CountryInfo {
    std::string name; // country's name - *exactly* as in input file
    long int pop; // country's population
};
// other declarations ...
using Ptr_Cmp_Func = bool (*)(CountryInfo const&, CountryInfo const&);

std::vector<CountryInfo> fill_vector_from_istream(std::istream& is);
size_t max_name_length(std::vector<CountryInfo> const& info);
void sort(std::vector<CountryInfo>& rv, Ptr_Cmp_Func cmp);
void write_to_ostream(std::vector<CountryInfo> const& v,
                      std::ostream& os, size_t fw);

bool cmp_name_less(CountryInfo const& left, CountryInfo const& right);
bool cmp_name_greater(CountryInfo const& left, CountryInfo const& right);
bool cmp_pop_less(CountryInfo const& left, CountryInfo const& right);
bool cmp_pop_greater(CountryInfo const& left, CountryInfo const& right);
} // end namespace HLP2
#endif
