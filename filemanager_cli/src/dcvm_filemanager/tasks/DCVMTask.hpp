#ifndef DCVM_FILEMANAGER_CLI_TASKS_DCVMTASK_HPP_
#define DCVM_FILEMANAGER_CLI_TASKS_DCVMTASK_HPP_

#include <dcvm/DCVMLogger.h>
#include <dcvm/cpp/base/DCVMTypes.hpp>
#include <dcvm/cpp/base/MemoryBase.hpp>
#include "../dcvm_wrapper/DCVMWrapper.hpp"

namespace dcvm_filemanager_cli {

class DCVMTask;

using Command = dcvm::base::DCVMVector_t<dcvm::base::DCVMString_t>;
using PTask = dcvm::base::DCVMSharedPtr_t<DCVMTask>;

class DCVMTask : public dcvm::base::MemoryBase
{
public:
    static dcvm::base::DCVMString_t GetFirstCommand(Command &cmd);
public:
    virtual void Help(Command &cmd) const;
    virtual DCVM_ERROR Execute(Command &cmd) const;
protected:
    explicit DCVMTask(DCVMWrapper &pAm);
    virtual ~DCVMTask() noexcept = 0;
    virtual void PrintError(const dcvm::base::DCVMString_t &msg) const;
    virtual void PrintHelp() const = 0;
    virtual PTask Generate(Command &cmd) const;
protected:
    DCVMWrapper &m_dcvm;
};

} // namespace dcvm_filemanager_cli

#endif