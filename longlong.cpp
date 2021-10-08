#include        "longlong.hpp"
#include        "cparser.h"
#include        <algorithm>
LongLong::LongLong () noexcept : LongLong (0ull,0ull)
{

}


LongLong::LongLong (const uint64_t& num) noexcept : LongLong (0ull, num)
{

}


LongLong::LongLong (const int64_t& num) noexcept
{
    _lower  = std::make_shared<const uint64_t> (num);
    _higher = std::make_shared<const int64_t>
            (num < 0ll ? ~0ull : 0ull);
}


LongLong::LongLong (const int64_t& higher, const uint64_t& lower) noexcept :
    _higher (std::make_shared<const int64_t>  (higher)),
    _lower  (std::make_shared<const uint64_t> (lower))
{

}


LongLong::LongLong (const LongLong& other) noexcept
{
    clone (other);
}

LongLong::LongLong (LongLong&& other) noexcept
{
    move (std::move (other));
}

LongLong::LongLong (const string& str) noexcept
{
    setFromString (str);
}

LongLong::~LongLong ()
{
    _higher.reset ();
    _lower.reset  ();
}

LongLong& LongLong::operator= (const LongLong& other) noexcept
{
    this->clone (other);
    return *this;
}

LongLong& LongLong::operator= (LongLong&& other) noexcept
{
    this->move (std::move (other));
    return *this;
}

LongLong& LongLong::operator= (const string& str)
{
    setFromString (str);
    return *this;
}

void LongLong::clone (const LongLong& other) noexcept
{
    this->_higher = other._higher;
    this->_lower  = other._lower ;
}

void LongLong::clone (LongLong&& other) noexcept
{
    this->move (std::move (other));
}

void LongLong::move (LongLong&& other) noexcept
{
    this->_higher = std::move (other._higher);
    this->_lower  = std::move (other._lower) ;
}

LongLong LongLong::add (const LongLong& other) const noexcept
{
    LongLong result = *this;
    result._add (other);
    return std::move (result);
}

LongLong LongLong::sub (const LongLong& other) const noexcept
{
    LongLong result = *this;
    result._add (other.neg());
    return std::move (result);
}


LongLong LongLong::mul (const LongLong& other) const noexcept
{
    LongLong result = *this;
    result._mul (other);
    return std::move (result);
}


LongLong LongLong::div (const LongLong& other) const
{
    LongLong result = *this;
    result = result._div (other);
    return std::move (result);
}

LongLong LongLong::div (const LongLong& other, LongLong& mod) const
{
    mod = *this;
    LongLong result = mod._div (other);
    return std::move (result);
}

LongLong LongLong::mod (const LongLong& other) const
{
    LongLong result = *this;
    result._div (other);
    return std::move (result);
}

LongLong LongLong::neg () const noexcept
{
    LongLong result = *this;
    result._neg ();
    return std::move (result);
}

LongLong LongLong::abs () const noexcept
{
    LongLong result = *this;
    result._abs ();
    return std::move (result);
}

LongLong LongLong::lShift (const uint32_t& n) const noexcept
{
    LongLong result = *this;
    result._lShift (n);
    return std::move (result);
}

LongLong LongLong::rShift (const uint32_t& n) const noexcept
{
    LongLong result = *this;
    result._rShift (n);
    return std::move (result);
}

LongLong LongLong::operator+ (const LongLong& other) const noexcept
{
    return this->add (other);
}

LongLong LongLong::operator- (const LongLong& other) const noexcept
{
    return this->sub (other);
}

LongLong LongLong::operator* (const LongLong& other) const noexcept
{
    return this->mul (other);
}

LongLong LongLong::operator/ (const LongLong& other) const
{
    return this->div (other);
}

LongLong LongLong::operator% (const LongLong& other) const
{
    return this->mod (other);
}

LongLong LongLong::operator- () const noexcept
{
    return this->neg ();
}

LongLong LongLong::operator<< (const uint32_t& n) const noexcept
{
    return this->lShift (n);
}

LongLong LongLong::operator>> (const uint32_t& n) const noexcept
{
    return this->rShift (n);
}

LongLong& LongLong::operator+= (const LongLong& other) noexcept
{
    this->_add (other);
    return *this;
}

LongLong& LongLong::operator-= (const LongLong& other) noexcept
{
    this->_add (other.neg());
    return *this;
}

LongLong& LongLong::operator*= (const LongLong& other) noexcept
{
    this->_mul (other);
    return *this;
}

LongLong& LongLong::operator/= (const LongLong& other)
{
    *this = this->_div (other);
    return *this;
}

LongLong& LongLong::operator%= (const LongLong& other)
{
    this->_div (other);
    return *this;
}

LongLong& LongLong::operator<<= (const uint32_t& n) noexcept
{
    this->_lShift (n);
    return *this;
}

LongLong& LongLong::operator>>= (const uint32_t& n) noexcept
{
    this->_rShift (n);
    return *this;
}

LongLong& LongLong::operator++ () noexcept
{
    bool carry = (*_lower == std::numeric_limits <uint64_t> ::max());
    setLower  (*_lower + 1);
    setHigher (*_higher + carry);
    return *this;
}

bool LongLong::operator== (const LongLong& other) const noexcept
{
    return (this->equals (other));
}

bool LongLong::operator!= (const LongLong& other) const noexcept
{
    return !(this->equals (other));
}

bool LongLong::operator> (const LongLong& other) const noexcept
{
    return (this->isLarger (other));
}

bool LongLong::operator< (const LongLong& other) const noexcept
{
    return (this->isSmaller (other));
}

bool LongLong::operator>= (const LongLong& other) const noexcept
{
    return this->equals (other) || (this->isLarger(other));
}

bool LongLong::operator<= (const LongLong& other) const noexcept
{
    return this->equals (other) || (this->isSmaller (other));
}

bool LongLong::equals (const LongLong& other) const noexcept
{
    return (*this->_lower  == *other._lower)
            && (*this->_higher == *other._higher);
}

bool LongLong::getSign () const noexcept
{
    return (*this->_higher & 0x8000000000000000);
}

bool LongLong::isSmaller (const LongLong& other) const noexcept
{
    return (*this->_higher < *other._higher)
            || ((*this->_higher == *other._higher)
                && (*this->_lower < *other._lower));
}

bool LongLong::isLarger (const LongLong& other) const noexcept
{
    return (*this->_higher > *other._higher)
            || ((*this->_higher == *other._higher)
                && (*this->_lower > *other._lower));
}

int8_t LongLong::compare (const LongLong& other) const noexcept
{
    int8_t result;
    if (*this->_higher == *other._higher) {
        if (*this->_lower == *other._lower) {
            result = 0;
        } else {
            result = (*this->_lower > *other._lower) ? 1 : -1;
        }
    } else {
        result = (*this->_higher > *other._higher) ? 1 : -1;
    }
    return result;
}

//std::string LongLong::toString () const noexcept
//{
//    bool sign = this->getSign ();
//    const LongLong& tmp = sign ? this->neg() : *this;
//    return string  ((sign) ? "-" : "") + "(" + std::to_string (*tmp._higher)
//            + " * 2^64 + " + std::to_string (*tmp._lower)  + ")";

//}

std::string LongLong::toString () const noexcept
{


  LongLong toDivide = *this;
  LongLong zero     = LongLong::zero ();
  LongLong ten      = LongLong (uint64_t (10));
  LongLong toPush;
  std::string result = (toDivide.equals (zero) ? "0" : "");
  bool sign;
  if (toDivide.getSign ()) {
    sign = true;
    toDivide._neg ();
  } else {
    sign = false;
  }
  while (!toDivide.equals (zero)) {
    toPush = toDivide;
    toDivide = toPush._div (ten);
    result.push_back ('0' + *toPush._lower);
  }
  if (sign) {
    result.push_back ('-');
  }
  std::reverse (result.begin (), result.end ());
  result.push_back ('\0');

  return std::move (result);
}

LongLong LongLong::getFromString (const string& str)
{
    return LongLong (str);
}

const uint64_t& LongLong::getLower () const noexcept
{
    return *this->_lower;
}

const int64_t& LongLong::getHigher () const noexcept
{
    return *this->_higher;
}

void LongLong::setLower (const uint64_t& lower) noexcept
{
    this->_lower = std::make_shared<const uint64_t> (lower);
}

void LongLong::setHigher (const int64_t& higher) noexcept
{
    this->_higher = std::make_shared<const int64_t> (higher);
}

void LongLong::setFromString (const string& str)
{
    _higher = std::make_shared <int64_t>  (0ll);
    _lower  = std::make_shared <uint64_t> (0ull);
}

LongLong LongLong::max () noexcept
{
    return LongLong (0x7FFFFFFFFFFFFFFFll,
                     0xFFFFFFFFFFFFFFFFull);
}

LongLong LongLong::zero () noexcept
{
    return LongLong (0ull, 0ull);
}

LongLong LongLong::min () noexcept
{
    return LongLong (0x8000000000000000, 0ull);
}

void LongLong::_bitReverse () noexcept
{
    setLower  (~(*_lower)) ;
    setHigher (~(*_higher));
}

uint64_t LongLong:: _64mul (const uint64_t& val1,
                            const uint64_t& val2,
                            uint64_t& overflow)   noexcept
{
    uint32_t val1H = (val1 >> 32), val1L = (val1 & 0xFFFFFFFF),
            val2H = (val2 >> 32), val2L = (val2 & 0xFFFFFFFF);

    uint64_t result        = (uint64_t)val1L * val2L;
    uint64_t first_H_Part  = (uint64_t)val1H * val2L;
    uint64_t second_H_Part = (uint64_t)val1L * val2H;

    uint64_t resultH       = (first_H_Part & 0xFFFFFFFF)
            + (second_H_Part & 0xFFFFFFFF);

    overflow = (uint64_t)val1H * val2H
            + (first_H_Part >> 32) + (second_H_Part >> 32)
            + (resultH >> 32)
            + (result > std::numeric_limits<uint64_t>::max ()
               - (resultH << 32));

    result += (resultH << 32);

    return result;
}

void LongLong::_add (const LongLong& other) noexcept
{
    bool carry = (*this->_lower > std::numeric_limits<uint64_t>::max ()
                  - *other._lower);
    this->setLower  (*this->_lower + *other._lower);
    this->setHigher ((uint64_t)*this->_higher + *other._higher + carry);
}

void LongLong::_mul (const LongLong& other) noexcept
{
    uint64_t thisH = *this->_higher;
    uint64_t thisL = *this->_lower ;
    uint64_t carry;
    this->setLower  (_64mul (thisL, *other._lower, carry));
    this->setHigher (thisH * (*other._lower)
                     + thisL * (*other._higher) + carry);
}

LongLong LongLong::_div (LongLong other)
{

    if (other == zero ()) {
        throw string ("divide by zero exception");
    }
    bool sign = false;
    if (this->getSign ()) {
        sign = !sign;
        this->_neg ();
    }
    if (other.getSign ()) {
        sign = !sign;
        other._neg ();
    }
    int32_t n = this->_findLeftNotZeroBit () - other._findLeftNotZeroBit ();
    other._lShift (n);
    LongLong res = (uint64_t)0;
    for (; n >= 0; other._rShift(1),--n) {
        res._lShift (1);
        if (*this >= other) {
            this->_add(other.neg());
            ++res;
        }
    }
    if (sign) {
        res._neg();
    }
    return std::move (res);
}

void LongLong::_neg () noexcept
{
    bool carryValue = *_lower == 0;
    _bitReverse ();
    _lower  = std::make_shared <uint64_t> (*_lower + 1);
    _higher = std::make_shared <int64_t>  (*_higher + carryValue);
}

void LongLong::_abs () noexcept
{
    if (getSign ()) {
        _neg ();
    }
}

void LongLong::_lShift (uint32_t n) noexcept
{
  n %= 128;
  uint64_t higher = *_higher,
           lower  = *_lower;
  if (n >= 64) {
    higher = lower << (n - 64);
    lower  = 0;
  } else if (n > 0) {
    uint64_t overflow = lower >> (64 - n);
    higher = (higher << n) + overflow;
    lower <<= n;
  }
  _higher = std::make_shared<int64_t>  (higher);
  _lower  = std::make_shared<uint64_t> (lower);

}

void LongLong::_rShift (uint32_t n) noexcept
{
    n %= 128;
    uint64_t higher = *_higher,
             lower  = *_lower;
    if (n >= 64) {
      lower  = higher >> (n - 64);
      higher = 0;
    } else if (n > 0) {
      uint64_t overflow = higher << (64 - n);
      higher >>= n;
      lower = (lower >> n) + overflow;
    }
    _higher = std::make_shared<int64_t>  (higher);
    _lower  = std::make_shared<uint64_t> (lower);
}

int32_t LongLong::_findLeftNotZeroBit () const noexcept
{
    int32_t res = 0;
    uint64_t tmp = (*_higher != 0)  ? (res += 64, *_higher) : *_lower;

    tmp = ((tmp >> 32) != 0) ? (res += 32, tmp >> 32) :
                               (tmp & 0xFFFFFFFF);

    tmp = ((tmp >> 16) != 0) ? (res += 16, tmp >> 16) :
                               (tmp & 0xFFFF);

    tmp = ((tmp >> 8) != 0) ? (res += 8, tmp >> 8) :
                              (tmp & 0xFF);

    res += 7;
    for (uint8_t i = 0x80; i != 0 && ((tmp & i) == 0) ; i >>= 1, --res)
        ;
    return res;
}

int32_t LongLong::_findRightNotZeroBit () const noexcept
{
    int32_t res = 0;
    uint64_t tmp = (*_lower != 0) ? (*_lower) : (res += 64, *_higher);
    tmp = ((tmp & 0xFFFFFFFF) != 0) ? (tmp & 0xFFFFFFFF) :
                                      (res += 32, tmp >> 32);

    tmp = ((tmp & 0xFFFF) != 0) ? (tmp & 0xFFFF) :
                                  (res += 16, tmp >> 16);

    tmp = ((tmp & 0xFF) != 0) ? (tmp & 0xFF) :
                                (res += 8, tmp >> 8);

    for (uint8_t i = 1; i != 0 && ((tmp & i) == 0); i <<= 1, ++res)
        ;
    return (res == 128) ? -1 : res;
}

std::ostream& operator<< (std::ostream& out, const LongLong& value) noexcept
{
  out << value.toString ();
  return out;
}


std::istream& operator>> (std::istream& in, LongLong& value)
{
  std::shared_ptr<_LongLong> _parseValue = parse (in);
  if (_parseValue != nullptr) {
    value.setLower (_parseValue->_lower);
    value.setHigher (_parseValue->_higher);
  } else {
    throw std::string("no_value_excecption");
  }
  return in;
}


/////////////////////////////////////////////////////////////////



//uint64_t LongLong::_64mult (const uint64_t& val1,
//                            const uint64_t& val2,
//                            uint64_t& overflow) noexcept
//{
//  uint64_t result  = 0             ;
//  uint64_t val1H   = (val1 >> 32)  ;
//  uint64_t val1L   = (uint32_t)val1;
//  uint64_t val2H   = (val2 >> 32)  ;
//  uint64_t val2L   = (uint32_t)val2;

//  overflow         = val1H * val2H ;
//  uint64_t resultL = val1L * val2L ;
//  uint64_t resultH = 0             ;
//  {
//    uint64_t firstPiece  = val1H * val2L;
//    uint64_t secondPiece = val1L * val2H;
//    overflow += (firstPiece >> 32);
//    overflow += (secondPiece >> 32);
//    firstPiece =  (uint32_t) firstPiece;
//    secondPiece = (uint32_t) secondPiece;
//    if (firstPiece > std::numeric_limits<uint32_t>::max () - secondPiece) {
//      ++overflow;
//    }
//    resultH = firstPiece + secondPiece;
//    if (resultH > std::numeric_limits<uint32_t>::max () - (resultL >> 32)) {
//      ++overflow;
//    }
//    resultH += (resultL >> 32);
//    resultL = (uint32_t)resultL;
//  }
//  result = (resultH << 32) + resultL;
//  return std::move(result);
//}




