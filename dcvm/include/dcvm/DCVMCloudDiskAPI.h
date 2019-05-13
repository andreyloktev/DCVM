#ifndef DCVM_DCVM_CLOUDSTORAGE_H_
#define DCVM_DCVM_CLOUDSTORAGE_H_

#include <dcvm/DCVMTypes.h>
#include <dcvm/DCVMError.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OAuthToken
{
    const dcvm_chat_t *pAccessToken;
    const dcvm_chat_t *pRefreshToken;
    const dcvm_chat_t *pTokenType;
};

enum DCVMFileType
{
    File
    , Dirctory
};

#define FILE_NAME_SIZE 256

typedef struct _DCVMFileInfo
{
    enum DCVMFileType   type;
    dcvm_char_t         name[FILE_NAME_SIZE];
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

/*!
 * @brief Get OAuth url.
 * @param [out] ppUrl url.
 * @param [in] pCtxt system context(optional).
 * @return Error code.
*/
typedef enum DCVM_ERROR (*DCVMCloudGetOAuthUrl)(dcvm_char_t **ppUrl, struct DCVMContext *pCtxt);

/*!
 * @brief Create an instance of DCVMCloudDisk(make log in operation).
 * @param [in] pOuthToken OAuth token.
 * @param [out] ppCloudDisk an instance of DCVMCloudDisk.
 * @param [in] pCtxt system context(optional).
 * @return Error code.
*/ 
typedef enum DCVM_ERROR (*DCVMCloudLogIn)(const OAuthToken *pOuthToken, struct DCVMCloudDisk *ppCloudDisk, struct DCVMContext *pCtxt);

/*!
 * @brief Log out. Release a DCVMCloudDisk instance created after LogIn operation.
 * @param [in] pCloudDisk DCVMCloudDisk instance.
 * @param [in] pCtxt system context(optional).
 * @retrun Error code.
*/
typedef enum DCVM_ERROR (*DCVMCloudLogOut)(struct DCVMCloudDisk *ppCloudDisk, struct DCVMContext *pCtxt);

/*!
 * @brief Create a file or directory.
 * @param [in] pCloudDisk an instance of DCVMCloudDisk.
 * @param [in] pFileName file to create.
 * @param [in] fileType file type to create.
 * @param [out] pFileInfo information about created file.
 * @param [out] ppFileHandle created file desciptor.
 * @param [in] pCreateFile call in the a next module.
 *                         If it's an upper filter then pCreateFile is a pointer to the DCVMCloudCreateFile of the next module.
 *                         If it's the lowest module then pCreateFile is null.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudCreateFile)(
    struct DCVMCloudDisk        *pCloudDisk
    , const dcvm_char_t         *pFileName
    , const enum DCVMFileType   fileType
    , struct DCVMFileInfo       *pFileInfo
    , struct DCVMHandle         **ppFileHandle
    , DCVMCloudCreateFile       *pCreateFile
    , struct DCVMContext        *pCtxt
);

/*!
 * @brief Open a file or directory.
 * @param [in] pCloudDisk an instance of DCVMCloudDisk.
 * @param [in] pFileName file to open.
 * @param [out] pFileInfo information about opened file.
 * @param [out] ppFileHandle opened file descriptor.
 * @param [in] pOpenFile call in the a next module.
 *                       If it's an upper filter then pOpenFile is a pointer to the DCVMCloudOpenFile of the next module.
 *                       If it's the lowest module then pOpenFile is null.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudOpenFile)(
    struct DCVMCloudDisk    *pCloudDisk
    , const dcvm_char_t     *pFileName
    , struct DCVMFileInfo   *pFileInfo
    , struct DCVMHandle     **ppFileHandle
    , DCVMCloudOpenFile     *pOpenFile
    , struct DCVMContext    *pCtxt
);

/*!
 * @brief Close a file or directory.
 * @param [in] pCloudDisk an instance of DCVMCloudDisk.
 * @param [in] pFileHandle opened file descriptor.
 * @param [in] pCloseFile call in the a next module.
 *                       If it's an upper filter then pCloseFile is a pointer to the DCVMCloudCloseFile of the next module.
 *                       If it's the lowest module then pCloseFile is null.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudCloseFile)(
    struct DCVMCloudDisk    *pCloudDisk
    , struct DCVMHandle     *pFileHandle
    , DCVMCloudCloseFile    *pCloseFile
    , struct DCVMContext    *pCtxt
);

/*!
 * @brief Get information about a file or directory.
 * @param [in] pCloudDisk an instance of DCVMCloudDisk.
 * @param [in] pFileHandle opened file descriptor.
 * @param [out] pFileInfo information about opened file.
 * @param [in] pGetFileInfo call in the a next module.
 *                       If it's an upper filter then pGetFileInfo is a pointer to the DCVMCloudGetFileInfo of the next module.
 *                       If it's the lowest module then pGetFileInfo is null.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudGetFileInfo)(
    struct DCVMCloudDisk    *pCloudDisk
    , struct DCVMHandle     *pFileHandle
    , DCVMCloudGetFileInfo  *pGetFileInfo
    , struct DCVMContext    *pCtxt
);

/*!
 * @brief Unlink file or directory.
 * @param [in] pCloudDisk an instance of DCVMCloudDisk.
 * @param [in] pFileName file to unlink.
 * @param [in] pUnlinkFile call in the a next module.
 *                       If it's an upper filter then pGetFileInfo is a pointer to the DCVMCloudUnlinkFile of the next module.
 *                       If it's the lowest module then pGetFileInfo is null.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudUnlinkFile)(
    struct DCVMCloudDisk    *pCloudDisk
    , const dcvm_char_t     *pFileName
    , DCVMCloudUnlinkFile   *pGetFileInfo
    , struct DCVMContext    *pCtxt
);

/*!
 * @brief Initialize enumrator to list all files in a directory.
 * @param [in] pCloudDisk an instance of DCVMCloudDisk.
 * @param [in] pDirName a directory name where to enumerate files.
 * @param [out] ppEnumerator file enumerator.
 * @param [in] pFindFirst call in the a next module.
 *                       If it's an upper filter then pFindFirst is a pointer to the DCVMCloudFindFirst of the next module.
 *                       If it's the lowest module then pFindFirst is null.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudFindFirst)(
    struct DCVMCloudDisk    *pCloudDisk
    , const dcvm_char_t     *pDirName
    , struct DCVMEnumerator **ppEnumerator
    , DCVMCloudFindFirst    *pFindFirst
    , struct DCVMContext    *pCtxt
);

/*!
 * @brief Find files in a directory.
 * @param [in] pCloudDisk an instance of DCVMCloudDisk.
 * @param [in] pEnumerator file enumerator.
 * @param [out] pFileInfo file information buffer.
 * @param [in] fiCnt buffer size.
 * @param [in] pFindNext call in the a next module.
 *                       If it's an upper filter then pFindNext is a pointer to the DCVMCloudFindNext of the next module.
 *                       If it's the lowest module then pFindNext is null.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudFindNext)(
    struct DCVMCloudDisk    *pCloudDisk
    , struct DCVMEnumerator *pEnumerator
    , DCVMCloudGetFileInfo  *pFileInfo
    , const dcvm_uint32_t   fiCnt
    , DCVMCloudFindNext     *pFindFirst
    , struct DCVMContext    *pCtxt
);

/*!
 * @brief Finish files enumeration. Release enumerator.
 * @param [in] pCloudDisk an instance of DCVMCloudDisk.
 * @param [in] pEnumerator file enumerator.
 * @param [in] pFindClose call in the a next module.
 *                       If it's an upper filter then pFindNext is a pointer to the DCVMCloudFindClose of the next module.
 *                       If it's the lowest module then pFindClose is null.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudFindClose)(
    struct DCVMCloudDisk    *pCloudDisk
    , struct DCVMEnumerator *pEnumerator
    , DCVMCloudFindClose    *pFindClose
    , struct DCVMContext    *pCtxt
);

/*!
 * @brief Move a file or directory.
 * @param [in] pCloudDisk an instance of DCVMCloudDisk.
 * @param [in] pSrcFileName a source file name.
 * @param [in] pSrcFileHandle a source file handle(optional).
 * @param [in] pDstFileName a destination file name.
 * @param [in] pReplace a replace destination file if it exists.
 * @param [in] pMoveFile call in the a next module.
 *                       If it's an upper filter then pMoveFile is a pointer to the DCVMCloudMoveFile of the next module.
 *                       If it's the lowest module then pMoveFile is null.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMCloudMoveFile)(
    struct DCVMCloudDisk    *pCloudDisk
    , const dcvm_char_t     *pSrcFile
    , struct DCVMHandle     *pSrcFileHandle
    , const dcvm_char_t     *pDstFileName
    , const dcvm_bool_t     bReplace
    , DCVMCloudMoveFile     *pMoveFile
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

typedef struct _DCVMCloudDiskAPI
{
    DCVMCloudGetOAuthUrl    GetOAuthUrl;
    DCVMCloudLogIn          LogIn;
    DCVMCloudLogOut         LogOut;
    DCVMCloudCreateFile     CreateFile;
    DCVMCloudOpenFile       OpenFile;
    DCVMCloudCloseFile      CloseFile;
    DCVMCloudGetFileInfo    GetFileInfo;
    DCVMCloudUnlinkFile     UnlinkFile;
    DCVMCloudFindFirst      FindFirst;
    DCVMCloudFindNext       FindNext;
    DCVMCloudFindClose      FindClose;
    DCVMCloudMoveFile       MoveFile;
    DCVMCloudGetDiskInfo    GetDiskInfo;
} DCVMCloudDiskAPI;

#ifdef __cplusplus
};
#endif

#endif