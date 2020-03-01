#ifndef DCVM_FILEMANAGER_CLI_TASKS_CONTROL_DCVMPROVIDERTASK_HPP_
#define DCVM_FILEMANAGER_CLI_TASKS_CONTROL_DCVMPROVIDERTASK_HPP_

#include "../DCVMTask.hpp"

namespace dcvm_filemanager_cli {

class DCVMProviderTask final : public DCVMTask
{
public:
    DCVMProviderTask(DCVMWrapper &dcvm);
private:
    void PrintHelp() const override;
    PTask Generate(Command &cmd) const override;
};

} // namespace dcvm_filemanager_cli

#endif