#ifndef DCVM_CORE_CLOUDDISK_COMPOSITEDISK_HPP_
#define DCVM_CORE_CLOUDDISK_COMPOSITEDISK_HPP_

#include "../ICloudDisk.hpp"
#include "../ICloudDiskControl.hpp"

namespace dcvm {
namespace clouddisk {
namespace compositedisk {

class CompositeDisk final : public ICloudDiskControl, public ICloudDisk
{
    unsigned long m_reffCnt = 1;
    std::vector<ICloudDisk*> m_disks;
public:
    CompositeDisk() = default;
    CompositeDisk(const CompositeDisk&) = delete;
    CompositeDisk& operator=(const CompositeDisk&) = delete;
    ~CompositeDisk() noexcept;

    /*!
     * Add disk to cloud disk set. This method is only actual for CompositeDisk.
     * @param [in] pDisk disk to add.
    */
    void AddDisk(ICloudDisk *pDisk) noexcept;

    //ICloudDiskBase interface implementation.
    DCVMError QueryInterface(CloudDiskInterface type, void* &pInstance) noexcept override;
    unsigned long AddReff() noexcept override;
    unsigned long Release() noexcept override;

    DCVMError LogIn(const DCVMString_t &authorizationCode) noexcept override;
};

} // namespace compositedisk
} // namespace clouddisk
} // namespace dcvm

#endif