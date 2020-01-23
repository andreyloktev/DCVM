// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "CloudDiskObject.hpp"

namespace dcvm      {
namespace clouddisk {
namespace objects   {

CloudDiskObject::CloudDiskObject(const DCVMFileInfo &fileInfo, struct DCVMHandle *pCloudFileObject, ICloudDisk *pCloudDisk) noexcept 
    : m_pCloudDisk(pCloudDisk), m_pCloudFileObject(pCloudFileObject), m_fileInfo(fileInfo), m_reffCnt(1)
{
}

dcvm_int32_t CloudDiskObject::IncReff() noexcept
{
    return ++m_reffCnt;
}

dcvm_int32_t CloudDiskObject::DecReff(struct DCVMContext *pCtxt) noexcept
{
    auto value = --m_reffCnt;

    if (0 == value)
    {
        Flush(pCtxt);
        delete this;
    }

    return value;
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