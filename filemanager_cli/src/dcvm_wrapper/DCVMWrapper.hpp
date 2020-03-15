#ifndef DCVM_DCVM_CPP_HPP_
#define DCVM_DCVM_CPP_HPP_

#include <dcvm/DCVMError.h>
#include <dcvm/cpp/base/DCVMTypes.hpp>
#include <dcvm/DCVMCloudProviderAPI.h>

namespace dcvm_filemanager_cli {

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

    DCVM_ERROR ControlGetListOfCloudProviders(dcvm::base::DCVMVector_t<dcvm::base::DCVMString_t> &providersIds) const noexcept;
    
    DCVM_ERROR ControlGetAuthorzationUri(const dcvm::base::DCVMStringView_t &providerId, dcvm::base::DCVMString_t &uri) const noexcept;

    DCVM_ERROR ControlCreateCloudDisk(
        const dcvm::base::DCVMStringView_t      &providerId
        , const dcvm::base::DCVMStringView_t    &oauthCode
        , dcvm_size_t                           &cloudDiskId
    ) const noexcept;

    DCVM_ERROR ControlGetListOfCloudDiskIds(dcvm::base::DCVMVector_t<dcvm_size_t> &ids) const noexcept;

    DCVM_ERROR ControlGetCloudDiskInformation(const dcvm_size_t cloudDiskId, DCVMCloudDiskInfo &info) const noexcept;
private:
    struct Impl;
    dcvm::base::DCVMUniquePtr_t<Impl> m_pImpl;
};

} // namespace dcvm

#endif