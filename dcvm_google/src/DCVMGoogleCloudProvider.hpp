#ifndef DCVM_GOOGLE_DCVMGOOGLECLOUDPROVIDER_HPP_
#define DCVM_GOOGLE_DCVMGOOGLECLOUDPROVIDER_HPP_

#include <dcvm/provider/DCVMCloudProvider.hpp>

namespace dcvm      {
namespace provider  {
namespace google    {

class DCVMGoogleCloudProvider final : public DCVMCloudProvider
{
    // These are test client id and client secret created in the Google.
    static constexpr dcvm_char_t g_ClientId[] = {
        '6', '7', '3', '8', '9', '0', '5', '5', '4', '0', '7', '4', '-',
        'f', 'd', '9', 'o', 'n', '3', 'j', 'q', 'i', '7', '4', '0', 'k',
        'i', 'g', '4', 'd', 'k', 'j', '4', 'a', 'g', '9', '7', 'e', 'k',
        'r', '8', 'i', 'i', '6', '3', '.', 'a', 'p', 'p', 's', '.', 'g',
        'o', 'o', 'g', 'l', 'e', 'u', 's', 'e', 'r', 'c', 'o', 'n', 't',
        'e', 'n', 't', '.', 'c', 'o', 'm'
    };

    static constexpr dcvm_char_t g_ClientSecret[] = {
        'z', 'm', 'o', '9', 'B', 'F', 'J', 'E', '6', 'A', 'L', 'a', '8', 'N', 'k', 's', 'I', 'C', '2', 'B', 'e', '7', 'q', 'f'
    };

    static constexpr dcvm_char_t *g_pAuthorizationEndpoint = DCVM_TEXT("https://accounts.google.com/o/oauth2/v2/auth");
public:
    static DCVM_ERROR AuthorizationUri(dcvm::base::DCVMString_t &uri, struct DCVMContext *pCtxt) noexcept;
public:
    DCVMGoogleCloudProvider() noexcept = default;

    ~DCVMGoogleCloudProvider() noexcept = default;
protected:
    DCVM_ERROR SendRequest(
        const DCVMHttpMethod                    method
        , const dcvm::base::DCVMStringView_t    &uri
        , const DCVMNameValue                   *pHeaders
        , dcvm_size_t                           amountHeaders
        , const dcvm_uint8_t                    *pBody
        , dcvm_size_t                           bodySize
        , dcvm_uint32_t                         *pResponseCode
        , dcvm_uint8_t                          **ppResponse
        , dcvm_size_t                           *pResponseSize
        , struct DCVMContext                    *pCtxt
    ) noexcept override;
};
    
} // namespace google
} // namespace provider
} // namespace dcvm

#endif