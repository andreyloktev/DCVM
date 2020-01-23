// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "CloudDiskDirectory.hpp"

namespace dcvm      {
namespace clouddisk {
namespace objects   {

CloudDiskDirectory::CloudDiskDirectory(
    const DCVMFileInfo  &fileInfo
    , struct DCVMHandle *pCloudFileObject
    , ICloudDisk        *pCloudDisk
) noexcept : CloudDiskObject(fileInfo, pCloudFileObject, pCloudDisk)
{
}

DCVM_ERROR CloudDiskDirectory::Flush(struct DCVMContext *pCtxt) noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

CloudDiskDirectory::~CloudDiskDirectory() noexcept
{
}

DCVM_ERROR CloudDiskDirectory::Read(
    const dcvm_uint32_t     index
    , DCVMFileInfo* const   pFiles
    , dcvm_uint32_t         filesToList
    , struct DCVMContext    *pCtxt
) noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDiskDirectory::OpenFile(
    const base::DCVMString_t    &fileName
    , const dcvm_uint32_t       shareMode
    , CloudDiskObject*          &pFileObject
    , struct DCVMContext        *pCtxt
) noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDiskDirectory::CreateFile(
    const base::DCVMString_t    &fileName
    , const dcvm_uint32_t       shareMode
    , CloudDiskFile*            &pFile
    , struct DCVMContext        *pCtxt
) noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDiskDirectory::CreateFile(
    const base::DCVMString_t    &dirName
    , const dcvm_uint32_t       shareMode
    , CloudDiskDirectory*       &pDir
    , struct DCVMContext        *pCtxt
) noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDiskDirectory::UnlinkFile(
    const base::DCVMString_t &fileName
    , struct DCVMContext     *pCtxt
) noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDiskDirectory::MoveFile(
    const base::DCVMString_t    &srcFileName
    , CloudDiskObject           *pSrcFileObject
    , CloudDiskDirectory        *pDstDir
    , const base::DCVMString_t  &dstFileName
    , dcvm_bool_t               bReplace
    , struct DCVMContext        *pCtxt
) noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

} // namespace objects
} // namespace clouddisk
} // namespace dcvm