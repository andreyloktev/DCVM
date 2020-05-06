#ifndef DCVM_PROVIDER_UTiLITIES_CONVERSIONS_DCVMCONVERSIONS_HPP_
#define DCVM_PROVIDER_UTiLITIES_CONVERSIONS_DCVMCONVERSIONS_HPP_

#include <dcvm/DCVMError.h>
#include <dcvm/cpp/base/DCVMTypes.hpp>

namespace dcvm          {
namespace provider      {
namespace utilities     {
namespace conversions   {

/*!
 * @brief Convert utf8 encoded string to utf16 encoded string.
 * @param [in] utf8Str utf8 encoded string.
 * @param [in, out] utf16Str resulted utf16 encoded string.
 * @return error code.
*/
DCVM_ERROR Utf8ToUtf16(const dcvm::base::DCVMUtf8String_t &utf8Str, dcvm::base::DCVMUtf16String_t &utf16Str) noexcept;

/*!
 * @brief (Stub) Convert utf16 encoded string to utf16 encoded string.
 * @param [in] utf16StrIn utf16 encoded string.
 * @param [in, out] utf16StrOut resulted utf16 encoded string.
 * @return error code.
*/
DCVM_ERROR Utf8ToUtf16(const dcvm::base::DCVMUtf16String_t &utf16StrIn, dcvm::base::DCVMUtf16String_t &utf16StrOut) noexcept;

/*!
 * @brief Convert utf16 encoded string to utf8 encoded string.
 * @param [in] utf16Str utf16 encoded string.
 * @param [in, out] utf8Str resulted utf8 encoded string.
 * @return error code.
*/
DCVM_ERROR Utf16ToUtf8(const dcvm::base::DCVMUtf16String_t &utf16Str, dcvm::base::DCVMUtf8String_t &utf8Str) noexcept;

/*!
 * @brief (Stub) Convert utf8 encoded string to utf8 encoded string.
 * @param [in] utf8StrIn utf8 encoded string.
 * @param [in, out] utf8StrOut resulted utf8 encoded string.
 * @return error code.
*/
DCVM_ERROR Utf16ToUtf8(const dcvm::base::DCVMUtf8String_t &utf8StrIn, dcvm::base::DCVMUtf8String_t &utf8StrOut) noexcept;

} // namespace conversions
} // namespace utilities
} // namespace provider
} // namespace dcvm

#endif