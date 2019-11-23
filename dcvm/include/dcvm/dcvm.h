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
 * Initialize DCVM.
 * @warning If function succeeds then DCVM obeject must be released with dcvm_Release.
 * @param [out] ppDcvm.
 * @param [in] pCtxt system context(optional).
 * @return error code.
*/
enum DCVM_ERROR dcvm_Init(DCVMSystemAPI systemApi, struct DCVM **ppDcvm, struct DCVMContext *pCtxt);

/*!
 * Release DCVM object.
 * @param [in] pDcvm DCVM object.
 * @param [in] pCtxt system context(optional).
*/
void dcvm_Release(struct DCVM *pDcvm, struct DCVMContext *pCtxt);

/*!
 * Add cloud disk client.
 * @param [in] pDcvm DCVM object.
 * @param [in] client cloud disk client.
 * @param [out] ppClientId added client id.
 * @param [in] pCtxt system context(optional).
 * @return error code.
*/
enum DCVM_ERROR dcvm_ControlAddClient(struct DCVM *pDcvm, const DCVMCloudDiskAPI client, dcvm_char_t **ppClientId, struct DCVMContext *pCtxt);

/*!
 * Get list of authorized clients.
 * @warning If result is success then after using ppClients have to be released by dcvm_ReleaseString.
 * @param [in] pDcvm DCVM object.
 * @param [out] pClients list of unauthorized clents. Buffer consist of null-terminated C strings.
 * @param [out] pAmountClients amount clients
 * @param [in] pCtxt system context(optional).
 * @return amount of authorized clients
*/
enum DCVM_ERROR dcvm_ControlGetClients(struct DCVM *pDcvm, dcvm_char_t **ppClients, dcvm_size_t *pAmountClients, struct DCVMContext *pCtxt);

/*!
 * Get list of unauthorized clients.
 * @warning If result is success, then after using ppClients have to be release by dcvm_ReleaseDCVMClientOAuthUriArray.
 * @param [in] pDcvm DCVM object.
 * @param [out] pClients list of unauthorized clents. Buffer consist of null-terminated C strings.
 * @param [out] pAmountClients amount clients
 * @param [in] pCtxt system context(optional).
 * @return amount of authorized clients
*/
enum DCVM_ERROR dcvm_ControlGetUnauthorizedClients(struct DCVM *pDcvm, DCVMClientOAuthUri **ppClients, dcvm_size_t *pAmountClients, struct DCVMContext *pCtxt);

/*!
 * Release a string.
 * @param [in] pDcvm DCVM object.
*/
void dcvm_ReleaseString(dcvm_char_t *pStr);

void dcvm_ReleaseDCVMClientOAuthUriArray(DCVMClientOAuthUri *pClients, const dcvm_size_t size) noexcept;

#ifdef __cplusplus
};
#endif

#endif