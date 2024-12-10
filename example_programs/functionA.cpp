#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

void functionA(const string &input)
{
  if (input.length() == 4)
  {
    int i = 2;
    if (input == "test")
    {
      i = 3;
      i = 4;
      i = 5;
      i = 6;
    }
  }
  else if (input.find("a"))
  {
    if (input.find("abc") != string::npos)
    {
      int i = 3;
      i = 4;
    }
  }
  else if (input.length() > 5)
  {
    int i = 3;
    i = 4;
  }
  else
  {
    int i = 3;
  }
}