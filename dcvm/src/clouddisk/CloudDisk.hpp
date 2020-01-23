#ifndef DCVM_CORE_CLOUDDSIK_CLOUDDISK_HPP_
#define DCVM_CORE_CLOUDDSIK_CLOUDDISK_HPP_

#include <dcvm/DCVMCloudProviderAPI.h>
#include "../base/ICloudDiskUnknown.hpp"
#include "../base/CloudProvider.hpp"

#include "ICloudDisk.hpp"

namespace dcvm      {
namespace clouddisk {

class CloudDisk final : public base::MemoryBase, public ICloudDisk
{
public:
    /*!
     * @brief Constructor.
     * @param [in] cloudApi cloud disk api.
    */
    explicit CloudDisk(const base::CloudProvider &cloudApi) noexcept;

    dcvm_int32_t IncReff() noexcept override;

    dcvm_int32_t DecReff(struct DCVMContext *pCtxt) noexcept override;

    base::DCVMString_t GetCloudDiskId(struct DCVMContext *pCtxt) const noexcept override;

    DCVM_ERROR GetOAuthUri(base::DCVMString_t &uri, struct DCVMContext *pCtxt) const noexcept override;

    DCVM_ERROR LogInWithOAuthCode(
        const base::DCVMStringView_t    &code
        , struct DCVMContext            *pCtxt
    ) noexcept override;

    DCVM_ERROR LogInWithRefreshToken(
        const base::DCVMStringView_t    refreshToken
        , struct DCVMContext            *pCtxt
    ) noexcept;

    DCVM_ERROR LogOut(struct DCVMContext *pCtxt) noexcept override;

    DCVM_ERROR Mount(
        const dcvm_uint64_t             flags
        , objects::CloudDiskDirectory*  &pRootDir
        , struct DCVMContext            *pCtxt
    ) noexcept override;

    DCVM_ERROR Unmount(struct DCVMContext *pCtxt) noexcept override;

    DCVM_ERROR CloudGetDiskInfo(
        DCVMCloudDiskInfo       *pDiskInfo
        , dcvm_size_t           &size
        , struct DCVMContext    *pCtxt
    ) const noexcept override;

    DCVM_ERROR Flush(struct DCVMContext *pCtxt) const noexcept override;
protected:
    DCVM_ERROR CloudCreateFile(
        const base::DCVMStringView_t    &fileName
        , const DCVMFileInfo            &fi
        , objects::CloudDiskFile*       &pFile
        , struct DCVMContext            *pCtxt
    ) noexcept override;

    DCVM_ERROR CloudCreateDirectory(
        const base::DCVMStringView_t    &dirName
        , objects::CloudDiskFile*       &pDir
        , struct DCVMContext            *pCtxt
    ) noexcept override;

    DCVM_ERROR CloudOpenFile(
        const base::DCVMStringView_t    &fileName
        , objects::CloudDiskFile*       &pFile
        , struct DCVMContext            *pCtxt
    ) noexcept override;

    DCVM_ERROR CloudCloseFile(
        objects::CloudDiskFile  *pFile
        , struct DCVMContext    *pCtxt
    ) noexcept override;

    DCVM_ERROR CloudReadFile(
        objects::CloudDiskFile  *pFile
        , const dcvm_uint64_t   offset
        , dcvm_uint8_t          *pBuffer
        , const dcvm_uint32_t   buffserSize
        , struct DCVMContext    *pCtxt
    ) const noexcept override;

    DCVM_ERROR CloudWriteFile(
        objects::CloudDiskFile  *pFile
        , const dcvm_uint64_t   offset
        , const dcvm_uint8_t    *pBuffer
        , const dcvm_uint32_t   buffserSize
        , struct DCVMContext    *pCtxt
    ) noexcept override;

    DCVM_ERROR CloudUnlinkFile(
        const base::DCVMStringView_t    &fileName
        , struct DCVMContext            *pCtxt
    ) const noexcept override;

    DCVM_ERROR CloudReadDirectory(
        const base::DCVMStringView_t    &dirName
        , DCVMFileInfo                  *pFIBuffer
        , const dcvm_uint32_t           fiCnt
        , dcvm_uint32_t                 &index
        , struct DCVMContext            *pCtxt
    ) const noexcept override;

    DCVM_ERROR CloudMoveFile(
        objects::CloudDiskDirectory         *pSrcDir
        , const base::DCVMStringView_t      &srcFileName
        , objects::CloudDiskFile            *pFile
        , const base::DCVMStringView_t      &dstFileName
        , objects::CloudDiskDirectory       *pDstDir
        , dcvm_bool_t                       bReplace
        , struct DCVMContext                *pCtxt
    ) noexcept override;
private:
    /*!
     * Destructor.
    */
   ~CloudDisk() noexcept;
private:
    base::CloudProvider m_cloudApi;
    objects::CloudDiskDirectory *m_pRootDir = nullptr;
    struct DCVMCloudProvider *m_pCloudProvider = nullptr;
    DCVMCloudDiskInfo m_cloudDiskInfo = {};
    dcvm_int32_t m_reffCnt = 0;
    static constexpr dcvm_char_t *ROOT_DIR_PATH = DCVM_TEXT("/");
};

} // namespace clouddisk
} // namespace dcvm

#endif