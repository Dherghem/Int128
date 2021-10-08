#ifndef LONGLONG_HPP
#define LONGLONG_HPP

#include        <iostream>
#include        <cstdint>
#include        <memory>
#include        <limits>
#include        <cmath>
#include        <utility>
#include        <exception>
#include        <initializer_list>
class LongLong
{
    using string = std::string;
public:
    LongLong ()                        noexcept;
    LongLong (const uint64_t&  num)    noexcept;
    LongLong (const int64_t&   num)    noexcept;
    LongLong (const int64_t&   higher,
              const uint64_t&  lower)  noexcept;
    LongLong (const LongLong&  other)  noexcept;
    LongLong (LongLong&&       other)  noexcept;
    LongLong (const string& str)       noexcept; // later


    LongLong& operator= (const LongLong& other) noexcept;
    LongLong& operator= (LongLong&& other)      noexcept;
    LongLong& operator= (const string& str)             ; //later


    virtual ~LongLong ();


    void clone (const LongLong& other) noexcept;
    void clone (LongLong&& other)      noexcept;
    void move  (LongLong&& other)      noexcept;


    LongLong add    (const LongLong& other)                const noexcept;
    LongLong sub    (const LongLong& other)                const noexcept;
    LongLong mul    (const LongLong& other)                const noexcept;
    LongLong div    (const LongLong& other)                const         ;
    LongLong div    (const LongLong& other, LongLong& mod) const         ;
    LongLong mod    (const LongLong& other)                const         ;
    LongLong neg    ()                                     const noexcept;
    LongLong abs    ()                                     const noexcept;
    LongLong lShift (const uint32_t& n)                    const noexcept;
    LongLong rShift (const uint32_t& n)                    const noexcept;


    LongLong operator+  (const LongLong& other) const noexcept;
    LongLong operator-  (const LongLong& other) const noexcept;
    LongLong operator*  (const LongLong& other) const noexcept;
    LongLong operator/  (const LongLong& other) const         ;
    LongLong operator%  (const LongLong& other) const         ;
    LongLong operator-  ()                      const noexcept;
    LongLong operator<< (const uint32_t& n)     const noexcept;
    LongLong operator>> (const uint32_t& n)     const noexcept;
    LongLong operator~  ()                      const noexcept; //later
    LongLong operator^  (const LongLong& other) const noexcept; //later
    LongLong operator&  (const LongLong& other) const noexcept; //later
    LongLong operator|  (const LongLong& other) const noexcept; //later


    LongLong& operator+=  (const LongLong& other) noexcept;
    LongLong& operator-=  (const LongLong& other) noexcept;
    LongLong& operator*=  (const LongLong& other) noexcept;
    LongLong& operator/=  (const LongLong& other)         ;
    LongLong& operator%=  (const LongLong& other)         ;
    LongLong& operator<<= (const uint32_t& n)     noexcept;
    LongLong& operator>>= (const uint32_t& n)     noexcept;
    LongLong& operator^=  (const LongLong& other) noexcept; //later
    LongLong& operator&=  (const LongLong& other) noexcept; //later
    LongLong& operator|=  (const LongLong& other) noexcept; //later
    LongLong& operator++  ()                      noexcept; //later
    LongLong& operator--  ()                      noexcept; //later


    bool operator== (const LongLong& other) const noexcept;
    bool operator!= (const LongLong& other) const noexcept;
    bool operator>  (const LongLong& other) const noexcept;
    bool operator<  (const LongLong& other) const noexcept;
    bool operator>= (const LongLong& other) const noexcept;
    bool operator<= (const LongLong& other) const noexcept;


    explicit operator int64_t  () const noexcept; //later
    explicit operator uint64_t () const noexcept; //later


    bool   equals     (const LongLong& other) const noexcept;
    bool   getSign    ()                      const noexcept;
    bool   isSmaller  (const LongLong& other) const noexcept;
    bool   isLarger   (const LongLong& other) const noexcept;
    int8_t compare    (const LongLong& other) const noexcept;
    string toString   ()                      const noexcept;


    static LongLong getFromString (const string& str); // later


    const uint64_t& getLower      ()                      const noexcept;
    const int64_t&  getHigher     ()                      const noexcept;
    void      setLower      (const uint64_t& lower)             noexcept;
    void      setHigher     (const int64_t&  higher)            noexcept;
    void      setFromString (const string& str)                         ; // later


    static LongLong max  () noexcept;
    static LongLong zero () noexcept;
    static LongLong min  () noexcept;

private:
    std::shared_ptr<const int64_t>  _higher;
    std::shared_ptr<const uint64_t> _lower;

    void     _bitReverse   ()                          noexcept;
    static uint64_t _64mul (const uint64_t& val1,
                                 const uint64_t& val2,
                                 uint64_t& overflow)   noexcept;
    void     _add          (const LongLong& other)     noexcept;
    void     _mul          (const LongLong& other)     noexcept;
    LongLong _div          (LongLong other)                    ;
    void     _neg          ()                          noexcept;
    void     _abs          ()                          noexcept;
    void     _lShift       (uint32_t n)                noexcept;
    void     _rShift       (uint32_t n)                noexcept;



    int32_t _findLeftNotZeroBit  () const noexcept;
    int32_t _findRightNotZeroBit () const noexcept;



    friend std::ostream& operator<<           (std::ostream& out,
                                               const LongLong& value) noexcept;// done
    friend std::istream& operator>>           (std::istream& in,
                                               LongLong& value)         ;// done


    friend LongLong std::numeric_limits<LongLong>::max () noexcept;
    friend LongLong std::numeric_limits<LongLong>::min () noexcept;
    //friend std::string   std::to_string<LongLong> (const LongLong& n);


};

//#include "longlong.inl"

#endif // LONGLONG_HPP
