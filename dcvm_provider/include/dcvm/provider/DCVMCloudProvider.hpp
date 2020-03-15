#ifndef DCVM_PROVIDER_DCVMCLOUDPROVIDER_HPP_
#define DCVM_PROVIDER_DCVMCLOUDPROVIDER_HPP_

#include <dcvm/cpp/base/DCVMTypes.hpp>

/*!
 * @brief Base cloud provider class used in the DCVMCloudProviderAPI
*/
struct DCVMCloudProvider
{
protected:
    dcvm::base::DCVMString_t m_accessToken;
    dcvm::base::DCVMString_t m_refreshToken;
public:
    virtual ~DCVMCloudProvider() noexcept {}
protected:
    /*!
     * @brief Send http request with relogin policy via refresh token.
     * @param [in] method http method.
     * @param [in] uri operation.
     * @param [in] pHeaders pointer to operation headers.
     * @param [in] amountHeaders amount operation headers.
     * @param [in] 
    */
    virtual DCVM_ERROR SendRequest(
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
    ) noexcept = 0;
};

#endif