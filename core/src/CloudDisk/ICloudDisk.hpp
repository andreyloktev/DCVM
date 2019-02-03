#ifndef DCVM_CORE_CLOUDDSIK_ICLOUDDISK_HPP_
#define DCVM_CORE_CLOUDDSIK_ICLOUDDISK_HPP_

#include <dcvm/DCVMError.h>
#include <dcvm_types.hpp>
#include "ICloudDiskBase.hpp"

namespace dcvm {
namespace clouddisk {

/*!
 * @class ICloudDisk is interface which lets to work with one or several cloud disk.
*/
struct ICloudDisk : public ICloudDiskBase
{
};

} // namespace clouddisk
} // namesapce dcvm

#endif