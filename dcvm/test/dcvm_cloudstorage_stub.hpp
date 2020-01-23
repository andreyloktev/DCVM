#ifndef DCVM_TEST_CLOUDSTORAGE_STUB_HPP_
#define DCVM_TEST_CLOUDSTORAGE_STUB_HPP_

#include <dcvm/DCVMCloudProviderAPI.h>

constexpr const dcvm_char_t *g_pCloudProviderStubId         = DCVM_TEXT("CloudStorageStub");
constexpr const dcvm_char_t *g_pCloudProviderStubOAuthUri   = DCVM_TEXT("http://localhost/dcvm/oauth");
constexpr const dcvm_char_t *g_pCloudStubOAauthCode1        = DCVM_TEXT("OAauthCode1");
constexpr const dcvm_char_t *g_pCloudStubOAauthCode2        = DCVM_TEXT("OAauthCode2");
constexpr const dcvm_char_t *g_pCloudStubUserName           = DCVM_TEXT("StubUser");

extern "C" 
{
    const dcvm_char_t* DCVMCloudGetProviderId_stub(struct DCVMContext *pCtxt);

    DCVM_ERROR DCVMCloudGetOAuthUrl_stub(dcvm_char_t **ppUrl, DCVMSystemAPI *pSystemApi, struct DCVMContext *pCtxt);

    DCVM_ERROR DCVMCloudLogInWithOAuthCode_stub(
        const dcvm_char_t           *pCode
        , struct DCVMCloudProvider  **ppCloudProvider
        , DCVMSystemAPI             *pSystemApi
        , struct DCVMContext        *pCtxt
    );

    DCVM_ERROR DCVMCloudLogInWithRefreshToken_stub(
        const dcvm_char_t           *pRefreshToken
        , struct DCVMCloudProvider  **ppCloudProvider
        , DCVMSystemAPI             *pSystemApi
        , struct DCVMContext        *pCtxt
    );

    OAuthToken DCVMCloudGetOAuthToken_stub(struct DCVMCloudProvider *pCloudProvider, struct DCVMContext *pCtxt);

    DCVM_ERROR DCVMCloudLogOut_stub(struct DCVMCloudProvider *pCloudProvider, struct DCVMContext *pCtxt);
    
    DCVM_ERROR DCVMCloudCreateFile_stub(
        struct DCVMCloudProvider        *pCloudProvider
        , const dcvm_char_t             *pFileName
        , const DCVMFileInfo            *pFi
        , DCVMFileInfo                  *pFileInfo
        , struct DCVMHandle             **ppFileHandle
        , struct DCVMContext            *pCtxt
    );

    DCVM_ERROR DCVMCloudOpenFile_stub(
        struct DCVMCloudProvider    *pCloudProvider
        , const dcvm_char_t         *pFileName
        , DCVMFileInfo              *pFileInfo
        , struct DCVMHandle         **ppFileHandle
        , struct DCVMContext        *pCtxt
    );

    DCVM_ERROR DCVMCloudCloseFile_stub(
        struct DCVMCloudProvider    *pCloudProvider
        , struct DCVMHandle         *pFileHandle
        , struct DCVMContext        *pCtxt
    );

    DCVM_ERROR DCVMCloudGetFileInfo_stub(
        struct DCVMCloudProvider    *pCloudProvider
        , struct DCVMHandle         *pFileHandle
        , DCVMFileInfo              *pFileInfo
        , struct DCVMContext        *pCtxt
    );

    DCVM_ERROR DCVMCloudReadFile_stub(
        struct DCVMCloudProvider    *pCloudProvider
        , struct DCVMHandle         *pFileHandle
        , dcvm_uint64_t             offset
        , dcvm_uint8_t              *pBuffer
        , dcvm_uint32_t             bufferSize
        , struct DCVMContext        *pCtxt
    );

    DCVM_ERROR DCVMCloudWriteFile_stub(
        struct DCVMCloudProvider    *pCloudProvider
        , struct DCVMHandle         *pFileHandle
        , dcvm_uint64_t             offset
        , const dcvm_uint8_t        *pBuffer
        , dcvm_uint32_t             bufferSize
        , struct DCVMContext        *pCtxt
    );

    DCVM_ERROR DCVMCloudUnlinkFile_stub(
        struct DCVMCloudProvider    *pCloudProvider
        , const dcvm_char_t         *pFileName
        , struct DCVMContext        *pCtxt
    );

    DCVM_ERROR DCVMCloudReadDirectory_stub(
        struct DCVMCloudProvider    *pCloudProvider
        , struct DCVMEnumerator     *pEnumerator
        , DCVMFileInfo              *pFileInfo
        , const dcvm_uint32_t       fiCnt
        , struct DCVMContext        *pCtxt
    );

    DCVM_ERROR DCVMCloudMoveFile_stub(
        struct DCVMCloudProvider    *pCloudProvider
        , const dcvm_char_t         *pSrcFile
        , struct DCVMHandle         *pSrcFileHandle
        , const dcvm_char_t         *pDstFileName
        , const dcvm_bool_t         bReplace
        , struct DCVMContext        *pCtxt
    );

    DCVM_ERROR DCVMCloudGetDiskInfo_stub(
        struct DCVMCloudProvider    *pCloudProvider
        , DCVMCloudDiskInfo         *pDiskInfo
        , struct DCVMContext        *pCtxt
    );
}

#endif