#ifndef DCVM_CORE_CLOUDDISK_COMPOSITEDISK_HPP_
#define DCVM_CORE_CLOUDDISK_COMPOSITEDISK_HPP_

#include "../ICloudDisk.hpp"
#include "../ICloudDiskControl.hpp"

namespace dcvm {
namespace clouddisk {
namespace compositedisk {

class CompositeDisk final : public ICloudDiskControl, public ICloudDisk
{
    std::vector<std::shared_ptr<ICloudDisk>> m_pDisks;
public:
    CompositeDisk() = default;
    CompositeDisk(const CompositeDisk&) = default;
    CompositeDisk& operator=(const CompositeDisk&) = default;

    DCVMError LogIn(const DCVMString_t &authorizationCode) noexcept override;
    void AddDisk(const std::shared_ptr<ICloudDisk> &pDisk) noexcept override;
};

} // namespace compositedisk
} // namespace clouddisk
} // namespace dcvm

#endif