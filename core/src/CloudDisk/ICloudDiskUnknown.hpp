#ifndef DCVM_CORE_CLOUDDISK_ICLOUDDISKUNKNOWN_HPP_
#define DCVM_CORE_CLOUDDISK_ICLOUDDISKUNKNOWN_HPP_

#include <dcvm_types.hpp>

namespace dcvm {
namespace clouddisk {

enum class CloudDiskInterface : unsigned char
{
    ICloudDiskBase
    , ICloudDisk
    , ICloudDiskControl
    
};

struct ICloudDiskUnknonw
{
    virtual 
};

} // namespace clouddisk
} // namespace dcvm

#endif