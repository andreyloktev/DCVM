#ifndef DCVM_BASE_DCVMTYPES_HPP_
#define DCVM_BASE_DCVMTYPES_HPP_

#include "dcvm_defines.hpp"
#include "EASTLAllocator.hpp"
#include <dcvm/DCVMTypes.h>

#include <EASTL/string.h>
#include <EASTL/vector.h>
#include <EASTL/unordered_map.h>

namespace dcvm {
namespace base {

using DCVMString_t = eastl::basic_string<dcvm_char_t, EASTLAllocator>;

template <typename T>
using DCVMVector_t = eastl::vector<T, EASTLAllocator>;

template <typename Key, typename T>
using DCVMUnorderedMap_t = eastl::unordered_map<Key, T, eastl::hash<Key>, eastl::equal_to<Key>, EASTLAllocator>;

template <typename First, typename Second>
using DCVMPair_t = eastl::pair<First, Second>;


} // namespace base
} // namespcae dcvm

#endif