#ifndef DCVM_CORE_CLOUDDISK_ICLOUDDISKUNKNOWN_HPP_
#define DCVM_CORE_CLOUDDISK_ICLOUDDISKUNKNOWN_HPP_

#include <dcvm/DCVMError.h>

namespace dcvm {
namespace clouddisk {

enum class CloudDiskInterface : unsigned char
{
    ICloudDiskBase
    , ICloudDisk
    , ICloudDiskControl
    
};

struct ICloudDiskBase
{
    virtual unsigned long AddReff() noexcept = 0;

    virtual unsigned long Release() noexcept = 0;

    virtual DCVMError QueryInterface(CloudDiskInterface iType, void* &pInstance) noexcept = 0;
};

} // namespace clouddisk
} // namespace dcvm

#endif