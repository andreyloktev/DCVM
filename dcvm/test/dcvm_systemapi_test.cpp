#include <cstdlib>
#include <cstring>
#include "dcvm_systemapi_test.h"

dcvm_int32_t g_MemoryCounter = 0; 

extern "C"
{
    void* DCVMMemoryAlloc_test(dcvm_size_t size, dcvm_bool_t bZero) noexcept
    {
        void *p = std::malloc(size);
        if ((nullptr != p) && (DCVM_TRUE == bZero))
        {
            std::memset(p, 0, size);
        }

        g_MemoryCounter++;

        return p;
    }

    void DCVMMemoryFree_test(void *pBlock) noexcept
    {
        if (pBlock)
        {
            g_MemoryCounter--;
            std::free(pBlock);
        }
    }

    void DCVMMemoryCopy_test(void *pDst, dcvm_size_t dstSize,  const void *pSrc, dcvm_size_t srcSize) noexcept
    {
        if ((nullptr == pDst) || (nullptr == pSrc) || (0 == dstSize) || (0 == srcSize))
        {
            return;
        }

        std::memcpy(pDst, pSrc, srcSize > dstSize ? dstSize : srcSize);
    }

    dcvm_int32_t DCVMMemoryCompare_test(void *pBlock1, const void *pBlock2, dcvm_size_t bytesToCmp) noexcept
    {
        if ((nullptr == pBlock1) && (nullptr == pBlock2))
        {
            return 0;
        }

        if ((nullptr == pBlock1) || (nullptr == pBlock2))
        {
            return -1;
        }

        return std::memcmp(pBlock1, pBlock2, bytesToCmp);
    }

    void DCVMMemorySet_test(void *pBlock, dcvm_size_t size, dcvm_uint8_t value) noexcept
    {
        if ((nullptr == pBlock) || (0 == size))
        {
            return;
        }

        std::memset(pBlock, value, size);
    }

    DCVM_ERROR DCVMSendHttpRequest_test(
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
    ) noexcept
    {
        DCVM_UNREFERENCED_PARAMETER(method);
        DCVM_UNREFERENCED_PARAMETER(pUri);
        DCVM_UNREFERENCED_PARAMETER(pHeaders);
        DCVM_UNREFERENCED_PARAMETER(amountHeaders);
        DCVM_UNREFERENCED_PARAMETER(pBody);
        DCVM_UNREFERENCED_PARAMETER(bodySize);
        DCVM_UNREFERENCED_PARAMETER(pResponseCode);
        DCVM_UNREFERENCED_PARAMETER(ppResponse);
        DCVM_UNREFERENCED_PARAMETER(pResponseSize);
        DCVM_UNREFERENCED_PARAMETER(pCtxt);


        return DCVM_ERR_NOT_IMPLEMENTED;
    }
}