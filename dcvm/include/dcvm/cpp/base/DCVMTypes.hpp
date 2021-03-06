#ifndef DCVM_BASE_DCVMTYPES_HPP_
#define DCVM_BASE_DCVMTYPES_HPP_

#include "dcvm_defines.hpp"
#include <dcvm/DCVMTypes.h>

#ifdef DCVM_USE_EASTL
#include <EASTL/string.h>
#include <EASTL/vector.h>
#include <EASTL/unordered_map.h>
#include <EASTL/map.h>
#include "EASTLAllocator.hpp"
#include <EASTL/unique_ptr.h>
#include <EASTL/shared_ptr.h>
#else
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <map>
#include "STLAllocator.hpp"
#include <memory>
#endif

namespace dcvm {
namespace base {

struct DCVMDeleter final
{
    void operator()(void *p) noexcept
    {
        if (p)
        {
            SystemApi::MemoryFree(p);
        }
    }
};

#ifdef DCVM_USE_EASTL

using DCVMString_t = eastl::basic_string<dcvm_char_t, EASTLAllocator>;

using DCVMUtf8String_t    = eastl::basic_string<char, EASTLAllocator>;

using DCVMUtf16String_t   = eastl::basic_string<wchar_t, EASTLAllocator>;

using DCVMStringView_t = eastl::string_view<dcvm_char_t>;

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

template <>
struct DCVMHash<DCVMStringView_t> final
{
    /*!
     * @brief Calculate a hash of string according to article http://www.cse.yorku.ca/~oz/hash.html
     *        TODO: Need to check implementtaion.
    */
    dcvm_size_t operator()(const DCVMStringView_t &str) const
    {
        auto pStr = str.data();

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

template <typename T, typename Deleter = DCVMDeleter>
using DCVMUniquePtr_t = eastl::unique_ptr<T, Deleter>;

template <typename T>
using DCVMSharedPtr_t = eastl::shared_ptr<T>;

#else

using DCVMString_t = std::basic_string<
    dcvm_char_t
    , std::char_traits<dcvm_char_t>
    , STLAllocator<dcvm_char_t>
>;

using DCVMUtf8String_t    = std::basic_string<char, std::char_traits<char>, STLAllocator<char>>;

using DCVMUtf16String_t   = std::basic_string<wchar_t, std::char_traits<wchar_t>, STLAllocator<wchar_t>>;

using DCVMStringView_t = std::basic_string_view<
    dcvm_char_t
    , std::char_traits<dcvm_char_t>
>;

template <typename T>
using DCVMVector_t = std::vector<T, STLAllocator<T>>;

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

template <>
struct DCVMHash<DCVMStringView_t> final
{
    /*!
     * @brief Calculate a hash of string according to article http://www.cse.yorku.ca/~oz/hash.html
     *        TODO: Need to check implementtaion.
    */
    dcvm_size_t operator()(const DCVMStringView_t &str) const
    {
        auto pStr = str.data();

        dcvm_size_t hash = 5381;
        int c = 0;

        while (c = *pStr++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
    }
};

template <typename First, typename Second>
using DCVMPair_t = std::pair<First, Second>;

template <typename Key, typename T>
using DCVMUnorderedMap_t = std::unordered_map<
    Key, T
    , DCVMHash<Key>
    , std::equal_to<Key>
    , STLAllocator<DCVMPair_t<const Key, T>>
>;

template <typename Key, typename T>
using DCVMMap_t = std::map<
    Key, T
    , std::equal_to<Key>
    , STLAllocator<DCVMPair_t<const Key, T>>
>;

template <typename T, typename Deleter = DCVMDeleter>
using DCVMUniquePtr_t = std::unique_ptr<T, Deleter>;

template <typename T>
using DCVMSharedPtr_t = std::shared_ptr<T>;

#endif


} // namespace base
} // namespcae dcvm

#endif

#include "DCVMFunctions.hpp"