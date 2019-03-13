#include <dcvm.h>

struct Dcvm final
{

};

extern "C"
{
    DCVMError dcvm_Init(struct DCVM **ppDcvm)
    {
        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    void dcvm_Release(struct DCVM *pDcvm)
    {
        if (pDcvm)
        {
            delete pDcvm;
        }
    }

    DCVMError dcvm_ControlGetOauth2Url(struct DCVM *pDcvm, DCVMCloudDiskTypes type, DCVMChar_t **ppUrl)
    {
        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    DCVMError dcvm_ControlLogIn(struct DCVM *pDcvm, DCVMCloudDiskTypes type, const DCVMChar_t *pCode)
    {
        return DCVM_ERR_NOT_IMPLEMENTED;
    }

    void dcvm_ReleaseString(struct DCVM *pDcvm, DCVMChar_t *pStr)
    {
        if (pStr)
        {
            delete[]pStr;
        }
    }
}