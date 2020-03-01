#include "DCVMDiskListTask.hpp"

namespace dcvm_filemanager_cli {

DCVMDiskListTask::DCVMDiskListTask(DCVMWrapper &dcvm) : DCVMTask(dcvm)
{
}

void DCVMDiskListTask::Help(Command &cmd) const
{
    PrintHelp();
}

DCVM_ERROR DCVMDiskListTask::Execute(Command &cmd) const
{
    if (!cmd.empty())
    {
        return DCVM_ERR_BAD_PARAMS;
    }

    std::vector<dcvm_size_t> ids;
    DCVM_ERROR err = m_dcvm.ControlGetListOfCloudDiskIds(ids);
    if (DCVM_FAILED(err))
    {
        return err;
    }

    for(const auto &id : ids)
    {
        DCVM_INFO_TRACE("0x%X", ids);
    }

    return DCVM_ERR_SUCCESS;
}

void DCVMDiskListTask::PrintHelp() const
{
    DCVM_INFO_TRACE("Get list of all created cloud disks ids\n");
    DCVM_INFO_TRACE("Usage:");
    DCVM_INFO_TRACE("control disk list");
}

void DCVMDiskListTask::PrintError(const DCVMString_t &msg) const
{
    DCVM_INFO_TRACE("Error: %s", msg);
    DCVM_INFO_TRACE("Type HELP CONTROL DISK LIST for usage");
}

} // namespace dcvm_filemanager_cli