#include <iostream>
#include <string>
#include <cstdlib>

bool verifyIBAN(std::string testIBAN)
{
  unsigned int n = stoi(testIBAN);

  int counter = 1;
  int total = 0;
  while (n != 0)
  {
    int subtotal = (n % 10) * counter;
    total = total + subtotal;
    std::cout << (n % 10) << " x " << counter << " = " << subtotal << std::endl;
    counter++;
    n /= 10;
  }

  int result = total % 11;
  if (result == 0)
  {
    std::cout << testIBAN << " is validated." << std::endl;
    return true;
  }
  std::cout << testIBAN << " is NOT validated." << std::endl;
  return false;
}

int main()
{
  std::string testIBAN = "231243138";
  verifyIBAN(testIBAN);
  return 0;
}
