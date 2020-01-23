#ifndef DCVM_TEST_DCVM_UTEST_HELPER_HPP_
#define DCVM_TEST_DCVM_UTEST_HELPER_HPP_

#include <dcvm/dcvm.h>
#include <memory>
#include <string>
#include "dcvm_systemapi_test.h"
#include "dcvm_cloudstorage_stub.hpp"

namespace dcvm_utests
{

#if _WIN32
using DCVMUtestString_t = std::wstring;
#else
using DCVMUtestString_t = std::string;
#endif

inline DCVMSystemAPI GetDCVMSystemApi() noexcept
{
    return DCVMSystemAPI
    {
        DCVMMemoryAlloc_test
        , DCVMMemoryFree_test
        , DCVMMemorySet_test
        , DCVMMemoryCopy_test
        , DCVMMemoryCompare_test
        , DCVMSendHttpRequest_test
    };
}

inline DCVMCloudProviderAPI GetDCVMCloudProviderApi() noexcept
{
    return DCVMCloudProviderAPI
    {
        DCVMCloudGetProviderId_stub
        , DCVMCloudGetOAuthUrl_stub
        , DCVMCloudLogInWithOAuthCode_stub
        , DCVMCloudLogInWithRefreshToken_stub
        , DCVMCloudLogOut_stub
        , DCVMCloudGetOAuthToken_stub
        , DCVMCloudCreateFile_stub
        , DCVMCloudOpenFile_stub
        , DCVMCloudCloseFile_stub
        , DCVMCloudGetFileInfo_stub
        , DCVMCloudUnlinkFile_stub
        , DCVMCloudReadFile_stub
        , DCVMCloudWriteFile_stub
        , DCVMCloudReadDirectory_stub
        , DCVMCloudMoveFile_stub
        , DCVMCloudGetDiskInfo_stub
    };
}

struct DCVMDeleter final
{
    void operator()(DCVM *p) noexcept
    {
        if (p)
        {
            dcvm_Release(p, nullptr);
        }
    }
};

using PDCVM = std::unique_ptr<DCVM, DCVMDeleter>;

inline PDCVM CreateDCVM()
{
    DCVM *pDCVM = nullptr;

    dcvm_Init(GetDCVMSystemApi(), &pDCVM, nullptr);
    return PDCVM(pDCVM);
}

inline dcvm_size_t SIZEOF_DCVM_CHAR_T_STRING(const dcvm_char_t *pStr)
{
    return DCVMUtestString_t(pStr).length() * sizeof(dcvm_char_t) + sizeof(dcvm_char_t);
}

} // namespace dcvm_utests

#endif