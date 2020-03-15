#include <functional>
#include "DCVMDiskInfoTask.hpp"

namespace dcvm_filemanager_cli {

DCVMDiskInfoTask::DCVMDiskInfoTask(DCVMWrapper &dcvm) : DCVMTask(dcvm)
{
}

void DCVMDiskInfoTask::Help(Command &cmd) const
{
    PrintHelp();
}

DCVM_ERROR DCVMDiskInfoTask::Execute(Command &cmd) const
{
    if (cmd.empty())
    {
        PrintHelp();
        return DCVM_ERR_SUCCESS;
    }

    if (1 != cmd.size())
    {
        return DCVM_ERR_BAD_PARAMS;
    }

    dcvm_size_t diskId = 0;
    try
    {
        diskId = std::stoll(cmd[0].c_str(), nullptr, 0);
    }
    catch(const std::exception&)
    {
        return DCVM_ERR_BAD_PARAMS;
    }
    

    DCVMCloudDiskInfo info{};
    DCVM_ERROR err = m_dcvm.ControlGetCloudDiskInformation(diskId, info);
    if (DCVM_FAILED(err))
    {
        return err;
    }

    std::function<void(const DCVMCloudDiskInfo&, int)> PrintDiskInfo = [=](const DCVMCloudDiskInfo &info, int indent) -> void
    {
        DCVM_INFO_TRACE("%*sProvider:       %s", indent, DCVM_TEXT(""), info.providerInfo.id);
        DCVM_INFO_TRACE("%*sUser:           %s", indent, DCVM_TEXT(""), info.userInfo.name);
        DCVM_INFO_TRACE("%*Max file size:   %lld", indent, DCVM_TEXT(""), info.maxFileSize);
        DCVM_INFO_TRACE("%*Total space:     %lld", indent, DCVM_TEXT(""), info.totalSpace);
        DCVM_INFO_TRACE("%*Used space:      %lld", indent, DCVM_TEXT(""), info.usedSpace);

        for(const auto &child : info.children)
        {
            PrintDiskInfo(child, indent++);
        }
    };

    PrintDiskInfo(info, 0);

    return DCVM_ERR_SUCCESS;
}

void DCVMDiskInfoTask::PrintHelp() const
{
    DCVM_INFO_TRACE("Get information about cloud disk.\n");
    DCVM_INFO_TRACE("Usage:");
    DCVM_INFO_TRACE("control disk <id>\n");
    DCVM_INFO_TRACE("Parameters:");
    DCVM_INFO_TRACE("  id -- cloud disk id.");
}

void DCVMDiskInfoTask::PrintError(const dcvm::base::DCVMString_t &msg) const
{
    DCVM_INFO_TRACE("Error: %s", msg);
    DCVM_INFO_TRACE("Type HELP CONTROL DISK INFO for usage");
}

} // namespace dcvm_filemanager_cli