#ifndef DCVM_BASE_NAMEVALUEPAIR_HPP_
#define DCVM_BASE_NAMEVALUEPAIR_HPP_

#include "DCVMTypes.hpp"

namespace dcvm {
namespace base {

struct NameValuePair final
{
    DCVMString_t name;
    DCVMString_t value;
}

} // namespace base
} // namespace dcvm

#endif