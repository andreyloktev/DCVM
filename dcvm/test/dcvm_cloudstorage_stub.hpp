#ifndef DCVM_CLOUDSTORAGE_STUB_HPP_
#define DCVM_CLOUDSTORAGE_STUB_HPP_

#include <dcvm/DCVMCloudDiskAPI.h>

extern "C" 
{
    const dcvm_char_t* DCVMCloudGetCloudDiskId_stub(struct DCVMContext *pCtxt);

    DCVM_ERROR DCVMCloudGetOAuthUrl_stub(dcvm_char_t **ppUrl, DCVMSystemAPI *pSystemApi, struct DCVMContext *pCtxt);

    DCVM_ERROR DCVMCloudLogInWithOAuthCode_stub(
        const dcvm_char_t       *pCode
        , struct DCVMCloudDisk  **ppCloudDisk
        , DCVMSystemAPI         *pSystemApi
        , struct DCVMContext    *pCtxt
    );

    DCVM_ERROR DCVMCloudLogInWithRefreshToken_stub(
        const dcvm_char_t       *pRefreshToken
        , struct DCVMCloudDisk  **ppCloudDisk
        , DCVMSystemAPI         *pSystemApi
        , struct DCVMContext    *pCtxt
    );

    OAuthToken DCVMGetOAuthToken_stub(struct DCVMCloudDisk *pCloudDisk, struct DCVMContext *pCtxt);

    DCVM_ERROR DCVMCloudLogOut_stub(struct DCVMCloudDisk *pCloudDisk, struct DCVMContext *pCtxt);
    
    DCVM_ERROR DCVMCloudCreateFile_stub(
        struct DCVMCloudDisk        *pCloudDisk
        , const dcvm_char_t         *pFileName
        , const DCVMFileInfo        *pFi
        , DCVMFileInfo              *pFileInfo
        , struct DCVMHandle         **ppFileHandle
        , struct DCVMContext        *pCtxt
    );

    DCVM_ERROR DCVMCloudOpenFile_stub(
        struct DCVMCloudDisk    *pCloudDisk
        , const dcvm_char_t     *pFileName
        , DCVMFileInfo          *pFileInfo
        , struct DCVMHandle     **ppFileHandle
        , struct DCVMContext    *pCtxt
    );

    DCVM_ERROR DCVMCloudCloseFile_stub(
        struct DCVMCloudDisk    *pCloudDisk
        , struct DCVMHandle     *pFileHandle
        , struct DCVMContext    *pCtxt
    );

    DCVM_ERROR DCVMCloudGetFileInfo_stub(
        struct DCVMCloudDisk    *pCloudDisk
        , struct DCVMHandle     *pFileHandle
        , DCVMFileInfo          *pFileInfo
        , struct DCVMContext    *pCtxt
    );

    DCVM_ERROR DCVMCloudReadFile_stub(
        struct DCVMCloudDisk    *pCloudDisk
        , struct DCVMHandle     *pFileHandle
        , dcvm_uint64_t         offset
        , dcvm_uint8_t          *pBuffer
        , dcvm_uint32_t         bufferSize
        , struct DCVMContext    *pCtxt
    );

    DCVM_ERROR DCVMCloudWriteFile_stub(
        struct DCVMCloudDisk    *pCloudDisk
        , struct DCVMHandle     *pFileHandle
        , dcvm_uint64_t         offset
        , const dcvm_uint8_t    *pBuffer
        , dcvm_uint32_t         bufferSize
        , struct DCVMContext    *pCtxt
    );

    DCVM_ERROR DCVMCloudUnlinkFile_stub(
        struct DCVMCloudDisk    *pCloudDisk
        , const dcvm_char_t     *pFileName
        , struct DCVMContext    *pCtxt
    );

    DCVM_ERROR DCVMCloudReadDirectory_stub(
        struct DCVMCloudDisk    *pCloudDisk
        , struct DCVMEnumerator *pEnumerator
        , DCVMCloudGetFileInfo  *pFileInfo
        , const dcvm_uint32_t   fiCnt
        , struct DCVMContext    *pCtxt
    );

    DCVM_ERROR DCVMCloudMoveFile_stub(
        struct DCVMCloudDisk    *pCloudDisk
        , const dcvm_char_t     *pSrcFile
        , struct DCVMHandle     *pSrcFileHandle
        , const dcvm_char_t     *pDstFileName
        , const dcvm_bool_t     bReplace
        , struct DCVMContext    *pCtxt
    );

    DCVM_ERROR DCVMCloudGetDiskInfo_stub(
        struct DCVMCloudDisk    *pCloudDisk
        , DCVMCloudDiskInfo     pDiskInfo
        , struct DCVMContext    *pCtxt
    );
}

#endif