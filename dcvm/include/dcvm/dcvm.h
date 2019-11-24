#ifndef DCVM_CORE_DCVM_H_
#define DCVM_CORE_DCVM_H_

#include "DCVMTypes.h"
#include "DCVMError.h"
#include "DCVMLogger.h"
#include "DCVMCloudDiskAPI.h"

/*!
 * @class DCVMClientOAuthUrl.
 * It's pair of client unique identifier and uri to get OAuth code.
*/
typedef struct _DCVMClientOAuthUri
{
    dcvm_char_t *pClientId;
    dcvm_char_t *pUri;
} DCVMClientOAuthUri;

/*!
 * @class DCVMClientOAuthCode.
 * It's pair of client unique identifier and OAuth code to get access and refresh tokens.
*/
typedef struct _DCVMClientOAuthCode
{
    const dcvm_char_t *pClientId;
    const dcvm_char_t *pOAuthCode;
} DCVMClientOAuthCode;

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Initialize DCVM.
 * @warning If function succeeds then DCVM obeject must be released with dcvm_Release.
 * @param [out] ppDcvm.
 * @param [in] pCtxt system context(optional).
 * @return error code.
*/
enum DCVM_ERROR dcvm_Init(DCVMSystemAPI systemApi, struct DCVM **ppDcvm, struct DCVMContext *pCtxt);

/*!
 * @brief Release DCVM object.
 * @param [in] pDcvm DCVM object.
 * @param [in] pCtxt system context(optional).
*/
void dcvm_Release(struct DCVM *pDcvm, struct DCVMContext *pCtxt);

/*!
 * @brief Add cloud disk client.
 * @param [in] pDcvm DCVM object.
 * @param [in] client cloud disk client.
 * @param [out] ppClientId added client id.
 * @param [in] pCtxt system context(optional).
 * @return error code.
*/
enum DCVM_ERROR dcvm_ControlAddClient(struct DCVM *pDcvm, const DCVMCloudDiskAPI client, dcvm_char_t **ppClientId, struct DCVMContext *pCtxt);

/*!
 * @brief Get list of authorized clients.
 * @warning If result is success then after using ppClients have to be released by dcvm_ReleaseString.
 * @param [in] pDcvm DCVM object.
 * @param [out] pClients list of unauthorized clents. Buffer consist of null-terminated C strings.
 * @param [out] pAmountClients amount clients
 * @param [in] pCtxt system context(optional).
 * @return amount of authorized clients
*/
enum DCVM_ERROR dcvm_ControlGetClients(struct DCVM *pDcvm, dcvm_char_t **ppClients, dcvm_size_t *pAmountClients, struct DCVMContext *pCtxt);

/*!
 * @brief Get list of unauthorized clients.
 * @warning If result is success, then after using ppClients have to be release by dcvm_ReleaseDCVMClientOAuthUriArray.
 * @param [in] pDcvm DCVM object.
 * @param [out] pClients list of unauthorized clents. Buffer consist of null-terminated C strings.
 * @param [out] pAmountClients amount clients
 * @param [in] pCtxt system context(optional).
 * @return amount of authorized clients
*/
enum DCVM_ERROR dcvm_ControlGetUnauthorizedClients(struct DCVM *pDcvm, DCVMClientOAuthUri **ppClients, dcvm_size_t *pAmountClients, struct DCVMContext *pCtxt);

/*!
 * @brief Authorize a client.
 * @param [in] pDcvm DCVM object.
 * @param [in] pOAuthCode OAuth code to authorize a client.
 * @param [in] pCtxt system context(optional).
 * @return error code.
*/
enum DCVM_ERROR dcvm_ControlAuthorizeClient(DCVM *pDcvm, const DCVMClientOAuthCode *pOAuthCode, struct DCVMContext *pCtxt);

/*!
 * @brief Initialize a cloud disk.
 * @warning Intialized cloud disk instance have to be released via dcvm_ControlReleaseCloudDisk.
 * @param [in] pDcvm DCVM object.
 * @param [in] pClientId cloud disk client id to initialize.
 * @param [in] flags initialization flags.
 * @param [out] ppCloudDisk initialized cloud disk.
 * @param [in] pCtxt system context(optional).
 * @return error code.
*/
enum DCVM_ERROR dcvm_InitCloudDisk(
    struct DCVM             *pDcvm
    , const dcvm_char_t     *pClientId
    , const dcvm_uint64_t   flags
    , struct DCVMCloudDisk  **ppCloudDisk
    , struct DCVMContext    *pCtxt
);

/*!
 * @brief Initialize a logical cloud disk based on several physical clients.
 * @warning Intialized cloud disk instance have to be released via dcvm_ControlReleaseCloudDisk.
 * @param [in] pDcvm DCVM object.
 * @param [in] ppClientIds array of clients ids.
 * @param [in] amountClients amount of clients ids.
 * @param [in] flags initialization flags.
 * @param [out] ppCloudDisk initialized logical cloud disk.
 * @param [in] pCtxt system context(optional).
 * @return error code.
*/
enum DCVM_ERROR dcvm_InitLogicalCloudDisk(
    struct DCVM                 *pDcvm
    , const dcvm_char_t* const  *ppClientIds
    , const dcvm_size_t         amountClients
    , const dcvm_size_t         flags
    , DCVMCloudDisk             **ppCloudDisk
    , struct DCVMContext        *pCtxt
);

/*!
 * Release a cloud disk instance.
 * @param [in] pDcvm DCVM object.
 * @param [in] pCloudDisk cloud disk instance to release.
 * @param [in] pCtxt system context(optional).
 * @return error code.
*/
DCVM_ERROR dcvm_ControlReleaseCloudDisk(struct DCVM *pDcvm, struct DCVMCloudDisk *pCloudDisk, struct DCVMContext *pCtxt);

/*!
 * @brief Release a string.
 * @param [in] pDcvm DCVM object.
*/
void dcvm_ReleaseString(dcvm_char_t *pStr);

/*!
 * @brief Release array of DCVMClientOAuthUri.
 * @param [in] pClients array to release.
 * @param [in] size amount items in array.
*/
void dcvm_ReleaseDCVMClientOAuthUriArray(DCVMClientOAuthUri *pClients, const dcvm_size_t size) noexcept;

#ifdef __cplusplus
};
#endif

#endif