#include <iostream>
#include "DCVMProviderUriTask.hpp"

namespace dcvm_filemanager_cli {

DCVMProviderUriTask::DCVMProviderUriTask(DCVMWrapper &dcvm) : DCVMTask(dcvm)
{
}

void DCVMProviderUriTask::Help(Command &cmd) const
{
    PrintHelp();
}

DCVM_ERROR DCVMProviderUriTask::Execute(Command &cmd) const
{
    if (cmd.empty())
    {
        PrintHelp();
        return DCVM_ERR_SUCCESS;
    }

    if (cmd.size() > 1)
    {
        PrintError(DCVM_TEXT("Too much parameters."));
        return DCVM_ERR_BAD_PARAMS;
    }

    DCVMString_t uri;
    DCVM_ERROR err = m_dcvm.ControlGetAuthorzationUri(cmd[0].c_str(), uri);
    if (DCVM_SUCCESS(err))
    {
        DCVM_INFO_TRACE("%s", uri.c_str());
    }

    return err;
}

void DCVMProviderUriTask::PrintError(const DCVMString_t &msg) const
{
    DCVM_INFO_TRACE("Error: %s", msg);
    DCVM_INFO_TRACE("Type HELP CONTROL PROVIDER URI for usage");
}

void DCVMProviderUriTask::PrintHelp() const
{
    DCVM_INFO_TRACE("Get authorization uri.\n");
    DCVM_INFO_TRACE("Usage:");
    DCVM_INFO_TRACE("control provider uri <provider>\n");
    DCVM_INFO_TRACE("Parameters:");
    DCVM_INFO_TRACE("  provider -- provider id. To get the list of supported cloud providers type: CONTROL PROVIDER LIST");
}

} // namespace dcvm_filemanager_cli