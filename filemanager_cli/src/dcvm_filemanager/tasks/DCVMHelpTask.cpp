#include "DCVMHelpTask.hpp"
#include "control/DCVMControlTask.hpp"

namespace dcvm_filemanager_cli {

DCVMHelpTask::DCVMHelpTask(DCVMWrapper &dcvm) : DCVMTask(dcvm)
{
}

void DCVMHelpTask::Help(Command&) const
{
    PrintHelp();
}

DCVM_ERROR DCVMHelpTask::Execute(Command &cmd) const
{
    if (cmd.empty())
    {
        PrintHelp();
        return DCVM_ERR_SUCCESS;
    }

    auto pTask = Generate(cmd);
    if (nullptr == pTask)
    {
        PrintHelp();
        return DCVM_ERR_SUCCESS;
    }

     pTask->Help(cmd);

     return DCVM_ERR_SUCCESS;
}

void DCVMHelpTask::PrintHelp() const
{
    DCVM_INFO_TRACE("help       -- print help.")
    DCVM_INFO_TRACE("control    -- control operation with cloud providers and disks.");
}

PTask DCVMHelpTask::Generate(Command &cmd) const
{
    auto helpCmd = GetFirstCommand(cmd);
    if (helpCmd.empty())
    {
        return nullptr;
    }

    if (DCVM_TEXT("control") == helpCmd)
    {
        return std::make_shared<DCVMControlTask>(m_dcvm);
    }

    return nullptr;
}

} //namespace dcvm_filemanager_cli