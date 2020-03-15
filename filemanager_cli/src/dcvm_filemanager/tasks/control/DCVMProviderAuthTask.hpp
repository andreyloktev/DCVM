#ifndef DCVM_FILEMANAGER_CLI_TASKS_CONTROL_DCVMPROVIDERAUTHTASK_HPP_
#define DCVM_FILEMANAGER_CLI_TASKS_CONTROL_DCVMPROVIDERAUTHTASK_HPP_

#include "../DCVMTask.hpp"

namespace dcvm_filemanager_cli {

class DCVMProviderAuthTask final : public DCVMTask
{
public:
    DCVMProviderAuthTask(DCVMWrapper &dcvm);
    void Help(Command &cmd) const override;
    DCVM_ERROR Execute(Command &cmd) const override;
private:
    void PrintHelp() const override;
    void PrintError(const dcvm::base::DCVMString_t &msg) const override;
};

} // namespace dcvm_filemanager_cli

#endif