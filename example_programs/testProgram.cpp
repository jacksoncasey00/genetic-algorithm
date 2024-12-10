#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

// Main Test Funciton to get the Input to Spell the Word "generic"
int test(string s)
{
  int i;
  if (s.size() == 7)
  {
    if (s[0] == 'g')
    {
      i = 0;
    }
    if (s[1] == 'e')
    {
      i = 1;
    }
    if (s[2] == 'n')
    {
      i = 2;
    }
    if (s[3] == 'e')
    {
      i = 3;
    }
    if (s[4] == 't')
    {
      i = 4;
    }
    if (s[5] == 'i')
    {
      i = 5;
    }
    if (s[6] == 'c')
    {
      i = 6;
    }
  }

  return 0;
}