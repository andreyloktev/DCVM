#ifndef DCVM_BASE_ICLOUDDISKUNKNOWN_HPP_
#define DCVM_BASE_ICLOUDDISKUNKNOWN_HPP_

#include <dcvm/DCVMTypes.h>

namespace dcvm {
namespace base {

struct ICloudDiskUnknown
{
    /*!
     * @brief Increment refference counter.
     * @return refference counter value.
    */
    virtual dcvm_int32_t IncReff() noexcept = 0;

    /*!
     * @brief Decrement refference counter.
     * @param [in] pCtxt system context(optional).
     * @return refference counter value.
    */
    virtual dcvm_int32_t DecReff(struct DCVMContext *pCtxt) noexcept = 0;
};

} // namespace base
} // namespace dcvm

#endif