/*
 * Test class adapted from the given tester.cpp class.
 * Each of the included tests look at several aspects of the
 * lineset class. Every class uses the verify method to make sure
 * results are truly correct (by comparing to contents of equal built
 * in set). Every class uses the constructor and destructor call counts
 * for both lineset and node objects to verify there have not been 
 * memory leaks.
 *
 * yankee.txt is necessary for one test. No other text files are required.
 *
 * Student Author: Kallie Bracken
 * 1/23/2014
 */

#include <iostream>
#include <fstream>
#include <set>
#include <iterator>
#include "lineset.h"
#include "node.h"
#include <sstream>

using namespace std;

// Note:  Our classes were declared in a cs3505 namepsace.
//        Instead of 'using namespace cs3505', I qualify our class names below with cs3505::

/*
 * Method used to see if elements of a given lineset are equal to 
 * elements of built in set. Iterates through built in set and uses 
 * contains method of lineset to see if each element is contained in 
 * the set.
 */
bool verify(cs3505::lineset ourSet, set<string> builtInSet)
{
    for (set<string>::iterator it = builtInSet.begin(); it != builtInSet.end(); it++)
    {
      string s = *it;
      if (!ourSet.contains(s))
	return false;
      
    }

    return true;
}

/* Adapted from given test. Adds and removes elements from
 * the lineset then uses verify method to make sure result
 * matches contents of built in set class.
 */
bool test_yankee_remove()
{
  cout << "Running test_yankee_remove()... ";

  string result = "PASSED.";
  
  {
    // Create the two sets.  Declaring the local variables constructs the objects.
  
    set<string>      stl_set_of_words;  // The built-in set class - no constructor parameters.

    cs3505::lineset  our_set_of_words(100);  // Our set class, with a hashtable of 1000 slots. // RESET TO 10000
  
    // Open the file stream for reading.  (We'll be able to use it just like
    //   the keyboard stream 'cin'.)

    ifstream in("Yankee.txt");

    // Loop for reading the file.  Note that it is controlled
    //   from within the loop (see the 'break').
    
    while (true)
    {
      // Read a word (don't worry about punctuation)
      
      string word;
      in >> word;

      // If the read failed, we're probably at end of file
      //   (or else the disk went bad).  Exit the loop.
      
      if (in.fail())
	break;

      // Word successfully read.  Add it to both sets.
      
      stl_set_of_words.insert(word);
      our_set_of_words.add(word);
    }

    // Close the file.

    in.close();

    // Make sure lineset and our set have same words
    if (!verify(our_set_of_words, stl_set_of_words))
      result = "FAILED: Discrepency between strings in built in set and in lineset.";

    // Try removing a word
    our_set_of_words.remove("DAMAGE.");
    stl_set_of_words.erase("DAMAGE.");
        // Make sure lineset and our set have same words

    if (!verify(our_set_of_words, stl_set_of_words))
      result = "FAILED: Discrepency between strings in built in set and in lineset.";

    our_set_of_words.add("DAMAGE.");
    stl_set_of_words.insert("DAMAGE.");

    // verify nuber of words in each set.
    if (stl_set_of_words.size()!=our_set_of_words.size())
       result = "FAILED: Discrepency between strings in built in set and in lineset.Set sizes do not match.";
      
  }

  // Verify lineset and node constructor and destructor counts
  if(cs3505::lineset::constructor_count()!=cs3505::lineset::destructor_count())
     result = "FAILED: Lineset constructor and destructor counts do not match.";

  if(cs3505::node::constructor_count()!=cs3505::node::destructor_count())
     result = "FAILED: Node constructor and destructor counts do not match.";

  cout << result << endl;

  if(result == "PASSED.")
    return true;
  
  return false;

}

bool test_remove()
{

  cout << "Running test_remove()... ";

  string result = "PASSED.";
  
  {
    // Create the two sets.  Declaring the local variables constructs the objects.
  
    set<string>      builtIn;  // The built-in set class - no constructor parameters.

    cs3505::lineset  set(100); 
    set.add("Apple");
    builtIn.insert("Apple");
       
    if (!verify(set, builtIn))
      result = "FAILED: Discrepency between strings in built in set and in lineset.";
	
    if(set.size()!=1)
      result = "FAILED: Failed to add element to set.";

    set.remove("Apple");
    builtIn.erase("Apple");

    if (!verify(set, builtIn))
      result = "FAILED: Discrepency between strings in built in set and in lineset.";
	
    if(set.size()!=0)
      result = "FAILED: Failed to remove element from set.";

    set.add("Apple");
    set.add("Baby");
    set.add("Carrot");
    builtIn.insert("Apple");
    builtIn.insert("Baby");
    builtIn.insert("Carrot");

    if (!verify(set, builtIn))
      result = "FAILED: Discrepency between strings in built in set and in lineset.";

    // verify nuber of words in each set.
    if (set.size()!=builtIn.size() && set.size()!=3)
      result = "FAILED: Discrepency between strings in built in set and in lineset.Set sizes do not match.";
 
    set.remove("Apple");
    builtIn.erase("Apple");

    if (!verify(set, builtIn))
      result = "FAILED: Discrepency between strings in built in set and in lineset.";

    // verify nuber of words in each set.
    if (set.size()!=builtIn.size() && set.size()!=2)
      result = "FAILED: Discrepency between strings in built in set and in lineset.Set sizes do not match.";
 
    set.remove("Apple");
    set.remove("NotInSet");

    if (!verify(set, builtIn))
      result = "FAILED: Discrepency between strings in built in set and in lineset.";

    // verify nuber of words in each set.
    if (set.size()!=builtIn.size() && set.size()!=2)
      result = "FAILED: Discrepency between strings in built in set and in lineset.Set sizes do not match.";

    set.remove("Carrot");
    set.remove("Baby");
    builtIn.erase("Carrot");
    builtIn.erase("Baby");

    if (!verify(set, builtIn))
      result = "FAILED: Discrepency between strings in built in set and in lineset.";

    // verify nuber of words in each set.
    if (set.size()!=builtIn.size() && set.size()!=0)
      result = "FAILED: Discrepency between strings in built in set and in lineset.Set sizes do not match.";

    }

    // Verify lineset and node constructor and destructor counts
  if(cs3505::lineset::constructor_count()!=cs3505::lineset::destructor_count())
     result = "FAILED: Lineset constructor and destructor counts do not match.";

  if(cs3505::node::constructor_count()!=cs3505::node::destructor_count())
     result = "FAILED: Node constructor and destructor counts do not match.";

  cout << result << endl;

  if(result == "PASSED.")
    return true;
  
  return false;

}

bool test_eqoperator()
{
  cout << "Running test_eqoperator()... ";

  string result = "PASSED.";
  
  {
    // Create the two sets.  Declaring the local variables constructs the objects.
  
    set<string>      builtIn;  // The built-in set class - no constructor parameters.
    set<string>      builtInb;
    set<string>      builtInEmpty;
    set<string>      builtInEmpty2;

    cs3505::lineset  set(10000); 
    cs3505::lineset  setb(3);
    cs3505::lineset  emptySet;
    cs3505::lineset  emptySet2;

    set.add("one");
    set.add("two");
    set.add("three");
    set.add("four");
    set.add("five");
    set.add("six");
    set.add("seven");
    builtIn.insert("one");
    builtIn.insert("two");
    builtIn.insert("three");
    builtIn.insert("four");
    builtIn.insert("five");
    builtIn.insert("six");
    builtIn.insert("seven");

    set.add("six"); // Shouldn't add again

    // verify nuber of words in each set.
    if (set.size()!=builtIn.size() && set.size()!=7)
      result = "FAILED: Discrepency between strings in built in set and in lineset.Set sizes do not match.";

    if (!verify(set, builtIn))
      result = "FAILED: Discrepency between strings in built in set and in lineset. Ref #1.";
    
    builtInb.insert("apple");
    builtInb.insert("baby");
    builtInb.insert("cat");
    builtInb.insert("dog");
    setb.add("apple");
    setb.add("baby");
    setb.add("cat");
    setb.add("dog");

    // verify nuber of words in each set.
    if (setb.size()!=builtInb.size() && set.size()!=4)
      result = "FAILED: Discrepency between strings in built in set and in lineset.Set sizes do not match.";


    if (!verify(setb, builtInb))
      result = "FAILED: Discrepency between strings in built in set and in lineset.Ref #2.";

    setb = set;

    if (!verify(setb, builtIn))
      result = "FAILED: Discrepency between strings in built in set and in lineset.Ref #3.";
 
    if (!verify(emptySet, builtInEmpty))
      result = "FAILED: Discrepency between strings in built in set and in lineset.Ref #4.";
 
    emptySet = setb;

    if (!verify(emptySet, builtIn))
      result = "FAILED: Discrepency between strings in built in set and in lineset.Ref #5.";


    setb = emptySet2; 

    if (!verify(setb, builtInEmpty2))
      result = "FAILED: Discrepency between strings in built in set and in lineset.Ref #6.";

  }

  // Verify lineset and node constructor and destructor counts
  if(cs3505::lineset::constructor_count()!=cs3505::lineset::destructor_count())
     result = "FAILED: Lineset constructor and destructor counts do not match.";

  if(cs3505::node::constructor_count()!=cs3505::node::destructor_count())
     result = "FAILED: Node constructor and destructor counts do not match.";

  cout << result << endl;

  if(result == "PASSED.")
    return true;
  
  return false;
  
}

bool test_get_elements()
{
  cout << "Running test_get_elements()... ";

  string result = "PASSED.";

  {
    set<string>      builtIn; 
    cs3505::lineset set(5);
    cs3505::lineset resultSet(5);

    set.add("one");
    set.add("two");
    set.add("three");
    set.add("four");
    set.add("five");
    set.add("six");
    set.add("seven");
    set.add("six"); // Shouldn't add again
    builtIn.insert("one");
    builtIn.insert("two");
    builtIn.insert("three");
    builtIn.insert("four");
    builtIn.insert("five");
    builtIn.insert("six");
    builtIn.insert("seven");

    if (!verify(set, builtIn))
      result = "FAILED: Discrepency between strings in built in set and in lineset.Ref #1.";
 
    string *array = new string[set.size()]; 
    int n = set.size();
      
    set.get_elements(array, n);

    for (int i = 0; i<n; i++)
      resultSet.add(array[i]); // Fill result lineset from array

    // Make sure all elements survived!

    if (!verify(resultSet, builtIn))
      result = "FAILED: Discrepency between strings in built in set and in lineset.Ref #2.";
 
  }


      // Verify lineset and node constructor and destructor counts
  if(cs3505::lineset::constructor_count()!=cs3505::lineset::destructor_count())
     result = "FAILED: Lineset constructor and destructor counts do not match.";

  if(cs3505::node::constructor_count()!=cs3505::node::destructor_count())
     result = "FAILED: Node constructor and destructor counts do not match.";

  cout << result << endl;

  if(result == "PASSED.")
    return true;
  
  return false;
  

}



bool test_defaultConstructor()
{
  cout << "Running test_defaultConstructor()... ";

  string result = "PASSED.";

  {
      cs3505::lineset set;
      if (set.size()!=0)
	result = "FAILED: Set size not equal to zero.";

  }

    // Verify lineset and node constructor and destructor counts
  if(cs3505::lineset::constructor_count()!=cs3505::lineset::destructor_count())
     result = "FAILED: Lineset constructor and destructor counts do not match.";

  if(cs3505::node::constructor_count()!=cs3505::node::destructor_count())
     result = "FAILED: Node constructor and destructor counts do not match.";

  cout << result << endl;

  if(result == "PASSED.")
    return true;
  
  return false;
  
}

bool test_defaultConstructor_capacity()
{
  cout << "Running test_defaultConstructor_capacity()... ";

  string result = "PASSED.";

  {
    cs3505::lineset set(1000000);
      if (set.size()!=0)
	result = "FAILED: Set size not equal to zero.";

  }

    // Verify lineset and node constructor and destructor counts
  if(cs3505::lineset::constructor_count()!=cs3505::lineset::destructor_count())
     result = "FAILED: Lineset constructor and destructor counts do not match.";

  if(cs3505::node::constructor_count()!=cs3505::node::destructor_count())
     result = "FAILED: Node constructor and destructor counts do not match.";

  cout << result << endl;

  if(result == "PASSED.")
    return true;
  
  return false;

}

bool test_add_remove_aLot()
{
  cout << "Running test_add_aLot()... ";

  string result = "PASSED.";

  {
    set<string>      builtIn; 
    cs3505::lineset set(1000000);

    set.remove("Happy");

    // make sure trying to remove from empty set doesn't break anything
    if (set.size()!=builtIn.size() && set.size()!=0)
      result = "FAILED: Set size not equal to 0.";
    
    for (int i =0; i<300000 ; i++)
      {
	string s = "";

	ostringstream converter;
	converter << i;
	
	s = s.append(converter.str());

	set.add(s);
	set.add("Element");
	builtIn.insert(s);
	builtIn.insert("Element");
      }

    // verify nuber of words in each set.

    if (set.size()!=builtIn.size() && set.size()!=300001)
      result = "FAILED: Set size not equal to 3,000,001.";

    for (int i =0; i<300 ; i++)
      {
	set.remove("Element");
	builtIn.erase("Element");
      }

    // verify nuber of words in each set.
    if (set.size()!=builtIn.size() && set.size()!=300000)
      result = "FAILED: Set size not equal to 3,000,001.";

    // Make sure sets contain the same elements
    if (!verify(set, builtIn))
      result = "FAILED: Discrepency between strings in built in set and in lineset.";

  }

    // Verify lineset and node constructor and destructor counts
  if(cs3505::lineset::constructor_count()!=cs3505::lineset::destructor_count())
     result = "FAILED: Lineset constructor and destructor counts do not match.";

  if(cs3505::node::constructor_count()!=cs3505::node::destructor_count())
     result = "FAILED: Node constructor and destructor counts do not match.";

  cout << result << endl;

  if(result == "PASSED.")
    return true;
  
  return false;
  
}

bool test_copyConstructor_getElements()
{
  cout << "Running test_copyConstructor_getELements()... ";

  string result = "PASSED.";

  {
    set<string>      resultSet;
    cs3505::lineset set(1000000);

    // fill set
    for (int i =0; i<300000 ; i++)
      {
	string s = "";

	ostringstream converter;
	converter << i;
	
	s = s.append(converter.str());

	set.add(s);
      }

    // verify nuber of words in set.
    if (set.size()!=300000)
      result = "FAILED: Set size not equal to 3,000,000.";

    cs3505::lineset copyConstructorSet(set);
    
    // Put copyCOnstructor set into array
    string *array = new string[copyConstructorSet.size()]; 
    int n = copyConstructorSet.size();
      
    copyConstructorSet.get_elements(array, n);

    for (int i = 0; i<n; i++)
      resultSet.insert(array[i]); // Fill result lineset from array
    
    // Make sure sets contain the same elements
    if (!verify(set,resultSet))
      result = "FAILED: Discrepency between strings in built in set and in lineset.";

  }

    // Verify lineset and node constructor and destructor counts
  if(cs3505::lineset::constructor_count()!=cs3505::lineset::destructor_count())
     result = "FAILED: Lineset constructor and destructor counts do not match.";

  if(cs3505::node::constructor_count()!=cs3505::node::destructor_count())
     result = "FAILED: Node constructor and destructor counts do not match.";

  cout << result << endl;

  if(result == "PASSED.")
    return true;
  
  return false;
}


int main ()
{

  bool set_of_tests_1 = (test_yankee_remove() && test_remove() && test_eqoperator() && test_get_elements());
  bool set_of_tests_2= (test_defaultConstructor() && test_defaultConstructor_capacity() && test_add_remove_aLot() && test_copyConstructor_getElements());
  bool all_passed = (set_of_tests_1 && set_of_tests_2);

  if (all_passed)
    cout << "Tests passed" << endl;
  else
    cout << "Tests failed" << endl;
  
  return 0;
}

