#ifndef DCVM_DCVM_SYSTEM_H_
#define DCVM_DCVM_SYSTEM_H_

#include "DCVMTypes.h"
#include "DCVMError.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _DCVMSystemAPI
{
    // Memory function;
    void* (*MmeoryAlloc)(unsigned int size);
    void (*MemoryFree)(void *p);
} DCVMSystemAPI;

#ifdef __cplusplus
}
#endif

#endif