#include <dcvm/DCVMLogger.h>
#include "CloudDiskControl.hpp"

#include "CompositeDisk/CompositeDisk.hpp"
#include "Yandex/YandexDisk.hpp"

namespace dcvm {
namespace clouddisk{

DCVMString_t CloudDiskControl::GetOAuthUrlToLogIn(const DCVMCloudDiskType type) noexcept
{
    switch (type)
    {
    case DCVMCloudDiskType::AmazonCloudDrive:
        return DCVMStr("");
    case DCVMCloudDiskType::DropBoxDrive:
        return DCVMStr("");
    case DCVMCloudDiskType::GoogleDrive:
        return DCVMStr("");
    case DCVMCloudDiskType::OneDrive:
        return DCVMStr("");
    case DCVMCloudDiskType::YandexDisk:
        return yandex::YandexDisk::GetOAuthUrlToLogIn();
    }

    return DCVMStr("");
}

DCVMError CloudDiskControl::LogIn(
    const DCVMCloudDiskType         type
    , const DCVMString_t            &authorizationCode
    , ICloudDisk                    *pRightHandDisk
    , ICloudDisk*                   &pDisk
) noexcept
{
    if (authorizationCode.empty())
    {
        DCVM_INFO_TRACE("Authorization code can not be empty");
        DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
        return DCVM_ERR_BAD_PARAMS;
    }

    try
    {
        switch (type)
        {
        case DCVMCloudDiskType::AmazonCloudDrive:
        {
            return DCVM_ERR_NOT_IMPLEMENTED;
        }
        case DCVMCloudDiskType::DropBoxDrive:
        {
            return DCVM_ERR_NOT_IMPLEMENTED;
        }
        case DCVMCloudDiskType::GoogleDrive:
        {
            return DCVM_ERR_NOT_IMPLEMENTED;
        }
        case DCVMCloudDiskType::OneDrive:
        {
            return DCVM_ERR_NOT_IMPLEMENTED;
        }
        case DCVMCloudDiskType::YandexDisk:
        {
            pDisk = new(std::nothrow) yandex::YandexDisk;
            break;
        }
        }
        
        if (nullptr == pDisk)
        {
            DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES, DCVMErrorToString(DCVM_ERR_INSUFFICIENT_RESOURCES));
            return DCVM_ERR_INSUFFICIENT_RESOURCES;
        }

        DCVMError err = pDisk->LogIn(authorizationCode);
        if (DCVM_FAILED(err))
        {
            DCVM_ERROR_TRACE(err, DCVMErrorToString(err));
            return err;
        }

        if (pRightHandDisk)
        {
            compositedisk::CompositeDisk *pCompositeDisk = new(std::nothrow) compositedisk::CompositeDisk;
            if (nullptr == pDisk)
            {
                pDisk->Release();
                DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES);
                return DCVM_ERR_INSUFFICIENT_RESOURCES;
            }

            pCompositeDisk->AddDisk(pDisk);
            pCompositeDisk->AddDisk(pRightHandDisk);
            pDisk = pCompositeDisk;
        }
    }
    catch (std::exception&)
    {
        DCVM_ERROR_TRACE(DCVM_ERR_INTERNAL);
        return DCVM_ERR_INTERNAL;
    }

    return DCVM_ERR_SUCCESS;
}

} // namespace clouddisk
} // namespace dcvm
