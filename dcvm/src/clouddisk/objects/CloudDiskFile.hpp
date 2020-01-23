#ifndef DCVM_CLOUDDSIK_OBJECTS_CLOUDDISKFILE_HPP_
#define DCVM_CLOUDDSIK_OBJECTS_CLOUDDISKFILE_HPP_

#include "CloudDiskObject.hpp"

namespace dcvm      {
namespace clouddisk {
namespace objects   {

class CloudDiskFile final : public CloudDiskObject
{
public:
    /*!
     * @brief Constructor.
     * @param pCloudDisk cloud disk which it belongs to.
    */
    CloudDiskFile(const DCVMFileInfo &fileInfo, struct DCVMHandle *pCloudFileObject, ICloudDisk *pCloudDisk) noexcept;

    DCVM_ERROR Flush(struct DCVMContext *pCtxt) noexcept override final;

    /*!
     * @brief Get file size.
     * @return file size.
    */
    dcvm_uint64_t GetSize() const noexcept;

    /*!
     * @brief Set file size.
     * @param [in] size new file size.
     * @param [in] pCtxt system context(optional).
     * @return error code.
    */
    DCVM_ERROR SetSize(const dcvm_uint64_t size, struct DCVMContext *pCtxt) const noexcept;

    /*!
     * @brief Read a file.
     * @param [in] offset file offset to read from.
     * @param [in, out] pBuffer buffer for recieved information.
     * @param [in] size amount bytes to read.
     * @param [in] pCtxt system context(optional).
    */
    DCVM_ERROR Read(
        dcvm_uint64_t           offset
        , dcvm_uint8_t* const   pBuffer
        , dcvm_uint32_t          size
        , struct DCVMContext    *pCtxt
    ) const noexcept;

    /*!
     * @brief Write into a file.
     * @param [in] offset file offset to write to.
     * @param [in, out] pBuffer buffer with information to write.
     * @param [in] size amount bytes to write.
     * @param [in] pCtxt system context(optional).
    */
    DCVM_ERROR Write(
        dcvm_uint64_t                   offset
        , const dcvm_uint8_t* const     pBuffer
        , dcvm_uint32_t                 size
        , struct DCVMContext            *pCtxt
    ) const noexcept;
private:
    ~CloudDiskFile() noexcept;
};

} // namespace objects
} // namespace clouddisk
} // namespace dcvm

#endif