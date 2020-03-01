#ifndef DCVM_FILEMANAGER_CLI_TASKS_CONTROL_DCVMDISKINFOTASK_HPP_
#define DCVM_FILEMANAGER_CLI_TASKS_CONTROL_DCVMDISKINFOTASK_HPP_

#include "../DCVMTask.hpp"

namespace dcvm_filemanager_cli {

class DCVMDiskInfoTask final : public DCVMTask
{
public:
    DCVMDiskInfoTask(DCVMWrapper &dcvm);
    void Help(Command &cmd) const override;
    DCVM_ERROR Execute(Command &cmd) const override;
private:
    void PrintHelp() const override;
    void PrintError(const DCVMString_t &msg) const override;
};

} // namespace dcvm_filemanager_cli

#endif