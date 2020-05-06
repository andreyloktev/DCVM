#ifndef DCVM_DCVM_DCVMERROR_H_
#define DCVM_DCVM_DCVMERROR_H_

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P) (P)
#endif

#define DCVMERROR_BASE 0xA0000000
#define MAKE_DCVM_ERROR(err) (DCVMERROR_BASE | (err))
#define IS_DCVM_ERROR(err) (DCVMERROR_BASE == (DCVMERROR_BASE & (err)))

#define DCVM_SUCCESS(err) (!IS_DCVM_ERROR((err)))
#define DCVM_FAILED(err) (IS_DCVM_ERROR((err)))

enum DCVM_ERROR
{
    DCVM_ERR_SUCCESS
    , DCVM_ERR_NOT_INITIALIZED                              = MAKE_DCVM_ERROR(0x1)
    , DCVM_ERR_NOT_IMPLEMENTED                              = MAKE_DCVM_ERROR(0x2)
    , DCVM_ERR_BAD_PARAMS                                   = MAKE_DCVM_ERROR(0x3)
    , DCVM_ERR_INSUFFICIENT_RESOURCES                       = MAKE_DCVM_ERROR(0x4)
    , DCVM_ERR_INTERNAL                                     = MAKE_DCVM_ERROR(0x5)
    , DCVM_ERR_CANNOT_LOG_IN                                = MAKE_DCVM_ERROR(0x6)
    , DCVM_ERR_PROVIDER_ID_IS_NOT_UNIQUE                    = MAKE_DCVM_ERROR(0x7)
    , DCVM_ERR_PROVIDER_IS_NOT_FOUND                        = MAKE_DCVM_ERROR(0x8)
    , DCVM_ERR_CLOUDDISK_IS_NOT_FOUND                       = MAKE_DCVM_ERROR(0x9)
    , DCVM_ERR_CLOUDDISK_HAS_BEEN_ALREADY_AUTHENTICATED     = 0xa
    , DCVM_ERR_CLOUDDISK_IS_NOT_AUTHORIZED                  = MAKE_DCVM_ERROR(0xb)
    , DCVM_ERR_FILE_IS_NOT_DIRECTORY                        = MAKE_DCVM_ERROR(0xc)
    , DCVM_ERR_CANNOT_SEND_REQUEST                          = MAKE_DCVM_ERROR(0xd)
    , DCVM_ERR_CRYPTO                                       = MAKE_DCVM_ERROR(0xe)
    , DCVM_ERR_UTF16_TO_UTF8_ERROR                          = MAKE_DCVM_ERROR(0xf)
    , DCVM_ERR_UTF8_TO_UTF16_ERROR                          = MAKE_DCVM_ERROR(0x10)
};

const char* DCVMErrorToString(enum DCVM_ERROR err);

#endif