#ifndef DCVM_PROVIDERS_DCVMCRYPTOHELPER_HPP_
#define DCVM_PROVIDERS_DCVMCRYPTOHELPER_HPP_

#include <dcvm/cpp/base/DCVMTypes.hpp>

namespace dcvm      {
namespace provider  {

class DCVMCryptoHelper final
{
public:
    /*!
     * @brief Encode input bytes sequence into base64.
     * @param [in] in input sequence of bytes to encode.
     * @param [out] out encoded sequence of bytes.
     * @param [in] bNoPadding add padding symbol?
     * @return error code
    */
    static DCVM_ERROR ToBase64Url(
        const base::DCVMVector_t<dcvm_uint8_t>  &in
        , base::DCVMVector_t<dcvm_uint8_t>      &out
        , bool                                  bNoPadding = false
    ) noexcept;
};

} // namespace providers
} // namespace dcvm

#endif