#ifndef DCVM_DCVMTYPES_HPP_
#define DCVM_DCVMTYPES_HPP_

#include <dcvm/DCVMTypes.h>
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <iostream>

namespace dcvm_filemanager_cli {

using DCVMString_t = std::basic_string<dcvm_char_t, std::char_traits<dcvm_char_t>>;
using DCVMStringView_t = std::basic_string_view<dcvm_char_t, std::char_traits<dcvm_char_t>>;

} // namespace dcvm_filemanager_cli

#endif