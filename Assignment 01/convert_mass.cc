/* Austin O'Connor
 * U0784820
 * 1/8/14
 *
 * Assignment 1 convert_mass.cc
 */

#include <iostream> // include library def
//#include <math> // math library
#include <iomanip> // used for rounding

using namespace std; // compiling convenience

// main method
int main()
{
  double weight, holder; // initial weight
  cout << "Enter a weight in pounds to be converted to kilograms: "; // prompt
  
  cin >> weight; // da weight
  if (cin.fail()) // check if the user entered a valid number
  {
    cout << "Sorry, you did not enter a proper weight.\n" << endl; // terminate if not
    return 0;
  }
  holder = weight; 
  weight = weight/2.2046;
  cout << setprecision(2) << fixed << holder << " pounds is " << weight << " kilograms.\n"; // print
  return 0;
}
