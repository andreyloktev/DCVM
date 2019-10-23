#ifndef DCVM_BASE_SYSTEMAPI_HPP_
#define DCVM_BASE_SYSTEMAPI_HPP_

#include <dcvm/dcvm_system.h>
#include "DCVMTypes.hpp"

namespace dcvm {

extern DCVMSystemAPI    *g_pSystemApi;

namespace base {

struct SystemApi final
{
    static void* MemoryAllocate(dcvm_size_t size) noexcept
    {
        return g_pSystemApi ? g_pSystemApi->MemoryAllocate(size) : nullptr;
    }

    static void MemoryFree(void *p) noexcept
    {
        g_pSystemApi ? g_pSystemApi->MemoryFree(p) : void();
    }

    static void MemorySet(void *p, dcvm_size_t size, dcvm_uint8_t value) noexcept
    {
        g_pSystemApi ? g_pSystemApi->MemorySet(p, size, value) : void();
    }

    static void MemoryCopy(void *pDst, dcvm_size_t dstSize,  const void *pSrc, dcvm_size_t srcSize) noexcept
    {
        g_pSystemApi ? g_pSystemApi->MemoryCopy(pDst, dstSize, pSrc, srcSize) : void();
    }

    static dcvm_int32_t MemoryCompare(void *pBlock1, const void *pBlock2, dcvm_size_t bytesToCmp) noexcept
    {
        return g_pSystemApi ? g_pSystemApi->MemoryCompare(pBlock1, pBlock2, bytesToCmp) : -1;
    }
};

} // namespace base
} // namespace dcvm

#endif