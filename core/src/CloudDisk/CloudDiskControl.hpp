#ifndef DCVM_CORE_CLOUDDISK_CLOUDDISK_HPP_
#define DCVM_CORE_CLOUDDISK_CLOUDDISK_HPP_

#include <dcvm/DCVMError.h>
#include <dcvm/DCVMCloudDiskType.h>
#include <dcvm_types.hpp>

#include "ICloudDisk.hpp"

namespace dcvm {
namespace clouddisk {

struct CloudDiskControl
{
    /*!
     * Get url to receive an authorization code (fabric method).
     * @param type cloud disk type to generate url.
     * @return url.
    */
    static DCVMString_t GetOAuthUrlToLogIn(const DCVMCloudDiskType type) noexcept;

    /*!
     * Get access and refresh tokens to cloud resource and return initialized cloud disk.
     * @param [in] type type of cloud disk to create.
     * @param [in] authorizationCode authorization code to get access and refresh tokens.
     * @param [in] pParentDisk if it is not null then created pDisk will be added to cloud disk set of parent disk (OPTIONAL).
     * @param [out] pDisk the new intialized cloud disk.
     * @return error code.
    */
    DCVMError LogIn(
        const DCVMCloudDiskType         type
        , const DCVMString_t            &authorizationCode
        , std::shared_ptr<ICloudDisk>   pParentDisk
        , std::shared_ptr<ICloudDisk>   &pDisk
    ) noexcept;
};

} // namespace clouddisk
} // namespace dcvm

#endif