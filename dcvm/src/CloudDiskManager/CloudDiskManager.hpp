#ifndef DCVM_CORE_CLOUDDSIKMANAGER_CLOUDDISKMANAGER_HPP_
#define DCVM_CORE_CLOUDDSIKMANAGER_CLOUDDISKMANAGER_HPP_

#include <dcvm/DCVMError.h>
#include <dcvm/DCVMCloudDiskAPI.h>
#include "../base/DCVMTypes.hpp"
#include "../base/MemoryBase.hpp"
#include "../CloudDisk/ICloudDisk.hpp"

namespace dcvm              {
namespace clouddiskmanager  {

/*!
 * @class CloudDiskManager.
 * @brief CloudDiskManager is responsible for managing cloud disk clients.
*/
template <class SystemApi>
class CloudDiskManager final : public base::MemoryBase<SystemApi>
{
    using ICloudDisk_t = clouddisk::ICloudDisk<SystemApi>;
    using DCVMCloudDisksPool = base::DCVMUnorderedMap_t<base::DCVMString_t, ICloudDisk_t>;
private:
    DCVMCloudDisksPool m_cloudDisdk;
public:
    CloudDiskManager() noexcept;
    ~CloudDiskManager() noexcept;
    CloudDiskManager(const CloudDiskManager&) = delete;
    CloudDiskManager& operator=(const CloudDiskManager&) = delete;
public:
    /*!
     * Add a client.
     * @param [in] client cloud disk clent.
     * @param [in] pCtxt system context(optional).
    */
    void AddClient(DCVMCloudDiskAPI client, struct DCVMContext *pCtxt) noexcept;

    /*!
     * Get all clients.
     * @param [in] pCtxt system context(optional).
     * @return list of all clients.
    */
    base::DCVMVector_t<base::DCVMString_t> GetClients(struct DCVMContext *pCtxt) const noexcept;

    /*!
     * Get all unauthorized clients.
     * @param [in] pCtxt system context(optional).
     * @return list <client id, OAuth url> of all unauthorized clients.
    */
    base::DCVMVector_t<base::DCVMPair_t<base::DCVMString_t, base::DCVMString_t>> GetUnauthorizedClients(
        struct DCVMContext *pCtxt
    ) const noexcept;

    /*!
     * Authorize a client.
     * @param [in] clientId client unique identifier.
     * @param [in] oauthCode authentication code.
     * @param [in] pCtxt system context(optional).
     * @return list <client id, OAuth url> of all unauthorized clients.
    */
    DCVM_ERROR AuthorizeClient(
        const base::DCVMString_t    &clientId
        , const base::DCVMString_t  &oauthCode
        , struct DCVMContext        *pCtxt
    ) noexcept;

    /*!
     * Create a cloud disk instance.
     * @param [in] clientId client id.
     * @param [out] pCloudDisk cloud disk instance
     * @param [in] pCtxt system context(optional).
     * @return error code.
    */
   DCVM_ERROR CreateCloudDisk(
       const base::DCVMString_t &clientId
       , clouddisk::ICloudDisk* &pCloudDisk
       , struct DCVMContext     *pCtxt
   ) const noexcept;

   /*!
     * Create a cloud disk instance.
     * Created a cloud disk instance works with several DCVMCloudDiskAPI clients -- represent all clients in one.
     * @param [in] clientIds list of client ids.
     * @param [out] pCloudDisk cloud disk instance.
     * @param [in] pCtxt system context(optional).
     * @return error code.
    */
   DCVM_ERROR CreateCloudDisk(
       const base::DCVMVector_t<base::DCVMString_t> &clientIds
       , clouddisk::ICloudDisk*                     &pCloudDisk
       , struct DCVMContext                         *pCtxt
   ) const noexcept;
};

} // namespace clouddiskmanager
} // namespace dcvm

#endif

#include "CloudDiskManager_impl.hpp"