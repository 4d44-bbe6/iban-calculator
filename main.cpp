#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <vector>
#include <mutex>

std::mutex mtx;

int totalVerifiedCounter = 0;
int index = 1;
int foundVerifiedIBAN = false;

int verifyIBAN(int IBAN, int modulus, int modus, int searchIBAN)
{
  int counter = 1;
  int total = 0;
  int tempIBAN = IBAN;
  while (tempIBAN != 0)
  {
    int subtotal = (tempIBAN % 10) * counter;
    total = total + subtotal;
    counter++;
    tempIBAN /= 10;
  }

  int result = total % modulus;
  if (result == 0)
  {
    if (modus == 0)
    {
      mtx.lock();
      totalVerifiedCounter = totalVerifiedCounter + 1;
      mtx.unlock();
      return 0;
    }
    else if (modus == 1)
    {
      std::cout << index << ": "
                << "Verified " << IBAN << std::endl;
      mtx.lock();
      index = index + 1;
      mtx.unlock();
      return 0;
    }
    else
    {

      if (IBAN == searchIBAN)
      {
        std::cout << "Verified: " << IBAN << std::endl;
        mtx.lock();
        foundVerifiedIBAN = true;
        mtx.unlock();
      }
    }
  }
  return 0;
}

int main(int argc, char *argv[])
{
  int lowerTreshold = atoi(argv[1]);
  int upperTreshold = atoi(argv[2]);
  int modulus = atoi(argv[3]);
  int numberThreads = atoi(argv[4]);
  int modus = atoi(argv[5]);
  int searchIBAN = atoi(argv[6]);

  std::cout << "Lower Treshold: " << lowerTreshold << std::endl;
  std::cout << "Upper Treshold: " << upperTreshold << std::endl;
  std::cout << "Number of threads: " << numberThreads << std::endl;
  std::cout << "Modulus: " << modulus << std::endl;
  std::cout << "Mode: " << modus << std::endl;
  std::cout << "Search for: " << searchIBAN << std::endl;

  std::vector<std::thread> thread_pool;
  thread_pool.reserve(numberThreads);

  for (int i = lowerTreshold; i < upperTreshold; i++)
  {

    thread_pool.push_back(std::thread(verifyIBAN, i, modulus, modus, searchIBAN));
    for (std::thread &th : thread_pool)
    {
      if (th.joinable())
        th.join();
    }
  }

  if (modus == 0)
  {
    std::cout << totalVerifiedCounter;
  }
  if (modus == 2)
  {
    if (foundVerifiedIBAN)
    {
      return 0;
    }
    return -1;
  }
  return 0;
}
