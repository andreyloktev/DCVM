#include <iostream>
#include <algorithm>
#include <cwctype>
#include "DCVMControlTask.hpp"
#include "DCVMProviderTask.hpp"
#include "DCVMDiskTask.hpp"

namespace dcvm_filemanager_cli {

DCVMControlTask::DCVMControlTask(DCVMWrapper &wrapper) : DCVMTask(wrapper)
{
}

void DCVMControlTask::PrintHelp() const
{
    DCVM_INFO_TRACE("provider -- operation under cloud providers. For more information type: HELP CONTROL PROVIDER.");
    DCVM_INFO_TRACE("disk     -- operation under cloud disks. For more information type: HELP CONTROL DISK.");
}

PTask DCVMControlTask::Generate(Command &cmd) const
{
    auto controlCmd = GetFirstCommand(cmd);

    if (controlCmd.empty())
    {
        return nullptr;
    }

    if (DCVM_TEXT("provider") == controlCmd)
    {
        return dcvm::base::DCVMMakeShared<DCVMProviderTask>(m_dcvm);
    }
    else if (DCVM_TEXT("disk") == controlCmd)
    {
        return dcvm::base::DCVMMakeShared<DCVMDiskTask>(m_dcvm);
    }

    return nullptr;
}

} // namespace dcvm_filemanager_cli