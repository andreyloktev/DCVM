// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


#include <dcvm/dcvm.h>
#include <dcvm/DCVMLogger.h>
#include "base/DCVMTypes.hpp"
#include "base/MemoryBase.hpp"
#include "base/SystemApi.hpp"
#include "CloudDiskManager/CloudDiskManager.hpp"

namespace dcvm {

DCVMSystemAPI g_systemApi = {};
using CloudDiskManager_t = dcvm::clouddiskmanager::CloudDiskManager;

namespace
{

template <class T>
inline dcvm_size_t SIZE_OF_DCVMSTRING(const T &str) noexcept
{
    return sizeof(dcvm_char_t) * str.length() + sizeof(dcvm_char_t);
}

dcvm_char_t* CopyDCVMString(const base::DCVMStringView_t &str) noexcept
{
    const auto STR_SIZE = SIZE_OF_DCVMSTRING(str);

    dcvm_char_t *pStr = static_cast<dcvm_char_t*>(base::SystemApi::MemoryAllocate(STR_SIZE, DCVM_TRUE));
    if (nullptr == pStr)
    {
        return pStr;
    }

    base::SystemApi::MemoryCopy(pStr, STR_SIZE, str.data(), STR_SIZE - sizeof(dcvm_char_t));

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

DCVMPrintError  g_DCVMPrintError = nullptr;
DCVMPrintInfo   g_DCVMPrintInfo = nullptr;

extern "C"
{
    void dcvm_InitLogger(DCVMPrintError pErrLogger, DCVMPrintInfo pInfoLogger)
    {
        g_DCVMPrintError = pErrLogger;
        g_DCVMPrintInfo = pInfoLogger;
    }

    DCVM_ERROR dcvm_Init(DCVMSystemAPI systemApi, DCVM **ppDcvm, struct DCVMContext *pCtxt)
    {
        UNREFFERENCE_VARIABLE(pCtxt);

        if (nullptr == ppDcvm)
        {
            DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
            return DCVM_ERR_BAD_PARAMS;
        }

        dcvm::g_systemApi = systemApi;

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

    DCVM_ERROR dcvm_ControlAddCloudProvider(struct DCVM *pDcvm, const DCVMCloudProviderAPI provider, dcvm_char_t **ppProviderId, struct DCVMContext *pCtxt)
    {
        if (nullptr == pDcvm)
        {
            DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
            return DCVM_ERR_BAD_PARAMS;
        }

        dcvm::base::DCVMStringView_t providerId;
        DCVM_ERROR err = pDcvm->cloudDiskManager.AddCloudProvider(provider, providerId, pCtxt);
        if (DCVM_FAILED(err))
        {
            DCVM_ERROR_TRACE(err);
            return err;
        }

        if (nullptr != ppProviderId)
        {
            *ppProviderId = dcvm::CopyDCVMString(providerId);
            if (nullptr == *ppProviderId)
            {
                DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES);
                return DCVM_ERR_INSUFFICIENT_RESOURCES;
            }
        }

        return DCVM_ERR_SUCCESS;
    }

    DCVM_ERROR dcvm_ControlGetCloudProviders(struct DCVM *pDcvm, dcvm_char_t **ppProvidersIds, dcvm_size_t *pSize, struct DCVMContext *pCtxt)
    {
        if ((nullptr == pDcvm) || (nullptr == ppProvidersIds) || (nullptr == pSize))
        {
            DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
            return DCVM_ERR_BAD_PARAMS;
        }

        // Copy clients.

        auto CalculateBufferSizeForClientsList = [](const dcvm::base::DCVMVector_t<dcvm::base::DCVMStringView_t> &providers) noexcept
        {
            dcvm_size_t bufferSize = 0;

            for (const auto &provider : providers)
            {
                bufferSize += dcvm::SIZE_OF_DCVMSTRING(provider);
            }

            return bufferSize;
        };

        const auto providers = pDcvm->cloudDiskManager.GetCloudProviders(pCtxt);
        if (providers.empty())
        {
            *ppProvidersIds = nullptr;
            *pSize = 0;
            return DCVM_ERR_SUCCESS;
        }

        const auto BUFFER_SIZE = CalculateBufferSizeForClientsList(providers);

        auto *pBuffer = static_cast<dcvm_char_t*>(dcvm::base::SystemApi::MemoryAllocate(BUFFER_SIZE, DCVM_TRUE));

        if (nullptr == pBuffer)
        {
            DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES);
            return DCVM_ERR_INSUFFICIENT_RESOURCES;
        }

        //There is not any out of range checking because of pBuffer has enougth size to contain all clients ids.
        dcvm_size_t index = 0;

        for (const auto &provider : providers)
        {
            dcvm::base::SystemApi::MemoryCopy(pBuffer + index, provider.length() * sizeof(dcvm_char_t), provider.data(), provider.length() * sizeof(dcvm_char_t));
            index += provider.length() + sizeof(dcvm_char_t);
        }

        *ppProvidersIds = pBuffer;
        *pSize = BUFFER_SIZE;

        return DCVM_ERR_SUCCESS;
    }

    DCVM_ERROR dcvm_ControlGetAuthorzationUri(struct DCVM *pDcvm, const dcvm_char_t *pProviderId, dcvm_char_t **ppUri, struct DCVMContext *pCtxt)
    {
        if ((nullptr == pDcvm) || (nullptr == pProviderId) || (nullptr == ppUri))
        {
            DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
            return DCVM_ERR_BAD_PARAMS;
        }

        dcvm::base::DCVMString_t uri;
        auto err = pDcvm->cloudDiskManager.GetAuthorizationUri(pProviderId, uri, pCtxt);
        if (DCVM_FAILED(err))
        {
            DCVM_ERROR_TRACE(err);
            return err;
        }

        *ppUri = dcvm::CopyDCVMString(uri.c_str());
        if (nullptr == *ppUri)
        {
            DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES);
            return DCVM_ERR_INSUFFICIENT_RESOURCES;
        }

        return DCVM_ERR_SUCCESS;
    }

    DCVM_ERROR dcvm_ControlCreateCloudDisk(DCVM *pDcvm, const DCVMClientOAuthCode *pOAuthCode, dcvm_size_t *pCloudDiskId, struct DCVMContext *pCtxt)
    {
        if (
            (nullptr == pDcvm) 
            || (nullptr == pOAuthCode) 
            || (nullptr == pOAuthCode->pProviderId) 
            || (nullptr == pOAuthCode->pOAuthCode)
            || (nullptr == pCloudDiskId)
        )
        {
            DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
            return DCVM_ERR_BAD_PARAMS;
        }

        return pDcvm->cloudDiskManager.CreateCloudDisk(pOAuthCode->pProviderId, pOAuthCode->pOAuthCode, *pCloudDiskId, pCtxt);
    }

    DCVM_ERROR dcvm_ControlGetCloudDisks(struct DCVM *pDcvm, dcvm_size_t **ppCloudDisksIds, dcvm_size_t *pAmountCloudDisksIds, struct DCVMContext *pCtxt)
    {
        if ((nullptr == pDcvm) || (nullptr == ppCloudDisksIds) || (nullptr == pAmountCloudDisksIds))
        {
            DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
            return DCVM_ERR_BAD_PARAMS;
        }

        const auto ids = pDcvm->cloudDiskManager.GetCloudDisks(pCtxt);
        if (ids.empty())
        {
            *ppCloudDisksIds = nullptr;
            *pAmountCloudDisksIds = 0;
            return DCVM_ERR_SUCCESS;
        }

        const dcvm_size_t BUFFER_SIZE = ids.size() * sizeof(dcvm_size_t);
        dcvm_size_t *pBuffer = static_cast<dcvm_size_t*>(dcvm::base::SystemApi::MemoryAllocate(BUFFER_SIZE, DCVM_TRUE));
        if (nullptr == pBuffer)
        {
            DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES);
            return DCVM_ERR_INSUFFICIENT_RESOURCES;
        }

        dcvm::base::SystemApi::MemoryCopy(pBuffer, BUFFER_SIZE, &ids[0], BUFFER_SIZE);

        *ppCloudDisksIds = pBuffer;
        *pAmountCloudDisksIds = ids.size();

        return DCVM_ERR_SUCCESS;
    }

    DCVM_ERROR dcvm_ControlGetCloudDiskInformation(struct DCVM *pDcvm, const dcvm_size_t id, DCVMCloudDiskInfo *pInfo, dcvm_size_t *pSize, struct DCVMContext *pCtxt) 
    {
        if ((nullptr == pDcvm) || (nullptr == pSize))
        {
            DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
            return DCVM_ERR_BAD_PARAMS;
        }

        return pDcvm->cloudDiskManager.GetCloudDiskInformation(id, pInfo, *pSize, pCtxt);
    }

    DCVM_ERROR dcvm_ControlInitCloudDisk(
        struct DCVM             *pDcvm
        , const dcvm_size_t     cloudDiskId
        , const dcvm_uint64_t   flags
        , struct DCVMCloudDisk  **ppCloudDisk
        , struct DCVMContext    *pCtxt
    )
    {
        if ((nullptr == pDcvm) || (nullptr == ppCloudDisk))
        {
            DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
            return DCVM_ERR_BAD_PARAMS;
        }

        dcvm::clouddisk::objects::CloudDiskDirectory *pRootDir = nullptr;
        dcvm::clouddisk::ICloudDisk *pCloudDisk = nullptr;

        DCVM_ERROR err = pDcvm->cloudDiskManager.InitCloudDisk(cloudDiskId, flags, pRootDir, pCloudDisk, pCtxt);
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
            pCloudDisk->DecReff(pCtxt);

            return DCVM_ERR_INSUFFICIENT_RESOURCES;
        }

        (*ppCloudDisk)->pCloudDisk = pCloudDisk;
        (*ppCloudDisk)->pRootDir = pRootDir;

        return DCVM_ERR_SUCCESS;
    }

    DCVM_ERROR dcvm_ControlInitLogicalCloudDisk(
        struct DCVM                 *pDcvm
        , const dcvm_size_t* const  pCloudDisksIds
        , const dcvm_size_t         amountCloudDisksIds
        , const dcvm_size_t         flags
        , struct DCVMCloudDisk      **ppCloudDisk
        , struct DCVMContext        *pCtxt
    )
    {
        if ((nullptr == pDcvm) || ((nullptr == pCloudDisksIds) && (0 != amountCloudDisksIds)) || (nullptr == ppCloudDisk))
        {
            DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
            return DCVM_ERR_BAD_PARAMS;
        }

        if (0 == amountCloudDisksIds)
        {
            *ppCloudDisk = nullptr;
            return DCVM_ERR_SUCCESS;
        }

        dcvm::clouddisk::objects::CloudDiskDirectory *pRootDir = nullptr;
        dcvm::clouddisk::ICloudDisk *pCloudDisk = nullptr;

        dcvm::base::DCVMVector_t<dcvm_size_t> cloudDisksIds;
        for (int i = 0; i < amountCloudDisksIds; i++)
        {
            cloudDisksIds.push_back(pCloudDisksIds[i]);
        }

        DCVM_ERROR err = pDcvm->cloudDiskManager.InitCloudDisk(cloudDisksIds, flags, pRootDir, pCloudDisk, pCtxt);
        if (DCVM_FAILED(err))
        {
            DCVM_ERROR_TRACE(err);
            return err;
        }

        *ppCloudDisk = new DCVMCloudDisk();
        if (nullptr == *ppCloudDisk)
        {
            DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES);

            pRootDir->DecReff(pCtxt);
            pCloudDisk->Unmount(pCtxt);
            pCloudDisk->DecReff(pCtxt);

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

        DCVM_ERROR err = pCloudDisk->pCloudDisk->Unmount(pCtxt);
        if (DCVM_FAILED(err))
        {
            DCVM_INFO_TRACE("Unmount error code is 0x%x.", err);
        }

        auto cnt = pCloudDisk->pCloudDisk->DecReff(pCtxt);
        if (cnt > 1)
        {
            DCVM_INFO_TRACE("Refference counter of the cloud disk instance is gteater than 1. Possible, DecReff operation has not been called.");
        }

        pCloudDisk->pRootDir = nullptr;
        pCloudDisk->pCloudDisk = nullptr;

        return DCVM_ERR_SUCCESS;
    }

    void dcvm_ReleaseBuffer(void *pBuffer)
    {
        if (nullptr == pBuffer)
        {
            return;
        }

        dcvm::base::SystemApi::MemoryFree(pBuffer);
    }
}