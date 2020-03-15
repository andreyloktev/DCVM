#ifndef DCVM_CORE_BASE_CLOUDPROVIDER_HPP_
#define DCVM_CORE_BASE_CLOUDPROVIDER_HPP_

#include <dcvm/DCVMCloudProviderAPI.h>
#include <dcvm/cpp/base/MemoryBase.hpp>
#include <dcvm/cpp/base/DCVMTypes.hpp>

namespace dcvm  {
namespace base  {

class CloudProvider final : public base::MemoryBase
{
public:
    CloudProvider() noexcept = default;

    explicit CloudProvider(const DCVMCloudProviderAPI &providerApi) noexcept : m_providerApi(providerApi)
    {
    }

    CloudProvider(const CloudProvider&) noexcept = default;

    CloudProvider& operator=(const CloudProvider&) noexcept = default;

    ~CloudProvider() noexcept = default;

    DCVMStringView_t GetProviderId(struct DCVMContext *pCtxt) const noexcept
    {
        return m_providerApi.GetProviderId(pCtxt);
    }

    DCVM_ERROR GetOAuthUri(DCVMString_t &url, struct DCVMContext *pCtxt) const noexcept
    {
        dcvm_char_t *pUrl = nullptr;
        auto err = m_providerApi.GetOAuthUri(&pUrl, &g_systemApi, pCtxt);
        if (DCVM_FAILED(err))
        {
            return err;
        }

        url = pUrl;
        SystemApi::MemoryFree(pUrl);

        return err;
    }

    DCVM_ERROR LogInWithOAuthCode(
        const DCVMStringView_t      &code
        , struct DCVMCloudProvider* &pCloudProvider
        , struct DCVMContext        *pCtxt
    ) const noexcept
    {
        return m_providerApi.LogInWithOAuthCode(
            code.data()
            , &pCloudProvider
            , &g_systemApi
            , pCtxt
        );
    }

    DCVM_ERROR LogInWithRefreshToken(
        const DCVMStringView_t      &refreshToken
        , struct DCVMCloudProvider* &pCloudProvider
        , struct DCVMContext        *pCtxt
    ) const noexcept
    {
        return m_providerApi.LogInWithOAuthCode(
            refreshToken.data()
            , &pCloudProvider
            , &g_systemApi
            , pCtxt
        );
    }

    OAuthToken GetOAuthToken(struct DCVMCloudProvider *pCloudProvider, struct DCVMContext *pCtxt) const noexcept
    {
        return m_providerApi.GetOAuthToken(pCloudProvider, pCtxt);
    }

    DCVM_ERROR LogOut(struct DCVMCloudProvider *pCloudProvider, struct DCVMContext *pCtxt) const noexcept
    {
        return m_providerApi.LogOut(pCloudProvider, pCtxt);
    }

    DCVM_ERROR CreateFile(
        struct DCVMCloudProvider    *pCloudProvider
        , const DCVMStringView_t    &fileName
        , const DCVMFileInfo        &fi
        , DCVMFileInfo              &fiOut
        , struct DCVMHandle*        &pFileHandle
        , struct DCVMContext        *pCtxt
    ) const noexcept
    {
        return m_providerApi.CreateFile(pCloudProvider, fileName.data(), &fi, &fiOut, &pFileHandle, pCtxt);
    }

    DCVM_ERROR OpenFile(
        struct DCVMCloudProvider    *pCloudProvider
        , const DCVMStringView_t    &fileName
        , DCVMFileInfo              &fi
        , struct DCVMHandle*        &pFileHandle
        , struct DCVMContext        *pCtxt
    ) const noexcept
    {
        return m_providerApi.OpenFile(pCloudProvider, fileName.data(), &fi, &pFileHandle, pCtxt);
    }

    DCVM_ERROR CloseFile(
        struct DCVMCloudProvider    *pCloudProvider
        , struct DCVMHandle         *pFileHandle
        , struct DCVMContext        *pCtxt
    ) const noexcept
    {
        return m_providerApi.CloseFile(pCloudProvider, pFileHandle, pCtxt);
    }

    DCVM_ERROR GetFileInfo(
        struct DCVMCloudProvider    *pCloudProvider
        , struct DCVMHandle         *pFileHandle
        , DCVMFileInfo              &fi
        , struct DCVMContext        *pCtxt
    ) const noexcept
    {
        return m_providerApi.GetFileInfo(pCloudProvider, pFileHandle, &fi, pCtxt);
    }

    DCVM_ERROR ReadFile(
        struct DCVMCloudProvider    *pCloudProvider
        , struct DCVMHandle         *pFileHandle
        , const dcvm_uint64_t       offset
        , dcvm_uint8_t              *pBuffer
        , dcvm_uint32_t             bufferSize
        , struct DCVMContext        *pCtxt
    ) const noexcept
    {
        return m_providerApi.ReadFile(pCloudProvider, pFileHandle, offset, pBuffer, bufferSize, pCtxt);
    }

    DCVM_ERROR WriteFile(
        struct DCVMCloudProvider    *pCloudProvider
        , struct DCVMHandle         *pFileHandle
        , const dcvm_uint64_t       offset
        , const dcvm_uint8_t        *pBuffer
        , dcvm_uint32_t             bufferSize
        , struct DCVMContext        *pCtxt
    ) const noexcept
    {
        return m_providerApi.WriteFiele(pCloudProvider, pFileHandle, offset, pBuffer, bufferSize, pCtxt);
    }

    DCVM_ERROR UnlinkFile(
        struct DCVMCloudProvider    *pCloudProvider
        , const DCVMStringView_t    &fileName
        , struct DCVMContext        *pCtxt
    ) const noexcept
    {
        return m_providerApi.UnlinkFile(pCloudProvider, fileName.data(), pCtxt);
    }

    DCVM_ERROR ReadDirectory(
        struct DCVMCloudProvider    *pCloudProvider
        , struct DCVMEnumerator     *pEnumerator
        , DCVMFileInfo              *pFileInfo
        , const dcvm_uint32_t       fiCnt
        , struct DCVMContext        *pCtxt
    ) const noexcept
    {
        return m_providerApi.ReadDirectory(pCloudProvider, pEnumerator, pFileInfo, fiCnt, pCtxt);
    }

    DCVM_ERROR MoveFile(
        struct DCVMCloudProvider    *pCloudProvider
        , const DCVMStringView_t    &srcFile
        , struct DCVMHandle         *pSrcFileHandle
        , const DCVMStringView_t    &dstFile
        , const dcvm_bool_t         bReplace
        , struct DCVMContext        *pCtxt
    ) const noexcept
    {
        return m_providerApi.MoveFile(pCloudProvider, srcFile.data(), pSrcFileHandle, dstFile.data(), bReplace, pCtxt);
    }

    DCVM_ERROR GetDiskInfo(
        struct DCVMCloudProvider    *pCloudProvider
        , DCVMCloudDiskInfo         &diskInfo
        , struct DCVMContext        *pCtxt
    ) const noexcept
    {
        return m_providerApi.GetDiskInfo(pCloudProvider, &diskInfo, pCtxt);
    }
private:
    DCVMCloudProviderAPI m_providerApi = {};
};

} // namespace base
} // namespace dcvm

#endif