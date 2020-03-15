#include <dcvm/provider/DCVMCryptoHelper.hpp>
#include "dcvm_systemapi_test.h"

#include <gtest/gtest.h>

TEST(DCVMCryptoHelper, dcvm_tobase64url_utest)
{
    InitDCVMSystemApi();

    {
        // Encode one symbol.
        dcvm::base::DCVMString_t inStr = DCVM_TEXT("A");
        dcvm::base::DCVMString_t verifyStr = DCVM_TEXT("QQ==");
        dcvm::base::DCVMVector_t<dcvm_uint8_t> out;

        auto err = dcvm::provider::DCVMCryptoHelper::ToBase64Url(dcvm::base::DCVMVector_t<dcvm_uint8_t>(inStr.cbegin(), inStr.cend()), out);
        ASSERT_TRUE(DCVM_SUCCESS(err));
        
        dcvm::base::DCVMString_t outStr(out.cbegin(), out.cend());
        EXPECT_TRUE(outStr == verifyStr);

        // Encode two symbol
        inStr = DCVM_TEXT("AA");
        verifyStr = DCVM_TEXT("QUE=");

        out.clear();
        err = dcvm::provider::DCVMCryptoHelper::ToBase64Url(dcvm::base::DCVMVector_t<dcvm_uint8_t>(inStr.cbegin(), inStr.cend()), out);
        ASSERT_TRUE(DCVM_SUCCESS(err));
        
        outStr = std::move(dcvm::base::DCVMString_t(out.cbegin(), out.cend()));
        EXPECT_TRUE(outStr == verifyStr);

        // Encode string without padding.
        inStr = DCVM_TEXT("My name is Andrey. I would like to create DCVM library");
        verifyStr = DCVM_TEXT("TXkgbmFtZSBpcyBBbmRyZXkuIEkgd291bGQgbGlrZSB0byBjcmVhdGUgRENWTSBsaWJyYXJ5");

        out.clear();
        err = dcvm::provider::DCVMCryptoHelper::ToBase64Url(dcvm::base::DCVMVector_t<dcvm_uint8_t>(inStr.cbegin(), inStr.cend()), out);
        ASSERT_TRUE(DCVM_SUCCESS(err));

        outStr = std::move(dcvm::base::DCVMString_t(out.cbegin(), out.cend()));
        EXPECT_TRUE(outStr == verifyStr);

        // Encode strign with length > 2 with padding
        inStr = DCVM_TEXT("My name is Andrey. I would like to create DCVM library!");
        verifyStr = DCVM_TEXT("TXkgbmFtZSBpcyBBbmRyZXkuIEkgd291bGQgbGlrZSB0byBjcmVhdGUgRENWTSBsaWJyYXJ5IQ==");

        out.clear();
        err = dcvm::provider::DCVMCryptoHelper::ToBase64Url(dcvm::base::DCVMVector_t<dcvm_uint8_t>(inStr.cbegin(), inStr.cend()), out);
        ASSERT_TRUE(DCVM_SUCCESS(err));
        
        outStr = std::move(dcvm::base::DCVMString_t(out.cbegin(), out.cend()));
        EXPECT_TRUE(outStr == verifyStr);

        // Encode empty string
        inStr = DCVM_TEXT("");
        out.clear();
        err = dcvm::provider::DCVMCryptoHelper::ToBase64Url(dcvm::base::DCVMVector_t<dcvm_uint8_t>(inStr.cbegin(), inStr.cend()), out);

        EXPECT_TRUE(out.empty());


    }

    ASSERT_TRUE(0 == g_MemoryCounter);
}

TEST(DCVMCryptoHelper, dcvm_tobase64url_no_padding_utest)
{
    InitDCVMSystemApi();

    {
        // Encode one symbol.
        dcvm::base::DCVMString_t inStr = DCVM_TEXT("A");
        dcvm::base::DCVMString_t verifyStr = DCVM_TEXT("QQ");
        dcvm::base::DCVMVector_t<dcvm_uint8_t> out;

        auto err = dcvm::provider::DCVMCryptoHelper::ToBase64Url(dcvm::base::DCVMVector_t<dcvm_uint8_t>(inStr.cbegin(), inStr.cend()), out, true);
        ASSERT_TRUE(DCVM_SUCCESS(err));
        
        dcvm::base::DCVMString_t outStr(out.cbegin(), out.cend());
        EXPECT_TRUE(outStr == verifyStr);

        // Encode two symbol
        inStr = DCVM_TEXT("AA");
        verifyStr = DCVM_TEXT("QUE");

        out.clear();
        err = dcvm::provider::DCVMCryptoHelper::ToBase64Url(dcvm::base::DCVMVector_t<dcvm_uint8_t>(inStr.cbegin(), inStr.cend()), out, true);
        ASSERT_TRUE(DCVM_SUCCESS(err));
        
        outStr = std::move(dcvm::base::DCVMString_t(out.cbegin(), out.cend()));
        EXPECT_TRUE(outStr == verifyStr);

        // Encode string without padding.
        inStr = DCVM_TEXT("My name is Andrey. I would like to create DCVM library");
        verifyStr = DCVM_TEXT("TXkgbmFtZSBpcyBBbmRyZXkuIEkgd291bGQgbGlrZSB0byBjcmVhdGUgRENWTSBsaWJyYXJ5");

        out.clear();
        err = dcvm::provider::DCVMCryptoHelper::ToBase64Url(dcvm::base::DCVMVector_t<dcvm_uint8_t>(inStr.cbegin(), inStr.cend()), out, true);
        ASSERT_TRUE(DCVM_SUCCESS(err));

        outStr = std::move(dcvm::base::DCVMString_t(out.cbegin(), out.cend()));
        EXPECT_TRUE(outStr == verifyStr);

        // Encode strign with length > 2 with padding
        inStr = DCVM_TEXT("My name is Andrey. I would like to create DCVM library!");
        verifyStr = DCVM_TEXT("TXkgbmFtZSBpcyBBbmRyZXkuIEkgd291bGQgbGlrZSB0byBjcmVhdGUgRENWTSBsaWJyYXJ5IQ");

        out.clear();
        err = dcvm::provider::DCVMCryptoHelper::ToBase64Url(dcvm::base::DCVMVector_t<dcvm_uint8_t>(inStr.cbegin(), inStr.cend()), out, true);
        ASSERT_TRUE(DCVM_SUCCESS(err));
        
        outStr = std::move(dcvm::base::DCVMString_t(out.cbegin(), out.cend()));
        EXPECT_TRUE(outStr == verifyStr);

        // Encode empty string
        inStr = DCVM_TEXT("");
        out.clear();
        err = dcvm::provider::DCVMCryptoHelper::ToBase64Url(dcvm::base::DCVMVector_t<dcvm_uint8_t>(inStr.cbegin(), inStr.cend()), out);

        EXPECT_TRUE(out.empty());


    }

    ASSERT_TRUE(0 == g_MemoryCounter);
}