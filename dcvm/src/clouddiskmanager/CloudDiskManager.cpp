// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


#include <dcvm/DCVMLogger.h>
#include "CloudDiskManager.hpp"
#include "../clouddisk/CloudDisk.hpp"

namespace dcvm              {
namespace clouddiskmanager  {

CloudDiskManager::CloudDiskManager() noexcept
{
    //TODO: Add initialization of saved clients
}

CloudDiskManager::~CloudDiskManager() noexcept
{
    for (auto& cloudDisk : m_cloudDisks)
    {
        if (nullptr != cloudDisk.second)
        {
            cloudDisk.second->DecReff(nullptr);
        }
    }
}

DCVM_ERROR CloudDiskManager::AddCloudProvider(
    DCVMCloudProviderAPI        provider
    , base::DCVMStringView_t    &providerId
    , struct DCVMContext        *pCtxt
) noexcept
{
    UNREFFERENCE_VARIABLE(pCtxt);

    if ((nullptr == provider.GetProviderId) || (nullptr == provider.GetProviderId(pCtxt)))
    {
        DCVM_INFO_TRACE("Bad parameters. DCVMCloudDiskProviderAPI::GetCloudDiskId is NULL or id is empty string");
        DCVM_ERROR_TRACE(DCVM_ERR_PROVIDER_ID_IS_NOT_UNIQUE);

        return DCVM_ERR_PROVIDER_ID_IS_NOT_UNIQUE;
    }

    providerId = provider.GetProviderId(pCtxt);
    if (providerId.empty())
    {
        DCVM_INFO_TRACE("Provider id is empty.");
        return DCVM_ERR_PROVIDER_ID_IS_NOT_UNIQUE;
    }

    auto it = m_providers.find(providerId.data());
    if (m_providers.cend() != it)
    {
        DCVM_ERROR_TRACE(DCVM_ERR_PROVIDER_ID_IS_NOT_UNIQUE);
        return DCVM_ERR_PROVIDER_ID_IS_NOT_UNIQUE;
    }

    m_providers.insert(base::DCVMMakePair(providerId.data(), base::CloudProvider(provider)));

    return DCVM_ERR_SUCCESS;
}

base::DCVMVector_t<base::DCVMStringView_t> CloudDiskManager::GetCloudProviders(struct DCVMContext *pCtxt) const noexcept
{
    UNREFFERENCE_VARIABLE(pCtxt);

    base::DCVMVector_t<base::DCVMStringView_t> providers;

    if (m_providers.empty())
    {
        return providers;
    }

    providers.reserve(m_providers.size());

    for (const auto &provider : m_providers)
    {
        providers.push_back(provider.first);
    }

    return providers;
}

DCVM_ERROR CloudDiskManager::GetAuthorizationUri(
    const base::DCVMStringView_t    &providerId
    , base::DCVMString_t            &uri
    , struct DCVMContext            *pCtxt
) const noexcept
{
    auto itProvider = m_providers.find(providerId);
    if (m_providers.cend() == itProvider)
    {
        return DCVM_ERR_PROVIDER_IS_NOT_FOUND;
    }

    return itProvider->second.GetOAuthUri(uri, pCtxt);
}

DCVM_ERROR CloudDiskManager::CreateCloudDisk(
    const base::DCVMStringView_t    &providerId
    , const base::DCVMStringView_t  &oauthCode
    , dcvm_size_t                   &cloudDiskId
    , struct DCVMContext            *pCtxt
) noexcept
{
    auto itProvider = m_providers.find(providerId);
    if (m_providers.cend() == itProvider)
    {
        DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES);
        return DCVM_ERR_PROVIDER_IS_NOT_FOUND;
    }

    auto pCloudDisk = new clouddisk::CloudDisk(itProvider->second);
    if (nullptr == pCloudDisk)
    {
        DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES);
        return DCVM_ERR_INSUFFICIENT_RESOURCES;
    }

    auto err = pCloudDisk->LogInWithOAuthCode(oauthCode, pCtxt);
    if (DCVM_FAILED(err))
    {
        DCVM_ERROR_TRACE(err);
        pCloudDisk->DecReff(pCtxt);
        return err;
    }

    DCVMCloudDiskInfo di = {};
    dcvm_size_t diSize = sizeof(di);

    err = pCloudDisk->CloudGetDiskInfo(&di, diSize, pCtxt);
    if (DCVM_FAILED(err))
    {
        DCVM_ERROR_TRACE(err);
        pCloudDisk->DecReff(pCtxt);
        return err;
    }

    cloudDiskId = base::DCVMHash<base::DCVMString_t>()(base::DCVMString_t(di.providerInfo.id) + DCVM_TEXT("_") + di.userInfo.name);

    m_cloudDisks.insert(base::DCVMMakePair(cloudDiskId, pCloudDisk));

    return err;
}

base::DCVMVector_t<dcvm_size_t> CloudDiskManager::GetCloudDisks(struct DCVMContext *pCtxt) const noexcept
{
    UNREFFERENCE_VARIABLE(pCtxt);
    
    base::DCVMVector_t<dcvm_size_t> cloudDisks;

    if (m_cloudDisks.empty())
    {
        return cloudDisks;
    }

    cloudDisks.reserve(m_cloudDisks.size());

    for (const auto &cloudDisk : m_cloudDisks)
    {
        cloudDisks.push_back(cloudDisk.first);
    }

    return cloudDisks;
}

DCVM_ERROR CloudDiskManager::GetCloudDiskInformation(
    const dcvm_size_t       id
    , DCVMCloudDiskInfo     *pCloudDiskInfo
    , dcvm_size_t           &size
    , struct DCVMContext    *pCtxt
) const noexcept
{
    auto itCloudDisk = m_cloudDisks.find(id);
    if (m_cloudDisks.cend() == itCloudDisk)
    {
        return DCVM_ERR_CLOUDDISK_IS_NOT_FOUND;
    }

    if (nullptr == itCloudDisk->second)
    {
        DCVM_INFO_TRACE("Cloud disk instance is nullptr");
        return DCVM_ERR_BAD_PARAMS;
    }

    return itCloudDisk->second->CloudGetDiskInfo(pCloudDiskInfo, size, pCtxt);
}

DCVM_ERROR CloudDiskManager::InitCloudDisk(
    const dcvm_size_t                           cloudDiskId
    , const dcvm_uint64_t                        flags
    , clouddisk::objects::CloudDiskDirectory*    &pRootDir
    , clouddisk::ICloudDisk*                     &pCloudDisk
    , struct DCVMContext                         *pCtxt
) const noexcept
{
    auto it = m_cloudDisks.find(cloudDiskId);
    if (m_cloudDisks.cend() == it)
    {
        DCVM_ERROR_TRACE(DCVM_ERR_CLOUDDISK_IS_NOT_FOUND);
        return DCVM_ERR_CLOUDDISK_IS_NOT_FOUND;
    }

    DCVM_ERROR err = it->second->Mount(flags, pRootDir, pCtxt);
    if (DCVM_FAILED(err))
    {
        DCVM_ERROR_TRACE(err);
        return err;
    }

    /// Increment refference counter before get this object to outside.
    pRootDir->IncReff();
    pCloudDisk = it->second;
    pCloudDisk->IncReff();

    return err;
}

DCVM_ERROR CloudDiskManager::InitCloudDisk(
    const base::DCVMVector_t<dcvm_size_t>        &cloudDisksIds
    , const dcvm_uint64_t                        flags
    , clouddisk::objects::CloudDiskDirectory*    &pRootDir
    , clouddisk::ICloudDisk*                     &pCloudDisk
    , struct DCVMContext                         *pCtxt
) const noexcept
{
    UNREFERENCED_PARAMETER(cloudDisksIds);
    UNREFERENCED_PARAMETER(flags);
    UNREFERENCED_PARAMETER(pRootDir);
    UNREFERENCED_PARAMETER(pCloudDisk);
    UNREFERENCED_PARAMETER(pCtxt);

    return DCVM_ERR_NOT_IMPLEMENTED;
}

} // namespace clouddiskmanager
} // namespace dcvm