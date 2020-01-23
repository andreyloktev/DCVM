#ifndef DCVM_CORE_CLOUDDSIKMANAGER_CLOUDDISKMANAGER_HPP_
#define DCVM_CORE_CLOUDDSIKMANAGER_CLOUDDISKMANAGER_HPP_

#include <dcvm/DCVMError.h>
#include <dcvm/DCVMCloudProviderAPI.h>
#include "../base/DCVMTypes.hpp"
#include "../base/MemoryBase.hpp"
#include "../base/CloudProvider.hpp"
#include "../CloudDisk/ICloudDisk.hpp"

namespace dcvm              {
namespace clouddiskmanager  {

/*!
 * @class CloudDiskManager.
 * @brief CloudDiskManager is responsible for managing cloud disk clients.
*/
class CloudDiskManager final : public base::MemoryBase
{
public:
    CloudDiskManager() noexcept;
    ~CloudDiskManager() noexcept;
    CloudDiskManager(const CloudDiskManager&) = delete;
    CloudDiskManager& operator=(const CloudDiskManager&) = delete;
public:
    /*!
     * @brief Add a provider.
     * @param [in] provider cloud disk clent.
     * @param [in] pCtxt system context(optional).
     * @return provider id.
    */
    DCVM_ERROR AddCloudProvider(
        DCVMCloudProviderAPI        provider
        , base::DCVMStringView_t    &providerId
        , struct DCVMContext        *pCtxt
    ) noexcept;

    /*!
     * Get list of cloud providers.
     * @param [in] pCtxt system context(optional).
     * @return list of provider ids.
    */
   base::DCVMVector_t<base::DCVMStringView_t> GetCloudProviders(struct DCVMContext *pCtxt) const noexcept;

    /*!
     * Get authorization uri.
     * @param [in] providerId provder id.
     * @param [out] uri authorization uri.
     * @param [in] pCtxt system context(optional).
     * @return error code.
    */
    DCVM_ERROR GetAuthorizationUri(
        const base::DCVMStringView_t  &providerId
        , base::DCVMString_t        &uri
        , struct DCVMContext        *pCtxt
    ) const noexcept;

    /*!
     * Create a cloud disk.
     * @param [in] providerId provider unique identifier.
     * @param [in] oauthCode authentication code.
     * @param [out] cloudDiskId id of created cloud disk.
     * @param [in] pCtxt system context(optional).
     * @return error code.
    */
    DCVM_ERROR CreateCloudDisk(
        const base::DCVMStringView_t    &providerId
        , const base::DCVMStringView_t  &oauthCode
        , dcvm_size_t                   &cloudDiskId
        , struct DCVMContext            *pCtxt
    ) noexcept;

    /*!
     * Get all cloud disks.
     * @param [in] pCtxt system context(optional).
     * @return list of all cloud disk ids.
    */
    base::DCVMVector_t<dcvm_size_t> GetCloudDisks(struct DCVMContext *pCtxt) const noexcept;

    /*!
     * Get a cloud disk information by its id.
     * @param [in] id cloud disk id.
     * @param [in, out] pCloudDiskInfo pointer to the buffer that recieve information about the cloud disk.
     * @param [in, out] size size of pCloudDiskInfo buffer. If pCloudDiskInfo is nullptr then size recieves necessary size of pCloudDiskInfo buffer.
     * @param [in] pCtxt system context(optional).
     * @return error code.
    */
    DCVM_ERROR GetCloudDiskInformation(
        const dcvm_size_t       id
        , DCVMCloudDiskInfo     *pCloudDiskInfo
        , dcvm_size_t           &size
        , struct DCVMContext    *pCtxt
    ) const noexcept;

    /*!
     * Create a cloud disk instance.
     * @param [in] cloudDiskId cloud disk id.
     * @param [in] flags initialization flags.
     * @param [out] pRootDir pointer to root directory.
     * @param [out] pCloudDisk cloud disk instance
     * @param [in] pCtxt system context(optional).
     * @return error code.
    */
   DCVM_ERROR InitCloudDisk(
       const dcvm_size_t                            cloudDiskId
       , const dcvm_uint64_t                        flags
       , clouddisk::objects::CloudDiskDirectory*    &pRootDir
       , clouddisk::ICloudDisk*                     &pCloudDisk
       , struct DCVMContext                         *pCtxt
   ) const noexcept;

   /*!
     * Create a cloud disk instance.
     * Created a cloud disk instance works with several DCVMCloudDiskProviderAPI clients -- represent all clients in one.
     * @param [in] cloudDisksIds list of cloud disks ids.
     * @param [out] pRootDir pointer to root directory.
     * @param [out] pCloudDisk cloud disk instance.
     * @param [in] pCtxt system context(optional).
     * @return error code.
    */
   DCVM_ERROR InitCloudDisk(
       const base::DCVMVector_t<dcvm_size_t>        &cloudDisksIds
       , const dcvm_uint64_t                        flags
       , clouddisk::objects::CloudDiskDirectory*    &pRootDir
       , clouddisk::ICloudDisk*                     &pCloudDisk
       , struct DCVMContext                         *pCtxt
   ) const noexcept;

private:
    using ICloudDisk_t = clouddisk::ICloudDisk;
    using DCVMCloudDisksPool = base::DCVMUnorderedMap_t<dcvm_size_t, ICloudDisk_t*>;
    using DCVMCloudDiskProvidersPool = base::DCVMUnorderedMap_t<base::DCVMStringView_t, base::CloudProvider>;
private:
    DCVMCloudDisksPool m_cloudDisks;
    DCVMCloudDiskProvidersPool m_providers;
};

} // namespace clouddiskmanager
} // namespace dcvm

#endif