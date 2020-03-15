#ifndef DCVM_BASE_STLALLOCATOR_HPP_
#define DCVM_BASE_STLALLOCATOR_HPP_

#include "SystemApi.hpp"

namespace dcvm {
namespace base {

template <typename T>
class STLAllocator final
{
public:
    using value_type         = T;
    using pointer           = T*;
    using const_pointer     = const T*;
    using reference         = T&;
    using const_reference   = const T&;
    using size_type         = size_t;
    using difference_type   = ptrdiff_t;
public:
    template<class U>
    struct rebind 
    { 
        typedef STLAllocator<U> other; 
    };
public:
    STLAllocator() noexcept = default;
    STLAllocator(const STLAllocator&) noexcept = default;
    template< class U >
    STLAllocator(const STLAllocator<U> &other) noexcept {}
    ~STLAllocator() noexcept = default;
    STLAllocator& operator=(const STLAllocator&) noexcept = delete;
public:
    pointer address(reference x) const noexcept
    {
        return &x;
    }

    const_pointer address(const_reference x) const noexcept
    {
        return &x;
    }

    pointer allocate(size_type n, const_pointer hint = 0) noexcept
    {
        return SystemApi::MemoryAllocate<T>(sizeof(T) * n, DCVM_FALSE);
    }

    void deallocate(pointer p, size_type n) noexcept
    {
        if (p)
        {
            SystemApi::MemoryFree(p);
        }
    }

    void construct(pointer p, const_reference val) noexcept
    {
        new(static_cast<void*>(p)) T(val);
    }

    template< class U, class... Args >
    void construct( U* p, Args&&... args )
    {
        new(static_cast<void*>(p)) U(std::forward<Args>(args)...);
    }

    void destroy(pointer p)
    {
        p->~T();
    }

    template< class U >
    void destroy( U* p )
    {
        p->~U();
    }
};

//STLAllocator does not have state. So all allocator are equal.

template <typename T>
inline bool operator==(
    const STLAllocator<T>     &a
    , const STLAllocator<T>   &b
) noexcept
{
    return true;
}

template <typename T>
inline bool operator!=(
    const STLAllocator<T>     &a
    , const STLAllocator<T>   &b
) noexcept
{
    return false;
}

} // namespace base
} // namespace dcvm

#endif