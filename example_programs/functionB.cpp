#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

void functionB(const string &input)
{
  for (size_t i = 0; i < input.length(); ++i)
  {
    if (input[i] == 'x')
    {
      int i = 3;
      i = 4;
    }
    else if (isdigit(input[i]))
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