#include <dcvm/provider/DCVMCryptoHelper.hpp>
#include <dcvm/DCVMLogger.h>

namespace dcvm      {
namespace provider  {

DCVM_ERROR DCVMCryptoHelper::ToBase64Url(
    const base::DCVMVector_t<dcvm_uint8_t>  &in
    , base::DCVMVector_t<dcvm_uint8_t>      &out
    , bool                                  bNoPadding
) noexcept
{
    static const dcvm_uint8_t Base64UrlAlphabet[] =
    {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',

        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 

        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',

        'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',

        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',

        'o', 'p', 'q', 'r', 's', 't', 'u', 'v',

        'w', 'x', 'y', 'z', '0', '1', '2', '3',

        '4', '5', '6', '7', '8', '9', '-', '_'
    };

    if (in.empty())
    {
        return {};
    }

    const dcvm_int32_t inSize = static_cast<dcvm_int32_t>(in.size());
    dcvm_int32_t outSize = 4 * ((inSize + 2) / 3);
    dcvm_int32_t padding = inSize % 3;

    if (bNoPadding && padding)
    {
        for (; padding < 3; padding++)
        {
            outSize--;
        }
    }

    DCVM_BEGIN_CATCH_HANDLER
    out.resize(outSize, 0);
    DCVM_END_CATCH_HANDLER

    dcvm_uint8_t *pOut = &out[0];

    int i = 0;
    for (;i < inSize - 2; i += 3)
    {
        *pOut++ = Base64UrlAlphabet[(in[i] >> 2) & 0x3F];
        *pOut++ = Base64UrlAlphabet[((in[i] & 0x3) << 4) | ((in[i+1] >> 4) & 0xF)];
        *pOut++ = Base64UrlAlphabet[((in[i+1] & 0xF) << 2) | ((in[i+2] >> 6) & 0x3)];
        *pOut++ = Base64UrlAlphabet[in[i+2] & 0x3F];
    }

    if (i < in.size())
    {
        *pOut++ = Base64UrlAlphabet[(in[i] >> 2) & 0x3F];

        if (i == (inSize - 1))
        {
            *pOut++ = Base64UrlAlphabet[(in[i] & 0x3) << 4];
        }
        else
        {
            *pOut++ = Base64UrlAlphabet[((in[i] & 0x3) << 4 ) | ((in[i+1] >> 4) & 0xF)];
            *pOut++ = Base64UrlAlphabet[((in[i+1] & 0xF) << 2)];
        }

        for (; (padding < 3) && !bNoPadding; padding++)
        {
            *pOut++ = '=';
        }
    }

    return DCVM_ERR_SUCCESS;
}

} // namespace providers
} // namespace dcvm