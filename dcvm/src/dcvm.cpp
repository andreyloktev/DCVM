#include <dcvm/dcvm.h>
#include "base/DCVMTypes.hpp"


struct DCVM final
{

};

extern "C"
{
    enum DCVM_ERROR dcvm_Init(struct DCVM **ppDcvm, struct DCVMContext *pCtxt)
    {

    }

    void dcvm_Release(struct DCVM *pDcvm, struct DCVMContext *pCtxt);

    
    void dcvm_ControlAddClient(struct DCVM *pDcvm, const DCVMCloudDiskAPI pClient, struct DCVMContext *pCtxt);

    
    void dcvm_ControlGetUnauthorizedClients(struct DCVM *pDcvm, DCVMClientOAuthUri **pClients, struct DCVMContext *pCtxt);

    
    enum DCVM_ERROR dcvm_ControlLogIn(struct DCVM *pDcvm, const DCVMClientOAuthCode *pCodes, struct DCVMCloudDisk **ppCloudDisk, struct DCVMContext *pCtxt);

    
    void dcvm_ControlLogOut(struct DCVM *pDcvm, struct DCVMCloudDisk *pCloudDisk, struct DCVMContext *pCtxt);

    
    void dcvm_ReleaseString(struct DCVM *pDcvm, dcvm_char_t *pStr);
}