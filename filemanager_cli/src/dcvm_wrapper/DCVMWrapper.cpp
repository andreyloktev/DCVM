#include "DCVMWrapper.hpp"
#include <dcvm/dcvm.h>

#ifdef WIN32
#include <system/dcvm_windows.h>
#endif

#include <functional>

namespace dcvm_filemanager_cli {

//TODO Add cloud provider implemntation
static constexpr DCVMCloudProviderAPI g_CloudProviderAPIs[] = { {} };

class DCVMStringBufferIterator final
{
public:
    static DCVMStringBufferIterator End() noexcept
    {
        return DCVMStringBufferIterator(nullptr, 0);
    }
public:
    DCVMStringBufferIterator(dcvm_char_t *pBuffer, dcvm_size_t bufSize) noexcept : m_pBuffer(pBuffer), m_bufSize(bufSize)
    {
    }

    DCVMStringBufferIterator& operator++() noexcept
    {
        if (0 == m_bufSize)
        {
            *this = End();
            return *this;
        }

        dcvm_size_t offset = SubStringLength() + 1;
        m_pBuffer += offset;
        m_bufSize -= offset;

        return *this;
    }

    DCVMStringBufferIterator operator++(int) noexcept
    {
        DCVMStringBufferIterator curIterator = *this;
        operator++();
        return curIterator;
    }

    bool operator==(const DCVMStringBufferIterator &rhs) noexcept
    {
        return (m_pBuffer == rhs.m_pBuffer) && (m_bufSize == rhs.m_bufSize);
    }

    bool operator!=(const DCVMStringBufferIterator &rhs) noexcept
    {
        return !(*this == rhs);
    }

    const dcvm_char_t* operator*() const noexcept
    {
        return m_pBuffer;
    }
private:
    dcvm_size_t SubStringLength() const noexcept
    {
        dcvm_size_t lenght = 0;
        while(m_pBuffer[lenght++]);
        
        return lenght;
    }
private:
    dcvm_size_t m_bufSize = 0;
    dcvm_char_t *m_pBuffer = nullptr;
};

struct DCVMDeleter final
{
    void operator()(DCVM *pDCVM) const noexcept
    {
        if (nullptr != pDCVM)
        {
            dcvm_Release(pDCVM, nullptr);
        }
    }
};

struct DCVMBufferDeleter final
{
    void operator()(void *pBuffer) const noexcept
    {
        if (nullptr != pBuffer)
        {
            dcvm_ReleaseBuffer(pBuffer);
        }
    }
};

struct DCVMWrapper::Impl final
{
    std::unique_ptr<DCVM, DCVMDeleter> m_pDCVM;

    Impl(DCVM *pDCVM)
    {
        m_pDCVM.reset(pDCVM);
    }

    DCVM* DCVM() const noexcept
    {
        return m_pDCVM.get();
    }
};

DCVMWrapper::DCVMWrapper() noexcept
{
    DCVMSystemAPI systemApi = 
    {
        sys_DCVMMemoryAlloc
        , sys_DCVMMemoryFree
        , sys_DCVMMemorySet
        , sys_DCVMMemoryCopy
        , sys_DCVMMemoryCompare
        , sys_DCVMSendHttpRequest
    };

    DCVM *pDCVM = nullptr;
    DCVM_ERROR err = dcvm_Init(systemApi, &pDCVM, nullptr);
    if (DCVM_FAILED(err))
    {
        DCVM_ERROR_TRACE(err);
        return;
    }

    m_pImpl.reset(new(std::nothrow) DCVMWrapper::Impl(pDCVM));
    if (nullptr == m_pImpl)
    {
        DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES);
        return;
    }

    for (dcvm_size_t i = 0; i < (sizeof(g_CloudProviderAPIs) / sizeof(DCVMCloudProviderAPI)); i++)
    {
        dcvm_ControlAddCloudProvider(m_pImpl->DCVM(), g_CloudProviderAPIs[i], nullptr, nullptr);
    }
}

DCVMWrapper::~DCVMWrapper() noexcept
{
}

DCVM_ERROR DCVMWrapper::ControlGetListOfCloudProviders(std::vector<DCVMString_t> &providersIds) const noexcept
{
    if (nullptr == m_pImpl)
    {
        DCVM_ERROR_TRACE(DCVM_ERR_NOT_INITIALIZED);
        return DCVM_ERR_NOT_INITIALIZED;
    }

    dcvm_char_t *pBuffer = nullptr;
    dcvm_size_t bufferSize = 0;
    
    auto err = dcvm_ControlGetCloudProviders(m_pImpl->DCVM(), &pBuffer, &bufferSize, nullptr);
    if (DCVM_FAILED(err))
    {
        return err;
    }

    try
    {
        std::unique_ptr<dcvm_char_t> pDcvmbuffer(pBuffer);

        DCVMStringBufferIterator dcvmBufIt(pDcvmbuffer.get(), bufferSize);
        for (; dcvmBufIt != DCVMStringBufferIterator::End(); dcvmBufIt++)
        {
            providersIds.emplace_back(*dcvmBufIt);
        }
    }
    catch (std::exception &e)
    {
        DCVM_INFO_TRACE(e.what());
        return DCVM_ERR_INTERNAL;
    }

    return DCVM_ERR_SUCCESS;
}

DCVM_ERROR DCVMWrapper::ControlGetAuthorzationUri(const DCVMStringView_t &providerId, DCVMString_t &uri) const noexcept
{
    if (nullptr == m_pImpl)
    {
        DCVM_ERROR_TRACE(DCVM_ERR_NOT_INITIALIZED);
        return DCVM_ERR_NOT_INITIALIZED;
    }

    if (providerId.empty())
    {
        DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
        return DCVM_ERR_BAD_PARAMS;
    }

    dcvm_char_t *pBuffer = nullptr;
    auto err = dcvm_ControlGetAuthorzationUri(m_pImpl->DCVM(), providerId.data(), &pBuffer, nullptr);
    if (DCVM_FAILED(err))
    {
        return err;
    }

    try
    {
        std::unique_ptr<dcvm_char_t> pUri(pBuffer);
        uri = pUri.get();
    }
    catch (std::exception &e)
    {
        DCVM_INFO_TRACE(e.what());
        return DCVM_ERR_INTERNAL;
    }

    return DCVM_ERR_SUCCESS;
}

DCVM_ERROR DCVMWrapper::ControlCreateCloudDisk(
    const DCVMStringView_t      &providerId
    , const DCVMStringView_t    &oauthCode
    , dcvm_size_t               &cloudDiskId
) const noexcept
{
    if (nullptr == m_pImpl)
    {
        DCVM_ERROR_TRACE(DCVM_ERR_NOT_INITIALIZED);
        return DCVM_ERR_NOT_INITIALIZED;
    }

    if (providerId.empty() || oauthCode.empty())
    {
        DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
        return DCVM_ERR_BAD_PARAMS;
    }

    DCVMClientOAuthCode clientOauthCode = 
    {
        providerId.data()
        , oauthCode.data()
    };

    return dcvm_ControlCreateCloudDisk(m_pImpl->DCVM(), &clientOauthCode, &cloudDiskId, nullptr);
}

DCVM_ERROR DCVMWrapper::ControlGetListOfCloudDiskIds(std::vector<dcvm_size_t> &ids) const noexcept
{
    if (nullptr == m_pImpl)
    {
        DCVM_ERROR_TRACE(DCVM_ERR_NOT_INITIALIZED);
        return DCVM_ERR_NOT_INITIALIZED;
    }

    dcvm_size_t *pBuf = nullptr;
    dcvm_size_t amountIds = 0;

    auto err = dcvm_ControlGetCloudDisks(m_pImpl->DCVM(), &pBuf, &amountIds, nullptr);
    if (DCVM_FAILED(err))
    {
        return err;
    }

    std::unique_ptr<dcvm_size_t, DCVMBufferDeleter> pIds(pBuf);

    try
    {
        ids = std::vector<dcvm_size_t>(pIds.get(), pIds.get() + amountIds);
    }
    catch (std::exception &e)
    {
        DCVM_INFO_TRACE(e.what());
        return DCVM_ERR_INTERNAL;
    }

    return err;
}

DCVM_ERROR DCVMWrapper::ControlGetCloudDiskInformation(const dcvm_size_t cloudDiskId, DCVMCloudDiskInfo &info) const noexcept
{
    if (nullptr == m_pImpl)
    {
        DCVM_ERROR_TRACE(DCVM_ERR_NOT_INITIALIZED);
        return DCVM_ERR_NOT_INITIALIZED;
    }

    dcvm_size_t diSize = 0;
    auto err = dcvm_ControlGetCloudDiskInformation(m_pImpl->DCVM(), cloudDiskId, nullptr, &diSize, nullptr);
    if (DCVM_FAILED(err))
    {
        return err;
    }

    std::unique_ptr<dcvm_uint8_t[]> pBuf(new(std::nothrow) dcvm_uint8_t[diSize]);
    if (nullptr == pBuf)
    {
        DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES);
        return DCVM_ERR_INSUFFICIENT_RESOURCES;
    }

    ::DCVMCloudDiskInfo *pDI = reinterpret_cast<::DCVMCloudDiskInfo*>(pBuf.get());

    err = dcvm_ControlGetCloudDiskInformation(m_pImpl->DCVM(), cloudDiskId, pDI, &diSize, nullptr);
    if (DCVM_FAILED(err))
    {
        return err;
    }

    std::function<void(const ::DCVMCloudDiskInfo* const, DCVMCloudDiskInfo&)> CopyDI;

    CopyDI = [=](const ::DCVMCloudDiskInfo * const pDiskInfo, DCVMCloudDiskInfo &out) noexcept
    {
        if (nullptr == pDiskInfo)
        {
            return;
        }

        if (0 != pDiskInfo->childrenCount)
        {
            for (dcvm_uint32_t i = 0; i < pDiskInfo->childrenCount; i++)
            {
                out.children.emplace_back(DCVMCloudDiskInfo());
                CopyDI(&pDI->pChildren[i], out.children.back());
            }
        }

        std::memcpy(out.providerInfo.id, pDiskInfo->providerInfo.id, sizeof(DCVMCloudProviderInfo::id));
        std::memcpy(out.userInfo.name, pDiskInfo->userInfo.name, sizeof(DCVMUserInfo::name));
        out.maxFileSize = pDiskInfo->maxFileSize;
        out.totalSpace = pDiskInfo->totalSpace;
        out.usedSpace = pDiskInfo->usedSpace;
    };

    CopyDI(pDI, info);

    return DCVM_ERR_SUCCESS;
}

} // namespace dcvm_cpp