#ifndef DCVM_DCVM_CPP_HPP_
#define DCVM_DCVM_CPP_HPP_

#include <dcvm/DCVMError.h>
#include "../DCVMTypes.hpp"

namespace dcvm_cpp {

struct DCVMCloudDiskInfo final
{
    DCVMCloudProviderInfo providerInfo;
    DCVMUserInfo userInfo;
    dcvm_uint64_t maxFileSize;
    dcvm_uint64_t totalSpace;
    dcvm_uint64_t usedSpace;
    std::vector<DCVMCloudDiskInfo> children;
};

class DCVMWrapper final
{
public:
    /*!
     * @brief Constructor. Intialize a DCVM library.
    */
    DCVMWrapper() noexcept;
    
    /*!
     * @brief Destructor.
    */
    ~DCVMWrapper() noexcept;
    
    DCVM_ERROR ControlGetAuthorzationUri(const DCVMStringView_t &providerId, DCVMString_t &uri) const noexcept;

    DCVM_ERROR ControlCreateCloudDisk(
        const DCVMStringView_t      &providerId
        , const DCVMStringView_t    &oauthCode
        , dcvm_size_t               &cloudDiskId
    ) const noexcept;

    DCVM_ERROR ControlGetCloudDiskInformation(const dcvm_size_t cloudDiskId, DCVMCloudDiskInfo &info) const noexcept;
private:
    struct Impl;
    std::unique_ptr<Impl> m_pImpl;
};

} // namespace dcvm

#endif