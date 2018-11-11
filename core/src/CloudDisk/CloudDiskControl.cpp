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
    , std::shared_ptr<ICloudDisk>   pParentDisk
    , std::shared_ptr<ICloudDisk>   &pDisk
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
        if (pParentDisk)
        {
            pDisk.reset(new(std::nothrow) compositedisk::CompositeDisk);
            if (nullptr == pDisk)
            {
                DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES);
                return DCVM_ERR_INSUFFICIENT_RESOURCES;
            }

            pDisk->AddDisk(pParentDisk);
        }
        else
        {
            
        }


    }
    catch (std::exception&)
    {
        DCVM_ERROR_TRACE(DCVM_ERR_INTERNAL);
        return DCVM_ERR_INTERNAL;
    }
}

} // namespace clouddisk
} // namespace dcvm
