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
class CloudDiskManager final : public base::MemoryBase
{
public:
    CloudDiskManager() noexcept;
    ~CloudDiskManager() noexcept;
    CloudDiskManager(const CloudDiskManager&) = delete;
    CloudDiskManager& operator=(const CloudDiskManager&) = delete;
public:
    /*!
     * @brief Add a client.
     * @param [in] client cloud disk clent.
     * @param [int, out] clientId client id.
     * @param [in] pCtxt system context(optional).
     * @return error code.
    */
    DCVM_ERROR AddClient(DCVMCloudDiskAPI client, base::DCVMString_t &clientId, struct DCVMContext *pCtxt) noexcept;

    /*!
     * Get all authorized clients.
     * @param [in] pCtxt system context(optional).
     * @return list of all clients.
    */
    base::DCVMVector_t<base::DCVMString_t> GetClients(struct DCVMContext *pCtxt) const noexcept;

    /*!
     * Get all unauthorized clients.
     * @param [out] clients array <client id, OAuth url> of all unauthorized clients.
     * @param [in] pCtxt system context(optional).
     * @return error code.
    */
    DCVM_ERROR GetUnauthorizedClients(
        base::DCVMVector_t<base::DCVMPair_t<base::DCVMString_t, base::DCVMString_t>>    &clients
        , struct DCVMContext                                                            *pCtxt
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
     * @param [in] flags initialization flags.
     * @param [out] pRootDir pointer to root directory.
     * @param [out] pCloudDisk cloud disk instance
     * @param [in] pCtxt system context(optional).
     * @return error code.
    */
   DCVM_ERROR InitCloudDisk(
       const base::DCVMString_t                     &clientId
       , const dcvm_uint64_t                        flags
       , clouddisk::objects::CloudDiskDirectory*    &pRootDir
       , clouddisk::ICloudDisk*                     &pCloudDisk
       , struct DCVMContext                         *pCtxt
   ) const noexcept;

   /*!
     * Create a cloud disk instance.
     * Created a cloud disk instance works with several DCVMCloudDiskAPI clients -- represent all clients in one.
     * @param [in] clientIds list of client ids.
     * @param [out] pRootDir pointer to root directory.
     * @param [out] pCloudDisk cloud disk instance.
     * @param [in] pCtxt system context(optional).
     * @return error code.
    */
   DCVM_ERROR InitCloudDisk(
       const base::DCVMVector_t<base::DCVMString_t> &clientIds
       , const dcvm_uint64_t                        flags
       , clouddisk::objects::CloudDiskDirectory*    &pRootDir
       , clouddisk::ICloudDisk*                     &pCloudDisk
       , struct DCVMContext                         *pCtxt
   ) const noexcept;

private:
    using ICloudDisk_t = clouddisk::ICloudDisk;
    using DCVMCloudDisksPool = base::DCVMMap_t<base::DCVMString_t, ICloudDisk_t*>;
private:
    DCVMCloudDisksPool m_clients; /// All unauthorized clients.
    DCVMCloudDisksPool m_authorzedClients; /// All authorized clients.
};

} // namespace clouddiskmanager
} // namespace dcvm

#endif