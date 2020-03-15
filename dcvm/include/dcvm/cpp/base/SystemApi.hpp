#ifndef DCVM_BASE_SYSTEMAPI_HPP_
#define DCVM_BASE_SYSTEMAPI_HPP_

#include <dcvm/DCVMSystemAPI.h>
#include <dcvm/DCVMTypes.h>

namespace dcvm {

extern DCVMSystemAPI g_systemApi;

namespace base {

struct HttpRequest final
{
    enum DCVMHttpMethod     method;
    const dcvm_char_t       *pUri;
    const DCVMNameValue     *pHeaders;
    dcvm_size_t             amountHeaders;
    const dcvm_uint8_t      *pBody;
    dcvm_size_t             bodySize;
};

struct HttpResponse final
{
    dcvm_uint32_t   responseCode;
    dcvm_uint8_t    *pResponse;
    dcvm_size_t     responseSize;
};

struct SystemApi final
{
    template<typename T>
    static T* MemoryAllocate(dcvm_size_t size, dcvm_bool_t bZero) noexcept
    {
        return g_systemApi.MemoryAllocate ? static_cast<T*>(g_systemApi.MemoryAllocate(size, bZero)) : nullptr;
    }

    static void MemoryFree(void *p) noexcept
    {
        g_systemApi.MemoryFree ? g_systemApi.MemoryFree(p) : void();
    }

    static void MemorySet(void *p, dcvm_size_t size, dcvm_uint8_t value) noexcept
    {
        g_systemApi.MemorySet ? g_systemApi.MemorySet(p, size, value) : void();
    }

    static void MemoryCopy(void *pDst, dcvm_size_t dstSize, const void *pSrc, dcvm_size_t srcSize) noexcept
    {
        g_systemApi.MemoryCopy ? g_systemApi.MemoryCopy(pDst, dstSize, pSrc, srcSize) : void();
    }

    static dcvm_int32_t MemoryCompare(const void *pBlock1, const void *pBlock2, dcvm_size_t bytesToCmp) noexcept
    {
        return g_systemApi.MemoryCompare ? g_systemApi.MemoryCompare(pBlock1, pBlock2, bytesToCmp) : -1;
    }

    static DCVM_ERROR SendHttpRequest(const HttpRequest &request, HttpResponse &response, struct DCVMContext *pCtxt) noexcept
    {
        return g_systemApi.SendHttpRequest ?
            g_systemApi.SendHttpRequest(
                request.method, request.pUri, request.pHeaders, request.amountHeaders, request.pBody, request.bodySize
                , &response.responseCode, &response.pResponse, &response.responseSize
                , pCtxt
            ) : DCVM_ERR_NOT_IMPLEMENTED;
    }

    static DCVM_ERROR CryptoRNG(dcvm_uint8_t *pBuffer, const dcvm_size_t bufSize, struct DCVMContext *pCtxt) noexcept
    {
        return g_systemApi.CryptoRNG ? g_systemApi.CryptoRNG(pBuffer, bufSize, pCtxt) : DCVM_ERR_NOT_IMPLEMENTED;
    }

    static DCVM_ERROR CryptoSHA256(
        const dcvm_uint8_t      *pDataToHash
        , const dcvm_size_t     dataToHashSize
        , dcvm_uint8_t*         &pHashedData
        , dcvm_size_t           &hashedDataSize
        , struct DCVMContext    *pCtxt
    ) noexcept
    {
        return g_systemApi.CryptoSHA256 ?
            g_systemApi.CryptoSHA256(pDataToHash, dataToHashSize, &pHashedData, &hashedDataSize, pCtxt) : DCVM_ERR_NOT_IMPLEMENTED;
    }
};

} // namespace base
} // namespace dcvm

#endif