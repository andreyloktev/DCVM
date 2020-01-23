#include "dcvm_cloudstorage_stub.hpp"
#include "dcvm_utest_helper.hpp"
#include "DCVMCloudProvider.hpp"

using namespace dcvm_utests;

extern "C" 
{
    const dcvm_char_t* DCVMCloudGetProviderId_stub(struct DCVMContext *pCtxt) noexcept
    {
        DCVM_UNREFERENCED_PARAMETER(pCtxt);
        return g_pCloudProviderStubId;
    }

    DCVM_ERROR DCVMCloudGetOAuthUrl_stub(
        dcvm_char_t*            *ppUrl
        , DCVMSystemAPI         *pSystemApi
        , struct DCVMContext    *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        if ((nullptr == ppUrl) || (nullptr == pSystemApi))
        {
            return DCVM_ERR_BAD_PARAMS;
        }

        const auto BUFFER_SIZE = SIZEOF_DCVM_CHAR_T_STRING(g_pCloudProviderStubOAuthUri);
        auto pBuffer = static_cast<dcvm_char_t*>(pSystemApi->MemoryAllocate(BUFFER_SIZE, DCVM_TRUE));

        pSystemApi->MemoryCopy(pBuffer, BUFFER_SIZE, g_pCloudProviderStubOAuthUri, SIZEOF_DCVM_CHAR_T_STRING(g_pCloudProviderStubOAuthUri));

        *ppUrl = pBuffer;

        return DCVM_ERR_SUCCESS;
    }

    DCVM_ERROR DCVMCloudLogInWithOAuthCode_stub(
        const dcvm_char_t           *pCode
        , struct DCVMCloudProvider  **ppCloudProvider
        , DCVMSystemAPI             *pSystemApi
        , struct DCVMContext        *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        if ((nullptr == pCode) || (nullptr == ppCloudProvider) || (nullptr == pSystemApi))
        {
            return DCVM_ERR_BAD_PARAMS;
        }

        *ppCloudProvider = new DCVMCloudProvider(pSystemApi);
        return (*ppCloudProvider)->LogInWithOAuthCode(pCode);
    }

    DCVM_ERROR DCVMCloudLogInWithRefreshToken_stub(
        const dcvm_char_t           *pRefreshToken
        , struct DCVMCloudProvider  **ppCloudProvider
        , DCVMSystemAPI             *pSystemApi
        , struct DCVMContext        *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pRefreshToken);
        DCVM_UNREFERENCED_PARAMETER(ppCloudProvider);
        DCVM_UNREFERENCED_PARAMETER(pSystemApi);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    OAuthToken DCVMCloudGetOAuthToken_stub(struct DCVMCloudProvider *pCloudProvider, struct DCVMContext *pCtxt)
    {
        DCVM_UNREFERENCED_PARAMETER();
        DCVM_UNREFERENCED_PARAMETER();
        DCVM_UNREFERENCED_PARAMETER();

        return OAuthToken{nullptr, nullptr, nullptr};
    }

    DCVM_ERROR DCVMCloudLogOut_stub(struct DCVMCloudProvider *pCloudProvider, struct DCVMContext *pCtxt)
    {
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        if (nullptr != pCloudProvider)
        {
            delete pCloudProvider;
        }

        return DCVM_ERR_SUCCESS;
    }
    
    DCVM_ERROR DCVMCloudCreateFile_stub(
        struct DCVMCloudProvider    *pCloudProvider
        , const dcvm_char_t         *pFileName
        , const DCVMFileInfo        *pFi
        , DCVMFileInfo              *pFileInfo
        , struct DCVMHandle         **ppFileHandle
        , struct DCVMContext        *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pCloudProvider);
        DCVM_UNREFERENCED_PARAMETER(pFileName);
        DCVM_UNREFERENCED_PARAMETER(pFi);
        DCVM_UNREFERENCED_PARAMETER(pFileInfo);
        DCVM_UNREFERENCED_PARAMETER(ppFileHandle);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    DCVM_ERROR DCVMCloudOpenFile_stub(
        struct DCVMCloudProvider    *pCloudProvider
        , const dcvm_char_t         *pFileName
        , DCVMFileInfo              *pFileInfo
        , struct DCVMHandle         **ppFileHandle
        , struct DCVMContext        *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pCloudProvider);
        DCVM_UNREFERENCED_PARAMETER(pFileName);
        DCVM_UNREFERENCED_PARAMETER(pFileInfo);
        DCVM_UNREFERENCED_PARAMETER(ppFileHandle);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    DCVM_ERROR DCVMCloudCloseFile_stub(
        struct DCVMCloudProvider    *pCloudProvider
        , struct DCVMHandle         *pFileHandle
        , struct DCVMContext        *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pCloudProvider);
        DCVM_UNREFERENCED_PARAMETER(pFileHandle);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    DCVM_ERROR DCVMCloudGetFileInfo_stub(
        struct DCVMCloudProvider    *pCloudProvider
        , struct DCVMHandle         *pFileHandle
        , DCVMFileInfo              *pFileInfo
        , struct DCVMContext        *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pCloudProvider);
        DCVM_UNREFERENCED_PARAMETER(pFileHandle);
        DCVM_UNREFERENCED_PARAMETER(pFileInfo);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    DCVM_ERROR DCVMCloudReadFile_stub(
        struct DCVMCloudProvider    *pCloudProvider
        , struct DCVMHandle         *pFileHandle
        , dcvm_uint64_t             offset
        , dcvm_uint8_t              *pBuffer
        , dcvm_uint32_t             bufferSize
        , struct DCVMContext        *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pCloudProvider);
        DCVM_UNREFERENCED_PARAMETER(pFileHandle);
        DCVM_UNREFERENCED_PARAMETER(offset);
        DCVM_UNREFERENCED_PARAMETER(pBuffer);
        DCVM_UNREFERENCED_PARAMETER(bufferSize);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    DCVM_ERROR DCVMCloudWriteFile_stub(
        struct DCVMCloudProvider    *pCloudProvider
        , struct DCVMHandle         *pFileHandle
        , dcvm_uint64_t             offset
        , const dcvm_uint8_t        *pBuffer
        , dcvm_uint32_t             bufferSize
        , struct DCVMContext        *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pCloudProvider);
        DCVM_UNREFERENCED_PARAMETER(pFileHandle);
        DCVM_UNREFERENCED_PARAMETER(offset);
        DCVM_UNREFERENCED_PARAMETER(pBuffer);
        DCVM_UNREFERENCED_PARAMETER(bufferSize);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    DCVM_ERROR DCVMCloudUnlinkFile_stub(
        struct DCVMCloudProvider    *pCloudProvider
        , const dcvm_char_t         *pFileName
        , struct DCVMContext        *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pCloudProvider);
        DCVM_UNREFERENCED_PARAMETER(pFileName);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    DCVM_ERROR DCVMCloudReadDirectory_stub(
        struct DCVMCloudProvider    *pCloudProvider
        , struct DCVMEnumerator     *pEnumerator
        , DCVMFileInfo              *pFileInfo
        , const dcvm_uint32_t       fiCnt
        , struct DCVMContext        *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pCloudProvider);
        DCVM_UNREFERENCED_PARAMETER(pEnumerator);
        DCVM_UNREFERENCED_PARAMETER(pFileInfo);
        DCVM_UNREFERENCED_PARAMETER(fiCnt);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    DCVM_ERROR DCVMCloudMoveFile_stub(
        struct DCVMCloudProvider    *pCloudProvider
        , const dcvm_char_t         *pSrcFile
        , struct DCVMHandle         *pSrcFileHandle
        , const dcvm_char_t         *pDstFileName
        , const dcvm_bool_t         bReplace
        , struct DCVMContext        *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pCloudProvider);
        DCVM_UNREFERENCED_PARAMETER(pSrcFile);
        DCVM_UNREFERENCED_PARAMETER(pSrcFileHandle);
        DCVM_UNREFERENCED_PARAMETER(pDstFileName);
        DCVM_UNREFERENCED_PARAMETER(bReplace);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    DCVM_ERROR DCVMCloudGetDiskInfo_stub(
        struct DCVMCloudProvider    *pCloudProvider
        , DCVMCloudDiskInfo         *pDiskInfo
        , struct DCVMContext        *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        if ((nullptr == pDiskInfo) || (nullptr == pCloudProvider))
        {
            return DCVM_ERR_BAD_PARAMS;
        }

        return pCloudProvider->GetDiskInfo(*pDiskInfo);
    }
}