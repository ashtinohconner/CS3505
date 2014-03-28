/* Austin O'Connor
 * U0784820
 * 1/8/14
 *
 * Assignment 1 test_prime.cc
 */

#include <iostream>  // include library def
#include <stdio.h>   //
#include <stdlib.h>  //

using namespace std; // compiling convenience

// main method
int main(int argc, char *argv[])
{
  //used for testing to display each argument passed.
  //int test;
  //cout << "\nCommand args:";
  //for(test = 0; test < argc; test++)
  //cout << " argv[" << test << "] " << argv[test] << "\n";

  // check for correct number of arguments.
  if(argc != 2)
  {
    cout << "Incorrect number of arguments passed.\n";
    return 0;
  }

  int p; // int to hold the number entered.
  p = atoi(argv[1]);
  
  // check if the number is a legit number.
  if(!p)
  {
    cout << "Invalid argument passed.\n";
    return 0;
  }

  bool isPrime; // boolean to check if number is prime.
  isPrime = true; 

  for(int i = 2; i < p; i++)
  {
      // check if the number is divisible by anything but 1 or itself.
      if(p%i == 0) 
      {
	isPrime = false;
	break;
      }
  }
  if(isPrime == false)
  {
      cout << "composite" << "\n"; // print if it is not prime
  }
  else
    cout << "prime"<< "\n"; // print if it is prime
  return 0;
}
