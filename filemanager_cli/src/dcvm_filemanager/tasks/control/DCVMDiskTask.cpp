#include "DCVMDiskTask.hpp"
#include "DCVMDiskListTask.hpp"
#include "DCVMDiskInfoTask.hpp"

namespace dcvm_filemanager_cli {

DCVMDiskTask::DCVMDiskTask(DCVMWrapper &dcvm) : DCVMTask(dcvm)
{
}

void DCVMDiskTask::PrintHelp() const
{
    DCVM_INFO_TRACE("list -- get list of all created cloud disk ids. For information type: CONTROL DISK LIST.");
    DCVM_INFO_TRACE("info -- get information about cloud disk. For information type: CONTROL DISK INFO.");
}

PTask DCVMDiskTask::Generate(Command &cmd) const
{
    auto diskCmd = GetFirstCommand(cmd);

    if (diskCmd.empty())
    {
        return nullptr;
    }

    if (DCVM_TEXT("list") == diskCmd)
    {
        return std::make_shared<DCVMDiskListTask>(m_dcvm);
    }
    else if (DCVM_TEXT("info") == diskCmd)
    {
        return std::make_shared<DCVMDiskInfoTask>(m_dcvm);
    }

    return nullptr;
}

} // namespace dcvm_filemanager_cli