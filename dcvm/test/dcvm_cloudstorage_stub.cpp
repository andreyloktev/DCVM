#include "dcvm_cloudstorage_stub.hpp"

namespace {

constexpr const dcvm_char_t *pCloudStorageStubId = DCVM_TEXT("CloudStorageStub");

}

extern "C" 
{
    const dcvm_char_t* DCVMCloudGetCloudDiskId_stub(struct DCVMContext *pCtxt) noexcept
    {
        DCVM_UNREFERENCED_PARAMETER(pCtxt);
        return pCloudStorageStubId;
    }

    DCVM_ERROR DCVMCloudGetOAuthUrl_stub(
        dcvm_char_t*            *ppUrl
        , DCVMSystemAPI         *pSystemApi
        , struct DCVMContext    *pCtxt
    ) noexcept
    {
        DCVM_UNREFERENCED_PARAMETER(ppUrl);
        DCVM_UNREFERENCED_PARAMETER(pSystemApi);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    DCVM_ERROR DCVMCloudLogInWithOAuthCode_stub(
        const dcvm_char_t       *pCode
        , struct DCVMCloudDisk  **ppCloudDisk
        , DCVMSystemAPI         *pSystemApi
        , struct DCVMContext    *pCtxt
    ) noexcept
    {
        DCVM_UNREFERENCED_PARAMETER(pCode);
        DCVM_UNREFERENCED_PARAMETER(ppCloudDisk);
        DCVM_UNREFERENCED_PARAMETER(pSystemApi);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    DCVM_ERROR DCVMCloudLogInWithRefreshToken_stub(
        const dcvm_char_t       *pRefreshToken
        , struct DCVMCloudDisk  **ppCloudDisk
        , DCVMSystemAPI         *pSystemApi
        , struct DCVMContext    *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pRefreshToken);
        DCVM_UNREFERENCED_PARAMETER(ppCloudDisk);
        DCVM_UNREFERENCED_PARAMETER(pSystemApi);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    OAuthToken DCVMGetOAuthToken_stub(struct DCVMCloudDisk *pCloudDisk, struct DCVMContext *pCtxt)
    {
        DCVM_UNREFERENCED_PARAMETER();
        DCVM_UNREFERENCED_PARAMETER();
        DCVM_UNREFERENCED_PARAMETER();

        return OAuthToken{nullptr, nullptr, nullptr};
    }

    DCVM_ERROR DCVMCloudLogOut_stub(struct DCVMCloudDisk *pCloudDisk, struct DCVMContext *pCtxt)
    {
        DCVM_UNREFERENCED_PARAMETER(pCloudDisk);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }
    
    DCVM_ERROR DCVMCloudCreateFile_stub(
        struct DCVMCloudDisk        *pCloudDisk
        , const dcvm_char_t         *pFileName
        , const DCVMFileInfo        *pFi
        , DCVMFileInfo              *pFileInfo
        , struct DCVMHandle         **ppFileHandle
        , struct DCVMContext        *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pCloudDisk);
        DCVM_UNREFERENCED_PARAMETER(pFileName);
        DCVM_UNREFERENCED_PARAMETER(pFi);
        DCVM_UNREFERENCED_PARAMETER(pFileInfo);
        DCVM_UNREFERENCED_PARAMETER(ppFileHandle);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    DCVM_ERROR DCVMCloudOpenFile_stub(
        struct DCVMCloudDisk    *pCloudDisk
        , const dcvm_char_t     *pFileName
        , DCVMFileInfo          *pFileInfo
        , struct DCVMHandle     **ppFileHandle
        , struct DCVMContext    *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pCloudDisk);
        DCVM_UNREFERENCED_PARAMETER(pFileName);
        DCVM_UNREFERENCED_PARAMETER(pFileInfo);
        DCVM_UNREFERENCED_PARAMETER(ppFileHandle);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    DCVM_ERROR DCVMCloudCloseFile_stub(
        struct DCVMCloudDisk    *pCloudDisk
        , struct DCVMHandle     *pFileHandle
        , struct DCVMContext    *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pCloudDisk);
        DCVM_UNREFERENCED_PARAMETER(pFileHandle);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    DCVM_ERROR DCVMCloudGetFileInfo_stub(
        struct DCVMCloudDisk    *pCloudDisk
        , struct DCVMHandle     *pFileHandle
        , DCVMFileInfo          *pFileInfo
        , struct DCVMContext    *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pCloudDisk);
        DCVM_UNREFERENCED_PARAMETER(pFileHandle);
        DCVM_UNREFERENCED_PARAMETER(pFileInfo);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    DCVM_ERROR DCVMCloudReadFile_stub(
        struct DCVMCloudDisk    *pCloudDisk
        , struct DCVMHandle     *pFileHandle
        , dcvm_uint64_t         offset
        , dcvm_uint8_t          *pBuffer
        , dcvm_uint32_t         bufferSize
        , struct DCVMContext    *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pCloudDisk);
        DCVM_UNREFERENCED_PARAMETER(pFileHandle);
        DCVM_UNREFERENCED_PARAMETER(offset);
        DCVM_UNREFERENCED_PARAMETER(pBuffer);
        DCVM_UNREFERENCED_PARAMETER(bufferSize);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    DCVM_ERROR DCVMCloudWriteFile_stub(
        struct DCVMCloudDisk    *pCloudDisk
        , struct DCVMHandle     *pFileHandle
        , dcvm_uint64_t         offset
        , const dcvm_uint8_t    *pBuffer
        , dcvm_uint32_t         bufferSize
        , struct DCVMContext    *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pCloudDisk);
        DCVM_UNREFERENCED_PARAMETER(pFileHandle);
        DCVM_UNREFERENCED_PARAMETER(offset);
        DCVM_UNREFERENCED_PARAMETER(pBuffer);
        DCVM_UNREFERENCED_PARAMETER(bufferSize);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    DCVM_ERROR DCVMCloudUnlinkFile_stub(
        struct DCVMCloudDisk    *pCloudDisk
        , const dcvm_char_t     *pFileName
        , struct DCVMContext    *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pCloudDisk);
        DCVM_UNREFERENCED_PARAMETER(pFileName);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    DCVM_ERROR DCVMCloudReadDirectory_stub(
        struct DCVMCloudDisk    *pCloudDisk
        , struct DCVMEnumerator *pEnumerator
        , DCVMCloudGetFileInfo  *pFileInfo
        , const dcvm_uint32_t   fiCnt
        , struct DCVMContext    *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pCloudDisk);
        DCVM_UNREFERENCED_PARAMETER(pEnumerator);
        DCVM_UNREFERENCED_PARAMETER(pFileInfo);
        DCVM_UNREFERENCED_PARAMETER(fiCnt);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    DCVM_ERROR DCVMCloudMoveFile_stub(
        struct DCVMCloudDisk    *pCloudDisk
        , const dcvm_char_t     *pSrcFile
        , struct DCVMHandle     *pSrcFileHandle
        , const dcvm_char_t     *pDstFileName
        , const dcvm_bool_t     bReplace
        , struct DCVMContext    *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pCloudDisk);
        DCVM_UNREFERENCED_PARAMETER(pSrcFile);
        DCVM_UNREFERENCED_PARAMETER(pSrcFileHandle);
        DCVM_UNREFERENCED_PARAMETER(pDstFileName);
        DCVM_UNREFERENCED_PARAMETER(bReplace);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    DCVM_ERROR DCVMCloudGetDiskInfo_stub(
        struct DCVMCloudDisk    *pCloudDisk
        , DCVMCloudDiskInfo     pDiskInfo
        , struct DCVMContext    *pCtxt
    )
    {
        DCVM_UNREFERENCED_PARAMETER(pCloudDisk);
        DCVM_UNREFERENCED_PARAMETER(pDiskInfo);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);

        return DCVM_ERR_NOT_IMPLEMENTED;
    }
}