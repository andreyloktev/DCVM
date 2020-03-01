#ifndef DCVM_FILEMANAGER_CLI_TASKS_CONTROL_DCVMCONTROLTASK_HPP_
#define DCVM_FILEMANAGER_CLI_TASKS_CONTROL_DCVMCONTROLTASK_HPP_

#include "../DCVMTask.hpp"

namespace dcvm_filemanager_cli {

class DCVMControlTask final : public DCVMTask
{
public:
    DCVMControlTask(DCVMWrapper &wrapper);
private:
    void PrintHelp() const override;
    PTask Generate(Command &cmd) const override;
};

} // namespace dcvm_filemanager_cli

#endif