/*
 * This is a tester similar to the tester written in class.  It reads
 * words from a text file, then adds the words to two sets: A built-in
 * set class, and our lineset class.  After reading the file, it
 * prints out all the words stored in the STL set object.  At the end
 * of the test, it prints out the sizes of both sets to see that they
 * are the same.
 *
 * After the test completes, I make sure the local variabls are properly
 * cleaned up.
 *
 * If the comments wrap lines, widen your emacs window.
 *
 * Peter Jensen
 * January 17, 2014
 */

#include <iostream>
#include <fstream>
#include <set>
#include <iterator>
#include "lineset.h"
#include "node.h"

using namespace std;

// Note:  Our classes were declared in a cs3505 namepsace.
//        Instead of 'using namespace cs3505', I qualify our class names below with cs3505::

int main ()
{
  // Open up another block.  This way, when the block ends,
  // variables local to the block will be destroyed, but main
  // will still be running.  (Did you know that you can open
  // up a block at any time to control local variable scope and
  // lifetime?)
  bool tests_passed = true;

  /*******************************************************************************************
   *                                                                                         *
   *                                       TEST 1                                            *
   *                                                                                         *
   *******************************************************************************************/
  {
    // Create the two sets.  Declaring the local variables constructs the objects.
    cout << "TEST 1: add method\n";
    set<string>      stl_set_of_words;  // The built-in set class - no constructor parameters.

    cs3505::lineset  our_set_of_words(1000);  // Our set class, with a hashtable of 1000 slots.
  
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

    // Print out the words found in the STL set.  I do this to show
    //   students how to get at the entries in an STL object.  For
    //   more examples, look up 'STL iterator examples'.
    // Notice that the iterator object 'it' acts like a pointer, but
    //   it is not a pointer.  (Bad, bad, bad design choice, but not mine!)
    // Feel free to comment this out.
  
    //for (set<string>::iterator it = stl_set_of_words.begin(); it != stl_set_of_words.end(); it++)
    //{
    //string s = *it;
    //cout << s << endl;
    //}

    if(stl_set_of_words.size() != our_set_of_words.size())
    {
      tests_passed = false;
      cout << "Test 1 failed\n";
      cout << "Not all elements were added!\n";
    }
    else
      cout << "Test 1 passed.\n";

    // Print out the number of words found in each set.

    // Done.  Notice that this code block ends below.  Any local
    // variables declared within this block will be automatically
    // destroyed.  Local objects will have their destructors
    // called.

  }


  /*******************************************************************************************
   *                                                                                         *
   *                                     TEST 2 Remove                                       *
   *                                                                                         *
   *******************************************************************************************/
  {
    // Create the two sets.  Declaring the local variables constructs the objects.
    cout << "TEST 2: remove method\n";
    cout << "Remove items and try removing the same item again.\n";
    set<string>      stl_set_of_words;  // The built-in set class - no constructor parameters.

    cs3505::lineset  our_set_of_words(1000);  // Our set class, with a hashtable of 1000 slots.
  
    // Open the file stream for reading.  (We'll be able to use it just like
    //   the keyboard stream 'cin'.)

    ifstream in("QuickTest.txt");

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

    // TRY TO REMOVE SOMETHING THAT SHOULD EXIST
    stl_set_of_words.erase("hello");
    stl_set_of_words.erase("tony");
    stl_set_of_words.erase("chen");
    stl_set_of_words.erase("hello"); // try removing it again.
    stl_set_of_words.erase("wasel");

    our_set_of_words.remove("hello");
    our_set_of_words.remove("tony");
    our_set_of_words.remove("chen");
    our_set_of_words.remove("hello"); // try removing it again.
    our_set_of_words.remove("wasel");
    //our_set_of_words.add("wasel");
    
    if(stl_set_of_words.size() != our_set_of_words.size())
    {
      tests_passed = false;
      cout << "Test 2 failed\n";
      cout << "Not all elements were removed!\n";
    }
    else
      cout << "Test 2 passed.\n";

    // Done.  Notice that this code block ends below.  Any local
    // variables declared within this block will be automatically
    // destroyed.  Local objects will have their destructors
    // called.

  }


  /*******************************************************************************************
   *                                                                                         *
   *                                    TEST 3 Operator =                                    *
   *                                                                                         *
   *******************************************************************************************/
  {
    // Create the two sets.  Declaring the local variables constructs the objects.
    cout << "TEST 3: Operator = test\n";
    cout << "Test if the sizes are the same after copying.\n";
    cs3505::lineset  our_set_of_words(100);  // Our set class, with a hashtable of 100 slots.
    cs3505::lineset  copy;                  // copy of our class should default to capacity 100.
  
    // add words
    our_set_of_words.add("balls");
    our_set_of_words.add("cheese");
    our_set_of_words.add("monkey");
    our_set_of_words.add("virus");
    our_set_of_words.add("pringle");
    our_set_of_words.add("smog");
    our_set_of_words.add("inversion");
    our_set_of_words.add("poop");
    our_set_of_words.add("wasel");

    // try the operator =
    copy = our_set_of_words;  

    if(copy.size() != our_set_of_words.size())
    {
      tests_passed = false;
      cout << "Test 3 failed\n";
      cout << "Not all elements were copied over!\n";
    }
    else
      cout << "Test 3 passed.\n";
 
    // Done.  Notice that this code block ends below.  Any local
    // variables declared within this block will be automatically
    // destroyed.  Local objects will have their destructors
    // called.
  }

  /*******************************************************************************************
   *                                                                                         *
   *                                    TEST 4 Operator =                                    *
   *                      and test removing stuff from the original list                     *
   *                                                                                         *
   *******************************************************************************************/
  {
    // Create the two sets.  Declaring the local variables constructs the objects.
    cout << "TEST 4: Operator = test\n";
    cout << "Test operator = and modify the original set after copying.\n";
    cs3505::lineset  our_set_of_words(100);  // Our set class, with a hashtable of 100 slots.
    cs3505::lineset  copy;                  // copy of our class should default to capacity 100.
  
    // add words
    our_set_of_words.add("balls");
    our_set_of_words.add("cheese");
    our_set_of_words.add("monkey");
    our_set_of_words.add("virus");
    our_set_of_words.add("pringle");
    our_set_of_words.add("smog");
    our_set_of_words.add("inversion");
    our_set_of_words.add("poop");
    our_set_of_words.add("wasel");

    // try the operator =
    copy = our_set_of_words;

    // try removing stuff from set 1.  set 2 should be unchanged.
    our_set_of_words.remove("virus");
    our_set_of_words.remove("smog");

    if(copy.size() != 9 && our_set_of_words.size() != 7)
    {
      tests_passed = false;
      cout << "Test 4 failed!\n";
      cout << "The copy set was changed along with the original set!\n";
    }
    else
      cout << "Test 4 passed.\n";
    
    // Done.  Notice that this code block ends below.  Any local
    // variables declared within this block will be automatically
    // destroyed.  Local objects will have their destructors
    // called.
  }

  /*******************************************************************************************
   *                                                                                         *
   *                                  TEST 5 get_elements                                    *
   *                      test getting elements and doing stuff with it                      *
   *                                    n = set.size()                                       *
   *                                                                                         *
   *******************************************************************************************/
  {
    // Create the two sets.  Declaring the local variables constructs the objects.
    cout << "TEST 5: \n";
    cout << "Getting n elements.  n = set.size()\n";
    cs3505::lineset  our_set_of_words(100);  // Our set class, with a hashtable of 100 slots.
  
    // add words
    our_set_of_words.add("balls");
    our_set_of_words.add("cheese");
    our_set_of_words.add("monkey");
    our_set_of_words.add("virus");
    our_set_of_words.add("pringle");
    our_set_of_words.add("smog");
    our_set_of_words.add("inversion");
    our_set_of_words.add("poop");
    our_set_of_words.add("wasel");

    // notify what we're doing.
    cout << "Getting elements from original set.\n";

    // Try to get n elements.  n = set.size()
    int n = 9;
    string *e = new string[n];
  
    our_set_of_words.get_elements(e, n);

    bool legit_words = true;

    // Check the items we got.
    for (int i = 0; i < n; i++)
    {
      string check = e[i];
      if(!(our_set_of_words.contains(check)))
      {
	legit_words = false;
      }
    }
   
    delete [] e;
   
    if(legit_words == false)
    {
      tests_passed = false;
      cout << "Test 5 failed!\n";
      cout << "The array contains something not in the set!\n";
    }
    else
      cout << "Test 5 passed.\n";

    // Done.  Notice that this code block ends below.  Any local
    // variables declared within this block will be automatically
    // destroyed.  Local objects will have their destructors
    // called.
  }

  /*******************************************************************************************
   *                                                                                         *
   *                                  TEST 6 get_elements                                    *
   *                      test getting elements and doing stuff with it                      *
   *                                    n < set.size()                                       *
   *                                                                                         *
   *******************************************************************************************/
  {
    // Create the two sets.  Declaring the local variables constructs the objects.
    cout << "TEST 6: \n";
    cout << "Getting n elements.  n < set.size()\n";
    cs3505::lineset  our_set_of_words(100);  // Our set class, with a hashtable of 100 slots.
  
    // add words
    our_set_of_words.add("balls");
    our_set_of_words.add("cheese");
    our_set_of_words.add("monkey");
    our_set_of_words.add("virus");
    our_set_of_words.add("pringle");
    our_set_of_words.add("smog");
    our_set_of_words.add("inversion");
    our_set_of_words.add("poop");
    our_set_of_words.add("wasel");
  
    // Try to get n elements.  n < set.size()
    int n = 4;
    string *e = new string[n];
  
    our_set_of_words.get_elements(e, n);

    bool legit_words = true;

    // Check the items we got.
    for (int i = 0; i < n; i++)
    {
      string check = e[i];
      if(!(our_set_of_words.contains(check)))
      {
	legit_words = false;
      }
    }

    delete [] e;
 
    if(legit_words == false)
    {
      tests_passed = false;
      cout << "Test 6 failed!\n";
      cout << "The array contains something not in the set!\n";
    }
    else
      cout << "Test 6 passed.\n";

    // Done.  Notice that this code block ends below.  Any local
    // variables declared within this block will be automatically
    // destroyed.  Local objects will have their destructors
    // called.
  }

  /*******************************************************************************************
   *                                                                                         *
   *                                  TEST 7 get_elements                                    *
   *                      test getting elements and doing stuff with it                      *
   *                                    n > set.size()                                       *
   *                                                                                         *
   *******************************************************************************************/
  {
    // Create the two sets.  Declaring the local variables constructs the objects.
    cout << "TEST 7: \n";
    cout << "Getting n elements.  n > set.size()\n";
    cs3505::lineset  our_set_of_words(100);  // Our set class, with a hashtable of 100 slots.
  
    // add words
    our_set_of_words.add("balls");
    our_set_of_words.add("cheese");
    our_set_of_words.add("monkey");
    our_set_of_words.add("virus");
    our_set_of_words.add("pringle");
    our_set_of_words.add("smog");
    our_set_of_words.add("inversion");
    our_set_of_words.add("poop");
    our_set_of_words.add("wasel");

    // Try to get n elements.  n > set.size()
    int n = 100;
    string *e = new string[n];
  
    our_set_of_words.get_elements(e, n);
   
    bool legit_words = true;

    // Check the items we got.
    for (int i = 0; i < our_set_of_words.size(); i++)
    {
      string check = e[i];
      if(!(our_set_of_words.contains(check)))
      {
	legit_words = false;
      }
    }

    delete [] e;

    if(legit_words == false)
    {
      tests_passed = false;
      cout << "Test 7 failed!\n";
      cout << "The array contains something not in the set!\n";
    }
    else
      cout << "Test 7 passed.\n";
   
    // Done.  Notice that this code block ends below.  Any local
    // variables declared within this block will be automatically
    // destroyed.  Local objects will have their destructors
    // called.
  }

  /*******************************************************************************************
   *                                                                                         *
   *                                  TEST 8 get_elements                                    *
   *                      test operator = and then delete the object.                        *
   *                                                                                         *
   *******************************************************************************************/
  {
    // Create the two sets.  Declaring the local variables constructs the objects.
    cout << "TEST 8: \n";
    cout << "Test operator = and then deleting the object.\n";
    cs3505::lineset  copy(100); 
    
    {
      cs3505::lineset  our_set_of_words(100);  // Our set class, with a hashtable of 100 slots.
  
      // add words
      our_set_of_words.add("balls");
      our_set_of_words.add("cheese");
      our_set_of_words.add("monkey");
      our_set_of_words.add("virus");
      our_set_of_words.add("pringle");
      our_set_of_words.add("smog");
      our_set_of_words.add("inversion");
      our_set_of_words.add("poop");
      our_set_of_words.add("wasel");

      // try the operator =
      copy = our_set_of_words;
    }
    // at this point our_set_of_words is deleted.

    // check if copy is still populated.
    if(copy.size() != 9)
    {
      tests_passed = false;
      cout << "Test 8 failed!\n";
      cout << "The copy set was changed along with the original set!\n";
    }
    else
      cout << "Test 8 passed.\n";
    
    // Done.  Notice that this code block ends below.  Any local
    // variables declared within this block will be automatically
    // destroyed.  Local objects will have their destructors
    // called.
  }

  /*******************************************************************************************
   *                                                                                         *
   *                                  TEST 9 get_elements                                    *
   *                                  Test doing everything all at once                      *
   *                                                                                         *
   *******************************************************************************************/
  {
    // Create the two sets.  Declaring the local variables constructs the objects.
    cout << "TEST 9: \n";
    cout << "Testing everything.\n";
    
    bool test_9_passed = true;
    
    cs3505::lineset  our_set_of_words(100);  // Our set class, with a hashtable of 100 slots.
  
    // add words
    our_set_of_words.add("balls");
    our_set_of_words.add("cheese");
    our_set_of_words.add("monkey");
    our_set_of_words.add("virus");
    our_set_of_words.add("pringle");
    our_set_of_words.add("smog");
    our_set_of_words.add("inversion");
    our_set_of_words.add("poop");
    our_set_of_words.add("wasel");

    // remove an item.
    our_set_of_words.remove("wasel");

    // check that the item was deleted.
    if(our_set_of_words.contains("wasel"))
    {
      cout << "Error!  Item was not deleted\n";
      test_9_passed = false;
      tests_passed = false;
    }
    
    // Try to get n elements.  n > set.size()
    int n = 100;
    string *e = new string[n];
  
    our_set_of_words.get_elements(e, n);
   
    bool legit_words = true;

    // Check the items we got.
    for (int i = 0; i < our_set_of_words.size(); i++)
    {
      string check = e[i];
      if(!(our_set_of_words.contains(check)))
      {
	legit_words = false;
      }
    }

    delete [] e;

    if(legit_words == false)
    {
      tests_passed = false;
      cout << "Test 9 failed!\n";
      cout << "The array contains something not in the set!\n";
      test_9_passed = false;
    }
    

    // copy
    cs3505::lineset  copy;
    
    copy = our_set_of_words;

    if(copy.contains("wasel"))
    {
      cout << "Test 9 failed!\n";
      cout << "The array contains an item that was deleted!\n";
      test_9_passed = false;
      tests_passed = false;
    }

    

    if(test_9_passed)
      cout << "Test 9 passed.\n";
    // Done.  Notice that this code block ends below.  Any local
    // variables declared within this block will be automatically
    // destroyed.  Local objects will have their destructors
    // called.
  }

  /*******************************************************************************************
   *                                                                                         *
   *                                     TEST 10 Remove                                      *
   *                         Test removing on a set with size of 1                           *
   *                                                                                         *
   *******************************************************************************************/
  {
    // Create the two sets.  Declaring the local variables constructs the objects.
    cout << "TEST 10: remove method\n";
    cout << "Remove items on a hash set with size 1\n";
    bool test_10_passed = true;

    {
      cs3505::lineset  set(1);  // Our set class, with a hashtable of 1 slot.
    
      set.add("mask");
      set.add("men");
      set.add("love");
      set.add("GameBoy");
      set.add("Ski");
      set.add("Utah");
      set.add("hello");
      set.add("jon");
      set.add("peter");
      set.add("jon");
      set.add("tony");
      set.add("rachel");
      set.add("notice");
      set.add("that");
      set.add("this");
      set.add("code");
      set.add("block");
      set.add("ends");
      set.add("below");
      set.add("any");
      set.add("local");
      

      // since items were all hashed at index 1 they should be in the same order.
      set.remove("mask");         // 1
      set.remove("men");          // 2
      set.remove("love");         // 3
      set.remove("GameBoy");      // 4
      set.remove("Ski");          // 5
      set.remove("Utah");         // 6
      set.remove("hello");        // 7
      set.remove("jon");          // 8
      set.remove("peter");        // 9
      set.remove("jon");          // 10
      set.remove("tony");         // 11
      set.remove("rachel");       // 12
      set.remove("notice");       // 13
      set.remove("that");         // 14
      set.remove("this");         // 15
      set.remove("code");         // 16
      set.remove("block");        // 17
      set.remove("ends");         // 18
      set.remove("below");        // 19
      set.remove("any");          // 20
      set.remove("local");        // 21

      if(set.size() != 0 || set.contains("tony"))
      {
	cout << "Test 10 failed!\n";
	cout << "The array contains an item that was deleted!\n";
	test_10_passed = false;
	tests_passed = false;
      }
    
    }


    // second part of test ----------------------------------------------------------------
    {
      cs3505::lineset  set(1);  // Our set class, with a hashtable of 1 slot.
    
      set.add("mask");
      
      // since items were all hashed at index 1 they should be in the same order.
      set.remove("mask");         // 1

      if(set.size() != 0 || set.contains("mask"))
      {
	cout << "Test 10 failed!\n";
	cout << "The array contains an item that was deleted!\n";
	test_10_passed = false;
	tests_passed = false;
      }
    
    }

    // third part of test ----------------------------------------------------------------
    {
      cs3505::lineset  set(1);  // Our set class, with a hashtable of 1 slot.
    
      set.add("mask");
      set.add("men");
      set.add("love");
      set.add("GameBoy");
      set.add("Ski");
      set.add("Utah");
      set.add("hello");
      set.add("jon");
      set.add("peter");
      set.add("jon");
      set.add("tony");
      set.add("rachel");
      set.add("notice");
      set.add("that");
      set.add("this");
      set.add("code");
      set.add("block");
      set.add("ends");
      set.add("below");
      set.add("any");
      set.add("local");
      

      // since items were all hashed at index 1 they should be in the same order.
      set.remove("local");        // 21
      set.remove("rachel");       // 12
      set.remove("Utah");         // 6
      set.remove("love");         // 3
      set.remove("that");         // 14
      set.remove("tony");         // 11
      set.remove("any");          // 20
      set.remove("block");        // 17
      set.remove("GameBoy");      // 4
      set.remove("men");          // 2
      set.remove("Ski");          // 5
      set.remove("hello");        // 7
      set.remove("this");         // 15
      set.remove("jon");          // 8
      set.remove("mask");         // 1
      set.remove("code");         // 16
      set.remove("peter");        // 9
      set.remove("jon");          // 10
      set.remove("ends");         // 18
      set.remove("notice");       // 13
      set.remove("below");        // 19

      if(set.size() != 0 || set.contains("ends"))
      {
	cout << "Test 10 failed!\n";
	cout << "The array contains an item that was deleted!\n";
	test_10_passed = false;
	tests_passed = false;
      }
    
    }
    
    if(test_10_passed)
      cout << "Test 10 passed.\n";
    // Done.  Notice that this code block ends below.  Any local
    // variables declared within this block will be automatically
    // destroyed.  Local objects will have their destructors
    // called.

  }

  // Now that the objects have been destroyed, I will simply call my auditing
  // code to print out how many times constructors have been called, and
  // how many times destructors have been called.  They should exactly match.
  // If not, we have a memory problem.

  cout << "Class cs3505::lineset:" << endl;
  cout << "    Objects created:  " << cs3505::lineset::constructor_count() << endl;
  cout << "    Objects deleted:  " << cs3505::lineset::destructor_count() << endl;
  cout << endl;

  cout << "Class cs3505::node:" << endl;
  cout << "    Objects created:  " << cs3505::node::constructor_count() << endl;
  cout << "    Objects deleted:  " << cs3505::node::destructor_count() << endl;
  cout << endl;

  if(tests_passed)
    cout << "Tests passed!\n";
  else
    cout << "Tests Failed!\n";
      
  // Now we're really done.  End main.
  
  return 0;
}
