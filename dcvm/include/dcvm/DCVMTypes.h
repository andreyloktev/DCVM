#ifndef DCVM_DCVM_DCVMTYPES_H_
#define DCVM_DCVM_DCVMTYPES_H_

#ifdef _WIN32
typedef wchar_t dcvm_char_t;
#else
typedef char dcvm_char_t; 
#endif

#define DCVM_TRUE   1
#define DCVM_FALSE  0

typedef unsigned char       dcvm_bool_t;

typedef unsigned char       dcvm_uint8_t;
typedef unsigned short      dcvm_uint16_t;
typedef unsigned int        dcvm_uint32_t;
typedef unsigned long long  dcvm_uint64_t;

typedef char                dcvm_int8_t;
typedef short               dcvm_int16_t;
typedef int                 dcvm_int32_t;
typedef long long           dcvm_int64_t;

#ifdef _WIN32
#ifdef _WIN64
typedef unsigned long long dcvm_size_t;
#else
typedef unsigned int dcvm_size_t;
#endif
#else
#endif

#define DCVM_UNREFERENCED_PARAMETER(x) x

#endif