
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdarg.h>

#include "dcvm_filemanager/tasks/DCVMHelpTask.hpp"
#include "dcvm_filemanager/tasks/control/DCVMControlTask.hpp"

using namespace dcvm_filemanager_cli;

#ifdef _WIN32
#define DCVMCout std::wcout
#define DCVMCin std::wcin
#else
#define DCVMCout std::cout
#define DCVMCin std::cin
#endif


DCVM_ERROR Execute(DCVMWrapper &dcvm, Command &cmd);
Command GenerateCommands(const dcvm::base::DCVMString_t &cmd);

void DCVMCliPrintError(enum DCVM_ERROR err, const char *pSrcFile, unsigned long line);
void DCVMCliPrintInfo(const dcvm_char_t *pFmt, ...);

void main(int argc, dcvm_char_t **ppArgv)
{
    dcvm_InitLogger(DCVMCliPrintError, DCVMCliPrintInfo);

    DCVMWrapper dcvm;

    dcvm::base::DCVMString_t cmdStr;
    DCVMCout << DCVM_TEXT("DCVM> ");
    while (std::getline(DCVMCin, cmdStr))
    {
        if (cmdStr.empty())
        {
            std::cout << "\nDCVM> ";
            continue;
        }
        else if (DCVM_TEXT("exit") == cmdStr)
        {
            break;
        }

        auto err = Execute(dcvm, GenerateCommands(cmdStr));
        if (DCVM_FAILED(err))
        {
            DCVM_INFO_TRACE("Error: 0x%X", err);
        }

        DCVMCout << DCVM_TEXT("DCVM> ");
    }
}

void DCVMCliPrintError(enum DCVM_ERROR err, const char *pSrcFile, unsigned long line)
{
    std::cout << "Error code: 0x" << std::hex << err << "; Src file: " << pSrcFile << "; Line " << std::dec << line << std::endl;
}

void DCVMCliPrintInfo(const dcvm_char_t *pFmt, ...)
{
    static const unsigned int size = 1024 * 10;

    va_list arg;
    va_start(arg, pFmt);
    dcvm_char_t msg[size] = {};
#ifdef _WIN32
    vswprintf(msg, size, pFmt, arg);
#else
    vsnprintf(msg, size, pFmt, arg);
#endif
    va_end(arg);

#ifdef _WIN32
    std::wcout << L"DCVM: " << msg << std::endl;
#else
    std::cout << "DCVM: " << msg << std::endl;
#endif
}

DCVM_ERROR Execute(DCVMWrapper &dcvm, Command &cmd)
{
    auto mainCmd = DCVMTask::GetFirstCommand(cmd);
    if (mainCmd.empty())
    {
        return DCVM_ERR_BAD_PARAMS;
    }

    PTask pHelpTask = std::make_shared<DCVMHelpTask>(dcvm);

    if (DCVM_TEXT("help") == mainCmd)
    {
        return pHelpTask->Execute(cmd);
    }
    else if (DCVM_TEXT("control") == mainCmd)
    {
        return std::make_shared<DCVMControlTask>(dcvm)->Execute(cmd);
    }

    return pHelpTask->Execute(Command{});
}

Command GenerateCommands(const dcvm::base::DCVMString_t &cmd)
{
    if (cmd.empty())
    {
        return {};
    }

    bool bDoubleQuotes = false;
    dcvm::base::DCVMString_t::size_type fromPos = 0;
    Command args{};

    dcvm::base::DCVMString_t::size_type i = 0;
    for(; i < cmd.length(); i++)
    {
        if (!bDoubleQuotes && DCVM_TEXT('\x20') == cmd[i])
        {
            args.emplace_back(cmd.substr(fromPos, i - fromPos));
            fromPos = i + 1; // i is space; i+1 points to next charcter.
        }
        else if (DCVM_TEXT('\x22') == cmd[i])
        {
            if (bDoubleQuotes)
            {
                args.emplace_back(cmd.substr(fromPos, i - fromPos));
                fromPos = i + 2;// i is double quotes; i+ 1 is space; i + 2 points to next charcter.
                i++;
                bDoubleQuotes = false;
                continue;
            }

            bDoubleQuotes = true;
            fromPos++;
        }
    }

    args.emplace_back(cmd.substr(fromPos, i - fromPos)); // last command

    return args;
}