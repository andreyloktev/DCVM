#include "DCVMProviderAuthTask.hpp"

namespace dcvm_filemanager_cli {

DCVMProviderAuthTask::DCVMProviderAuthTask(DCVMWrapper &dcvm) : DCVMTask(dcvm)
{
}

void DCVMProviderAuthTask::Help(Command&) const
{
    PrintHelp();
}

DCVM_ERROR DCVMProviderAuthTask::Execute(Command &cmd) const
{
    if (cmd.empty())
    {
        PrintHelp();
        return DCVM_ERR_SUCCESS;
    }

    if (2 != cmd.size())
    {
        return DCVM_ERR_BAD_PARAMS;
    }

    const auto &providerId = cmd[0];
    const auto &authCode = cmd[1];

    dcvm_size_t cloudDiskId = -1;
    DCVM_ERROR err = m_dcvm.ControlCreateCloudDisk(providerId.c_str(), authCode.c_str(), cloudDiskId);
    if (DCVM_FAILED(err))
    {
        return err;
    }

    DCVM_INFO_TRACE("Cloud disk id -- 0x%X", cloudDiskId);

    return DCVM_ERR_SUCCESS;
}

void DCVMProviderAuthTask::PrintHelp() const
{
    DCVM_INFO_TRACE("Authenticate cloud provider.\n");
    DCVM_INFO_TRACE("Usage:");
    DCVM_INFO_TRACE("control provider auth <id> <code>\n");
    DCVM_INFO_TRACE("Parameters:");
    DCVM_INFO_TRACE("  id   -- provider id to authenticate.");
    DCVM_INFO_TRACE("  code -- authentication code.");
}

void DCVMProviderAuthTask::PrintError(const dcvm::base::DCVMString_t &msg) const
{
    DCVM_INFO_TRACE("Error: %s", msg);
    DCVM_INFO_TRACE("Type HELP CONTROL PROVIDER LIST for usage");
}

} // namespace namespace dcvm_filemanager_cli