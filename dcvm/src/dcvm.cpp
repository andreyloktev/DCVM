#include <dcvm/dcvm.h>
#include <dcvm/DCVMLogger.h>
#include "base/DCVMTypes.hpp"
#include "base/MemoryBase.hpp"
#include "base/SystemApi.hpp"
#include "CloudDiskManager/CloudDiskManager.hpp"

namespace dcvm {

DCVMSystemAPI g_pSystemApi = {};
using CloudDiskManager_t = dcvm::clouddiskmanager::CloudDiskManager;

namespace
{

inline dcvm_size_t SIZE_OF_DCVMSTRING(const base::DCVMString_t &str) noexcept
{
    return sizeof(dcvm_char_t) * str.length() + sizeof(dcvm_char_t);
}

dcvm_char_t* CopyDCVMString(const base::DCVMString_t &str) noexcept
{
    const auto STR_SIZE = SIZE_OF_DCVMSTRING(str);

    dcvm_char_t *pStr = static_cast<dcvm_char_t*>(base::SystemApi::MemoryAllocate(STR_SIZE, DCVM_TRUE));
    if (nullptr == pStr)
    {
        return pStr;
    }

    base::SystemApi::MemoryCopy(pStr, STR_SIZE, str.c_str(), STR_SIZE - sizeof(dcvm_char_t));

    return pStr;
}

} // namespace 

} //namespace dcvm

/*!
 * @class DCVM is control block of Dynamic cloud volume manager library.
*/
struct DCVM final : public dcvm::base::MemoryBase
{
    dcvm::CloudDiskManager_t cloudDiskManager;
};

/*!
 * @class DCVMCloudDisk represents initialized cloud disk instance.
*/
struct DCVMCloudDisk final : public dcvm::base::MemoryBase
{
    dcvm::clouddisk::ICloudDisk                     *pCloudDisk = nullptr;
    dcvm::clouddisk::objects::CloudDiskDirectory    *pRootDir   = nullptr;
};



extern "C"
{
    DCVM_ERROR dcvm_Init(DCVMSystemAPI systemApi, DCVM **ppDcvm, struct DCVMContext *pCtxt) noexcept
    {
        UNREFFERENCE_VARIABLE(pCtxt);

        if (nullptr == ppDcvm)
        {
            DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
            return DCVM_ERR_BAD_PARAMS;
        }

        dcvm::g_pSystemApi = systemApi;

        *ppDcvm = new DCVM();
        if (nullptr == *ppDcvm)
        {
            DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES);
            return DCVM_ERR_INSUFFICIENT_RESOURCES;
        }

        return DCVM_ERR_SUCCESS;
    }

    void dcvm_Release(DCVM *pDcvm, struct DCVMContext *pCtxt)
    {
        UNREFFERENCE_VARIABLE(pCtxt);

        if (nullptr == pDcvm)
        {
            return;
        }

        delete pDcvm;
    }

    DCVM_ERROR dcvm_ControlAddClient(DCVM *pDcvm, const DCVMCloudDiskAPI client, dcvm_char_t **ppClientId, struct DCVMContext *pCtxt) noexcept
    {
        if ((nullptr == pDcvm) || (nullptr == ppClientId))
        {
            DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
            return DCVM_ERR_BAD_PARAMS;
        }

        dcvm::base::DCVMString_t clientId;
        DCVM_ERROR err = pDcvm->cloudDiskManager.AddClient(client, clientId, pCtxt);
        if (DCVM_FAILED(err))
        {
            DCVM_ERROR_TRACE(err);
            return err;
        }

        dcvm_size_t clientIdSize = clientId.length() * sizeof(dcvm_char_t) + sizeof(dcvm_char_t);

        *ppClientId = static_cast<dcvm_char_t*>(dcvm::base::SystemApi::MemoryAllocate(clientIdSize, DCVM_TRUE));
        if (nullptr == *ppClientId)
        {
            DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES);
            return DCVM_ERR_INSUFFICIENT_RESOURCES;
        }

        dcvm::base::SystemApi::MemoryCopy(*ppClientId, clientIdSize, clientId.c_str(), clientId.length());

        return DCVM_ERR_SUCCESS;
    }

    DCVM_ERROR dcvm_ControlGetClients(DCVM *pDcvm, dcvm_char_t **ppClients, dcvm_size_t *pAmountClients, struct DCVMContext *pCtxt) noexcept
    {
        if ((nullptr == pDcvm) || (nullptr == ppClients) || (nullptr == pAmountClients))
        {
            DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
            return DCVM_ERR_BAD_PARAMS;
        }

        // Copy clients.

        auto CalculateBufferSizeForClientsList = [](const dcvm::base::DCVMVector_t<dcvm::base::DCVMString_t> &clients) noexcept
        {
            dcvm_size_t bufferSize = 0;

            for (const auto &client : clients)
            {
                bufferSize += dcvm::SIZE_OF_DCVMSTRING(client);
            }

            return bufferSize;
        };

        const auto clients = pDcvm->cloudDiskManager.GetClients(pCtxt);

        *pAmountClients = clients.size();

        if (0 == *pAmountClients)
        {
            *ppClients = nullptr;
            return DCVM_ERR_SUCCESS;
        }

        *ppClients = static_cast<dcvm_char_t*>(dcvm::base::SystemApi::MemoryAllocate(
            CalculateBufferSizeForClientsList(clients), DCVM_TRUE
        ));

        if (nullptr == *ppClients)
        {
            DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES);
            return DCVM_ERR_INSUFFICIENT_RESOURCES;
        }

        //There is not any out of range checking because of pBuffer has enougth size to contain all clients ids.
        dcvm_size_t index = 0;

        for (const auto &client : clients)
        {
            dcvm::base::SystemApi::MemoryCopy(*ppClients + index, client.length() * sizeof(dcvm_char_t), client.c_str(), client.length() * sizeof(dcvm_char_t));
            index += client.length() + sizeof(dcvm_char_t);
        }

        return DCVM_ERR_SUCCESS;
    }

    
    DCVM_ERROR dcvm_ControlGetUnauthorizedClients(DCVM *pDcvm, DCVMClientOAuthUri **ppClients, dcvm_size_t *pAmountClients, struct DCVMContext *pCtxt) noexcept
    {
        if ((nullptr == pDcvm) || (nullptr == ppClients) || (nullptr == pAmountClients))
        {
            DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
            return DCVM_ERR_BAD_PARAMS;
        }

        using Clients = dcvm::base::DCVMVector_t<dcvm::base::DCVMPair_t<dcvm::base::DCVMString_t, dcvm::base::DCVMString_t>>;

        Clients clients;
        DCVM_ERROR err = pDcvm->cloudDiskManager.GetUnauthorizedClients(clients, pCtxt);
        if (DCVM_FAILED(err))
        {
            DCVM_ERROR_TRACE(err);
            return err;
        }

        *pAmountClients = clients.size();

        if (0 == *pAmountClients)
        {
            *ppClients = nullptr;
            return DCVM_ERR_SUCCESS;
        }

        *ppClients = static_cast<DCVMClientOAuthUri*>(dcvm::base::SystemApi::MemoryAllocate(sizeof(DCVMClientOAuthUri) * clients.size(), DCVM_TRUE));
        if (nullptr == *ppClients)
        {
            DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES);
            return DCVM_ERR_INSUFFICIENT_RESOURCES;
        }

        for (Clients::size_type i = 0; i < clients.size(); i++)
        {
            ppClients[i]->pClientId = dcvm::CopyDCVMString(clients[i].first);
            ppClients[i]->pUri = dcvm::CopyDCVMString(clients[i].second);
        }

        return DCVM_ERR_SUCCESS;
    }

    DCVM_ERROR dcvm_ControlAuthorizeClient(DCVM *pDcvm, const DCVMClientOAuthCode *pOAuthCode, struct DCVMContext *pCtxt)
    {
        if (
            (nullptr == pDcvm) 
            || (nullptr == pOAuthCode) 
            || (nullptr == pOAuthCode->pClientId) 
            || (nullptr == pOAuthCode->pOAuthCode)
        )
        {
            DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
            return DCVM_ERR_BAD_PARAMS;
        }

        return pDcvm->cloudDiskManager.AuthorizeClient(pOAuthCode->pClientId, pOAuthCode->pOAuthCode, pCtxt);
    }

    DCVM_ERROR dcvm_InitCloudDisk(
        struct DCVM             *pDcvm
        , const dcvm_char_t     *pClientId
        , const dcvm_uint64_t   flags
        , struct DCVMCloudDisk  **ppCloudDisk
        , struct DCVMContext    *pCtxt
    )
    {
        if ((nullptr == pDcvm) || (nullptr == pClientId) || (nullptr == ppCloudDisk))
        {
            DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
            return DCVM_ERR_BAD_PARAMS;
        }

        dcvm::clouddisk::objects::CloudDiskDirectory *pRootDir = nullptr;
        dcvm::clouddisk::ICloudDisk *pCloudDisk = nullptr;

        DCVM_ERROR err = pDcvm->cloudDiskManager.InitCloudDisk(pClientId, flags, pRootDir, pCloudDisk, pCtxt);
        if (DCVM_FAILED(err))
        {
            return err;
        }

        *ppCloudDisk = new DCVMCloudDisk();
        if (nullptr == *ppCloudDisk)
        {
            DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES);

            pRootDir->DecReff(pCtxt);
            pCloudDisk->Unmount(pCtxt);

            return DCVM_ERR_INSUFFICIENT_RESOURCES;
        }

        (*ppCloudDisk)->pCloudDisk = pCloudDisk;
        (*ppCloudDisk)->pRootDir = pRootDir;

        return DCVM_ERR_SUCCESS;
    }

    DCVM_ERROR dcvm_InitLogicalCloudDisk(
        struct DCVM                 *pDcvm
        , const dcvm_char_t* const  *ppClientIds
        , const dcvm_size_t         amountClients
        , const dcvm_size_t         flags
        , DCVMCloudDisk             **ppCloudDisk
        , struct DCVMContext        *pCtxt
    )
    {
        if ((nullptr == pDcvm) || ((nullptr == ppClientIds) && (0 != amountClients)) || (nullptr == ppCloudDisk))
        {
            DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
            return DCVM_ERR_BAD_PARAMS;
        }

        if (0 == amountClients)
        {
            *ppCloudDisk = nullptr;
            return DCVM_ERR_SUCCESS;
        }

        dcvm::clouddisk::objects::CloudDiskDirectory *pRootDir = nullptr;
        dcvm::clouddisk::ICloudDisk *pCloudDisk = nullptr;

        dcvm::base::DCVMVector_t<dcvm::base::DCVMString_t> clients;
        for (int i = 0; i < amountClients; i++)
        {
            clients.push_back(ppClientIds[i]);
        }

        DCVM_ERROR err = pDcvm->cloudDiskManager.InitCloudDisk(clients, flags, pRootDir, pCloudDisk, pCtxt);
        if (DCVM_FAILED(err))
        {
            return err;
        }

        *ppCloudDisk = new DCVMCloudDisk();
        if (nullptr == *ppCloudDisk)
        {
            DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES);

            pRootDir->DecReff(pCtxt);
            pCloudDisk->Unmount(pCtxt);

            return DCVM_ERR_INSUFFICIENT_RESOURCES;
        }

        (*ppCloudDisk)->pCloudDisk = pCloudDisk;
        (*ppCloudDisk)->pRootDir = pRootDir;

        return DCVM_ERR_SUCCESS;
    }

    DCVM_ERROR dcvm_ControlReleaseCloudDisk(struct DCVM *pDcvm, struct DCVMCloudDisk *pCloudDisk, struct DCVMContext *pCtxt)
    {
        if ((nullptr == pDcvm) || (nullptr == pCloudDisk))
        {
            DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
            return DCVM_ERR_BAD_PARAMS;
        }

        auto cnt = pCloudDisk->pRootDir->DecReff(pCtxt);
        if (cnt > 1)
        {
            DCVM_INFO_TRACE("Refference counter of the root directory is gteater than 1. Possible, close operation has not been called.");
        }

        DCVM_ERROR err = pCloudDisk->pCloudDisk->Unmount(pCtxt);
        if (DCVM_FAILED(err))
        {
            return err;
        }

        cnt = pCloudDisk->pCloudDisk->DecReff(pCtxt);
        if (cnt > 1)
        {
            DCVM_INFO_TRACE("Refference counter of the cloud disk instance is gteater than 1. Possible, DecReff operation has not been called.");
        }

        pCloudDisk->pRootDir = nullptr;
        pCloudDisk->pCloudDisk = nullptr;

        return DCVM_ERR_SUCCESS;
    }

    void dcvm_ReleaseString(dcvm_char_t *pStr) noexcept
    {
        if (nullptr == pStr)
        {
            return;
        }

        dcvm::base::SystemApi::MemoryFree(pStr);
    }

    void dcvm_ReleaseDCVMClientOAuthUriArray(DCVMClientOAuthUri *pClients, const dcvm_size_t size) noexcept
    {
        if (nullptr == pClients)
        {
            return;
        }

        for (dcvm_size_t i = 0; i < size; i++)
        {
            dcvm::base::SystemApi::MemoryFree(pClients[i].pClientId);
            dcvm::base::SystemApi::MemoryFree(pClients[i].pUri);
        }

        dcvm::base::SystemApi::MemoryFree(pClients);
    }
}