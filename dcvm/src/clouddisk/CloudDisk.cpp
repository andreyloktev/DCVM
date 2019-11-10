#include <dcvm/DCVMLogger.h>
#include "../base/SystemApi.hpp"
#include "CloudDisk.hpp"

namespace dcvm      {
namespace clouddisk {

CloudDisk::CloudDisk(const DCVMCloudDiskAPI &cloudApi) noexcept : m_cloudApi(cloudApi), m_reffCnt(1)
{
}

CloudDisk::~CloudDisk() noexcept
{
}

 dcvm_int32_t CloudDisk::IncReff() noexcept
 {
     return ++m_reffCnt;
 }

dcvm_int32_t CloudDisk::DecReff() noexcept
{
    return --m_reffCnt;
}

base::DCVMString_t CloudDisk::GetCloudDiskId(struct DCVMContext *pCtxt) const noexcept 
{
    return base::DCVMString_t(m_cloudApi.GetCloudDiskId(pCtxt));
}

DCVM_ERROR CloudDisk::GetOAuthUri(base::DCVMString_t &uri, struct DCVMContext *pCtxt) const noexcept
{
    dcvm_char_t *pUri = nullptr;

    DCVM_ERROR err = m_cloudApi.GetOAuthUri(&pUri, g_pSystemApi, pCtxt);
    if (DCVM_FAILED(err))
    {
        DCVM_ERROR_TRACE(err);
        return err;
    }

    uri = base::DCVMString_t(pUri);
    base::SystemApi::MemoryFree(pUri);

    return err;
}

DCVM_ERROR CloudDisk::LogInWithOAuthCode(
    const base::DCVMString_t    &code
    , base::DCVMString_t        &refreshToken
    , struct DCVMContext        *pCtxt
) noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDisk::LogInWithRefreshToken(
    const base::DCVMString_t    refreshToken
    , base::DCVMString_t        &newRefreshToken
    , struct DCVMContext        *pCtxt
) noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDisk::LogOut(struct DCVMContext *pCtxt) noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDisk::Mount(
    const dcvm_uint64_t             flags
    , objects::CloudDiskDirectory*  &pRootDir
    , struct DCVMContext            *pCtxt
) noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDisk::Unmount(struct DCVMContext *pCtxt) noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDisk::CloudGetDiskInfo(
    DCVMCloudDiskInfo       &di
    , struct DCVMContext    *pCtxt
) const noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDisk::CloudCreateFile(
    const base::DCVMString_t    &fileName
    , const DCVMFileInfo        &fi
    , objects::CloudDiskFile*   &pFile
    , struct DCVMContext        *pCtxt
) noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDisk::CloudCreateDirectory(
    const base::DCVMString_t    &dirName
    , objects::CloudDiskFile*   &pDir
    , struct DCVMContext        *pCtxt
) noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDisk::CloudOpenFile(
    const base::DCVMString_t    &fileName
    , objects::CloudDiskFile*   &pFile
    , struct DCVMContext        *pCtxt
) noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDisk::CloudCloseFile(
    objects::CloudDiskFile  *pFile
    , struct DCVMContext    *pCtxt
) noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDisk::CloudReadFile(
    objects::CloudDiskFile  *pFile
    , const dcvm_uint64_t   offset
    , dcvm_uint8_t          *pBuffer
    , const dcvm_uint32_t   buffserSize
    , struct DCVMContext    *pCtxt
) const noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDisk::CloudWriteFile(
    objects::CloudDiskFile  *pFile
    , const dcvm_uint64_t   offset
    , const dcvm_uint8_t    *pBuffer
    , const dcvm_uint32_t   buffserSize
    , struct DCVMContext    *pCtxt
) noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDisk::CloudUnlinkFile(
    const base::DCVMString_t    &fileName
    , struct DCVMContext        *pCtxt
) const noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDisk::CloudReadDirectory(
    const base::DCVMString_t    &dirName
    , DCVMFileInfo              *pFIBuffer
    , const dcvm_uint32_t       fiCnt
    , dcvm_uint32_t             &index
    , struct DCVMContext        *pCtxt
) const noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDisk::CloudMoveFile(
    objects::CloudDiskDirectory     *pSrcDir
    , const base::DCVMString_t      &srcFileName
    , objects::CloudDiskFile        *pFile
    , const base::DCVMString_t      &dstFileName
    , objects::CloudDiskDirectory   *pDstDir
    , dcvm_bool_t                   bReplace
    , struct DCVMContext            *pCtxt
) noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

} // namespace clouddisk
} // namespace dcvm