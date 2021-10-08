#ifndef __CPARSER_HPP__
#define __CPARSER_HPP__
#include <stdint.h>

#ifdef __cplusplus
#include <istream>
#include <memory>
#endif



#ifdef __cplusplus

struct _LongLong
{
  int64_t _higher;
  uint64_t _lower;
};

std::shared_ptr<_LongLong> parse(std::istream& stream);

#endif



#ifdef __cplusplus
extern "C"
{
#endif

void putNumber (uint64_t num) ;
char getChar   ()             ;
void negative  ()             ;

#ifdef __cplusplus
}
#endif


#endif
