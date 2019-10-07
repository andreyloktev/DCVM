#ifndef DCVM_DCVM_DCVMLOGGER_H_
#define DCVM_DCVM_DCVMLOGGER_H_

#include "DCVMError.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * Print error message
 * @param err error code.
 * @param pSrcFile source file name of the error.
 * @param line source file line of error
*/
typedef void (*DCVMPrintError)(enum DCVM_ERROR err, const char *pSrcFile, unsigned long line);

/*!
 * Pring debug information.
 * @param pFmt message(format string)
*/
typedef void (*DCVMPrintInfo)(const char *pFmt, ...);

/*!
 * Initialize or reinitialize logger.
 * @param pErrLogger pointer to print error function.
 * @param pInfoLogger pointer to print debug information function.
*/
void dcvm_InitLogger(DCVMPrintError pErrLogger, DCVMPrintInfo pInfoLogger);

#ifdef __cplusplus
};
#endif

extern DCVMPrintError   g_DCVMPrintError;
extern DCVMPrintInfo    g_DCVMPrintInfo;

#define DCVM_ERROR_TRACE(err)                           \
do                                                      \
{                                                       \
    if (g_DCVMPrintError)                               \
    {                                                   \
        g_DCVMPrintError((err), __FILE__, __LINE__);    \
    }                                                   \
}                                                       \
while (0);

#define DCVM_INFO_TRACE(Format, ...)                    \
do                                                      \
{                                                       \
    if (g_DCVMPrintInfo)                                \
    {                                                   \
        g_DCVMPrintInfo((Format), ##__VA_ARGS__);       \
    }                                                   \
}                                                       \
while (0);

#endif