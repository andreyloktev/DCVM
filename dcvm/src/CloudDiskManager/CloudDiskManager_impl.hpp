#ifndef DCVM_CORE_CLOUDDSIKMANAGER_CLOUDDISKMANAGER_IMPL_HPP_
#define DCVM_CORE_CLOUDDSIKMANAGER_CLOUDDISKMANAGER_IMPL_HPP_

namespace dcvm              {
namespace clouddiskmanager  {

template <class SystemApi>
CloudDiskManager<SystemApi>::CloudDiskManager() noexcept
{
    //TODO: Add initialization of saved clients
}

template <class SystemApi>
CloudDiskManager<SystemApi>::~CloudDiskManager() noexcept
{
    //TODO: Add logic for saving refresh tokens
}

template <class SystemApi>
void CloudDiskManager<SystemApi>::AddClient(DCVMCloudDiskAPI client, struct DCVMContext *pCtxt) noexcept
{
    
}

} // namespace clouddiskmanager
} // namespace dcvm

#endif