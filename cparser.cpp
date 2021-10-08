#include "cparser.h"
#include <istream>
#include <list>
#include <limits>
extern "C" {
#include "fromstring.tab.h"
}
static char lastReaden;
static std::istream*              inputStream ;
static std::shared_ptr<_LongLong> returnValue ;

static bool isFirst = true;

static void multiplyToTen ();

std::shared_ptr<_LongLong> parse (std::istream& stream)
{
  inputStream = &stream;
  yyparse ();
  inputStream->putback (lastReaden);
  std::shared_ptr<_LongLong> result = returnValue;
  returnValue = nullptr;
  inputStream = nullptr;
  isFirst     = true;
  return result;
}


extern "C" void putNumber (uint64_t num)
{
  if (returnValue == nullptr) {
    returnValue = std::make_shared<_LongLong> ();
    returnValue->_lower = std::move (num);
  } else {
    multiplyToTen ();
    returnValue->_lower += num;
  }
}

static void multiplyToTen ()
{
  uint64_t _higherFirst = returnValue->_higher;
  uint64_t _lowerFirst  = returnValue->_lower ;

  uint64_t _higherSecond = returnValue->_higher;
  uint64_t _lowerSecond  = returnValue->_lower ;

  uint64_t overflow = _lowerFirst >> (64 - 3);
  _lowerFirst  <<= 3;
  _higherFirst <<= 3;
  _higherFirst += overflow;

  overflow = _lowerSecond >> (64 - 1);
  _lowerSecond  <<= 1;
  _higherSecond <<= 1;
  _higherSecond += overflow;

  overflow = (_lowerFirst > std::numeric_limits<uint64_t>::max ()
                            - _lowerSecond);
  returnValue->_lower  = _lowerFirst  + _lowerSecond            ;
  returnValue->_higher = _higherFirst + _higherSecond + overflow;

}

extern "C" char getChar ()
{
  int32_t result = inputStream->get ();
  while (isspace(result) && isFirst) {
    result = inputStream->get ();
  }
  if (!(isdigit (result) || (result == '-') && isFirst)) {
    result = 0;
  }
  isFirst = false;
  lastReaden = result;
  return result;
}

extern "C" void negative ()
{
  uint64_t overflow = (returnValue->_lower == 0);
  returnValue->_lower  = ~returnValue->_lower + 1        ;
  returnValue->_higher = ~returnValue->_higher + overflow;
}
