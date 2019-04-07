#ifndef DCVM_DCVM_CLOUDSTORAGE_H_
#define DCVM_DCVM_CLOUDSTORAGE_H_

#include <dcvm/DCVMTypes.h>
#include <dcvm/DCVMError.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _DCVMCloudStorage
{
    /*!
     * \brief Get
    */
    enum DCVMError (*GetOAuthUrl)(dcvm_char_t **ppUrl, struct DCVMContext *pContext);
} DCVMCloudStorage;

#ifdef __cplusplus
};
#endif

#endif