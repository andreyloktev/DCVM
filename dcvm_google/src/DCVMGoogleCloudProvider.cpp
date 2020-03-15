#include <dcvm/DCVMLogger.h>
#include "DCVMGoogleCloudProvider.hpp"
#include <dcvm/provider/DCVMCryptoHelper.hpp>

namespace dcvm      {
namespace provider  {
namespace google    {

namespace internal {

DCVM_ERROR RandomDataBase64url(dcvm_size_t size, base::DCVMVector_t<uint8_t> &base64RNG, struct DCVMContext *pCtxt)
{
    dcvm_uint8_t *pBuf = base::SystemApi::MemoryAllocate<dcvm_uint8_t>(size, DCVM_FALSE);
    if (nullptr == pBuf)
    {
        DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES);
        return DCVM_ERR_INSUFFICIENT_RESOURCES;
    }

    auto err = base::SystemApi::CryptoRNG(pBuf, size, pCtxt);
    if (DCVM_FAILED(err))
    {
        DCVM_ERROR_TRACE(err);
        return err;
    }

    err = DCVMCryptoHelper::ToBase64Url(base::DCVMVector_t<uint8_t>(pBuf, pBuf + size), base64RNG);
    if (DCVM_FAILED(err))
    {
        DCVM_ERROR_TRACE(err);
        base64RNG.clear();
        return err;
    }

    return DCVM_ERR_SUCCESS;
}

} // namespace internal

DCVM_ERROR DCVMGoogleCloudProvider::AuthorizationUri(dcvm::base::DCVMString_t &uri, struct DCVMContext *pCtxt) noexcept
{
    // Based on https://github.com/googlesamples/oauth-apps-for-windows/blob/master/OAuthConsoleApp/OAuthConsoleApp/Program.cs

    const dcvm_char_t *pCodeChallengeMethod = DCVM_TEXT("S256");
    dcvm::base::DCVMString_t state, codeVerifier, codeChallenge;

    DCVM_BEGIN_CATCH_HANDLER

    dcvm::base::DCVMVector_t<dcvm_uint8_t> base64RNG;
    auto err = internal::RandomDataBase64url(32, base64RNG, pCtxt);
    if (DCVM_FAILED(err))
    {
        DCVM_ERROR_TRACE(err);
        return err;
    }

    state = dcvm::base::DCVMString_t(base64RNG.cbegin(), base64RNG.cend());

    err = internal::RandomDataBase64url(32, base64RNG, pCtxt);
    if (DCVM_FAILED(err))
    {
        DCVM_ERROR_TRACE(err);
        return err;
    }

    codeVerifier = dcvm::base::DCVMString_t(base64RNG.cbegin(), base64RNG.cend());

    dcvm_uint8_t *pTmp = nullptr;
    dcvm_size_t hashedDataSize = 0;

    err = dcvm::base::SystemApi::CryptoSHA256(&base64RNG[0], base64RNG.size(), pTmp, hashedDataSize, pCtxt);
    if (DCVM_FAILED(err))
    {
        DCVM_ERROR_TRACE(err);
        return err;
    }

    base::DCVMUniquePtr_t<dcvm_uint8_t> pHashedData(pTmp);

    base::DCVMVector_t<uint8_t> hashedBase64;
    err = DCVMCryptoHelper::ToBase64Url(base::DCVMVector_t<uint8_t>(pHashedData.get(), pHashedData.get() + hashedDataSize), hashedBase64, true);
    if (DCVM_FAILED(err))
    {
        DCVM_ERROR_TRACE(err);
        return err;
    }

    codeChallenge = base::DCVMString_t(hashedBase64.cbegin(), hashedBase64.cend());

    //uri += g_pAuthorizationEndpoint + 

    DCVM_END_CATCH_HANDLER

    return DCVM_ERR_SUCCESS;
}

} // namespace google
} // namespace provider
} // namespace dcvm