#ifndef DCVM_CORE_CLOUDDSIK_ICLOUDDISK_HPP_
#define DCVM_CORE_CLOUDDSIK_ICLOUDDISK_HPP_

#include <dcvm/DCVMError.h>
#include "../base/DCVMTypes.hpp"
#include "../base/MemoryBase.hpp"
#include "../base/ICloudDiskUnknown.hpp"
#include <dcvm/DCVMCloudDiskAPI.h>
#include "objects/CloudDiskDirectory.hpp"
#include "objects/CloudDiskFile.hpp"

namespace dcvm      {
namespace clouddisk {

/*!
 * @class ICloudDisk is interface which lets to work with one or several cloud disk.
*/
class ICloudDisk : public base::ICloudDiskUnknown
{
public:
    /*!
     * @brief Get cloud disk unique identifier.
     * @param [in] pCtxt system context(optional).
     * @return cloud disk identifier.
    */
   virtual base::DCVMString_t GetCloudDiskId(struct DCVMContext *pCtxt) const noexcept = 0;

   /*!
    * @brief Get uri to get OAuth code.
    * @param [out] uri
    * @param [in] pCtxt system context(optional).
    * @return error code.
   */
   virtual DCVM_ERROR GetOAuthUri(base::DCVMString_t &uri, struct DCVMContext *pCtxt) const noexcept = 0;

    /*!
     * @brief Initialize CloudDisk using OAuth code.
     * @param [in] code OAuth code.
     * @param [out] refreshToken a refresh token which might be used in the next login using LogInWithRefreshToken.
     * @param [in] pCtxt system context(optional).
     * @return Error code.
    */
    virtual DCVM_ERROR LogInWithOAuthCode(
        const base::DCVMString_t    &code
        , base::DCVMString_t        &refreshToken
        , struct DCVMContext        *pCtxt
    ) noexcept = 0;

    /*!
     * @brief Initialize CloudDisk using OAuth refresh token.
     * @param [in] refreshToken OAuth refresh token.
     * @param [out] newRefreshToken a refresh token which might be used in the next login using LogInWithRefreshToken.
     * @param [in] pCtxt system context(optional).
     * @return Error code.
    */
    virtual DCVM_ERROR LogInWithRefreshToken(
        const base::DCVMString_t    refreshToken
        , base::DCVMString_t        &newRefreshToken
        , struct DCVMContext        *pCtxt
    ) noexcept = 0;

    /*!
     * @brief Release all resources and destroy CloudDisk.
     * @param [in] pCtxt system context(optional).
     * @return Error code.
    */
    virtual DCVM_ERROR LogOut(struct DCVMContext *pCtxt) noexcept = 0;

    /*!
     * @brief Mount cloud disk(Initialize)
     * @param [in] flags mount flags.
     * @param [out] pRootDir root directory.
     * @param [in] pCtxt system context(optional).
     * @return Error code.
    */
   virtual DCVM_ERROR Mount(
       const dcvm_uint64_t              flags
       , objects::CloudDiskDirectory*   &pRootDir
       , struct DCVMContext             *pCtxt
   ) noexcept = 0;

    /*!
     * @brief Unmount cloud disk(Flush all cached info, release all internal allocated structures).
     * @param [in] pCtxt system context(optional).
     * @return Error code.
    */
   virtual DCVM_ERROR Unmount(struct DCVMContext *pCtxt) noexcept = 0;

    /*!
     * Get information about a cloud disk.
     * @param [in] di disk information.
     * @param [in] pCtxt system context(optional).
     * @return Error code.
    */
    virtual DCVM_ERROR CloudGetDiskInfo(
        DCVMCloudDiskInfo       &di
        , struct DCVMContext    *pCtxt
    ) const noexcept = 0;
protected:
    /*!
     * @brief Create a file.
     * @param [in] fileName full specified file name (file path + file name).
     * @param [in] fi additional file information used to create a file(file flags)
     * @param [out] pFile handle to a created file.
     * @param [in] pCtxt system context(optional).
     * @return Error code.
    */
    virtual DCVM_ERROR CloudCreateFile(
        const base::DCVMString_t    &fileName
        , const DCVMFileInfo        &fi
        , objects::CloudDiskFile*   &pFile
        , struct DCVMContext        *pCtxt
    ) noexcept = 0;

    /*!
     * @brief Create a directory.
     * @param [in] dirName full specified directory name (path + directory name).
     * @param [out] pDirectory handle to a created directory.
     * @param [in] pCtxt system context(optional).
     * @return Error code.
    */
    virtual DCVM_ERROR CloudCreateDirectory(
        const base::DCVMString_t    &dirName
        , objects::CloudDiskFile*   &pDir
        , struct DCVMContext        *pCtxt
    ) noexcept = 0;

    /*!
     * @brief Open a file.
     * @param [in] fileName full specified file name (path + file name).
     * @param [out] pFile handle to a opened file.
     * @param [in] pCtxt system context(optional).
     * @return Error code.
    */
    virtual DCVM_ERROR CloudOpenFile(
        const base::DCVMString_t    &fileName
        , objects::CloudDiskFile*   &pFile
        , struct DCVMContext        *pCtxt
    ) noexcept = 0;

    /*!
     * @brief Close a file.
     * @param [in] pFile file to close.
     * @param [in] pCtxt system context(optional).
     * @return Error code.
    */
    virtual DCVM_ERROR CloudCloseFile(
        objects::CloudDiskFile  *pFile
        , struct DCVMContext    *pCtxt
    ) noexcept = 0;

    /*!
     * @brief Read a file.
     * @param [in] pFile file handle.
     * @param [in] offset
     * @param [in,out] pBuffer
     * @param [in] buffserSize
     * @param [in] pCtxt system context(optional).
     * @return Error code.
    */
    virtual DCVM_ERROR CloudReadFile(
        objects::CloudDiskFile  *pFile
        , const dcvm_uint64_t   offset
        , dcvm_uint8_t          *pBuffer
        , const dcvm_uint32_t   buffserSize
        , struct DCVMContext    *pCtxt
    ) const noexcept = 0;

    /*!
     * @brief Write a file.
     * @param [in] pFile file handle.
     * @param [in] offset
     * @param [in,out] pBuffer
     * @param [in] buffserSize
     * @param [in] pCtxt system context(optional).
     * @return Error code.
    */
    virtual DCVM_ERROR CloudWriteFile(
        objects::CloudDiskFile  *pFile
        , const dcvm_uint64_t   offset
        , const dcvm_uint8_t    *pBuffer
        , const dcvm_uint32_t   buffserSize
        , struct DCVMContext    *pCtxt
    ) noexcept = 0;

    /*!
     * @brief Unlink a file.
     * @param [in] fileName full specified file name to unlink(path + file name).
     * @param [in] pCtxt system context(optional).
     * @return Error code.
    */
    virtual DCVM_ERROR CloudUnlinkFile(
        const base::DCVMString_t    &fileName
        , struct DCVMContext        *pCtxt
    ) const noexcept = 0;

    /*!
     * @brief REad a directory.
     * @param [in] dirName Full path to directory to read.
     * @param [in] pFIBuffer buffer to fill in.
     * @param [in] fiCnt size of pFIBuffer
     * @param [in, out] index. Input -- position to begin read. Output -- position where reading is interrupted.
     * @param [in] pCtxt system context(optional).
     * @return Error code. If DCVM_ERR_NO_MORE_FILE is returned then all directory content was read.
     * 
    */
    virtual DCVM_ERROR CloudReadDirectory(
        const base::DCVMString_t    &dirName
        , DCVMFileInfo              *pFIBuffer
        , const dcvm_uint32_t       fiCnt
        , dcvm_uint32_t             &index
        , struct DCVMContext        *pCtxt
    ) const noexcept = 0;

    /*!
     * Move a file.
     * @param [in] pSrcDir source directory.
     * @param [in] srcFileName source full file name.
     * @param [in] pFile source file handle if file was openned before(optional).
     * @param [in] dstFileName destibation full file name.
     * @param [in] bReplace replace destination file name if it exists.
     * @param [in] pCtxt system context(optional).
     * @return Error code.
    */
    virtual DCVM_ERROR CloudMoveFile(
        objects::CloudDiskDirectory     *pSrcDir
        , const base::DCVMString_t      &srcFileName
        , objects::CloudDiskFile        *pFile
        , const base::DCVMString_t      &dstFileName
        , objects::CloudDiskDirectory   *pDstDir
        , dcvm_bool_t                   bReplace
        , struct DCVMContext            *pCtxt
    ) noexcept = 0;
};

} // namespace clouddisk
} // namesapce dcvm

#endif