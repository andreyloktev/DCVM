#ifndef DCVM_FILEMANAGER_CLI_TASKS_DCVMHELPTASK_HPP_
#define DCVM_FILEMANAGER_CLI_TASKS_DCVMHELPTASK_HPP_

#include "DCVMTask.hpp"

namespace dcvm_filemanager_cli {

class DCVMHelpTask final : public DCVMTask
{
public:
    DCVMHelpTask(DCVMWrapper &dcvm);
    void Help(Command &cmd) const override;
    DCVM_ERROR Execute(Command &cmd) const override;
private:
    void PrintHelp() const override;
    PTask Generate(Command &cmd) const;
};

} // namespace dcvm_filemanager_cli

#endif