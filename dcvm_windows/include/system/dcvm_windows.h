#include <dcvm/DCVMError.h>
#include <dcvm/DCVMTypes.h>
#include <dcvm/DCVMSystemAPI.h>

#ifdef __cplusplus
extern "C" {
#endif

void* win_DCVMMemoryAlloc(dcvm_size_t size, dcvm_bool_t bZero);

void win_DCVMMemoryFree(void *pBlock);

void win_DCVMMemoryCopy(void *pDst, dcvm_size_t dstSize,  const void *pSrc, dcvm_size_t srcSize);

dcvm_int32_t win_DCVMMemoryCompare(const void *pBlock1, const void *pBlock2, dcvm_size_t bytesToCmp);

void win_DCVMMemorySet(void *pBlock, dcvm_size_t size, dcvm_uint8_t value);

enum DCVM_ERROR win_DCVMSendHttpRequest(
    const enum DCVMHttpMethod   method
    , const dcvm_char_t         *pUri
    , const DCVMNameValue       *pHeaders
    , dcvm_size_t               amountHeaders
    , const dcvm_uint8_t        *pBody
    , dcvm_size_t               bodySize
    , dcvm_uint32_t             *pResponseCode
    , dcvm_uint8_t              **ppResponse
    , dcvm_size_t               *pResponseSize
    , struct DCVMContext        *pCtxt
);

#ifdef __cplusplus
}
#endif