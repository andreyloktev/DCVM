// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <dcvm/cpp/base/dcvm_defines.hpp>
#include "CloudDiskFile.hpp"

namespace dcvm      {
namespace clouddisk {
namespace objects   {

CloudDiskFile::CloudDiskFile(
    const DCVMFileInfo  &fileInfo
    , struct DCVMHandle *pCloudFileObject
    , ICloudDisk        *pCloudDisk
) noexcept : CloudDiskObject(fileInfo, pCloudFileObject, pCloudDisk)
{
}

DCVM_ERROR CloudDiskFile::Flush(struct DCVMContext *pCtxt) noexcept
{
    UNREFFERENCE_VARIABLE(pCtxt);

    return DCVM_ERR_NOT_IMPLEMENTED;
}

CloudDiskFile::~CloudDiskFile() noexcept
{
}

dcvm_uint64_t CloudDiskFile::GetSize() const noexcept
{
    return m_fileInfo.fileSize;
}

DCVM_ERROR CloudDiskFile::SetSize(
    const dcvm_uint64_t     size
    , struct DCVMContext    *pCtxt
) const noexcept
{
    UNREFFERENCE_VARIABLE(size);
    UNREFFERENCE_VARIABLE(pCtxt);

    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDiskFile::Read(
    dcvm_uint64_t           offset
    , dcvm_uint8_t* const   pBuffer
    , dcvm_uint32_t         size
    , struct DCVMContext    *pCtxt
) const noexcept
{
    UNREFFERENCE_VARIABLE(offset);
    UNREFFERENCE_VARIABLE(pBuffer);
    UNREFFERENCE_VARIABLE(size);
    UNREFFERENCE_VARIABLE(pCtxt);

    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDiskFile::Write(
    dcvm_uint64_t                   offset
    , const dcvm_uint8_t* const     pBuffer
    , dcvm_uint32_t                 size
    , struct DCVMContext            *pCtxt
) const noexcept
{
    UNREFFERENCE_VARIABLE(offset);
    UNREFFERENCE_VARIABLE(pBuffer);
    UNREFFERENCE_VARIABLE(size);
    UNREFFERENCE_VARIABLE(pCtxt);

    return DCVM_ERR_NOT_IMPLEMENTED;
}

} // namespace objects
} // namespace clouddisk
} // namespace dcvm