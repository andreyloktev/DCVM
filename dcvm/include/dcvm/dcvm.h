#ifndef DCVM_DCVM_H_
#define DCVM_DCVM_H_

#include "DCVMTypes.h"
#include "DCVMError.h"
#include "DCVMLogger.h"
#include "DCVMCloudProviderAPI.h"

/*!
 * @class DCVMClientOAuthUrl.
 * It's pair of provider unique identifier and uri to get OAuth code.
*/
typedef struct _DCVMProviderOAuthUri
{
    dcvm_char_t *pProviderId;
    dcvm_char_t *pUri;
} DCVMClientOAuthUri;

/*!
 * @class DCVMClientOAuthCode.
 * It's pair of provider unique identifier and OAuth code to get access and refresh tokens.
*/
typedef struct _DCVMProviderOAuthCode
{
    const dcvm_char_t *pProviderId;
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
 * @warning pProviderId should be released with dcvm_ReleaseBuffer.
 * @param [in] pDcvm DCVM object.
 * @param [in] provider cloud disk provider api.
 * @param [out] ppProviderId added provider id.
 * @param [in] pCtxt system context(optional).
 * @return error code.
*/
enum DCVM_ERROR dcvm_ControlAddCloudProvider(struct DCVM *pDcvm, const DCVMCloudProviderAPI provider, dcvm_char_t **ppProviderId, struct DCVMContext *pCtxt);

/*!
 * Get list of providers.
 * @warning pBuffer should be released by dcvm_ReleaseBuffer.
 * @param [in] pDcvm DCVM object.
 * @param [out] ppProvidersIds pointer to the buffer that recieves providers ids. Provider id delimeter is '\0'.
 * @param [out] pSize size of buffer with providers ids.
 * @param [in] pCtxt system context(optional).
 * @return error code.
*/
enum DCVM_ERROR dcvm_ControlGetCloudProviders(struct DCVM *pDcvm, dcvm_char_t **ppProvidersIds, dcvm_size_t *pSize, struct DCVMContext *pCtxt);

/*!
 * @brief Get authorization uri.
 * @warning pUri should be released with dcvm_ReleaseBuffer.
 * @param [in] pDcvm DCVM object.
 * @param [in] pProviderId provider id.
 * @param [out] ppUri pointer to the buffer that recieves authorization uri.
 * @param [in] pCtxt system context(optional).
 * @return error code.
*/
enum DCVM_ERROR dcvm_ControlGetAuthorzationUri(struct DCVM *pDcvm, const dcvm_char_t *pProviderId, dcvm_char_t **ppUri, struct DCVMContext *pCtxt);

/*!
 * @brief Create a cloud disk.
 * @param [in] pDcvm DCVM object.
 * @param [in] pOAuthCode OAuth code to authorize a client.
 * @param [out] pCloudDiskId pointer to the id of the created cloud disk.
 * @param [in] pCtxt system context(optional).
 * @return error code.
*/
enum DCVM_ERROR dcvm_ControlCreateCloudDisk(DCVM *pDcvm, const DCVMClientOAuthCode *pOAuthCode, dcvm_size_t *pCloudDiskId, struct DCVMContext *pCtxt);

/*!
 * @brief Get list of authorized clients.
 * @warning pCloudDisksIds should be release with dcvm_ReleaseBuffer.
 * @param [in] pDcvm DCVM object.
 * @param [out] ppCloudDisksIds list of cloud disks ids.
 * @param [out] pAmountClients amount cloud disks ids.
 * @param [in] pCtxt system context(optional).
 * @return error code.
*/
enum DCVM_ERROR dcvm_ControlGetCloudDisks(struct DCVM *pDcvm, dcvm_size_t **ppCloudDisksIds, dcvm_size_t *pAmountCloudDisksIds, struct DCVMContext *pCtxt);

/*!
 * @brief Get information about the cloud disk.
 * @param [in] pDcvm DCVM object.
 * @param [in] id cloud disk id.
 * @param [in, out] pInfo the buffer that recieves infroamtion about the cloud disk.
 * @param [in, out] pSize size of pInfo buffer. If pInfo is null the pSize recieves required pInfo buffer size.
 * @param [in] pCtxt system context(optional).
 * @return error code.
*/
enum DCVM_ERROR dcvm_ControlGetCloudDiskInformation(struct DCVM *pDcvm, const dcvm_size_t id, DCVMCloudDiskInfo *pInfo, dcvm_size_t *pSize, struct DCVMContext *pCtxt);

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
enum DCVM_ERROR dcvm_ControlInitCloudDisk(
    struct DCVM             *pDcvm
    , const dcvm_size_t     cloudDiskId
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
enum DCVM_ERROR dcvm_ControlInitLogicalCloudDisk(
    struct DCVM                 *pDcvm
    , const dcvm_size_t* const  ppCloudDisksIds
    , const dcvm_size_t         amountCloudDisksIds
    , const dcvm_size_t         flags
    , struct DCVMCloudDisk      **ppCloudDisk
    , struct DCVMContext        *pCtxt
);

/*!
 * @brief Release the cloud disk.
 * @param [in] pDcvm DCVM object.
 * @param [in] pCloudDisk cloud disk o release.
 * @param [in] pCtxt system context(optional).
 * @return error code.
*/
DCVM_ERROR dcvm_ControlReleaseCloudDisk(struct DCVM *pDcvm, struct DCVMCloudDisk *pCloudDisk, struct DCVMContext *pCtxt);

/*!
 * @brief Release a buffer.
 * @param [in] pDcvm DCVM object.
*/
void dcvm_ReleaseBuffer(void *pBuffer);

#ifdef __cplusplus
};
#endif

#endif