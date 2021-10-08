#include <iostream>
#include <iomanip>
#include <cstdint>
#include "longlong.hpp"

using namespace std;

void printMenu    ()                        ;
int32_t getValue  (std::istream& stream)    ;
LongLong readLong (std::istream& stream)    ;
void swap         (LongLong& a, LongLong& b);

int main()
{
  LongLong firstValue,
           secondValue,
           resultValue;

  bool resultIsValid = false;

  int32_t  choose = 1;

  while (choose) {
    cout << "First Value : " << firstValue << "\t"
         << "Second Value : " << secondValue << endl;
    if (resultIsValid) {
      cout << "Result Value : " << resultValue << endl;
    }
    cout << endl;
    printMenu ();

    choose = getValue (cin);

    switch (choose) {

    case 1:
      firstValue = readLong (cin);
      break;

    case 2:
      secondValue = readLong (cin);
      break;

    case 3:
      resultValue   = firstValue + secondValue;
      resultIsValid = true;
      break;

    case 4:
      resultValue   = firstValue - secondValue;
      resultIsValid = true;
      break;

    case 5:
      resultValue   = firstValue * secondValue;
      resultIsValid = true;
      break;

    case 6:
      try {
        resultValue   = firstValue / secondValue;
        resultIsValid = true;
      } catch (string error) {
        cout << endl << "Second value is zero!" << endl;
      }
      break;

    case 7:
      resultValue   = firstValue % secondValue;
      resultIsValid = true;
      break;

    case 8:
      swap (firstValue, secondValue);
      resultIsValid = false;
      break;

    case 9:
      firstValue    = resultIsValid ? std::move (resultValue) : firstValue;
      resultIsValid = false;
      break;

    case 10:
      secondValue   = resultIsValid ? std::move (resultValue) : secondValue;
      resultIsValid = false;
      break;

    case 0:
      cout << "Exiting..." << endl;
      break;

    default:
      cout << "Choosen menu item is not exist!" << endl;
    }
  }
  return 0;
}

void printMenu ()
{
  const char * const menu[] = {
    "1. Enter first value.",
    "2. Enter second value.",
    "3. Add values.",
    "4. Substract from the first value the second.",
    "5. Multiplicate values.",
    "6. Divide from the first value second.",
    "7. Substract the remainder from the division",
    "8. Swap first and second values.",
    "9. Assign the result to the first value.",
    "10. Assign the result to the second value.",
    "0. Exit."
  };
  for (int32_t i = 0; i < sizeof(menu) / sizeof(char*); ++i) {
    cout << menu[i] << endl << endl;
  }
}

int32_t getValue (istream& stream)
{
    cout << "Enter value: " << endl;
    bool state = stream.sync_with_stdio (false);
    int32_t res;
    stream >> res;
    while (stream.rdbuf ()->in_avail() > 1) {
        cout << "Error. Try again: " << endl;
        stream.clear ();
        stream.ignore (stream.rdbuf ()->in_avail ());
        stream >> res;
    }
    stream.ignore (stream.rdbuf ()->in_avail ());
    stream.sync_with_stdio (state);
    return res;
}


LongLong readLong (std::istream& stream)
{
  LongLong result;
  std::cout << "Input a number : ";
  try {
    stream >> result;
  } catch (string err) {
    result = LongLong ();
    std::cout << endl << "incorrect number format" << endl;
  }
  stream.ignore (stream.rdbuf ()->in_avail());
  return std::move (result);
}


void swap (LongLong& a, LongLong& b)
{
  LongLong tmp = std::move (a);
  a            = std::move (b);
  b            = std::move (tmp);
}
