#include <iostream>
#include <cstdlib>

int gcd(int &a, int &b)
{
  int x = a;
  int y = b;

  while(y != 0)
  {
    int temp = x;
    x = y;
    y = temp%y;
  }

  return x;
}

bool readInNumbers(int &a, int &b)
{
  std::cout << "A?" << std::endl;
  std::cin >> a;
  if(a < 0)
  {
    std::cout << "A must be greater than 0!" << std::endl;
    return false;
  }

  std::cout << "B?" << std::endl;
  std::cin >> b;
  if(b < 0)
  {
    std::cout << "B must be greater than 0!" << std::endl;
    return false;
  }

  return true;
}

int main(int argc, char *argv[])
{
  int a, b;

  switch(argc)
  {
  case 1: 
    std::cout << "read in" << std::endl;
    if(readInNumbers(a, b))
    {
      std::cout << "The GCD of " << a << " and " << b << " is " << gcd(a, b) << "." << std::endl;
    }
    break;

  case 3:
    a = atoi(argv[1]);
    b = atoi(argv[2]);
    std::cout << gcd(a, b) << std::endl;
    break;

  default:
    std::cout << "Usage: euclid-cpp [a b]" << std::endl;
  }

  return 0;
}
