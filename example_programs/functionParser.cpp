#include <iostream>
#include <vector>
#include <string>

#include "longestSubstring.cpp"
#include "palindrome.cpp"
#include "testProgram.cpp"


// Parses Call From Genetic Algorithm and Calls Appropriate Function
int main (int argc, char *argv[]) {
  string functionName = argv[1];

  if (functionName == "longestSubstring") {
    if (argc > 2) {
    lengthOfLongestSubstring(argv[2]);
    }
  }
  else if (functionName == "palindrome") {
    if (argc > 2) {
    longestPalindrome(argv[2]);
    }
  }
  else if (functionName == "testProgram") {
    if (argc > 2) {
    test(argv[2]);
    }
  }
  return 0;
}