#ifndef DCVM_BASE_DCVMFUNCTIONS_HPP_
#define DCVM_BASE_DCVMFUNCTIONS_HPP_

#include "SystemApi.hpp"

#ifdef DCVM_USE_EASTL
#include "EASTLAllocator.hpp"
#else
#include "STLAllocator.hpp"
#endif

namespace dcvm {
namespace base {

template <typename First, typename Second>
constexpr inline auto DCVMMakePair(First &&first, Second &&second) noexcept
{
#ifdef DCVM_USE_EASTL
    return eastl::make_pair(first, second);
#else
    return std::make_pair(first, second);
#endif
}

template <typename T, typename... Args>
inline DCVMSharedPtr_t<T> DCVMMakeShared(Args&&... args) noexcept
{
#ifdef DCVM_USE_EASTL
    return DCVMSharedPtr_t<T>(new T(eastl::forward<Args>(args)...), DCVMDeleter(), EASTLAllocator(nullptr));
#else
    return DCVMSharedPtr_t<T>(new T(std::forward<Args>(args)...), DCVMDeleter(), STLAllocator<T>());
#endif
}

} // namespace base
} // namespace dcvm

#endif