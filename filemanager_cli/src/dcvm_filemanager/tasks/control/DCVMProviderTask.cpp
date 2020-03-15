#include "DCVMProviderTask.hpp"
#include "DCVMProviderUriTask.hpp"
#include "DCVMProviderListTask.hpp"
#include "DCVMProviderAuthTask.hpp"

namespace dcvm_filemanager_cli {

DCVMProviderTask::DCVMProviderTask(DCVMWrapper &dcvm) : DCVMTask(dcvm)
{
}

void DCVMProviderTask::PrintHelp() const
{
    DCVM_INFO_TRACE("list  -- get cloud providers list. For more information type: HELP CONTROL LIST.");
    DCVM_INFO_TRACE("uri   -- get authorization uri. For more information type: HELP CONTROL URI.");
    DCVM_INFO_TRACE("auth  -- authentication. For more information: HELP CONTROL AUTH.");
}

PTask DCVMProviderTask::Generate(Command &cmd) const
{
    auto controlCmd = GetFirstCommand(cmd);

    if (controlCmd.empty())
    {
        return nullptr;
    }

    if (DCVM_TEXT("uri") == controlCmd)
    {
        return dcvm::base::DCVMMakeShared<DCVMProviderUriTask>(m_dcvm);
    }
    else if (DCVM_TEXT("auth") == controlCmd)
    {
        return dcvm::base::DCVMMakeShared<DCVMProviderAuthTask>(m_dcvm);
    }
    else if (DCVM_TEXT("list") == controlCmd)
    {
        return dcvm::base::DCVMMakeShared<DCVMProviderListTask>(m_dcvm);
    }

    return nullptr;
}

} // namespace dcvm_filemanager_cli