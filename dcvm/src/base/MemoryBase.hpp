#ifndef DCVM_BASE_MEMORYBASE_HPP_
#define DCVM_BASE_MEMORYBASE_HPP_

namespace dcvm {
namespace base {

template <typename SystemApi>
struct MemoryBase
{
    MemoryBase() noexcept = default;
    ~MemoryBase() noexcept = default;
    MemoryBase(const MemBased&) noexcept = default;
    MemoryBase& operator=(const MemBased&) noexcept = default;

    static void* operator new(dcvm_size_t size) noexcept
    {
        void *p = SystemApi::MemoryAllocate(static_cast<unsigned long>(size));
        if (p)
        {
            SystemApi::MemorySet(p, size, 0);
        }

        return p;
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
        void *p = SystemApi::MemoryAllocate(static_cast<unsigned long>(size));
        if (p)
        {
            SystemApi::MemorySet(p, size, 0);
        }

        return p;
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