#ifndef DCVM_DCVM_DCVMERROR_H_
#define DCVM_DCVM_DCVMERROR_H_

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P) (P)
#endif

#define DCVMERROR_BASE 0xA0000000
#define MAKE_DCVM_ERROR(err) (DCVMERROR_BASE | (err))
#define IS_DCVM_ERROR(err) (DCVMERROR_BASE == DCVMERROR_BASE & (err))

#define DCVM_SUCCESS(err) (!IS_DCVM_ERROR((err)))
#define DCVM_FAILED(err) (IS_DCVM_ERROR((err)))

enum DCVM_ERROR
{
    DCVM_ERR_SUCCESS
    , DCVM_ERR_NOT_IMPLEMENTED          = MAKE_DCVM_ERROR(0x1)
    , DCVM_ERR_BAD_PARAMS               = MAKE_DCVM_ERROR(0x2)
    , DCVM_ERR_INSUFFICIENT_RESOURCES   = MAKE_DCVM_ERROR(0x3)
    , DCVM_ERR_INTERNAL                 = MAKE_DCVM_ERROR(0x4)
    , DCVM_ERR_CANNOT_LOG_IN            = MAKE_DCVM_ERROR(0x5)
};

const char* DCVMErrorToString(enum DCVM_ERROR err);

#endif