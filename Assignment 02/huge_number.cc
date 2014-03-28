/* huge_number.cc
 * Austin O'Connor
 * CS3505 Assignment #2
 * 1/14/14
 */

#include "huge_number.h"
#include <iostream>
#include <string>

using namespace std;

/*
 * Default constructor - initializes number to 0.
 */
huge_number::huge_number()
{
  num = "0";
  //cout << "Default constructor called with " << num << endl;
}
/*
 * Single param constructor - sets number to the argument passed.
 */
huge_number::huge_number(string s)
{
  num = s;
  //cout << "Single param constructor called with " << s << endl;
}

/*
 * Copy constructor - copys the number from one huge_number to another one.
 */
huge_number::huge_number(const huge_number & other)
{
  num = other.num;
  //cout << "Copy constructor called with " << num << endl;
}

/*
 * Returns the number held in a huge_number object.
 */
string huge_number::get_value()
{
  //cout << "get_value called, " << num << " returned." << endl;
  return num;
}

/*
 * Adds two huge_numbers together.
 * Returns a string.
 * Borrowed from Peter Jensen's lecture.
 */
string huge_number::add(string a, string b)
{
  // initialize a string to hold the result.
  string result = "";

  // Get the right most value of both strings.
  int a_pos = a.length() - 1;
  int b_pos = b.length() - 1;

  // initialize a carry int to 0.
  // this will be used to determine if the addition of
  // two numbers is greator than 10 and needs to be carried
  // over to the next addition. (a_pos - 1 and b_pos - 1)
  int carry = 0;

  // Keep looping until there is nothing left to add.
  while (a_pos >= 0 || b_pos >= 0 || carry > 0)
  {
    // retreive digits from the strings.

    // if the position we are at is greator than 0, get the number
    // then decrement a_pos.
    // if the position we are at is not greator than 0 we will use a
    // zero.
    int a_digit = a_pos >= 0 ? a[a_pos--] - '0' : 0;
    int b_digit = b_pos >= 0 ? b[b_pos--] - '0' : 0;

    // calculate the sum.
    int sum = a_digit + b_digit + carry;

    // update carry
    carry = sum / 10;

    // mod the sum by 10 so that we don't add anything greator than 
    // 10 to one column
    sum = sum % 10 + '0';

    // put the sum into the result string at the left.
    result.insert(0, 1, static_cast<char>(sum));

  }

  // Remove leading 0's
  while(result.length() > 0 && result[0] == '0')
    result.erase(0, 1);

  // if the string is empty the result was 0.
  if(result.length() == 0)
    result = "0";
  
  //cout << "Sum = " << result << endl;
  return result;
}

/*
 * Multiplication.  This is repeated addition.
 * Borrowed from Peter Jensen's lecture.
 */
string huge_number::multiply(string a, string b)
{
  // initialize a string to hold the result.
  string result = "0";

  int b_pos = 0;

  while (b_pos < b.length())
  {
    // multiply the product by 10.
    result.append("0"); 

    int b_digit = b[b_pos++] - '0';
    
    for (int i = 0; i < b_digit; i++)
      result = add(result, a);
  }

  // Remove leading 0's
  while(result.length() > 0 && result[0] == '0')
    result.erase(0, 1);

  // if the string is empty the result was 0.
  if(result.length() == 0)
    result = "0";
  
  //cout << "Multiply = " << result << endl;
  return result;
  
}

/*
 * Subtract method
 */
string huge_number::subtract(string a, string b)
{
  // check to see if the right number is bigger than the left number.
  if(is_bigger(a, b))
  {
    //cout << "Right number is greator than the left. Return 0." << endl; 
    return "0";
  }

  // initialize a string to hold the result.
  string result = "";

  // Get the right most value of both strings.
  int a_pos = a.length() - 1;
  int b_pos = b.length() - 1;

  // initialize a borrow variable for borrowing from other numbers.
  int borrow = 0;

  // variable to keep track of the current position we are at.
  int current_pos;

  // boolean to check if we have borrowed.
  bool is_borrowed = false;
  
  // Keep looping until there is nothing left to subtract.
  while (a_pos >= 0 || b_pos >= 0)
  {
    // retreive digits from the strings.

    // if the position we are at is greator than 0, get the number
    // then decrement a_pos.
    // if the position we are at is not greator than 0 we will use a
    // zero.
    int a_digit = a_pos >= 0 ? a[a_pos--] - '0' : 0;
    int b_digit = b_pos >= 0 ? b[b_pos--] - '0' : 0;

 
    // if the right number is bigger than the left number
    // we need to borrow from the left.
    if(b_digit > a_digit)
    {
      is_borrowed = true;

      // Check to see if the previous position is 0.
      if(a[a_pos] == '0')
      {
	// set up current_pos to hold a_pos
	current_pos = a_pos;

	// while the previous terms = 0
	while (a[a_pos] == '0')
	{
	  // set them to 9 (10-1 which is borrowing convention.)
	  a[a_pos] = '9';
	  a_pos--;
	}

	// now borrow.
	borrow = a[a_pos] - '1';
	a[a_pos] = borrow + '0';

	// restore a_pos to its original location.
	a_pos = current_pos; 
      }

      // The next left number is not 0
      else
      {
	borrow = a[a_pos] - '1';
	a[a_pos] = borrow + '0';
      }

      // used for debugging.
      //cout << "Borrow is " << borrow << endl;
      //cout << "a[a_pos] is " << a[a_pos] << endl;
      //cout << "Borrow is now " << a[a_pos] << endl;
      //cout << "a is now " << a << endl;
    }
    

    // calculate the sum.
    int res;

    // if we borrowed, add 10 to the current number.
    if(is_borrowed)
    {
      res = (10 + a_digit) - b_digit + '0';
    }

    // we did not borrow.
    else
    {	
      res = a_digit - b_digit + '0';
    }

    // reset is_borrowed to false so that we can check future numbers.
    is_borrowed = false;

    // put the sum into the result string at the left
    result.insert(0, 1, static_cast<char>(res));

  }

  // Remove leading 0's
  while(result.length() > 0 && result[0] == '0')
    result.erase(0, 1);

  // if the string is empty the result was 0.
  if(result.length() == 0)
    result = "0";

  //cout << "Result = " << result << endl;
  return result;
}

/*
 * Divide method
 */
string huge_number::divide (string a, string b)
{
  // check if b or a = 0.
  
  // Remove leading 0's for a.
  while(a.length() > 0 && a[0] == '0')
    a.erase(0, 1);
  
  // if the a is empty the result was 0.
  if(a.length() == 0)
    a = "0";
  
  // Remove leading 0's for b.
  while(b.length() > 0 && b[0] == '0')
    b.erase(0, 1);
  
  // if the b is empty the result was 0.
  if(b.length() == 0)
    return "0";
  
  // check if they are equal
  if(a == b)
    return "1";
  
  // check if b > a
  if(is_bigger(a, b))
  {
    //cout << "right is bigger than left, return 0. " << endl;
    return "0";
  }
  
  // If we are dividing by one return a.
  if (b == "1")
    return a;
  
  // initialize a string to return.
  string result = "";
  
  // set up a string that never changes.
  string a_holder = a;
  string new_a = a;
  string b_holder = b;
  
  // set up a string that will change.
  string temp_a = a;
  string temp_b = b;
  
  // set up positions to point
  // i want to be checking the left most digit.
  int a_zero = 0; // will stay at zero.
  int a_pos = 1;
  int count = 1;

  // keeps track of the previous position when subtracting.
  int prev_count = 0;
  string add_to_res = "";
  
  // boolean to check if we are dividing the first time in the loop
  bool is_hit = false;
  
  // set up a string that will hold the substring of a.
  string a_substr = a_holder.substr(a_zero, a_pos);
  
  // while count < the string lenght we are dividing by.
  while(is_bigger(temp_b, new_a) || count < new_a.length() || temp_b == new_a)
  {
    // while b > a substr move a position down a
    if(temp_b != a_substr)
    {
      while(is_bigger(a_substr, temp_b))
      {
	// if we hit the end of the string, break.
	if(count == new_a.length())
	  break;

	// increment count and update the substr
	else
	{
	  count++;
	  a_substr = new_a.substr(0, count);
	}
	
      }
    }

    // at this point we have a substring that is able to fit
    // our divsior.
      
    // case 1: if our divisor will fit into our substring.
    if(is_smaller(a_substr, temp_b) || a_substr == temp_b)
    {
      // figure out how many times our divisor will fit into the substring.
      while(temp_b == a_substr || is_smaller(a_substr, temp_b))
      {
	// update how many times the divisor went into the substring.
	add_to_res = add(add_to_res, "1");
	
	// subtract
	a_substr = subtract(a_substr, temp_b);
      }
    }
    // case 2: if our divisor will not fit into our substring
    else
    {
      // add a zero to the end of our result
      add_to_res = "0";
      count++;
    }

    // update new_a with the remainder from subtraction and the
    // remainder of the substring.
    
    // check if it is our first time in the loop
    if(!is_hit)
    {
      // if it is set prev count to count
      prev_count = count;
      is_hit = true;
    }
    
    // update the old count
    count = a_substr.length();
    
    // update result
    result = result + add_to_res;

    // reset add_to_res
    add_to_res = "";
    
    // remainder is held in a_substr

    // check to see if we have walked the whole length
    if(prev_count == a_holder.length())
      break;

    // update substrings.
    // new_a = difference + remaining digits in numerator
    new_a = a_substr + a_holder.substr(prev_count, (a_holder.length() - prev_count));
    
    // update substring 
    a_substr = new_a.substr(0, count);

    // update previous count
    prev_count++;
    
    
  }


  // ------------------------------------------------------------------------------------------------------------------------------------------------------
  // old divison method, takes too long.

  /*

  string check = "";
  // probably wont work, need to write an is_smaller method.
    while (is_smaller(a_holder, temp_b))
    {
      // if temp_b + b > a_holder
      check = add(temp_b, b_holder);
     
    
      // add temp_b + b and result++
      temp_b = check;

      // check if we are bigger before incrementing.
      if(is_bigger(a_holder, check))
	return result;

      result = add(result, "1");
     }
    //result = add(result, "1");

    //result = result + add_to_res;

    */


  //cout << "Result is = " << result << endl;

  return result;
}


/*
 * Mod method
 */
string huge_number::mod (string a, string b)
{
  // check if b = 0.

  // Remove leading 0's for b.
  while(b.length() > 0 && b[0] == '0')
    b.erase(0, 1);

  // if the b is empty the result was 0.
  if(b.length() == 0)
    return "0";
  
  // anything mod 1 is 0.
  if(b == "1")
    return "0";

  // a % b if b > a return a.
  if(is_bigger(a, b))
    return a;

  // divide to find out how many times b can go into a.
  string temp = divide(a, b);
  //cout << a << " / " << b << " = " << temp << endl;

  // multiply b by how many times it can go into a.
  string temp2 = multiply(temp, b);
  //cout << temp << " * " << b << " = " << temp2 << endl;

  // subtract and return the remainder
  string remainder = subtract(a, temp2);
  //cout << a << " - " << temp2 << " = " << remainder << endl;
  //cout << a << " % " << b << " = " << remainder << endl;
  return remainder;
  
}

/*
 * Override operator =
 */
string & huge_number::operator= (const huge_number & rhs)
{
  //cout << "Assignment called with rhs " << rhs.num << endl;
  num = rhs.num;
  return num;
}

/*
 * Override operator +
 */
const string huge_number::operator + (const huge_number & rhs)
{
  //cout << "Operator + called with " << num << " + " << rhs.num << endl;
  string temp;
  temp = add(num, rhs.num);
  return temp;
}

/*
 * Override operator -
 */
const string huge_number::operator - (const huge_number & rhs)
{
  //cout << "Operator - called with " << num << " - " << rhs.num << endl;
  string temp;
  temp = subtract(num, rhs.num);
  return temp;
}

/*
 * Override operator /
 */
const string huge_number::operator / (const huge_number & rhs)
{
  //cout << "Operator / called with " << num << " / " << rhs.num << endl;
  string temp;
  temp = divide(num, rhs.num);
  return temp;
}

/*
 * Override operator %
 */
const string huge_number::operator % (const huge_number & rhs)
{
  //cout << "Operator % called with " << num << " % " << rhs.num << endl;
  string temp;
  temp = mod(num, rhs.num);
  return temp;
}

/*
 * Override operator *
 */
const string huge_number::operator * (const huge_number & rhs)
{
  //cout << "Operator * called with " << num << " * " << rhs.num << endl;
  string temp;
  temp = multiply(num, rhs.num);
  return temp;
}

/*
 * Helper method to help see if the rhs number is bigger
 * than the lhs number.  If this is the case then subtraction would
 * result in a negative number.  According to the specifications we 
 * need to prevent this and return 0.
 * b > a
 */
bool huge_number::is_bigger(string a, string b)
{
  //Trim any leading 0's from both numbers.
 
  // Remove leading 0's for a.
  while(a.length() > 0 && a[0] == '0')
    a.erase(0, 1);

  // if the a is empty the result was 0.
  if(a.length() == 0)
    a = "0";

  // Remove leading 0's for b.
  while(b.length() > 0 && b[0] == '0')
    b.erase(0, 1);

  // if the b is empty the result was 0.
  if(b.length() == 0)
    b = "0";

  // case 1: if the rhs length is greator than the
  // lhs length
  if(b.length() > a.length())
  {
    return true;
  }
  // case 2: the lengths are equal.
  else if (a.length() == b.length())
  {
    // check each position for b > a
    for (int i = 0; i < a.length(); i++)
    {
      if(b[i] < a[i])
	return false;
      if(b[i] > a[i])
	return true;
    }
  }
  // case 3: the rhs length is less than the lhs length.
  else if (a.length() > b.length())
    return false;
  else
    return false;

  return false;
}

/*
 * Helper method to see if the rhs number is smaller
 * than the lhs number.  
 * b < a
 */
bool huge_number::is_smaller(string a, string b)
{
  //Trim any leading 0's from both numbers.
 
  // Remove leading 0's for a.
  while(a.length() > 0 && a[0] == '0')
    a.erase(0, 1);

  // if the a is empty the result was 0.
  if(a.length() == 0)
    a = "0";

  // Remove leading 0's for b.
  while(b.length() > 0 && b[0] == '0')
    b.erase(0, 1);

  // if the b is empty the result was 0.
  if(b.length() == 0)
    b = "0";
  
  // case 1: if the rhs length is greator than the
  // lhs length
  if(b.length() > a.length())
  {
    return false;
  }
  // case 2: the lengths are equal.
  else if (a.length() == b.length())
  {
    // check each position for b < a
    for (int i = 0; i < a.length(); i++)
    {
      if(b[i] < a[i])
	return true;
      if(b[i] > a[i])
	return false;
    }
  }
  // case 3: the rhs length is less than the lhs length.
  else // if (b.length() < a.length())
    return true;

  return false;
}
