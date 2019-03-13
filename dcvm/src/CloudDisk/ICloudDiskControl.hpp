#ifndef DCVM_CORE_CLOUDDISK_ICLOUDDISK_HPP_
#define DCVM_CORE_CLOUDDISK_ICLOUDDISK_HPP_

#include <dcvm/DCVMError.h>
#include <dcvm_types.hpp>
#include "ICloudDiskBase.hpp"
#include "ICloudDisk.hpp"

namespace dcvm {
namespace clouddisk {

/*!
 * @class ICloudDiskControl is interface describing control part of a cloud disk.
*/
struct ICloudDiskControl : public ICloudDiskBase
{
    /*!
     * Get access and refresh tokens to access to cloude storage.
     * @param [in] authorizationCode OAuth2 authorization code.
     * @retunr error code.
    */
    virtual DCVMError LogIn(const DCVMString_t &authorizationCode) noexcept = 0;
};


} // namespace clouddisk
} // namespace dcvm

#endif