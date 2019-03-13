#ifndef DCVM_CORE_CLOUDDISK_YANDEX_YANDEXDISK_HPP_
#define DCVM_CORE_CLOUDDISK_YANDEX_YANDEXDISK_HPP_

#include "../ICloudDisk.hpp"
#include "../ICloudDiskControl.hpp"

namespace dcvm {
namespace clouddisk {
namespace yandex {

class YandexDisk final : public ICloudDiskControl, public ICloudDisk
{
    DCVMString_t m_accessToken;
    DCVMString_t m_refreshToken;
public:
    static DCVMString_t GetOAuthUrlToLogIn();
public:
    YandexDisk() = default;
    YandexDisk(const YandexDisk&) = delete;
    YandexDisk& operator=(const YandexDisk&) = delete;
    
    DCVMError LogIn(const DCVMString_t &authorizationCode) noexcept override;
};

} // namespace yandex
} // namespace clouddisk
} // namespace dcvm

#endif