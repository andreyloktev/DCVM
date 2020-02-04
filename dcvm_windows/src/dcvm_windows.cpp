#include <system/dcvm_windows.h>
#include <dcvm/DCVMLogger.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include <cpprest/http_client.h>
#include <cpprest/streams.h>

namespace dcvm_win {

inline web::http::method ToCppRestMethod(DCVMHttpMethod method) noexcept
{
    switch (method)
    {
    case DCVMHttpMethod::DCVM_CONNECT:
        return web::http::methods::CONNECT;
    case DCVMHttpMethod::DCVM_DEL:
        return web::http::methods::DEL;
    case DCVMHttpMethod::DCVM_GET:
        return web::http::methods::GET;
    case DCVMHttpMethod::DCVM_HEAD:
        return web::http::methods::HEAD;
    case DCVMHttpMethod::DCVM_MERGE:
        return web::http::methods::MERGE;
    case DCVMHttpMethod::DCVM_OPTIONS:
        return web::http::methods::OPTIONS;
    case DCVMHttpMethod::DCVM_PATCH:
        return web::http::methods::PATCH;
    case DCVMHttpMethod::DCVM_POST:
        return web::http::methods::POST;
    case DCVMHttpMethod::DCVM_PUT:
        return web::http::methods::PUT;
    case DCVMHttpMethod::DCVM_TRCE:
        return web::http::methods::TRCE;

    }

    return web::http::method();
}

} // namespace dcvm_win

extern "C" {

void* win_DCVMMemoryAlloc(dcvm_size_t size, dcvm_bool_t bZero)
{
    void *pBuf = ::malloc(size);
    if (bZero && pBuf)
    {
        ::memset(pBuf, 0, size);
    }

    return pBuf;
}

void win_DCVMMemoryFree(void *pBlock)
{
    if (pBlock)
    {
        ::free(pBlock);
    }
}

void win_DCVMMemoryCopy(void *pDst, dcvm_size_t dstSize,  const void *pSrc, dcvm_size_t srcSize)
{
    if ((nullptr == pDst) || (nullptr == pSrc) || (0 == dstSize) || (0 == srcSize))
    {
        return;
    }

    ::memcpy_s(pDst, dstSize, pSrc, srcSize);
}

dcvm_int32_t win_DCVMMemoryCompare(const void *pBlock1, const void *pBlock2, dcvm_size_t bytesToCmp)
{
    return ::memcmp(pBlock1, pBlock2, bytesToCmp);
}

void win_DCVMMemorySet(void *pBlock, dcvm_size_t size, dcvm_uint8_t value)
{
    if ((nullptr == pBlock) || (0 == size))
    {
        return;
    }

    ::memset(pBlock, value, size);
}

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
)
{
    if (
        (nullptr == pUri) 
        || ((nullptr == pHeaders) && (0 != amountHeaders)) 
        || ((nullptr == pBody) && (0 != bodySize)) 
        || (nullptr == pResponseCode)
        || ((nullptr != ppResponse) && (nullptr == pResponseSize))
    )
    {
        DCVM_ERROR_TRACE(DCVM_ERROR::DCVM_ERR_BAD_PARAMS);
        return DCVM_ERR_BAD_PARAMS;
    }

    try
    {
        web::http::http_request msg(dcvm_win::ToCppRestMethod(method));
        
        for (int i = 0; i < amountHeaders; i++)
        {
            if ((nullptr != pHeaders[i].pName) && (nullptr != pHeaders[i].pValue))
            {
                msg.headers()[pHeaders[i].pName] = pHeaders[i].pValue;
            }
        }

        if (0 != bodySize)
        {
            msg.set_body(std::vector<dcvm_uint8_t>(pBody, pBody + bodySize));
        }

        web::http::client::http_client client(pUri);

        return client.request(msg)
            .then([=](web::http::http_response &response) -> DCVM_ERROR
            {
                *pResponseCode = response.status_code();

                if (nullptr != ppResponse)
                {
                    if (response.headers().has(U("Content-Length")))
                    {
                        *pResponseSize = std::stoul(response.headers()[U("Content-Length")]);
                        if (0 != *pResponseSize)
                        {
                            *ppResponse = static_cast<dcvm_uint8_t*>(win_DCVMMemoryAlloc(*pResponseSize, DCVM_FALSE));
                            if (nullptr == *ppResponse)
                            {
                                DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES);
                                return DCVM_ERR_INSUFFICIENT_RESOURCES;
                            }

                            //Concurrency::streams::streambuf<dcvm_uint8_t>(
                        }
                    }
                }

                return DCVM_ERR_SUCCESS;
            }).get();
    }
    catch (web::http::http_exception &httpEx)
    {
        DCVM_INFO_TRACE("web::http::http_exception. Error code is 0x%X. Message is %s", httpEx.error_code().value(), httpEx.what());
        return DCVM_ERR_CANNOT_SEND_REQUEST;
    }
    catch (std::exception &e)
    {
        DCVM_INFO_TRACE("Unknonwn exception. Message is %s", e.what());
        return DCVM_ERR_CANNOT_SEND_REQUEST;
    }
}

} // extern "C"