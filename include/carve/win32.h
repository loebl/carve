// Copyright 2006 Tobias Sargeant (toby@permuted.net)
// All rights reserved.
#pragma once

#if defined(_MSC_VER)
#pragma warning (disable : 4996)
#pragma warning (disable : 4786)
#pragma warning (disable : 4201)
#endif

#ifdef carve_EXPORTS
#define CARVE_API __declspec(dllexport)
#elif CARVE_SHARED
#define CARVE_API __declspec(dllimport)
#else
#define CARVE_API
#endif


#include <cstring>
#include <cstdlib>

inline int strcasecmp(const char *a, const char *b) {
  return _stricmp(a,b);
}

inline void srandom(unsigned long input) {
  srand(input);
}

inline int random() {
  return rand();
}

#if defined(_MSC_VER)
#  if _MSC_VER < 1600
// stdint.h is not available before VS2010
#if defined(_WIN32) && !defined(__MINGW32__)
/* The __intXX are built-in types of the visual compiler! So we don't
   need to include anything else here. */

typedef signed __int8  int8_t;
typedef signed __int16 int16_t;
typedef signed __int32 int32_t;

typedef unsigned __int8  uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
#endif

typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#  else
#    include <cstdint>
#  endif
#endif

#if(_MSC_VER < 1900)
static inline double round(double value) {
  return (value >= 0) ? floor(value + 0.5) : ceil(value - 0.5);
}
#endif
