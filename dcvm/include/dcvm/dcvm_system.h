#ifndef DCVM_DCVM_SYSTEM_H_
#define DCVM_DCVM_SYSTEM_H_

#include "DCVMTypes.h"
#include "DCVMError.h"

typedef struct _NameValue
{
    const dcvm_char_t *pName;
    const dcvm_char_t *pValue;
} NameValue;

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Allocate a blok of memory.
 * @param [in] size size of memory to allocate.
 * @return pointer to an allocated block memory.
*/
typedef void* (*DCVMMemoryAlloc)(dcvm_size_t size);

/*!
 * Free previously allocated memory.
 * @param [in] pBlock block of memory.
*/
typedef void (*DCVMMemoryFree)(void *pBlock);

/*!
 * @brief Copy block of memory.
 * @param [in,out] pDst pointer to a memory to copy to..
 * @param [in] dstSize size of memory block to copy to.
 * @param [in] pSrc pointer to memory to copy from.
 * @param [in] srcSize amount bytes to coopy.
*/
typedef void (*DCVMMemoryCopy)(void *pDst, dcvm_size_t dstSize,  const void *pSrc, dcvm_size_t srcSize);

/*!
 * @brief Compare two blocks of memory.
 * @param [in] pBlock1 first block of memory to compare.
 * @param [in] pBlock2 second block of memory to compare.
 * @param [in] bytesToCmp amount bytes to compare.
 * @return result of compare.
*/
typedef dcvm_int32_t (*DCVMMemoryCompare)(void *pBlock1, const void *pBlock2, dcvm_size_t bytesToCmp);

/*!
 * @brief Sets the first 'size' bytes of the block of memory pointed by pBlock to the specified value.
 * @param [in] pBlock block of memory to initialize.
 * @param [in] size memory block size.
 * @param [in] value.
*/
typedef void (*DCVMMemorySet)(void *pBlock, dcvm_size_t size, dcvm_uint8_t value);

/*!
 * @brief Send http request and get response.
 * @param [in] pMethod http request method.
 * @param [in] pUri operation
 * @param [in] pHeaders array of http request headers. If there are no headers then pHeaders is nullptr.
 * @param [in] amountHeaders amount of headers.
 * @param [in] pBody pointer to memory with body data.
 * @param [in] bodySize body size.
 * @param [out] pResponseCode response code.
 * @param [out] ppResponse response.
 * @param [out] pResponseSize response size.
 * @param [in] pCtxt system context(optional).
*/
typedef enum DCVM_ERROR (*DCVMSendHttpRequest)(
    const dcvm_char_t       *pMethod
    , const dcvm_char_t     *pUri
    , const NameValue       *pHeaders
    , dcvm_size_t           amountHeaders
    , const dcvm_uint8_t    *pBody
    , dcvm_size_t           bodySize
    , dcvm_uint32_t         *pResponseCode
    , dcvm_uint8_t          **ppResponse
    , dcvm_size_t           *pResponseSize
    , struct DCVMContext    *pCtxt
);

#ifdef __cplusplus
}
#endif

typedef struct _DCVMSystemAPI
{
    DCVMMemoryAlloc     MemoryAllocate;
    DCVMMemoryFree      MemoryFree;
    DCVMMemorySet       MemorySet;
    DCVMMemoryCopy      MemoryCopy;
    DCVMMemoryCompare   MemoryCompare;
    DCVMSendHttpRequest SendHttpRequest;
} DCVMSystemAPI;

#endif