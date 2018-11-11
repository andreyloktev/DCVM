#ifndef DCVM_DCVM_TYPES_HPP_
#define DCVM_DCVM_TYPES_HPP_

#include <string>
#include <vector>
#include <memory>

namespace dcvm {

#ifdef _WIN32
using DCVMString_t = std::wstring;
#define DCVMStr(str) L ## str
#else
using DCVMString_t = std::string;
#define DCVMStr(str) str
#endif

} // namespace dcvm

#endif