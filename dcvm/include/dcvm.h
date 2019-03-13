#ifndef DCVM_CORE_DCVM_H_
#define DCVM_CORE_DCVM_H_

#include "dcvm/DCVMTypes.h"
#include "dcvm/DCVMError.h"
#include "dcvm/DCVMLogger.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * Initialize DCVM.
 * @warning If function succeeds then DCVM obeject must be released with dcvm_Release.
 * @param [out] ppDcvm.
 * @return error code.
*/
DCVMError dcvm_Init(struct DCVM **ppDcvm);

/*!
 * Release DCVM object.
 * @param [in] pDcvm DCVM object.
*/
void dcvm_Release(struct DCVM *pDcvm);

/*!
 * Return Oauth2 url to receive an authorization code. When an authorization code is received then dcvm_ControlLogIn must be used.
 * @warning If function succeeds then ppUrl buffer must be freed with dcvm_ReleaseString.
 * @param [in] pDcvm DCVM object.
 * @param [in] type clode disk type.
 * @param [out] ppUrl url to receive an authorization code(null terminated string).
 * @return error code.
*/
DCVMError dcvm_ControlGetOauth2Url(struct DCVM *pDcvm, DCVMCloudDiskType type, DCVMChar_t **ppUrl);

/*!
 * Log in(get access and refresh token). If log in succedds then cloud disk service dynamically will be added to list of cloud disks.
 * @param [in] pDcvm DCVM object.
 * @param [in] type clode disk type.
 * @param [in] pCode an authorization code(null terminated string).
 * @return error code.
*/
DCVMError dcvm_ControlLogIn(struct DCVM *pDcvm, DCVMCloudDiskType type, const DCVMChar_t *pCode);

/*!
 * Release a string.
 * @param [in] pDcvm DCVM object.
 * @param [in] pStr string to release.
*/
void dcvm_ReleaseString(struct DCVM *pDcvm, DCVMChar_t *pStr);

#ifdef __cplusplus
};
#endif

#endif