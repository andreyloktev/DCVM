#ifndef DCVM_TEST_DCVM_UTEST_DCVMCLOUDPROVIDER_HPP_
#define DCVM_TEST_DCVM_UTEST_DCVMCLOUDPROVIDER_HPP_

#include "dcvm_utest_helper.hpp"
#include "dcvm_cloudstorage_stub.hpp"

using namespace dcvm_utests;

struct DCVMCloudProvider final
{
    explicit DCVMCloudProvider(DCVMSystemAPI *pSysmApi) : m_pSystemApi(pSysmApi)
    {
    }

    DCVM_ERROR LogInWithOAuthCode(const DCVMUtestString_t &oauthCode)
    {
        if (nullptr == m_pSystemApi)
        {
            return DCVM_ERR_BAD_PARAMS;
        }

        m_accessToken = (oauthCode + DCVM_TEXT("_access_token"));
        m_refreshToken = (oauthCode + DCVM_TEXT("_refresh_token"));

        m_pSystemApi->MemorySet(&m_diskInfo, sizeof(m_diskInfo), 0);

        m_diskInfo.childrenCount = 0;
        m_diskInfo.pChildren = nullptr;
        m_diskInfo.maxFileSize = 1024;
        m_diskInfo.totalSpace = 1024 * 1024 * 1024;
        m_diskInfo.usedSpace = 0;

        m_pSystemApi->MemoryCopy(
            m_diskInfo.providerInfo.id
            , CLOUD_PROVIDER_ID_SIZE * sizeof(dcvm_char_t)
            , g_pCloudProviderStubId
            , DCVMUtestString_t(g_pCloudProviderStubId).length() * sizeof(dcvm_char_t)
        );

        m_pSystemApi->MemoryCopy(
            m_diskInfo.userInfo.name
            , USER_NAME_SIZE * sizeof(dcvm_char_t)
            , g_pCloudStubUserName
            , DCVMUtestString_t(g_pCloudStubUserName).length() * sizeof(dcvm_char_t)
        );

        return DCVM_ERR_SUCCESS;
    }

    DCVM_ERROR GetDiskInfo(
        DCVMCloudDiskInfo &diskInfo
    ) const
    {
        if (nullptr == m_pSystemApi)
        {
            return DCVM_ERR_BAD_PARAMS;
        }

        m_pSystemApi->MemoryCopy(&diskInfo, sizeof(DCVMCloudDiskInfo), &m_diskInfo, sizeof(DCVMCloudDiskInfo));

        return DCVM_ERR_SUCCESS;
    }
private:
    DCVMUtestString_t m_accessToken;
    DCVMUtestString_t m_refreshToken;
    DCVMSystemAPI *m_pSystemApi = nullptr;
    DCVMCloudDiskInfo m_diskInfo;
};

#endif