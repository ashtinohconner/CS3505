// Test class

#include "huge_number.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
  string s = "345";
  huge_number y(s);
  huge_number x(y);
  huge_number z("56");
  huge_number p;
  x.get_value();
  if(x.get_value() == "345")
    cout << "Test 1 passed!" << endl;

  huge_number a("20000000000000000000000000");
  huge_number d("2");
  huge_number c;

  c = a / d + d;
  if(c.get_value() == "10000000000000000000000000")
    cout << "Test 2 passed!" << endl;
 
  huge_number a1("20");
  huge_number d1("2");
  huge_number c1;

  c1 = (a1 * d1);
  if(c.get_value() == "20")
    cout << "Test 3 passed!" << endl;

  // test 4
  string aaa = "123";
  string bbb = "456";
  huge_number xx(aaa);
  huge_number yy(bbb);
  huge_number zz;
  // 56088 - 123
  zz = xx * yy;
  zz = zz - xx;
  if(zz.get_value() == "55965")
    cout << "Test 4 passed!" << endl;

  
  // big test
  huge_number aa("101");
  huge_number bb("10"); // 101 / 10 = 10
  //huge_number cc("");
  //huge_number dd("");
  //huge_number ee("");
  //huge_number ff("");

  /*
  g = e % f;

  j = h % i;
  */
  return 0;
}
