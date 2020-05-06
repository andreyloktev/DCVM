#include <dcvm/provider/utilities/DCVMUriBuilder.hpp>
#include "dcvm_systemapi_test.h"
#include <gtest/gtest.h>

using namespace dcvm::provider::utilities;

TEST(DCVMUriBuilder, base_tests)
{
    InitDCVMSystemApi();

    {
        auto validUri = DCVM_TEXT("http://127.0.0.1/hello/world?firstname=Andrey&lastname=Loktev");

        auto uri = DCVMUriBuilder()
            .SetScheme(DCVM_TEXT("http"))
            .SetHost(DCVM_TEXT("127.0.0.1"))
            .AppendPath(DCVM_TEXT("hello/world"))
            .AppendQuery(DCVM_TEXT("firstname=Andrey&lastname=Loktev"))
            .Build();

        EXPECT_EQ(validUri, uri);
    }

    ASSERT_TRUE(0 == g_MemoryCounter);
}