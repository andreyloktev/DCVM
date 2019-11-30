#ifndef DCVM_BASE_SYSTEMAPI_HPP_
#define DCVM_BASE_SYSTEMAPI_HPP_

#include <dcvm/DCVMSystemAPI.h>
#include <dcvm/DCVMTypes.h>

namespace dcvm {

extern DCVMSystemAPI g_systemApi;

namespace base {

struct SystemApi final
{
    static void* MemoryAllocate(dcvm_size_t size, dcvm_bool_t bZero) noexcept
    {
        return g_systemApi.MemoryAllocate ? g_systemApi.MemoryAllocate(size, bZero) : nullptr;
    }

    static void MemoryFree(void *p) noexcept
    {
        g_systemApi.MemoryFree ? g_systemApi.MemoryFree(p) : void();
    }

    static void MemorySet(void *p, dcvm_size_t size, dcvm_uint8_t value) noexcept
    {
        g_systemApi.MemorySet ? g_systemApi.MemorySet(p, size, value) : void();
    }

    static void MemoryCopy(void *pDst, dcvm_size_t dstSize,  const void *pSrc, dcvm_size_t srcSize) noexcept
    {
        g_systemApi.MemoryCopy ? g_systemApi.MemoryCopy(pDst, dstSize, pSrc, srcSize) : void();
    }

    static dcvm_int32_t MemoryCompare(void *pBlock1, const void *pBlock2, dcvm_size_t bytesToCmp) noexcept
    {
        return g_systemApi.MemoryCompare ? g_systemApi.MemoryCompare(pBlock1, pBlock2, bytesToCmp) : -1;
    }
};

} // namespace base
} // namespace dcvm

#endif