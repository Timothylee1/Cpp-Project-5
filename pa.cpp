/******************************************************************************
\File pa.cpp
\Author Timothy Lee Ke xin
\Par DP email: timothykexin.lee@digipen.edu.sg
\Par Course: RSE 1202
\Par Section: Problem Solving with vectors and strings 
\Par Programming Assignment #3
\Date 04-02-2022

  \Brief
  This program is used to read, process and transform an input file 
  worldpop.txt that has a table of names and populations of countries into four 
  output files containing tables with countries names sorted in increasing and 
  decreasing orders and population counts sorted in increasing and decreasing 
  orders.
  
  - Ptr_Cmp_Func
      Although this function is not does not need to be defined in this file, 
      it is declared in the pa.hpp file. It is used for function pointer that
      takes in two parameters, both of type read-only reference and returns a
      bool.
  
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
      Function returns true if the country name referenced by left is 
      lexicographically less than the country name referenced by right; 
      Otherwise, the function returns false. 

  - cmp_name_greater
      Function returns true if the country name referenced by left is 
      lexicographically more than the country name referenced by right; 
      Otherwise, the function returns false. 
 
  - cmp_pop_less
      Function name returns true if population of object referenced by 
      left is numerically less than population of object referenced by right;
      Otherwise, the function returns false.
 
  - cmp_pop_greater
      Function name returns true if population of object referenced by left is
       numerically more than population of object referenced by right; 
       Otherwise, the function returns false. 
 
  - write_to_ostream
      Writes the contents of the container referenced by v into the output 
      stream referenced by os. Each element of the container must be separated 
      by a newline. The two data members of CountryInfo must be left justified.
      To format using the setw function with width specified in the function
      parameter fw. Does not return any argument/s.

******************************************************************************/
#include "pa.hpp"

namespace HLP2 {

    /*************************************************************************/
    /*! 
    \brief
        Reads a line of text, parse the line into a string specifying a 
        country's name and a long int specifying the country's population, and 
        augment a vector<CountryInfo> container with this information. Returns 
        the name of the vector struct CountryInfo. 

    \param is
        The input file stream from which the inputs are to be read and made
        use of for the purpose of this function.

    \param info
        The name of the vector struct CountryInfo. This pointer is returned 
        after function execution.

    \param line
        To assign the read line of the input file stream using getline().

    \param pop
        To assign the population long int collected from line.

    \param alpha
        To assign the characters for identification of countrys' names.

    \param nums
        To assign the characters for identification of population size.

    \param i
        Indicator for number of elements required for the vector struct. It 
        helps with the dynamic allocation of memory performed by vector.

    \param first
        Signifies the first occurence of a specific type, either alpha or nums.
        
    \param last
        Signifies the last occurence of a specific type, either alpha or nums.
    */    
    /*************************************************************************/
    std::vector<HLP2::CountryInfo> fill_vector_from_istream(std::istream& is) {
        std::vector<HLP2::CountryInfo> info;
        std::string line, pop, alpha;
        //Hardcoding way to identify since i'm not using stringstream
        alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz()";
        std::string nums = "0123456789";
        for (int i{}; is; i++) {
            std::getline(is, line);

            //In the event getline reads an empty line i.e. end of file has an 
            //empty line after newline
            if (line.empty())
                break;
            //Push back new subject created with default constructor
            //Cant access vector with [#] until an element exists in 
            //the vector at that index. This populates the [#] and 
            //modifies it afterward by parsing.
            info.push_back(HLP2::CountryInfo());
            std::size_t first = line.find_first_of(alpha);
            std::size_t last = line.find_last_of(alpha);
            info[i].name = line.substr(first, last-first+1);
                        //std::cout << info[i].name << "  ";
            first = line.find_first_of(nums);
            last = line.find_last_of(nums);
            pop = line.substr(first, last-first+1);
            std::size_t pos = pop.find(',');

            //Begin search at pos position
            for (; pos != std::string::npos; pos = pop.find(',', pos)) { 
                //Erase only one character rather than everything after
                pop.erase(pos, 1); 
            }
            info[i].pop = std::stol(pop);
                    //std::cout << info[i].pop << '\n';
        }
        return info;
    }

    /*************************************************************************/
    /*! 
    \brief
        This function returns the length of the longest country's name in the
        vector struct CountryInfo. Returns the value of type size_t. 

    \param info
        The name of the vector struct CountryInfo that contains a pointer to 
        the struct vector CountryInfo.
        
    \param max
        To assign the max name length of the country found in info. 
        This argument is returned after function execution.

    \param i
        Indicator for number of elements required for the vector struct. It 
        helps with the dynamic allocation of memory performed by vector.

    \param name_length
        To assign the name length of the country found in info.
.
    */    
    /*************************************************************************/
    size_t max_name_length(std::vector<HLP2::CountryInfo> const& info) {
        //returns length of the longest country's name
        std::size_t max{};
        for (std::size_t i{}; i<info.size(); i++) {
            std::size_t name_length = (info[i].name).size();
            max = max <= name_length ? name_length : max;
        }
        return max;
    }       

    /*************************************************************************/
    /*! 
    \brief
        Sorts all elements in vector struct CountryInfo object referenced by rv 
        using a sorting criterion specified by the comparison function pointed 
        to by cmp. Does not return any argument/s. 

    \param rv
        The name of the vector struct CountryInfo that contains a pointer to 
        the struct vector CountryInfo.

    \param size
        The name of elements in rv.

    \param i
        Indicator for the first element to be compared.
        
    \param j
        Indicator of number of the last element to be compared.

    \param temp_name
        A temporary holder for rv element name.

    \param temp_pop
        A temporary holder for rv element pop.

    */    
    /*************************************************************************/
    void sort(std::vector<HLP2::CountryInfo>& rv, HLP2::Ptr_Cmp_Func cmp) {
        //sorts all elements in rv using criterion in cmp
        std::size_t size = rv.size();
        for (std::size_t i{}; i < size; ++i) {
            for (std::size_t j = size-1; j > i; j--) {
                //True then swap places
                if (!cmp(rv[i], rv[j])) {
                    std::string temp_name = rv[j].name;
                    long int temp_pop = rv[j].pop;
                    rv[j].name = rv[i].name;
                    rv[j].pop = rv[i].pop;
                    rv[i].name = temp_name;
                    rv[i].pop = temp_pop;
                }
            }
        }
    }

    /*************************************************************************/
    /*! 
    \brief
        Function cmp_name_less returns true if the country name referenced by 
        left is lexicographically less than the country name referenced by 
        right; Otherwise, the function returns false. In the event the 
        comparing names are identical, it should return the shortest name 
        hence, returns true.

    \param left
        The name of the vector struct CountryInfo that contains a pointer to 
        the first element of the struct vector CountryInfo.

    \param right
        The name of the vector struct CountryInfo that contains a pointer to 
        the last element of the struct vector CountryInfo.

    \param minlength
        Contains the length of the left element name. To ultimately contain
        the shorter length of the left and right element names.

    \param minlength2
        Contains the length of the right element name.

    \param i
        Indicator element assessed and checked with minlength to prevent out of
        range stderr.
        
    */    
    /*************************************************************************/
    bool cmp_name_less(HLP2::CountryInfo const& left, HLP2::CountryInfo const& 
                       right) {
        //Determines length of string to prevent out of range stderr when 
        //comparing function param
        std::size_t minlength = (left.name).size();
        std::size_t minlength2 = (right.name).size(); 

        //Assigns size_t type value for shortest string length to minlength
        minlength = minlength < minlength2 ? minlength : minlength2; 
        for (size_t i{}; i<minlength; i++) {
            //Element in subscript i in left is lexicographically less than 
            //in right
            if (left.name[i] < right.name[i]) { 
                return true;
            }
            //Element in subscript i in left is lexicographically more than 
            //in right
            else if (left.name[i] > right.name[i]) {
                return false;
            }
            //Else if left[i] == right[i]; means that the letter is the same  
            //and to continue comparing for shortest string length number of 
            //times
        }
        //In the event the comparing names are identical, it should return 
        //the shortest name hence, returns true such that no swaps are made
        return true;
    }

    /*************************************************************************/
    /*! 
    \brief
        Function returns true if the country name referenced by left is 
        lexicographically less than the country name referenced by right; 
        Otherwise, the function returns false. In the event the comparing 
        names are identical, it should return the shortest name hence, 
        returns true.

    \param left
        The name of the vector struct CountryInfo that contains a pointer to 
        the first element of the struct vector CountryInfo.

    \param right
        The name of the vector struct CountryInfo that contains a pointer to 
        the last element of the struct vector CountryInfo.

    \param minlength
        Contains the length of the left element name. To ultimately contain
        the shorter length of the left and right element names.

    \param minlength2
        Contains the length of the right element name.

    \param i
        Indicator element assessed and checked with minlength to prevent out of
        range stderr.
        
    */    
    /*************************************************************************/
    bool cmp_name_greater(HLP2::CountryInfo const& left, HLP2::CountryInfo const& 
                          right) {
        //Determines length of string to prevent out of range stderr when comparing 
        //function param
        std::size_t minlength = (left.name).size();
        std::size_t minlength2 = (right.name).size(); 

        //Assigns size_t type value for shortest string length to minlength
        minlength = minlength < minlength2 ? minlength : minlength2; 
        for (size_t i{}; i<minlength; i++) {
            //Element in subscript i in left is lexicographically less than in 
            //right
            if (left.name[i] < right.name[i]) { 
                return false;
            }
            //Element in subscript i in left is lexicographically more than in 
            //right
            else if (left.name[i] > right.name[i]) {
                return true;
            }
            //Else if left[i] == right[i]; means that the letter is the same  
            //and to continue comparing for shortest string length number of 
            //times
        }
        //In the event the comparing names are identical, it should return 
        //the shortest name hence, returns true such that no swaps are made
        return true; 
    }   

    /*************************************************************************/
    /*! 
    \brief
        Function name returns true if population of object referenced by left
        is numerically less than population of object referenced by right;
        Otherwise, the function returns false. 

    \param left
        The name of the vector struct CountryInfo that contains a pointer to 
        the first element of the struct vector CountryInfo.

    \param right
        The name of the vector struct CountryInfo that contains a pointer to 
        the last element of the struct vector CountryInfo.
    */    
    /*************************************************************************/
    bool cmp_pop_less(HLP2::CountryInfo const& left, HLP2::CountryInfo const& 
                      right) {
        //Returns true if left is numerically less than population right, else, 
        //false. No need to check length as the string taken in fill_vector... 
        //function removed the ',' and did a stol conversion and stored it into 
        //the struct HLP2::CountryInfo long int pop
        return left.pop < right.pop ? true : false;
    }

    /*************************************************************************/
    /*! 
    \brief
        Function name returns true if population of object referenced by left
        is numerically more than population of object referenced by right;
        Otherwise, the function returns false.  

    \param left
        The name of the vector struct CountryInfo that contains a pointer to 
        the first element of the struct vector CountryInfo.

    \param right
        The name of the vector struct CountryInfo that contains a pointer to 
        the last element of the struct vector CountryInfo.
    */    
    /*************************************************************************/
    bool cmp_pop_greater(HLP2::CountryInfo const& left, HLP2::CountryInfo const& 
                         right) {
        //Returns true if left is numerically more than population right, else, 
        //false. No need to check length as the string taken in fill_vector... 
        //function removed the ',' and did a stol conversion and stored it into 
        //the struct HLP2::CountryInfo long int pop
        return left.pop > right.pop ? true : false;
    }

    /*************************************************************************/
    /*! 
    \brief
        Writes the contents of the container referenced by v into the output 
        stream referenced by os. Each element of the container must be 
        separated by a newline. The two data members of CountryInfo must be 
        left justified. To format using the setw function with width specified 
        in the function parameter fw. Does not return any argument/s.

    \param v
        The name of the vector struct CountryInfo that contains a pointer to 
        the struct vector CountryInfo.

    \param os
        The output file stream where the formatted arrangement of countries 
        names and population are printed to.
        
    \param fw
        The width specified as the formatted spacing between the first letter
        of the name and the first number of the population.

    \param i
        Indicator for lines to be printed out which is checked across the 
        number of elements found in v.

    */    
    /*************************************************************************/
    void write_to_ostream(std::vector<HLP2::CountryInfo> const& v,
                          std::ostream& os, size_t fw) {
        //Print out with formatting for all the elements in struct 
        //HLP2::CountryInfo v with a newline separator
        for (size_t i{}; i < v.size(); i++) {
            os << std::setw(fw) << std::left << v[i].name << v[i].pop << '\n';
        }
    }
}
