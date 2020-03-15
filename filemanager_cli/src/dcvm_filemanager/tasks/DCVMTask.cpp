#include <algorithm>
#include "DCVMTask.hpp"

namespace dcvm_filemanager_cli {

template<typename T>
static T ToLower(const T ch) noexcept
{
    return ch;
}

template<>
static char ToLower<char>(const char ch) noexcept
{
    return ::tolower(ch);
}

template<>
static wchar_t ToLower<wchar_t>(const wchar_t ch) noexcept
{
    return ::towlower(ch);
}

DCVMTask::DCVMTask(DCVMWrapper &wrapper)  : m_dcvm(wrapper)
{
}

DCVMTask::~DCVMTask() noexcept
{
}

void DCVMTask::Help(Command &cmd) const
{
    auto pTask = Generate(cmd);
    if (nullptr != pTask)
    {
        pTask->Help(cmd);
        return;
    }

    PrintHelp();
}

DCVM_ERROR DCVMTask::Execute(Command &cmd) const
{
    auto pTask = Generate(cmd);
    if (nullptr == pTask)
    {
        PrintHelp();
        return DCVM_ERR_SUCCESS;
    }

    return pTask->Execute(cmd);
}

PTask DCVMTask::Generate(Command &cmd) const
{
    return nullptr;
}

void DCVMTask::PrintError(const dcvm::base::DCVMString_t&) const
{
    // Nothing to do
}

dcvm::base::DCVMString_t DCVMTask::GetFirstCommand(Command &cmd)
{
    if (cmd.empty())
    {
        return dcvm::base::DCVMString_t();
    }

    dcvm::base::DCVMString_t licenseCmd = cmd[0];
    cmd.erase(cmd.begin());

    std::transform(licenseCmd.begin(), licenseCmd.end(), licenseCmd.begin(), ToLower<dcvm_char_t>);
    
    return licenseCmd;
}

} // namespace dcvm_filemanager_cli