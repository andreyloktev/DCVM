#include <dcvm/dcvm.h>
#include "dcvm_systemapi_test.h"

#include <memory>
#include <gtest/gtest.h>

namespace {

DCVMSystemAPI GetDCVMSystemApi()
{
    return DCVMSystemAPI
    {
        DCVMMemoryAlloc_test
        , DCVMMemoryFree_test
        , DCVMMemorySet_test
        , DCVMMemoryCopy_test
        , DCVMMemoryCompare_test
        , DCVMSendHttpRequest_test
    };
}

struct DCVMDeleter final
{
    void operator()(DCVM *p) noexcept
    {
        if (p)
        {
            dcvm_Release(p, nullptr);
        }
    }
};

using PDCVM = std::unique_ptr<DCVM, DCVMDeleter>;

PDCVM CreateDCVM()
{
    DCVM *pDCVM = nullptr;

    dcvm_Init(GetDCVMSystemApi(), &pDCVM, nullptr);
    return PDCVM(pDCVM);
}

} // namespace 

TEST(DCVMControl, dcvm_library_initialization)
{
    DCVM *pDCVM = nullptr;

    DCVM_ERROR err = dcvm_Init(GetDCVMSystemApi(), &pDCVM, nullptr);
    EXPECT_TRUE(DCVM_SUCCESS(err));

    dcvm_Release(pDCVM, nullptr);

    EXPECT_EQ(g_MemoryCounter, 0);
}