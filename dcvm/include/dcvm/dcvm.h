#ifndef DCVM_CORE_DCVM_H_
#define DCVM_CORE_DCVM_H_

#include "DCVMTypes.h"
#include "DCVMError.h"
#include "DCVMLogger.h"
#include "dcvm_system.h"
#include "DCVMCloudDiskAPI.h"

/*!
 * @class DCVMClientOAuthUrl.
 * It's pair of client unique identifier and uri to get OAuth code.
*/
struct DCVMClientOAuthUri
{
    const dcvm_char_t *pClientId;
    const dcvm_char_t *pUri;
};

/*!
 * @class DCVMClientOAuthCode.
 * It's pair of client unique identifier and OAuth code to get access and refresh tokens.
*/
struct DCVMClientOAuthCode
{
    const dcvm_char_t *pClientId;
    const dcvm_char_t *pOAuthCode;
};

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
enum DCVM_ERROR dcvm_Init(DCVMSystemAPI *pSystemApi, struct DCVM **ppDcvm, struct DCVMContext *pCtxt);

/*!
 * Release DCVM object.
 * @param [in] pDcvm DCVM object.
 * @param [in] pCtxt system context(optional).
*/
void dcvm_Release(struct DCVM *pDcvm, struct DCVMContext *pCtxt);

/*!
 * Add cloud disk client.
 * @param [in] pDcvm DCVM object.
 * @param [in] pClient client.
 * @param [in] pCtxt system context(optional).
*/
void dcvm_ControlAddClient(struct DCVM *pDcvm, const DCVMCloudDiskAPI pClient, struct DCVMContext *pCtxt);

/*!
 * Get list of unauthorized clients.
 * @param [in] pDcvm DCVM object.
 * @param [out] pClients list of unauthorized clents. Mark of last elment is nullptr.
 * @param [in] pCtxt system context(optional).
*/
void dcvm_ControlGetUnauthorizedClients(struct DCVM *pDcvm, DCVMClientOAuthUri **pClients, struct DCVMContext *pCtxt);

/*!
 * LogIn. Crate a cloud disk.
 * @warning created cloud disk control block must be freed via dcvm_ControlLogOut.
 * @param [in] pDcvm DCVM object.
 * @param [in] pCodes List of OAuth codes. Mark of end of the list is nullptr. If the input list contains several OAuth code for differnet clients, then a cloud disk control block under these clients will be created.
 * @param [out] ppCloudDisk cloud disk control block.
 * @param [in] pCtxt system context(optional).
 * @retunr error code.
*/
enum DCVM_ERROR dcvm_ControlLogIn(struct DCVM *pDcvm, const DCVMClientOAuthCode *pCodes, struct DCVMCloudDisk **ppCloudDisk, struct DCVMContext *pCtxt);

/*!
 * LogOut. Release cloud disk control block.
 * @param [in] pDcvm DCVM object.
 * @param [in] ppCloudDisk cloud disk control block to release.
 * @param [in] pCtxt system context(optional).
*/
void dcvm_ControlLogOut(struct DCVM *pDcvm, struct DCVMCloudDisk *pCloudDisk, struct DCVMContext *pCtxt);

/*!
 * Release a string.
 * @param [in] pDcvm DCVM object.
 * @param [in] pStr string to release.
*/
void dcvm_ReleaseString(struct DCVM *pDcvm, dcvm_char_t *pStr);

#ifdef __cplusplus
};
#endif

#endif