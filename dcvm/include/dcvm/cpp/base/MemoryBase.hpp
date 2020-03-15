#ifndef DCVM_BASE_MEMORYBASE_HPP_
#define DCVM_BASE_MEMORYBASE_HPP_

#include "SystemApi.hpp"

namespace dcvm {
namespace base {

struct MemoryBase
{
    MemoryBase() noexcept = default;
    ~MemoryBase() noexcept = default;
    MemoryBase(const MemoryBase&) noexcept = default;
    MemoryBase& operator=(const MemoryBase&) noexcept = default;

    static void* operator new(dcvm_size_t size) noexcept
    {
        return SystemApi::MemoryAllocate<void>(static_cast<unsigned long>(size), DCVM_TRUE);
    }

    static void operator delete(void *pBuffer) noexcept
    {
        if (pBuffer)
        {
            SystemApi::MemoryFree(pBuffer);
        }
    }

    static void* operator new[](dcvm_size_t size) noexcept
    {
        return SystemApi::MemoryAllocate<void>(static_cast<unsigned long>(size), DCVM_TRUE);
    }

    static void operator delete[](void *pBuffer) noexcept
    {
        if (pBuffer)
        {
           SystemApi::MemoryFree(pBuffer);
        }
    }

    static void* operator new(dcvm_size_t, void* __p) noexcept {return __p;}
    static void* operator new[](dcvm_size_t, void* __p) noexcept {return __p;}
    static void  operator delete  (void*, void*) noexcept {}
    static void  operator delete[](void*, void*) noexcept {}

};

} // namespace base
} // namespace dcvm

#endif