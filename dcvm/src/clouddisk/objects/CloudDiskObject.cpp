#include "CloudDiskObject.hpp"

namespace dcvm      {
namespace clouddisk {
namespace objects   {

CloudDiskObject::CloudDiskObject(const DCVMFileInfo &fileInfo, ICloudDisk *pCloudDisk) noexcept 
    : m_pCloudDisk(pCloudDisk), m_fileInfo(fileInfo), m_reffCnt(1)
{
}

dcvm_int32_t CloudDiskObject::IncReff() noexcept
{
    return ++m_reffCnt;
}

dcvm_int32_t CloudDiskObject::DecReff() noexcept
{
    return --m_reffCnt;
}

DCVMFileType CloudDiskObject::GetType() const noexcept
{
    return m_fileInfo.type;
}

const DCVMFileInfo& CloudDiskObject::GetFileInfo() const noexcept
{
    return m_fileInfo;
}

} // namespace objects
} // namespace clouddisk
} // namespace dcvm