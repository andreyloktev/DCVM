#ifndef DCVM_BASE_EASTLALLOCATOR_HPP_
#define DCVM_BASE_EASTLALLOCATOR_HPP_

#include "SystemApi.hpp"
#include <dcvm/DCVMTypes.h>

namespace dcvm {
namespace base {

class EASTLAllocator final
{
    static constexpr const char *ALLOCATOR_NAME = "DCVM";
private:
    const char *m_pName = nullptr;
public:
    explicit EASTLAllocator(const char *pName) noexcept: m_pName(pName ? pName : ALLOCATOR_NAME)
    {
    }

    EASTLAllocator(const EASTLAllocator &eastlAlloc) noexcept
    {
        m_pName = eastlAlloc.m_pName;
    }

    EASTLAllocator(const EASTLAllocator &/*x*/, const char *pName) noexcept
    {
        m_pName = pName ? pName : ALLOCATOR_NAME;
    }

    EASTLAllocator& operator=(const EASTLAllocator& x) noexcept
    {
        if (this != &x)
        {
            this->m_pName = x.m_pName;
        }

        return *this;
    }

    void* allocate(dcvm_size_t size, dcvm_int32_t flags = 0) noexcept
    {
        DCVM_UNREFERENCED_PARAMETER(flags);

        if (0 == size)
        {
            return nullptr;
        }

        void *pMem = SystemApi::MemoryAllocate(size + sizeof(void*));
        if (nullptr == pMem)
        {
            return nullptr;
        }
 
        void **ppPtr = (void**)(reinterpret_cast<dcvm_size_t>(pMem) + sizeof(void*));
        ppPtr[-1] = pMem;

        return ppPtr;
    }

    void* allocate(dcvm_size_t size, dcvm_size_t alignment, dcvm_size_t offset, dcvm_int32_t flags = 0) noexcept
    {
        DCVM_UNREFERENCED_PARAMETER(offset);
        DCVM_UNREFERENCED_PARAMETER(flags);

        if (0 == size)
        {
            return nullptr;
        }

        auto AlignSizeUp = [](dcvm_size_t value, dcvm_size_t alignment) -> dcvm_size_t
        {
            return (value + (alignment - 1)) & (~(alignment - 1));
        };

        void *pMem = SystemApi::MemoryAllocate(size + sizeof(void*) + (alignment - 1));
        if (nullptr == pMem)
        {
            return nullptr;
        }
 
        void **ppPtr = reinterpret_cast<void**>(
            AlignSizeUp(
                reinterpret_cast<dcvm_size_t>(pMem) + sizeof(void*)
                , alignment
            )
        );

        ppPtr[-1] = pMem;

        return ppPtr;
    }

    void  deallocate(void* p, dcvm_size_t n) noexcept
    {
        if (p)
        {
            void *pMem = reinterpret_cast<void**>(p)[-1];
            SystemApi::MemoryFree(pMem);
        }
    }

    const char* get_name() const noexcept
    {
        return m_pName;
    }

    void set_name(const char* pName) noexcept
    {
        m_pName = pName;
    }
};

} // namespace base
} // namespace dcvm

bool operator==(
    const dcvm::base::EASTLAllocator     &a
    , const dcvm::base::EASTLAllocator   &b
) noexcept
{
    return &a == &b;
}

bool operator!=(
    const dcvm::base::EASTLAllocator     &a
    , const dcvm::base::EASTLAllocator   &b
) noexcept
{
    return &a != &b;
}

#endif