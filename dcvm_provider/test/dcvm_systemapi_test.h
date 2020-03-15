
#ifndef DCVM_SYSTEMAPI_TEST_H_
#define DCVM_SYSTEMAPI_TEST_H_

#include <dcvm/cpp/base/SystemApi.hpp>

extern dcvm_int32_t g_MemoryCounter;

extern "C" 
{
    void* DCVMMemoryAlloc_test(dcvm_size_t size, dcvm_bool_t bZero);

    void DCVMMemoryFree_test(void *pBlock);

    void DCVMMemoryCopy_test(void *pDst, dcvm_size_t dstSize,  const void *pSrc, dcvm_size_t srcSize);

    dcvm_int32_t DCVMMemoryCompare_test(const void *pBlock1, const void *pBlock2, dcvm_size_t bytesToCmp);

    void DCVMMemorySet_test(void *pBlock, dcvm_size_t size, dcvm_uint8_t value);

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
    );
}

inline void InitDCVMSystemApi() noexcept
{
    if (nullptr == dcvm::g_systemApi.MemoryAllocate)
    {
        dcvm::g_systemApi.MemoryAllocate = DCVMMemoryAlloc_test;
        dcvm::g_systemApi.MemoryCompare = DCVMMemoryCompare_test;
        dcvm::g_systemApi.MemoryCopy = DCVMMemoryCopy_test;
        dcvm::g_systemApi.MemoryFree = DCVMMemoryFree_test;
        dcvm::g_systemApi.MemorySet = DCVMMemorySet_test;
        dcvm::g_systemApi.SendHttpRequest = DCVMSendHttpRequest_test;
    }
}


#endif