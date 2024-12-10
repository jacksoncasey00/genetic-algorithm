#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

void functionC(const string &input)
{
  if (!input.empty())
  {
    int i = 3;
    switch (input[0])
    {
    case 'a':
      i = 3;
      i = 4;
      break;
    case 'b':
      i = 3;
      i = 4;
      break;
    case 'z':
      i = 3;
      i = 4;
      break;
    default:
      i = 3;
      break;
    }
  }
  else
  {
    int i = 3;
  }
}