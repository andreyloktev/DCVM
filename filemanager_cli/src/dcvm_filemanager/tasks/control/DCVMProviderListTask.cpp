#include "DCVMProviderListTask.hpp"

namespace dcvm_filemanager_cli {

DCVMProviderListTask::DCVMProviderListTask(DCVMWrapper &dcvm) : DCVMTask(dcvm)
{
}

void DCVMProviderListTask::Help(Command&) const
{
    PrintHelp();
}

DCVM_ERROR DCVMProviderListTask::Execute(Command &cmd) const
{
    if (!cmd.empty())
    {
        PrintError(DCVM_TEXT("Bad parameters."));
        return DCVM_ERR_BAD_PARAMS;
    }

    dcvm::base::DCVMVector_t<dcvm::base::DCVMString_t> providersIds;
    DCVM_ERROR err = m_dcvm.ControlGetListOfCloudProviders(providersIds);
    if (DCVM_FAILED(err))
    {
        return err;
    }

    for (const auto &id : providersIds)
    {
        DCVM_INFO_TRACE("%s", id.c_str());
    }

    return DCVM_ERR_SUCCESS;
}

void DCVMProviderListTask::PrintHelp() const
{
    DCVM_INFO_TRACE("Get list of supported cloud providers.\n");
    DCVM_INFO_TRACE("Usage:");
    DCVM_INFO_TRACE("control provider list");
}

void DCVMProviderListTask::PrintError(const dcvm::base::DCVMString_t &msg) const
{
    DCVM_INFO_TRACE("Error: %s", msg);
    DCVM_INFO_TRACE("Type HELP CONTROL PROVIDER LIST for usage");
}

} // namespace dcvm_filemanager_cli