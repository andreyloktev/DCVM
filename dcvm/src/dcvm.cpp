#include <dcvm/dcvm.h>
#include <dcvm/DCVMLogger.h>
#include "base/DCVMTypes.hpp"
#include "base/MemoryBase.hpp"
#include "base/SystemApi.hpp"

namespace dcvm {

DCVMSystemAPI *g_pSystemApi = nullptr;

} //namespace dcvm

struct DCVM final : public dcvm::base::MemoryBase<dcvm::base::SystemApi>
{
};

extern "C"
{
    DCVM_ERROR dcvm_Init(DCVMSystemAPI *pSystemApi, struct DCVM **ppDcvm, struct DCVMContext *pCtxt)
    {
        UNREFFERENCE_VARIABLE(pCtxt);

        if ((nullptr == pSystemApi) || (nullptr == ppDcvm))
        {
            DCVM_ERROR_TRACE(DCVM_ERR_BAD_PARAMS);
            return DCVM_ERR_BAD_PARAMS;
        }

        dcvm::g_pSystemApi = pSystemApi;

        *ppDcvm = new DCVM();
        if (nullptr == *ppDcvm)
        {
            DCVM_ERROR_TRACE(DCVM_ERR_INSUFFICIENT_RESOURCES);
            return DCVM_ERR_INSUFFICIENT_RESOURCES;
        }

        return DCVM_ERR_SUCCESS;
    }

    void dcvm_Release(DCVM *pDcvm, struct DCVMContext *pCtxt)
    {
        UNREFFERENCE_VARIABLE(pCtxt);

        if (nullptr == pDcvm)
        {
            return;
        }

        delete pDcvm;
    }

    
    void dcvm_ControlAddClient(struct DCVM *pDcvm, const DCVMCloudDiskAPI pClient, struct DCVMContext *pCtxt);

    
    void dcvm_ControlGetUnauthorizedClients(struct DCVM *pDcvm, DCVMClientOAuthUri **pClients, struct DCVMContext *pCtxt);

    
    enum DCVM_ERROR dcvm_ControlLogIn(struct DCVM *pDcvm, const DCVMClientOAuthCode *pCodes, struct DCVMCloudDisk **ppCloudDisk, struct DCVMContext *pCtxt);

    
    void dcvm_ControlLogOut(struct DCVM *pDcvm, struct DCVMCloudDisk *pCloudDisk, struct DCVMContext *pCtxt);

    
    void dcvm_ReleaseString(struct DCVM *pDcvm, dcvm_char_t *pStr);
}