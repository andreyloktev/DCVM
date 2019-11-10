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
        DCVM_ERROR_TRACE(DCVM_ERR_SUCH_CLIENT_ALREADY_EXISTS);
        return DCVM_ERR_SUCH_CLIENT_ALREADY_EXISTS;
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

        auto item = eastl::make_pair(client.first, uri);
        clients.emplace_back(item);
    }

    return err;
}

} // namespace clouddiskmanager
} // namespace dcvm