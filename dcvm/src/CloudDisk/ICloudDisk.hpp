#ifndef DCVM_CORE_CLOUDDSIK_ICLOUDDISK_HPP_
#define DCVM_CORE_CLOUDDSIK_ICLOUDDISK_HPP_

#include <dcvm/DCVMError.h>
#include "../base/DCVMTypes.hpp"
#include "../base/MemoryBase.hpp"
#include <dcvm/DCVMCloudDiskAPI.h>

namespace dcvm      {
namespace clouddisk {

struct DCVMHandle;

template <class SystemApi>
struct ICloudDisk;

template<class SystemApi>
class CloudDiskFile final : public base::MemoryBase<SystemApi>
{
    dcvm_uint32_t m_reffCnt = 0;
    DCVMHandle *m_pFileHandle = nullptr;
    DCVMFileInfo m_fileInfo = {};
    ICloudDisk<SystemApi> *m_pCloudDisk;
private:
    CloudDiskFile(struct DCVMHandle *pFileHandle, const DCVMFileInfo &fi, ICloudDisk *pCloudDisk) noexcept;
    ~CloudDiskFile() noexcept;
    DCVMHandle* GetFileHandle() noexcept;
public:
    void IncReff() noexcept;
    void DecReff() noexcept;
    const DCVMFileInfo& GetFileInfo() const noexcept;
};

/*!
 * @class ICloudDisk is interface which lets to work with one or several cloud disk.
*/
template <class SystemApi>
struct ICloudDisk
{
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
        , CloudDiskFile<SystemApi>* &pFile
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
        , CloudDiskFile<SystemApi>* &pDir
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
        , CloudDiskFile<SystemApi>* &pFile
        , struct DCVMContext        *pCtxt
    ) noexcept = 0;

    /*!
     * @brief Close a file.
     * @param [in] pFile file to close.
     * @param [in] pCtxt system context(optional).
     * @return Error code.
    */
    virtual DCVM_ERROR CloudCloseFile(
        CloudDiskFile<SystemApi>    *pFile
        , struct DCVMContext        *pCtxt
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
        CloudDiskFile<SystemApi>    *pFile
        , const dcvm_uint64_t       offset
        , dcvm_uint8_t              *pBuffer
        , const dcvm_uint32_t       buffserSize
        , struct DCVMContext        *pCtxt
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
        CloudDiskFile<SystemApi>    *pFile
        , const dcvm_uint64_t       offset
        , const dcvm_uint8_t        *pBuffer
        , const dcvm_uint32_t       buffserSize
        , struct DCVMContext        *pCtxt
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
     * @param [in] srcFileName source full file name.
     * @param [in] pFile source file handle if file was openned before(optional).
     * @param [in] dstFileName destibation full file name.
     * @param [in] bReplace replace destination file name if it exists.
     * @param [in] pCtxt system context(optional).
     * @return Error code.
    */
    virtual DCVM_ERROR CloudMoveFile(
        const base::DCVMString_t    &srcFileName
        , CloudDiskFile<SystemApi>  *pFile
        , const base::DCVMString_t  &dstFileName
        , dcvm_bool_t               bReplace
        , struct DCVMContext        *pCtxt
    ) noexcept = 0;

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
};

} // namespace clouddisk
} // namesapce dcvm

#endif