#ifndef DCVM_PROVIDER_GOOGLE_H_
#define DCVM_PROVIDER_GOOGLE_H_

#include <dcvm/DCVMCloudProviderAPI.h>

#ifdef __cplusplus
extern "C" {
#endif

const dcvm_char_t* google_DCVMCloudGetProviderId(struct DCVMContext *pCtxt);

enum DCVM_ERROR google_DCVMCloudGetOAuthUri(dcvm_char_t **ppUrl, DCVMSystemAPI *pSystemApi, struct DCVMContext *pCtxt);

enum DCVM_ERROR google_DCVMCloudLogInWithOAuthCode(
    const dcvm_char_t           *pCode
    , struct DCVMCloudProvider  **ppCloudProvider
    , DCVMSystemAPI             *pSystemApi
    , struct DCVMContext        *pCtxt
);

enum DCVM_ERROR google_DCVMCloudLogInWithRefreshToken(
    const dcvm_char_t           *pRefreshToken
    , struct DCVMCloudProvider  **ppCloudProvider
    , DCVMSystemAPI             *pSystemApi
    , struct DCVMContext        *pCtxt
);

OAuthToken google_DCVMGetOAuthToken(struct DCVMCloudProvider *pCloudProvider, struct DCVMContext *pCtxt);

enum DCVM_ERROR google_DCVMCloudLogOut(struct DCVMCloudProvider *pCloudProvider, struct DCVMContext *pCtxt);

enum DCVM_ERROR google_DCVMCloudCreateFile(
    struct DCVMCloudProvider    *pCloudProvider
    , const dcvm_char_t         *pFileName
    , const DCVMFileInfo        *pFi
    , DCVMFileInfo              *pFileInfo
    , struct DCVMHandle         **ppFileHandle
    , struct DCVMContext        *pCtxt
);

enum DCVM_ERROR google_DCVMCloudOpenFile(
    struct DCVMCloudProvider    *pCloudProvider
    , const dcvm_char_t         *pFileName
    , DCVMFileInfo              *pFileInfo
    , struct DCVMHandle         **ppFileHandle
    , struct DCVMContext        *pCtxt
);

enum DCVM_ERROR google_DCVMCloudCloseFile(
    struct DCVMCloudProvider    *pCloudProvider
    , struct DCVMHandle         *pFileHandle
    , struct DCVMContext        *pCtxt
);

enum DCVM_ERROR google_DCVMCloudGetFileInfo(
    struct DCVMCloudProvider    *pCloudProvider
    , struct DCVMHandle         *pFileHandle
    , DCVMFileInfo              *pFileInfo
    , struct DCVMContext        *pCtxt
);

enum DCVM_ERROR google_DCVMCloudReadFile(
    struct DCVMCloudProvider    *pCloudProvider
    , struct DCVMHandle         *pFileHandle
    , dcvm_uint64_t             offset
    , dcvm_uint8_t              *pBuffer
    , dcvm_uint32_t             bufferSize
    , struct DCVMContext        *pCtxt
);

enum DCVM_ERROR google_DCVMCloudWriteFile(
    struct DCVMCloudProvider    *pCloudProvider
    , struct DCVMHandle         *pFileHandle
    , dcvm_uint64_t             offset
    , const dcvm_uint8_t        *pBuffer
    , dcvm_uint32_t             bufferSize
    , struct DCVMContext        *pCtxt
);

enum DCVM_ERROR google_DCVMCloudUnlinkFile(
    struct DCVMCloudProvider    *pCloudProvider
    , const dcvm_char_t         *pFileName
    , struct DCVMContext        *pCtxt
);

enum DCVM_ERROR google_DCVMCloudReadDirectory(
    struct DCVMCloudProvider    *pCloudProvider
    , struct DCVMEnumerator     *pEnumerator
    , DCVMFileInfo              *pFileInfo
    , const dcvm_uint32_t       fiCnt
    , struct DCVMContext        *pCtxt
);

enum DCVM_ERROR google_DCVMCloudMoveFile(
    struct DCVMCloudProvider    *pCloudProvider
    , const dcvm_char_t         *pSrcFile
    , struct DCVMHandle         *pSrcFileHandle
    , const dcvm_char_t         *pDstFileName
    , const dcvm_bool_t         bReplace
    , struct DCVMContext        *pCtxt
);

enum DCVM_ERROR google_DCVMCloudGetDiskInfo(
    struct DCVMCloudProvider    *pCloudProvider
    , DCVMCloudDiskInfo         *pDiskInfo
    , struct DCVMContext        *pCtxt
);

#ifdef __cplusplus
}
#endif

#endif