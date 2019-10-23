#ifndef DCVM_DCVM_CLOUDDISKAPI_H_
#define DCVM_DCVM_CLOUDDISKAPI_H_

#include "DCVMTypes.h"
#include "DCVMError.h"
#include "dcvm_system.h"

typedef struct OAuthToken
{
    const dcvm_char_t *pAccessToken;
    const dcvm_char_t *pRefreshToken;
    const dcvm_char_t *pTokenType;
};

enum DCVMFileType
{
    File
    , Dirctory
    , SymbolicLink
};

#define FILE_NAME_SIZE 256
#define FILE_FLAG_READ_ONLY 0x00000001

typedef struct _DCVMFileInfo
{
    enum DCVMFileType   type;
    dcvm_char_t         name[FILE_NAME_SIZE];
    dcvm_uint32_t       flags;
    dcvm_uint64_t       fileSize;
    dcvm_uint64_t       creationTime;
    dcvm_uint64_t       modificationTime;
} DCVMFileInfo;

typedef struct _DCVMCloudDiskInfo
{
    dcvm_uint64_t maxFileSize;
    dcvm_uint64_t totalSpace;
    dcvm_uint64_t usedSpace;
} DCVMCloudDiskInfo;

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * Get unique client identifier. It's may be just a client name. For example, "Yandex Disk".
 * @warning It's must have to implement function.
 * @return unique client identification.
*/
typedef const dcvm_char_t (*DCVMCloudGetCloudDiskId)(struct DCVMContext *pCtxt);

/*!
 * @brief Get OAuth url.
 * @param [out] ppUrl url.
 * @param [in] pSystemApi set of System API function.
 * @param [in] pCtxt system context(optional).
 * @return Error code.
*/
typedef enum DCVM_ERROR (*DCVMCloudGetOAuthUrl)(dcvm_char_t **ppUrl, DCVMSystemAPI *pSystemApi, struct DCVMContext *pCtxt);

/*!
 * @brief Create an instance of DCVMCloudDisk(make log in operation by OAuth codes).
 * @param [in] pCode OAuth code.
 * @param [out] ppCloudDisk an instance of DCVMCloudDisk.
 * @param [in] pSystemApi set of System API function.
 * @param [in] pCtxt system context(optional).
 * @return Error code.
*/ 
typedef enum DCVM_ERROR (*DCVMCloudLogInWithOAuthCode)(
    const dcvm_char_t       *pCode
    , struct DCVMCloudDisk  **ppCloudDisk
    , DCVMSystemAPI         *pSystemApi
    , struct DCVMContext    *pCtxt
);

/*!
 * @brief Create an instance of DCVMCloudDisk(make log in operation by OAuth refresh token).
 * @param [in] pRefreshToken OAuth refresh token.
 * @param [out] ppCloudDisk an instance of DCVMCloudDisk.
 * @param [in] pSystemApi set of System API function.
 * @param [in] pCtxt system context(optional).
 * @return Error code.
*/ 
typedef enum DCVM_ERROR (*DCVMCloudLogInWithRefreshToken)(
    const dcvm_char_t       *pRefreshToken
    , struct DCVMCloudDisk  **ppCloudDisk
    , DCVMSystemAPI         *pSystemApi
    , struct DCVMContext    *pCtxt
);

/*!
 * @brief Get OAuthToken(access token, refresh token and token type)
 * @param [in] pCloudDisk an instance of DCVMCloudDisk.
 * @param [in] pCtxt system context(optional).
 * @return OAuthToken object
*/
typedef OAuthToken (*DCVMGetOAuthToken)(struct DCVMCloudDisk *pCloudDisk, struct DCVMContext *pCtxt);

/*!
 * @brief Log out. Release a DCVMCloudDisk instance created after LogIn operation.
 * @param [in] pCloudDisk DCVMCloudDisk instance.
 * @param [in] pCtxt system context(optional).
 * @retrun Error code.
*/
typedef enum DCVM_ERROR (*DCVMCloudLogOut)(struct DCVMCloudDisk *pCloudDisk, struct DCVMContext *pCtxt);

/*!
 * @brief Create a file or directory.
 * @param [in] pCloudDisk an instance of DCVMCloudDisk.
 * @param [in] pFileName file to create.
 * @param [in] pFi information about a creating file.
 * @param [out] pFileInfo information about created file.
 * @param [out] ppFileHandle created file desciptor.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudCreateFile)(
    struct DCVMCloudDisk        *pCloudDisk
    , const dcvm_char_t         *pFileName
    , const DCVMFileInfo        *pFi
    , DCVMFileInfo              *pFileInfo
    , struct DCVMHandle         **ppFileHandle
    , struct DCVMContext        *pCtxt
);

/*!
 * @brief Open a file or directory.
 * @param [in] pCloudDisk an instance of DCVMCloudDisk.
 * @param [in] pFileName file to open.
 * @param [out] pFileInfo information about opened file.
 * @param [out] ppFileHandle opened file descriptor.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudOpenFile)(
    struct DCVMCloudDisk    *pCloudDisk
    , const dcvm_char_t     *pFileName
    , DCVMFileInfo          *pFileInfo
    , struct DCVMHandle     **ppFileHandle
    , struct DCVMContext    *pCtxt
);

/*!
 * @brief Close a file or directory.
 * @param [in] pCloudDisk an instance of DCVMCloudDisk.
 * @param [in] pFileHandle opened file descriptor.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudCloseFile)(
    struct DCVMCloudDisk    *pCloudDisk
    , struct DCVMHandle     *pFileHandle
    , struct DCVMContext    *pCtxt
);

/*!
 * @brief Get information about a file or directory.
 * @param [in] pCloudDisk an instance of DCVMCloudDisk.
 * @param [in] pFileHandle opened file descriptor.
 * @param [out] pFileInfo information about opened file.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudGetFileInfo)(
    struct DCVMCloudDisk    *pCloudDisk
    , struct DCVMHandle     *pFileHandle
    , DCVMFileInfo          *pFileInfo
    , struct DCVMContext    *pCtxt
);

/*!
 * @brief Read a file.
 * @param [in] pCloudDisk an instance of DCVMCloudDisk.
 * @param [in] pFileHandle opened file descriptor.
 * @param [in] offset offset to read from.
 * @param [in, out] pBuffer pointer to memory to read to.
 * @param [in] bufferSize buffer size.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudReadFile)(
    struct DCVMCloudDisk    *pCloudDisk
    , struct DCVMHandle     *pFileHandle
    , dcvm_uint64_t         offset
    , dcvm_uint8_t          *pBuffer
    , dcvm_uint32_t         bufferSize
    , struct DCVMContext    *pCtxt
);

/*!
 * @brief Write a file.
 * @param [in] pCloudDisk an instance of DCVMCloudDisk.
 * @param [in] pFileHandle opened file descriptor.
 * @param [in] offset offset to read from.
 * @param [in, out] pBuffer pointer to memory to write from.
 * @param [in] bufferSize buffer size.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudWriteFile)(
    struct DCVMCloudDisk    *pCloudDisk
    , struct DCVMHandle     *pFileHandle
    , dcvm_uint64_t         offset
    , const dcvm_uint8_t    *pBuffer
    , dcvm_uint32_t         bufferSize
    , struct DCVMContext    *pCtxt
);

/*!
 * @brief Unlink file or directory.
 * @param [in] pCloudDisk an instance of DCVMCloudDisk.
 * @param [in] pFileName file to unlink.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudUnlinkFile)(
    struct DCVMCloudDisk    *pCloudDisk
    , const dcvm_char_t     *pFileName
    , struct DCVMContext    *pCtxt
);

/*!
 * @brief Read a directory.
 * @param [in] pCloudDisk an instance of DCVMCloudDisk.
 * @param [in] pDirName directory name to read.
 * @param [out] pFileInfo file information buffer.
 * @param [in] fiCnt buffer size.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudReadDirectory)(
    struct DCVMCloudDisk    *pCloudDisk
    , struct DCVMEnumerator *pEnumerator
    , DCVMCloudGetFileInfo  *pFileInfo
    , const dcvm_uint32_t   fiCnt
    , struct DCVMContext    *pCtxt
);

/*!
 * @brief Move a file or directory.
 * @param [in] pCloudDisk an instance of DCVMCloudDisk.
 * @param [in] pSrcFileName a source file name.
 * @param [in] pSrcFileHandle a source file handle(optional).
 * @param [in] pDstFileName a destination file name.
 * @param [in] pReplace a replace destination file if it exists.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudMoveFile)(
    struct DCVMCloudDisk    *pCloudDisk
    , const dcvm_char_t     *pSrcFile
    , struct DCVMHandle     *pSrcFileHandle
    , const dcvm_char_t     *pDstFileName
    , const dcvm_bool_t     bReplace
    , struct DCVMContext    *pCtxt
);

/*!
 * @brief Get information about cloud disk.
 * @param [in] pCloudDisk an instance of DCVMCloudDisk.
 * @param [out] pCloudDiskinfo information about cloud storage.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudGetDiskInfo)(
    struct DCVMCloudDisk    *pCloudDisk
    , DCVMCloudDiskInfo     pDiskInfo
    , struct DCVMContext    *pCtxt
);

#ifdef __cplusplus
};
#endif

typedef struct _DCVMCloudDiskAPI
{
    DCVMCloudGetOAuthUrl            GetOAuthUrl;
    DCVMCloudLogInWithOAuthCode     LogInWithOAuthCode;
    DCVMCloudLogInWithRefreshToken  LogInWithRefreshToken;
    DCVMCloudLogOut                 LogOut;
    DCVMGetOAuthToken               GetOAuthToken;
    DCVMCloudCreateFile             CreateFile;
    DCVMCloudOpenFile               OpenFile;
    DCVMCloudCloseFile              CloseFile;
    DCVMCloudGetFileInfo            GetFileInfo;
    DCVMCloudUnlinkFile             UnlinkFile;
    DCVMCloudReadFile               ReadFile;
    DCVMCloudWriteFile              WriteFiele;
    DCVMCloudReadDirectory          ReadDirectory;
    DCVMCloudMoveFile               MoveFile;
    DCVMCloudGetDiskInfo            GetDiskInfo;
} DCVMCloudDiskAPI;

#endif