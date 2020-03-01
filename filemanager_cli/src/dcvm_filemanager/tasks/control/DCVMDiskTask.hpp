#ifndef DCVM_FILEMANAGER_CLI_TASKS_CONTROL_DCVMDISKTASK_HPP_
#define DCVM_FILEMANAGER_CLI_TASKS_CONTROL_DCVMDISKTASK_HPP_

#include "../DCVMTask.hpp"

namespace dcvm_filemanager_cli {

class DCVMDiskTask final : public DCVMTask
{
public:
    DCVMDiskTask(DCVMWrapper &dcvm);
private:
    void PrintHelp() const override;
    PTask Generate(Command &cmd) const override;
};

} // namespace dcvm_filemanager_cli

#endif