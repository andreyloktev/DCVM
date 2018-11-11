#ifndef DCVM_CORE_CLOUDDSIK_ICLOUDDISK_HPP_
#define DCVM_CORE_CLOUDDSIK_ICLOUDDISK_HPP_

#include <dcvm/DCVMError.h>
#include <dcvm_types.hpp>

namespace dcvm {
namespace clouddisk {

/*!
 * @class ICloudDisk is interface which lets to work with one or several cloud disk.
*/
struct ICloudDisk
{
    /*!
     * Add disk to cloud disk set. This method is only actual for CompositeDisk.
     * @param [in] pDisk disk to add.
    */
    virtual void AddDisk(const std::shared_ptr<ICloudDisk> &pDisk) noexcept = 0;
};

} // namespace clouddisk
} // namesapce dcvm

#endif