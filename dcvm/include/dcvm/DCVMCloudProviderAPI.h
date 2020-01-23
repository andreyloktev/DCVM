#ifndef DCVM_DCVM_CLOUDDISKPROVIDERAPI_H_
#define DCVM_DCVM_CLOUDDISKPROVIDERAPI_H_

#include "DCVMTypes.h"
#include "DCVMError.h"
#include "DCVMSystemAPI.h"

typedef struct _OAuthToken
{
    const dcvm_char_t *pAccessToken;
    const dcvm_char_t *pRefreshToken;
    const dcvm_char_t *pTokenType;
} OAuthToken;

enum DCVMFileType
{
    DCVM_File
    , DCVM_Dirctory
    , DCVM_SymbolicLink
};

#define FILE_NAME_SIZE          256
#define CLOUD_PROVIDER_ID_SIZE  1024
#define USER_NAME_SIZE          1024
#define FILE_FLAG_READ_ONLY     0x00000001

typedef struct _DCVMFileInfo
{
    enum DCVMFileType   type;
    dcvm_char_t         name[FILE_NAME_SIZE];
    dcvm_uint32_t       flags;
    dcvm_uint64_t       fileSize;
    dcvm_uint64_t       creationTime;
    dcvm_uint64_t       modificationTime;
} DCVMFileInfo;

typedef struct _DCVMCloudProviderInfo
{
    dcvm_char_t id[CLOUD_PROVIDER_ID_SIZE];
} DCVMCloudProviderInfo;

typedef struct _DCVMUserInfo
{
    dcvm_char_t name[USER_NAME_SIZE];
} DCVMUserInfo;

typedef struct _DCVMCloudDiskInfo
{
    DCVMCloudProviderInfo providerInfo;
    DCVMUserInfo userInfo;
    dcvm_uint64_t maxFileSize;
    dcvm_uint64_t totalSpace;
    dcvm_uint64_t usedSpace;
    dcvm_uint32_t childrenCount;
    struct _DCVMCloudDiskInfo *pChildren;
} DCVMCloudDiskInfo;

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * Get unique provider identifier. It's may be just a provider name. For example, "YandexDisk".
 * @warning It's must have to implement function.
 * @return unique client identification.
*/
typedef const dcvm_char_t* (*DCVMCloudGetProviderId)(struct DCVMContext *pCtxt);

/*!
 * @brief Get OAuth url.
 * @param [out] ppUrl url.
 * @param [in] pSystemApi set of System API function.
 * @param [in] pCtxt system context(optional).
 * @return Error code.
*/
typedef enum DCVM_ERROR (*DCVMCloudGetOAuthUri)(dcvm_char_t **ppUrl, DCVMSystemAPI *pSystemApi, struct DCVMContext *pCtxt);

/*!
 * @brief Create an instance of DCVMCloudDiskProvider(make log in operation by OAuth codes).
 * @param [in] pCode OAuth code.
 * @param [out] ppCloudProvider an instance of DCVMCloudDiskProvider.
 * @param [in] pSystemApi set of System API function.
 * @param [in] pCtxt system context(optional).
 * @return Error code.
*/ 
typedef enum DCVM_ERROR (*DCVMCloudLogInWithOAuthCode)(
    const dcvm_char_t           *pCode
    , struct DCVMCloudProvider  **ppCloudProvider
    , DCVMSystemAPI             *pSystemApi
    , struct DCVMContext        *pCtxt
);

/*!
 * @brief Create an instance of DCVMCloudDiskProvider(make log in operation by OAuth refresh token).
 * @param [in] pRefreshToken OAuth refresh token.
 * @param [out] ppCloudProvider an instance of DCVMCloudDiskProvider.
 * @param [in] pSystemApi set of System API function.
 * @param [in] pCtxt system context(optional).
 * @return Error code.
*/ 
typedef enum DCVM_ERROR (*DCVMCloudLogInWithRefreshToken)(
    const dcvm_char_t           *pRefreshToken
    , struct DCVMCloudProvider  **ppCloudProvider
    , DCVMSystemAPI             *pSystemApi
    , struct DCVMContext        *pCtxt
);

/*!
 * @brief Get OAuthToken(access token, refresh token and token type)
 * @param [in] pCloudProvider an instance of DCVMCloudDiskProvider.
 * @param [in] pCtxt system context(optional).
 * @return OAuthToken object
*/
typedef OAuthToken (*DCVMGetOAuthToken)(struct DCVMCloudProvider *pCloudProvider, struct DCVMContext *pCtxt);

/*!
 * @brief Log out. Release a DCVMCloudDiskProvider instance created after LogIn operation.
 * @param [in] pCloudProvider DCVMCloudDiskProvider instance.
 * @param [in] pCtxt system context(optional).
 * @retrun Error code.
*/
typedef enum DCVM_ERROR (*DCVMCloudLogOut)(struct DCVMCloudProvider *pCloudProvider, struct DCVMContext *pCtxt);

/*!
 * @brief Create a file or directory.
 * @param [in] pCloudProvider an instance of DCVMCloudDiskProvider.
 * @param [in] pFileName file to create.
 * @param [in] pFi information about a creating file.
 * @param [out] pFileInfo information about created file.
 * @param [out] ppFileHandle created file desciptor.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudCreateFile)(
    struct DCVMCloudProvider    *pCloudProvider
    , const dcvm_char_t         *pFileName
    , const DCVMFileInfo        *pFi
    , DCVMFileInfo              *pFileInfo
    , struct DCVMHandle         **ppFileHandle
    , struct DCVMContext        *pCtxt
);

/*!
 * @brief Open a file or directory.
 * @param [in] pCloudProvider an instance of DCVMCloudDiskProvider.
 * @param [in] pFileName file to open.
 * @param [out] pFileInfo information about opened file.
 * @param [out] ppFileHandle opened file descriptor.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudOpenFile)(
    struct DCVMCloudProvider    *pCloudProvider
    , const dcvm_char_t         *pFileName
    , DCVMFileInfo              *pFileInfo
    , struct DCVMHandle         **ppFileHandle
    , struct DCVMContext        *pCtxt
);

/*!
 * @brief Close a file or directory.
 * @param [in] pCloudProvider an instance of DCVMCloudDiskProvider.
 * @param [in] pFileHandle opened file descriptor.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudCloseFile)(
    struct DCVMCloudProvider    *pCloudProvider
    , struct DCVMHandle         *pFileHandle
    , struct DCVMContext        *pCtxt
);

/*!
 * @brief Get information about a file or directory.
 * @param [in] pCloudProvider an instance of DCVMCloudDiskProvider.
 * @param [in] pFileHandle opened file descriptor.
 * @param [out] pFileInfo information about opened file.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudGetFileInfo)(
    struct DCVMCloudProvider    *pCloudProvider
    , struct DCVMHandle         *pFileHandle
    , DCVMFileInfo              *pFileInfo
    , struct DCVMContext        *pCtxt
);

/*!
 * @brief Read a file.
 * @param [in] pCloudProvider an instance of DCVMCloudDiskProvider.
 * @param [in] pFileHandle opened file descriptor.
 * @param [in] offset offset to read from.
 * @param [in, out] pBuffer pointer to memory to read to.
 * @param [in] bufferSize buffer size.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudReadFile)(
    struct DCVMCloudProvider    *pCloudProvider
    , struct DCVMHandle         *pFileHandle
    , dcvm_uint64_t             offset
    , dcvm_uint8_t              *pBuffer
    , dcvm_uint32_t             bufferSize
    , struct DCVMContext        *pCtxt
);

/*!
 * @brief Write a file.
 * @param [in] pCloudProvider an instance of DCVMCloudDiskProvider.
 * @param [in] pFileHandle opened file descriptor.
 * @param [in] offset offset to read from.
 * @param [in, out] pBuffer pointer to memory to write from.
 * @param [in] bufferSize buffer size.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudWriteFile)(
    struct DCVMCloudProvider    *pCloudProvider
    , struct DCVMHandle         *pFileHandle
    , dcvm_uint64_t             offset
    , const dcvm_uint8_t        *pBuffer
    , dcvm_uint32_t             bufferSize
    , struct DCVMContext        *pCtxt
);

/*!
 * @brief Unlink file or directory.
 * @param [in] pCloudProvider an instance of DCVMCloudDiskProvider.
 * @param [in] pFileName file to unlink.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudUnlinkFile)(
    struct DCVMCloudProvider    *pCloudProvider
    , const dcvm_char_t         *pFileName
    , struct DCVMContext        *pCtxt
);

/*!
 * @brief Read a directory.
 * @param [in] pCloudProvider an instance of DCVMCloudDiskProvider.
 * @param [in] pDirName directory name to read.
 * @param [out] pFileInfo file information buffer.
 * @param [in] fiCnt buffer size.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudReadDirectory)(
    struct DCVMCloudProvider    *pCloudProvider
    , struct DCVMEnumerator     *pEnumerator
    , DCVMFileInfo              *pFileInfo
    , const dcvm_uint32_t       fiCnt
    , struct DCVMContext        *pCtxt
);

/*!
 * @brief Move a file or directory.
 * @param [in] pCloudProvider an instance of DCVMCloudDiskProvider.
 * @param [in] pSrcFileName a source file name.
 * @param [in] pSrcFileHandle a source file handle(optional).
 * @param [in] pDstFileName a destination file name.
 * @param [in] pReplace a replace destination file if it exists.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudMoveFile)(
    struct DCVMCloudProvider    *pCloudProvider
    , const dcvm_char_t         *pSrcFile
    , struct DCVMHandle         *pSrcFileHandle
    , const dcvm_char_t         *pDstFileName
    , const dcvm_bool_t         bReplace
    , struct DCVMContext        *pCtxt
);

/*!
 * @brief Get information about cloud disk.
 * @param [in] pCloudProvider an instance of DCVMCloudDiskProvider.
 * @param [out] pDiskinfo information about cloud storage.
 * @param [in] diskInfoSize size of pDiskinfo buffer. 
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudGetDiskInfo)(
    struct DCVMCloudProvider    *pCloudProvider
    , DCVMCloudDiskInfo         *pDiskInfo
    , struct DCVMContext        *pCtxt
);

#ifdef __cplusplus
};
#endif

typedef struct _DCVMCloudProviderAPI
{
    DCVMCloudGetProviderId          GetProviderId;
    DCVMCloudGetOAuthUri            GetOAuthUri;
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
} DCVMCloudProviderAPI;

#endif