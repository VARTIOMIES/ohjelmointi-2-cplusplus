#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

bool palindrome_recursive(std::string s)
{
  RECURSIVE_FUNC
  // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
  // ------------
  if (s.length()<=1)
  {
      return true;
  }
  std::string::iterator first = s.begin();
  if (s.at(0)==s.at(s.length()-1))
  {
      s.erase(first);
      s.pop_back();
      if (palindrome_recursive(s))
      {
          return true;
      }
      else
      {
          return false;
      }
  }
  else
  {
      return false;
  }

  // Add your implementation here
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
#endif
