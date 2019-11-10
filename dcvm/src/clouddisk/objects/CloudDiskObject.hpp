#ifndef DCVM_CLOUDDSIK_OBJECTS_CLOUDDISKOBJECT_HPP_
#define DCVM_CLOUDDSIK_OBJECTS_CLOUDDISKOBJECT_HPP_

#include <dcvm/DCVMCloudDiskAPI.h>
#include "../../base/MemoryBase.hpp"
#include "../../base/ICloudDiskUnknown.hpp"

namespace dcvm      {
namespace clouddisk {

class ICloudDisk;

namespace objects   {

/*!
 * @class CloudDiskObject
 * It's a base class for all cloud disk objects: files, directories and etc
*/
class CloudDiskObject : public base::MemoryBase, public base::ICloudDiskUnknown
{
public:
    dcvm_int32_t IncReff() noexcept override final;

    dcvm_int32_t DecReff() noexcept override final;

    /*!
     * @brief Constructor.
     * @param pCloudDisk cloud disk which it belongs to.
    */
    CloudDiskObject(const DCVMFileInfo &fileInfo, ICloudDisk *pCloudDisk) noexcept;

    /*!
     * @brief Get cloud disk object type.
     * @return object type.
    */
    DCVMFileType GetType() const noexcept;

    /*!
     * @brief Get information about file object(file, directory, etc)
     * @return file object information.
    */
    const DCVMFileInfo& GetFileInfo() const noexcept;

    /*!
     * @brief Flush all cached information into cloud disk.
     * @param pCtxt system context(optional). 
     * @return error code.
    */
    virtual DCVM_ERROR Flush(struct DCVMContext *pCtxt) noexcept = 0;
protected:
    virtual ~CloudDiskObject() noexcept {}
protected:
    ICloudDisk *m_pCloudDisk = nullptr;
    DCVMFileInfo m_fileInfo = {};
private:
    dcvm_int32_t m_reffCnt = 0;
};

} // namespace objects
} // namespace clouddisk
} // namespace dcvm

#endif