// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <dcvm/DCVMLogger.h>
#include "../base/SystemApi.hpp"
#include "CloudDisk.hpp"

namespace dcvm      {
namespace clouddisk {

CloudDisk::CloudDisk(const base::CloudProvider &cloudApi) noexcept : m_cloudApi(cloudApi), m_reffCnt(1)
{
}

CloudDisk::~CloudDisk() noexcept
{
    m_cloudApi.LogOut(m_pCloudProvider, nullptr);
}

 dcvm_int32_t CloudDisk::IncReff() noexcept
 {
     return ++m_reffCnt;
 }

dcvm_int32_t CloudDisk::DecReff(struct DCVMContext *pCtxt) noexcept
{
    auto value = --m_reffCnt;

    if (0 == value)
    {
        Flush(pCtxt);
        delete this;
    }

    return value;
}

base::DCVMString_t CloudDisk::GetCloudDiskId(struct DCVMContext *pCtxt) const noexcept 
{
    return base::DCVMString_t(m_cloudApi.GetProviderId(pCtxt));
}

DCVM_ERROR CloudDisk::GetOAuthUri(base::DCVMString_t &uri, struct DCVMContext *pCtxt) const noexcept
{
    return m_cloudApi.GetOAuthUri(uri, pCtxt);
}

DCVM_ERROR CloudDisk::LogInWithOAuthCode(
    const base::DCVMStringView_t    &code
    , struct DCVMContext            *pCtxt
) noexcept
{
    if (nullptr != m_pCloudProvider)
    {
        DCVM_INFO_TRACE("CloudDisk has been already authenticated");
        return DCVM_ERR_CLOUDDISK_HAS_BEEN_ALREADY_AUTHENTICATED;
    }

    auto err = m_cloudApi.LogInWithOAuthCode(code, m_pCloudProvider, pCtxt);
    if (DCVM_FAILED(err))
    {
        DCVM_ERROR_TRACE(err);
        return err;
    }

    err = m_cloudApi.GetDiskInfo(m_pCloudProvider, m_cloudDiskInfo, nullptr);
    if (DCVM_FAILED(err))
    {
        DCVM_ERROR_TRACE(err);
        m_cloudApi.LogOut(m_pCloudProvider, pCtxt);
        m_pCloudProvider = nullptr;
        return err;
    }

    return err;
}

DCVM_ERROR CloudDisk::LogInWithRefreshToken(
    const base::DCVMStringView_t    refreshToken
    , struct DCVMContext            *pCtxt
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
    if (nullptr == m_pCloudProvider)
    {
        DCVM_ERROR_TRACE(DCVM_ERR_NOT_INITIALIZED);
        return DCVM_ERR_NOT_INITIALIZED;
    }

    struct DCVMHandle *pDirHandle = nullptr;
    DCVMFileInfo fi = {};
    auto err = m_cloudApi.OpenFile(m_pCloudProvider, ROOT_DIR_PATH, fi, pDirHandle, pCtxt);
    if (DCVM_FAILED(err))
    {
        DCVM_ERROR_TRACE(err);
        return err;
    }

    if (DCVM_Dirctory != fi.type)
    {
        DCVM_ERROR_TRACE(DCVM_ERR_FILE_IS_NOT_DIRECTORY);
        m_cloudApi.CloseFile(m_pCloudProvider, pDirHandle, pCtxt);
        return DCVM_ERR_FILE_IS_NOT_DIRECTORY;
    }

    m_pRootDir = new objects::CloudDiskDirectory(fi, pDirHandle, this);
    if (nullptr == m_pRootDir)
    {
        DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES);
        m_cloudApi.CloseFile(m_pCloudProvider, pDirHandle, pCtxt);
        return DCVM_ERR_INSUFFICIENT_RESOURCES;
    }

    m_pRootDir->IncReff();
    pRootDir = m_pRootDir;

    return DCVM_ERR_SUCCESS;
}

DCVM_ERROR CloudDisk::Unmount(struct DCVMContext *pCtxt) noexcept
{
    if ((nullptr == m_pCloudProvider) || (nullptr == m_pRootDir))
    {
        DCVM_ERROR_TRACE(DCVM_ERR_NOT_INITIALIZED);
        return DCVM_ERR_NOT_INITIALIZED;
    }

    Flush(pCtxt);
    auto reffCnt = m_pRootDir->DecReff(pCtxt);
    if (0 != reffCnt)
    {
        DCVM_INFO_TRACE("Root directory refference counter is not 0. DecReff was not called somewhere.");
    }

    m_pRootDir = nullptr;


    return DCVM_ERR_SUCCESS;
}

DCVM_ERROR CloudDisk::CloudGetDiskInfo(
    DCVMCloudDiskInfo       *pDiskInfo
    , dcvm_size_t           &size
    , struct DCVMContext    *pCtxt
) const noexcept
{
    if ((nullptr != pDiskInfo) && (0 == size))
    {
        DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
        return DCVM_ERR_BAD_PARAMS;
    }

    if (nullptr == pDiskInfo)
    {
        size = sizeof(m_cloudDiskInfo);
        return DCVM_ERR_SUCCESS;
    }

    if (size < sizeof(m_cloudDiskInfo))
    {
        DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES);
        return DCVM_ERR_INSUFFICIENT_RESOURCES;
    }

    base::SystemApi::MemoryCopy(pDiskInfo, size, &m_cloudDiskInfo, sizeof(m_cloudDiskInfo));
    size = sizeof(m_cloudDiskInfo);

    return DCVM_ERR_SUCCESS;
}

DCVM_ERROR CloudDisk::Flush(struct DCVMContext *pCtxt) const noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDisk::CloudCreateFile(
    const base::DCVMStringView_t    &fileName
    , const DCVMFileInfo            &fi
    , objects::CloudDiskFile*       &pFile
    , struct DCVMContext            *pCtxt
) noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDisk::CloudCreateDirectory(
    const base::DCVMStringView_t    &dirName
    , objects::CloudDiskFile*       &pDir
    , struct DCVMContext            *pCtxt
) noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDisk::CloudOpenFile(
    const base::DCVMStringView_t    &fileName
    , objects::CloudDiskFile*       &pFile
    , struct DCVMContext            *pCtxt
) noexcept
{
    if (fileName.empty())
    {
        DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
        return DCVM_ERR_BAD_PARAMS;
    }

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
    const base::DCVMStringView_t    &fileName
    , struct DCVMContext            *pCtxt
) const noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDisk::CloudReadDirectory(
    const base::DCVMStringView_t    &dirName
    , DCVMFileInfo                  *pFiBuffer
    , const dcvm_uint32_t           fiCnt
    , dcvm_uint32_t                 &index
    , struct DCVMContext            *pCtxt
) const noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

DCVM_ERROR CloudDisk::CloudMoveFile(
    objects::CloudDiskDirectory         *pSrcDir
    , const base::DCVMStringView_t      &srcFileName
    , objects::CloudDiskFile            *pFile
    , const base::DCVMStringView_t      &dstFileName
    , objects::CloudDiskDirectory       *pDstDir
    , dcvm_bool_t                       bReplace
    , struct DCVMContext                *pCtxt
) noexcept
{
    return DCVM_ERR_NOT_IMPLEMENTED;
}

} // namespace clouddisk
} // namespace dcvm