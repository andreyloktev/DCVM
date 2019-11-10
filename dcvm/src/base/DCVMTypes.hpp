#ifndef DCVM_BASE_DCVMTYPES_HPP_
#define DCVM_BASE_DCVMTYPES_HPP_

#include "dcvm_defines.hpp"
#include "EASTLAllocator.hpp"
#include <dcvm/DCVMTypes.h>

#include <EASTL/string.h>
#include <EASTL/vector.h>
#include <EASTL/unordered_map.h>
#include <EASTL/map.h>

namespace dcvm {
namespace base {

using DCVMString_t = eastl::basic_string<dcvm_char_t, EASTLAllocator>;

template <typename T>
using DCVMVector_t = eastl::vector<T, EASTLAllocator>;

template <class T>
struct DCVMHash final
{
    /*!
     * @brief Calculate a hash of string according to article http://www.cse.yorku.ca/~oz/hash.html
     *        TODO: Need to check implementtaion.
    */
    dcvm_size_t operator()(const T value) const
    {
        return dcvm_size_t(value);
    }
};

template <>
struct DCVMHash<DCVMString_t> final
{
    /*!
     * @brief Calculate a hash of string according to article http://www.cse.yorku.ca/~oz/hash.html
     *        TODO: Need to check implementtaion.
    */
    dcvm_size_t operator()(const DCVMString_t &str) const
    {
        auto pStr = str.c_str();

        dcvm_size_t hash = 5381;
        int c = 0;

        while (c = *pStr++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
    }
};

template <typename Key, typename T>
using DCVMUnorderedMap_t = eastl::unordered_map<Key, T, DCVMHash<Key>, eastl::equal_to<Key>, EASTLAllocator>;

template <typename First, typename Second>
using DCVMPair_t = eastl::pair<First, Second>;

template <typename Key, typename T>
using DCVMMap_t = eastl::map<Key, T, eastl::equal_to<Key>, EASTLAllocator>;

} // namespace base
} // namespcae dcvm

#endif