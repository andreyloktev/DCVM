#ifndef DCVM_BASE_DCVMFUNCTIONS_HPP_
#define DCVM_BASE_DCVMFUNCTIONS_HPP_

#include "DCVMTypes.hpp"

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

} // namespace base
} // namespace dcvm

#endif