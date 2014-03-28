/* huge_number.h
 * Austin O'Connor
 * CS3505 Assignment #2
 * 1/14/14
 */

#ifndef HUGE_NUMBER
#define HUGE_NUMBER
#include <string>

// Class header.
class huge_number
{
  // EVERYTHING PRIVATE GOES HERE
private:
  // private string object to hold the number.
  std::string num;

  // Addition method
  std::string add(std::string a, std::string b);

  // Multiplication method
  std::string multiply (std::string a, std::string b);

  // Subtraction method
  std::string subtract (std::string a, std::string b);

  // Divide method
  std::string divide(std::string a, std::string b);

  // Mod method
  std::string mod(std::string a, std::string b);
  
  // Is bigger method, to check if b > a
  bool is_bigger (std::string a, std::string b);

  // method to check if b < a.
  bool is_smaller(std::string a, std::string b);


  // EVERYTHING PUBLIC GOES HERE
public:
  // default constructor.
  huge_number();

  // single param constructor.
  huge_number(std::string num);

  // copy constructor
  huge_number(const huge_number & other);

  // get value method.
  std::string get_value();

  // override the + operator
  const std::string operator + (const huge_number & rhs);

  // override the * operator
  const std::string operator * (const huge_number & rhs);

  // override the - operator
  const std::string operator - (const huge_number & rhs);

  // override the / operator
  const std::string operator / (const huge_number & rhs);

  // override the % operator
  const std::string operator % (const huge_number & rhs);
  
  // override the = operator
  std::string & operator = (const huge_number & rhs);


}; // End of header file.

#endif
