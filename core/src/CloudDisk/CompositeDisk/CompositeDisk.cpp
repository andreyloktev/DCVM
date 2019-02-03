#include "CompositeDisk.hpp"
#include <dcvm/DCVMLogger.h>

namespace dcvm {
namespace clouddisk {
namespace compositedisk {

CompositeDisk::~CompositeDisk() noexcept
{
    for (ICloudDisk *pDisk : m_disks)
    {
        pDisk->Release();
    }
}

void CompositeDisk::AddDisk(ICloudDisk *pDisk) noexcept
{
    if (pDisk)
    {
        m_disks.push_back(pDisk);
    }
}

//ICloudDiskBase interface implementation.
DCVMError CompositeDisk::QueryInterface(CloudDiskInterface type, void* &pInstance) noexcept
{
    switch (type)
    {
    case CloudDiskInterface::ICloudDiskBase:
    {
        pInstance = static_cast<ICloudDisk*>(this);
        break;
    }

    case CloudDiskInterface::ICloudDisk:
    {
        pInstance = this;
        break;
    }

    case CloudDiskInterface::ICloudDiskControl:
    {
        pInstance = static_cast<ICloudDiskControl*>(this);
        break;
    }

    default:
    {
        DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS, DCVMErrorToString(DCVM_ERR_BAD_PARAMS));
        return DCVM_ERR_BAD_PARAMS;
    }
    }

    AddReff();
    return DCVM_ERR_SUCCESS;
}

unsigned long CompositeDisk::AddReff() noexcept
{
    return ++m_reffCnt;
}

unsigned long CompositeDisk::Release() noexcept
{
    if (--m_reffCnt)
    {
        delete this;
        return 0;
    }

    return m_reffCnt;
}

DCVMError LogIn(const DCVMString_t &authorizationCode) noexcept
{
    UNREFERENCED_PARAMETER(authorizationCode);
    return DCVM_ERR_SUCCESS;
}

} // namespace compositedisk
} // namespace clouddisk
} // namespace dcvm