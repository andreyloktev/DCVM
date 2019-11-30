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
    //TODO: Add logic for saving refresh tokens
}

DCVM_ERROR CloudDiskManager::AddClient(DCVMCloudDiskAPI client, base::DCVMString_t &clientId, struct DCVMContext *pCtxt) noexcept
{
    UNREFFERENCE_VARIABLE(pCtxt);

    if ((nullptr == client.GetCloudDiskId) || (0 == *(client.GetCloudDiskId(pCtxt))))
    {
        DCVM_INFO_TRACE("Bad parameters. DCVMCloudDiskAPI::GetCloudDiskId is NULL or id is empty string");
        DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);

        return DCVM_ERR_BAD_PARAMS;
    }

    auto it = m_clients.find(client.GetCloudDiskId(pCtxt));
    if (m_clients.cend() != it)
    {
        DCVM_ERROR_TRACE(DCVM_ERR_CLIENT_ALREADY_EXISTS);
        return DCVM_ERR_CLIENT_ALREADY_EXISTS;
    }

    auto pCloudDisk = new clouddisk::CloudDisk(client);
    if (nullptr == pCloudDisk)
    {
        DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES);
        return DCVM_ERR_INSUFFICIENT_RESOURCES;
    }

    clientId = client.GetCloudDiskId(pCtxt);
    m_clients.insert(base::DCVMPair_t<base::DCVMString_t, ICloudDisk_t*>(clientId, pCloudDisk));

    return DCVM_ERR_SUCCESS;
}

base::DCVMVector_t<base::DCVMString_t> CloudDiskManager::GetClients(struct DCVMContext *pCtxt) const noexcept
{
    UNREFFERENCE_VARIABLE(pCtxt);

    base::DCVMVector_t<base::DCVMString_t> clients;

    if (m_authorzedClients.empty())
    {
        return clients;
    }

    clients.reserve(m_authorzedClients.size());

    for (const auto &client : m_authorzedClients)
    {
        clients.push_back(client.first);
    }

    return clients;
}

DCVM_ERROR CloudDiskManager::GetUnauthorizedClients(
    base::DCVMVector_t<base::DCVMPair_t<base::DCVMString_t, base::DCVMString_t>>    &clients
    , struct DCVMContext                                                            *pCtxt
) const noexcept
{
    UNREFFERENCE_VARIABLE(pCtxt);
    
    if (m_clients.empty())
    {
        return DCVM_ERR_SUCCESS;
    }

    DCVM_ERROR err = DCVM_ERR_SUCCESS;
    base::DCVMString_t uri;
    clients.reserve(m_clients.size());

    for (const auto &client : m_clients)
    {
        err = client.second->GetOAuthUri(uri, pCtxt);
        if (DCVM_FAILED(err))
        {
            DCVM_ERROR_TRACE(err);
            clients.clear();
            return err;
        }

        auto item = base::DCVMMakePair(client.first, uri);
        clients.emplace_back(item);
    }

    return err;
}

DCVM_ERROR CloudDiskManager::AuthorizeClient(
    const base::DCVMString_t    &clientId
    , const base::DCVMString_t  &oauthCode
    , struct DCVMContext        *pCtxt
) noexcept
{
    if (clientId.empty() || oauthCode.empty())
    {
        DCVM_INFO_TRACE("\"clientId\" or \"oauthCode\" or both are empty.");
        DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
        return DCVM_ERR_BAD_PARAMS;
    }

    auto it = m_authorzedClients.find(clientId);
    if (m_authorzedClients.cend() != it)
    {
        return DCVM_ERR_CLIENT_HAS_BEEN_ALREADY_AUTHORIZED;
    }

    it = m_clients.find(clientId);
    if (m_clients.cend() == it)
    {
        DCVM_ERROR_TRACE(DCVM_ERR_CLIENT_DOES_NOT_EXIST);
        return DCVM_ERR_CLIENT_DOES_NOT_EXIST;
    }

    base::DCVMString_t refreshToken; ///TODO Now refresh token is not used. But later saving refresh token and auto login will be added.
    DCVM_ERROR err = it->second->LogInWithOAuthCode(oauthCode, refreshToken, pCtxt);
    if (DCVM_FAILED(err))
    {
        DCVM_ERROR_TRACE(err);
        return err;
    }

    m_authorzedClients.insert(*it);

    return err;
}

DCVM_ERROR CloudDiskManager::InitCloudDisk(
    const base::DCVMString_t                     &clientId
    , const dcvm_uint64_t                        flags
    , clouddisk::objects::CloudDiskDirectory*    &pRootDir
    , clouddisk::ICloudDisk*                     &pCloudDisk
    , struct DCVMContext                         *pCtxt
) const noexcept
{
    if (clientId.empty())
    {
        DCVM_INFO_TRACE("\"clientId\" is empty.");
        DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
        return DCVM_ERR_BAD_PARAMS;
    }

    auto it = m_authorzedClients.find(clientId);
    if (m_authorzedClients.cend() == it)
    {
        DCVM_ERROR_TRACE(DCVM_ERR_CLIENT_IS_NOT_AUTHORIZED);
        return DCVM_ERR_CLIENT_IS_NOT_AUTHORIZED;
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
    const base::DCVMVector_t<base::DCVMString_t> &clientIds
    , const dcvm_uint64_t                        flags
    , clouddisk::objects::CloudDiskDirectory*    &pRootDir
    , clouddisk::ICloudDisk*                     &pCloudDisk
    , struct DCVMContext                         *pCtxt
) const noexcept
{
    UNREFERENCED_PARAMETER(clientIds);
    UNREFERENCED_PARAMETER(flags);
    UNREFERENCED_PARAMETER(pRootDir);
    UNREFERENCED_PARAMETER(pCloudDisk);
    UNREFERENCED_PARAMETER(pCtxt);

    return DCVM_ERR_NOT_IMPLEMENTED;
}

} // namespace clouddiskmanager
} // namespace dcvm