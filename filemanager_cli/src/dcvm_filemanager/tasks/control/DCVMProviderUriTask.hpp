#ifndef DCVM_FILEMANAGER_CLI_TASKS_CONTROL_DCVMPROVIDERURITASK_HPP_
#define DCVM_FILEMANAGER_CLI_TASKS_CONTROL_DCVMPROVIDERURITASK_HPP_

#include "../DCVMTask.hpp"

namespace dcvm_filemanager_cli {

class DCVMProviderUriTask final : public DCVMTask
{
public:
    DCVMProviderUriTask(DCVMWrapper &dcvm);
    void Help(Command &cmd) const override;
    DCVM_ERROR Execute(Command &cmd) const override;
private:
    void PrintError(const dcvm::base::DCVMString_t &msg) const override;
    void PrintHelp() const override;
};

} // namespace dcvm_filemanager_cli

#endif