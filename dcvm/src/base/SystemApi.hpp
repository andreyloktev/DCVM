#ifndef DCVM_BASE_SYSTEMAPI_HPP_
#define DCVM_BASE_SYSTEMAPI_HPP_

#include <dcvm/dcvm_system.h>

extern DCVMMemoryAlloc     g_MemoryAllocate;
extern DCVMMemoryFree      g_MemoryFree;
extern DCVMMemoryCopy      g_MemoryCopy;
extern DCVMMemoryCompare   g_MemoryCompare;

namespace dcvm {
namespace base {

struct SystemApi final
{
    static void* MemoryAllocate(dcvm_size_t size) noexcept
    {
        return g_MemoryAllocate ? g_MemoryAllocate(size) : nullptr;
    }

    static void MemoryFree(void *p) noexcept
    {
        g_MemoryFree ? g_MemoryFree(p) : void();
    }

    static void MemoryCopy(void *pDst, dcvm_size_t dstSize,  const void *pSrc, dcvm_size_t srcSize) noexcept
    {
        g_MemoryCopy ? g_MemoryCopy(pDst, dstSize, pSrc, srcSize) : void();
    }

    static dcvm_int32_t MemoryCompare(void *pBlock1, const void *pBlock2, dcvm_size_t bytesToCmp) noexcept
    {
        return g_MemoryCompare ? g_MemoryCompare(pBlock1, pBlock2, bytesToCmp) : -1;
    }
};

} // namespace base
} // namespace dcvm

#endif