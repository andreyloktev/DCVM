#include <dcvm/provider/dcvm_google.h>
#include <dcvm/provider/DCVMCryptoHelper.hpp>

extern "C" {

static const dcvm_char_t *DCVM_GOOGLE_PROVIDER_ID = DCVM_TEXT("Google Inc.");

const dcvm_char_t* google_DCVMCloudGetProviderId(struct DCVMContext *pCtxt)
{
    DCVM_UNREFERENCED_PARAMETER(pCtxt);
    
    return DCVM_GOOGLE_PROVIDER_ID;
}

enum DCVM_ERROR google_DCVMCloudGetOAuthUri(dcvm_char_t **ppUrl, DCVMSystemAPI *pSystemApi, struct DCVMContext *pCtxt)
{
    if ((nullptr == ppUrl) || (nullptr == pSystemApi))
    {
        return DCVM_ERR_BAD_PARAMS;
    }


}

enum DCVM_ERROR google_DCVMCloudLogInWithOAuthCode(
    const dcvm_char_t           *pCode
    , struct DCVMCloudProvider  **ppCloudProvider
    , DCVMSystemAPI             *pSystemApi
    , struct DCVMContext        *pCtxt
)
{
    DCVM_UNREFERENCED_PARAMETER(pCode);
    DCVM_UNREFERENCED_PARAMETER(ppCloudProvider);
    DCVM_UNREFERENCED_PARAMETER(pSystemApi);
    DCVM_UNREFERENCED_PARAMETER(pCtxt);

    return DCVM_ERR_NOT_IMPLEMENTED;
}

enum DCVM_ERROR google_DCVMCloudLogInWithRefreshToken(
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

OAuthToken google_DCVMGetOAuthToken(struct DCVMCloudProvider *pCloudProvider, struct DCVMContext *pCtxt)
{
    DCVM_UNREFERENCED_PARAMETER(pCloudProvider);
    DCVM_UNREFERENCED_PARAMETER(pCtxt);

    return OAuthToken{};
}

enum DCVM_ERROR google_DCVMCloudLogOut(struct DCVMCloudProvider *pCloudProvider, struct DCVMContext *pCtxt)
{
    DCVM_UNREFERENCED_PARAMETER(pCloudProvider);
    DCVM_UNREFERENCED_PARAMETER(pCtxt);

    return DCVM_ERR_NOT_IMPLEMENTED;
}

enum DCVM_ERROR google_DCVMCloudCreateFile(
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

enum DCVM_ERROR google_DCVMCloudOpenFile(
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

enum DCVM_ERROR google_DCVMCloudCloseFile(
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

enum DCVM_ERROR google_DCVMCloudGetFileInfo(
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

enum DCVM_ERROR google_DCVMCloudReadFile(
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

enum DCVM_ERROR google_DCVMCloudWriteFile(
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

enum DCVM_ERROR google_DCVMCloudUnlinkFile(
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

enum DCVM_ERROR google_DCVMCloudReadDirectory(
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

enum DCVM_ERROR google_DCVMCloudMoveFile(
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

enum DCVM_ERROR google_DCVMCloudGetDiskInfo(
    struct DCVMCloudProvider    *pCloudProvider
    , DCVMCloudDiskInfo         *pDiskInfo
    , struct DCVMContext        *pCtxt
)
{
    DCVM_UNREFERENCED_PARAMETER(pCloudProvider);
    DCVM_UNREFERENCED_PARAMETER(pDiskInfo);
    DCVM_UNREFERENCED_PARAMETER(pCtxt);

    return DCVM_ERR_NOT_IMPLEMENTED;
}

} // extern "C"