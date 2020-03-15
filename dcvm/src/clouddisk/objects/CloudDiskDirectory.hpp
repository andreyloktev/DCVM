#ifndef DCVM_CLOUDDSIK_OBJECTS_CLOUDDISKDIRECTORY_HPP_
#define DCVM_CLOUDDSIK_OBJECTS_CLOUDDISKDIRECTORY_HPP_

#include <dcvm/cpp/base/DCVMTypes.hpp>
#include "CloudDiskObject.hpp"
#include "CloudDiskFile.hpp"

namespace dcvm      {
namespace clouddisk {
namespace objects   {

class CloudDiskDirectory final : public CloudDiskObject
{
public:
    /*!
     * @brief Constructor.
     * @param pCloudDisk cloud disk which it belongs to.
    */
    CloudDiskDirectory(const DCVMFileInfo &fileInfo, struct DCVMHandle *pCloudFileObject, ICloudDisk *pCloudDisk) noexcept;

    DCVM_ERROR Flush(struct DCVMContext *pCtxt) noexcept override final;

    /*!
     * @brief List files in the directory.
     * @param [in] index position to start listing.
     * @param [in, out] pFiles pointer to array of file insformation structures.
     * @param [in] filesToList amount files to list in this request.
     * @param [in] pCtxt system context(optional).
    */
    DCVM_ERROR Read(
        const dcvm_uint32_t     index
        , DCVMFileInfo* const   pFiles
        , dcvm_uint32_t         filesToList
        , struct DCVMContext    *pCtxt
    ) noexcept;

    /*!
     * @brief Open a file or a directory in the directory.
     * @param [in] fileName file name to open.
     * @param [in] shareMode sharing mode(Support will be added in the future when microservice will be created).
     * @param [out] pFileObject opened file object.
     * @param [in] pCtxt system context(optional).
    */
    DCVM_ERROR OpenFile(
        const base::DCVMString_t    &fileName
        , const dcvm_uint32_t       shareMode
        , CloudDiskObject*          &pFileObject
        , struct DCVMContext        *pCtxt
    ) noexcept;

    /*!
     * @brief Crete a new file.
     * @param [in] fileName new file name.
     * @param [in] shareMode sharing mode(Support will be added in the future when microservice will be created).
     * @param [out] pFile a created file.
     * @param [in] pCtxt system context(optional).
    */
    DCVM_ERROR CreateFile(
        const base::DCVMString_t    &fileName
        , const dcvm_uint32_t       shareMode
        , CloudDiskFile*            &pFile
        , struct DCVMContext        *pCtxt
    ) noexcept;

    /*!
     * @brief Create a new directory.
     * @param [in] dirName new directory name.
     * @param [in] shareMode sharing mode(Support will be added in the future when microservice will be created).
     * @param [out] pDir a created directory.
     * @param [in] pCtxt system context(optional).
    */
    DCVM_ERROR CreateFile(
        const base::DCVMString_t    &dirName
        , const dcvm_uint32_t       shareMode
        , CloudDiskDirectory*       &pDir
        , struct DCVMContext        *pCtxt
    ) noexcept;

    /*!
     * @brief Remove file or directory.
     * @param [in] fileName file name to delete.
     * @param [in] pCtxt system context(optional).
    */
   DCVM_ERROR UnlinkFile(
       const base::DCVMString_t &fileName
       , struct DCVMContext     *pCtxt
   ) noexcept;

   /*!
    * @brief Rename or Move a cloud disk object in this directory.
    * @param [in] srcFileName source file name.
    * @param [in] pSrcFileObject cloud disk object to move/rename (optional).
    * @param [in] pDstDir destination directory.
    * @param [in] dstFileName destination file name.
    * @param [in] pCtxt system context(optional).
   */
    DCVM_ERROR MoveFile(
        const base::DCVMString_t    &srcFileName
        , CloudDiskObject           *pSrcFileObject
        , CloudDiskDirectory        *pDstDir
        , const base::DCVMString_t  &dstFileName
        , dcvm_bool_t               bReplace
        , struct DCVMContext        *pCtxt
    ) noexcept;
private:
    ~CloudDiskDirectory() noexcept;
};

} // namespace objects
} // namespace clouddisk
} // namespace dcvm

#endif