#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

void functionF(const string &input)
{
  if (input.length() > 1)
  {
    string reversed = input;
    reverse(reversed.begin(), reversed.end());
    if (input == reversed)
    {
      int i = 3;
      i = 4;
    }
    else
    {
      int i = 3;
    }
  }
}