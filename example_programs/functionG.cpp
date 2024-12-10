#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

void functionG(const string &input)
{
  try
  {
    int value = stoi(input);
    if (value > 100)
    {
      int i = 3;
      i = 4;
      i = 5;
      i = 6;
    }
    else if (value > 10)
    {
      int i = 3;
      i = 4;
      i = 5;
    }
    else
    {
      int i = 3;
      i = 4;
    }
  }
  catch (const invalid_argument &)
  {
    int i = 3;
  }
}