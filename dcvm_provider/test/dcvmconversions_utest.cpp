#include <dcvm/provider/utilities/conversions/DCVMConversions.hpp>
#include "dcvm_systemapi_test.h"

#include <gtest/gtest.h>

using namespace dcvm::provider::utilities::conversions;

TEST(DCVMConversions, dcvm_utf16_to_utf8_utest)
{
    InitDCVMSystemApi();

    {
        dcvm::base::DCVMUtf8String_t validDstStr = {
            (char)0x48, (char)0x65, (char)0x6C, (char)0x6C,
            (char)0x6F, (char)0x20, (char)0x77, (char)0x6F,
            (char)0x72, (char)0x6C, (char)0x64
        };

        dcvm::base::DCVMUtf16String_t srcStr = {
            (wchar_t)0x48, (wchar_t)0x65, (wchar_t)0x6C, (wchar_t)0x6C,
            (wchar_t)0x6F, (wchar_t)0x20, (wchar_t)0x77, (wchar_t)0x6F,
            (wchar_t)0x72, (wchar_t)0x6C, (wchar_t)0x64
        };

        dcvm::base::DCVMUtf8String_t dstStr;

        // One byte sequence
        EXPECT_TRUE(DCVM_SUCCESS(Utf16ToUtf8(srcStr, dstStr)));
        EXPECT_EQ(dstStr.length(), validDstStr.length());
        EXPECT_EQ(dstStr, validDstStr);

        // Two bytes sequence
        validDstStr = {
            (char)0xD0, (char)0x9F, (char)0xD1, (char)0x80, (char)0xD0, (char)0xB8,
            (char)0xD0, (char)0xB2, (char)0xD0, (char)0xB5, (char)0xD1, (char)0x82,
            (char)0x20, (char)0xD0, (char)0xBC, (char)0xD0, (char)0xB8, (char)0xD1,
            (char)0x80
        };

        srcStr = {
            (wchar_t)0x041f, (wchar_t)0x0440, (wchar_t)0x0438, (wchar_t)0x0432,
            (wchar_t)0x0435, (wchar_t)0x0442, (wchar_t)0x0020, (wchar_t)0x043c,
            (wchar_t)0x0438, (wchar_t)0x0440
        };

        EXPECT_TRUE(DCVM_SUCCESS(Utf16ToUtf8(srcStr, dstStr)));
        EXPECT_EQ(dstStr.length(), validDstStr.length());
        EXPECT_EQ(dstStr, validDstStr);

        // Three bytes sequence
        validDstStr = {
            (char)0xEC, (char)0x95, (char)0x88, (char)0xEB, (char)0x85, (char)0x95,
            (char)0xED, (char)0x95, (char)0x98, (char)0xEC, (char)0x84, (char)0xB8,
            (char)0xEC, (char)0x9A, (char)0x94, (char)0x20, (char)0xEC, (char)0x84,
            (char)0xB8, (char)0xEA, (char)0xB3, (char)0x84
        };

        srcStr = {
            (wchar_t)0xC548, (wchar_t)0xB155, (wchar_t)0xD558, (wchar_t)0xC138,
            (wchar_t)0xC694, (wchar_t)0x0020, (wchar_t)0xC138, (wchar_t)0xACC4
        };

        EXPECT_TRUE(DCVM_SUCCESS(Utf16ToUtf8(srcStr, dstStr)));
        EXPECT_EQ(dstStr.length(), validDstStr.length());
        EXPECT_EQ(dstStr, validDstStr);

        // Four bytes sequence.
        validDstStr = {
            (char)0xF0, (char)0x90, (char)0x80, (char)0x80,
            (char)0xF0, (char)0x90, (char)0xB9, (char)0xAD,
            (char)0xF0, (char)0x9D, (char)0x84, (char)0x9E,
            (char)0xF4, (char)0x8F, (char)0xBF, (char)0xBF
        };

        srcStr = {
            (wchar_t)0xD800, (wchar_t)0xDC00,
            (wchar_t)0xD803, (wchar_t)0xDE6D,
            (wchar_t)0xD834, (wchar_t)0xDD1E,
            (wchar_t)0xDBFF, (wchar_t)0xDFFF
        };

        EXPECT_TRUE(DCVM_SUCCESS(Utf16ToUtf8(srcStr, dstStr)));
        EXPECT_EQ(dstStr.length(), validDstStr.length());
        EXPECT_EQ(dstStr, validDstStr);
    }

    ASSERT_TRUE(0 == g_MemoryCounter);
}

TEST(DCVMConversions, dcvm_utf16_to_utf8_negative_utest)
{
    InitDCVMSystemApi();

    {
        dcvm::base::DCVMUtf8String_t dstStr;
        dcvm::base::DCVMUtf16String_t srcStr;

        EXPECT_TRUE(DCVM_SUCCESS(Utf16ToUtf8(srcStr, dstStr)));
        EXPECT_TRUE(dstStr.empty());

        // Miss low surrogate
        srcStr = {
            (wchar_t)0xD800
        };

        EXPECT_TRUE(DCVM_FAILED(Utf16ToUtf8(srcStr, dstStr)));

        // Invalid surrogate pair
        srcStr = {
            (wchar_t)0xD800, (wchar_t)0xACC4
        };

        EXPECT_TRUE(DCVM_FAILED(Utf16ToUtf8(srcStr, dstStr)));
    }

    ASSERT_TRUE(0 == g_MemoryCounter);
}

TEST(DCVMConversons, dcvm_utf8_to_utf16_utest)
{
    InitDCVMSystemApi();

    {
        dcvm::base::DCVMUtf16String_t validDstStr = {
            (wchar_t)0x48, (wchar_t)0x65, (wchar_t)0x6C, (wchar_t)0x6C,
            (wchar_t)0x6F, (wchar_t)0x20, (wchar_t)0x77, (wchar_t)0x6F,
            (wchar_t)0x72, (wchar_t)0x6C, (wchar_t)0x64
        };

        dcvm::base::DCVMUtf8String_t srcStr = {
            (char)0x48, (char)0x65, (char)0x6C, (char)0x6C,
            (char)0x6F, (char)0x20, (char)0x77, (char)0x6F,
            (char)0x72, (char)0x6C, (char)0x64
        };

        dcvm::base::DCVMUtf16String_t dstStr;

        // One byte sequence
        EXPECT_TRUE(DCVM_SUCCESS(Utf8ToUtf16(srcStr, dstStr)));
        EXPECT_EQ(dstStr.length(), validDstStr.length());
        EXPECT_EQ(dstStr, validDstStr);

        // Two bytes sequence
        validDstStr = {
            (wchar_t)0x041f, (wchar_t)0x0440, (wchar_t)0x0438, (wchar_t)0x0432,
            (wchar_t)0x0435, (wchar_t)0x0442, (wchar_t)0x0020, (wchar_t)0x043c,
            (wchar_t)0x0438, (wchar_t)0x0440
        };

        srcStr = {
            (char)0xD0, (char)0x9F, (char)0xD1, (char)0x80, (char)0xD0, (char)0xB8,
            (char)0xD0, (char)0xB2, (char)0xD0, (char)0xB5, (char)0xD1, (char)0x82,
            (char)0x20, (char)0xD0, (char)0xBC, (char)0xD0, (char)0xB8, (char)0xD1,
            (char)0x80
        };

        EXPECT_TRUE(DCVM_SUCCESS(Utf8ToUtf16(srcStr, dstStr)));
        EXPECT_EQ(dstStr.length(), validDstStr.length());
        EXPECT_EQ(dstStr, validDstStr);

        // Three bytes sequence
        validDstStr = {
            (wchar_t)0xC548, (wchar_t)0xB155, (wchar_t)0xD558, (wchar_t)0xC138,
            (wchar_t)0xC694, (wchar_t)0x0020, (wchar_t)0xC138, (wchar_t)0xACC4
        };

        srcStr = {
            (char)0xEC, (char)0x95, (char)0x88, (char)0xEB, (char)0x85, (char)0x95,
            (char)0xED, (char)0x95, (char)0x98, (char)0xEC, (char)0x84, (char)0xB8,
            (char)0xEC, (char)0x9A, (char)0x94, (char)0x20, (char)0xEC, (char)0x84,
            (char)0xB8, (char)0xEA, (char)0xB3, (char)0x84
        };

        EXPECT_TRUE(DCVM_SUCCESS(Utf8ToUtf16(srcStr, dstStr)));
        EXPECT_EQ(dstStr.length(), validDstStr.length());
        EXPECT_EQ(dstStr, validDstStr);

        // Four bytes sequence.
        validDstStr = {
            (wchar_t)0xD800, (wchar_t)0xDC00,
            (wchar_t)0xD803, (wchar_t)0xDE6D,
            (wchar_t)0xD834, (wchar_t)0xDD1E,
            (wchar_t)0xDBFF, (wchar_t)0xDFFF
        };
        
        srcStr = {
            (char)0xF0, (char)0x90, (char)0x80, (char)0x80,
            (char)0xF0, (char)0x90, (char)0xB9, (char)0xAD,
            (char)0xF0, (char)0x9D, (char)0x84, (char)0x9E,
            (char)0xF4, (char)0x8F, (char)0xBF, (char)0xBF
        };

        EXPECT_TRUE(DCVM_SUCCESS(Utf8ToUtf16(srcStr, dstStr)));
        EXPECT_EQ(dstStr.length(), validDstStr.length());
        EXPECT_EQ(dstStr, validDstStr);
    }

    ASSERT_TRUE(0 == g_MemoryCounter);
}

TEST(DCVMConversions, dcvm_utf8_to_utf16_negative_utest)
{
    InitDCVMSystemApi();

    {
        dcvm::base::DCVMUtf16String_t dstStr;
        dcvm::base::DCVMUtf8String_t srcStr;

        EXPECT_TRUE(DCVM_SUCCESS(Utf8ToUtf16(srcStr, dstStr)));
        EXPECT_TRUE(dstStr.empty());

        // Start with invalid byte
        srcStr = {
            (char)0x9F, (char)0xD1, (char)0x80, (char)0xD0, (char)0xB8,
            (char)0xD0, (char)0xB2, (char)0xD0, (char)0xB5, (char)0xD1, (char)0x82
        };

        EXPECT_TRUE(DCVM_FAILED(Utf8ToUtf16(srcStr, dstStr)));

        // Missed one byte in two bytes sequence
        srcStr = {
            (char)0xD0, (char)0xD1, (char)0x80, (char)0xD0, (char)0xB8,
            (char)0xD0, (char)0xB2, (char)0xD0, (char)0xB5, (char)0xD1, (char)0x82
        };

        EXPECT_TRUE(DCVM_FAILED(Utf8ToUtf16(srcStr, dstStr)));

        // Missed one byte in three bytes sequence
        srcStr = {
            (char)0xEC, (char)0x95
        };

        EXPECT_TRUE(DCVM_FAILED(Utf8ToUtf16(srcStr, dstStr)));

        // Invalid bytes order in thre bytes sequrnce
        srcStr = {
            (char)0x95, (char)0xEC, (char)0x88, (char)0xEB, (char)0x85, (char)0x95,
            (char)0xED, (char)0x95, (char)0x98, (char)0xEC, (char)0x84, (char)0xB8,
            (char)0xEC, (char)0x9A, (char)0x94, (char)0x20
        };

        EXPECT_TRUE(DCVM_FAILED(Utf8ToUtf16(srcStr, dstStr)));

        // Missed one byte in four bytes sequence
        srcStr = {
            (char)0xF0, (char)0x90, (char)0x80
        };

        EXPECT_TRUE(DCVM_FAILED(Utf8ToUtf16(srcStr, dstStr)));

        // Invalid bytes order in four bytes sequence
        srcStr = {
            (char)0xF0, (char)0x90, (char)0x80, (char)0x80,
            (char)0xF0, (char)0x90, (char)0xB9, (char)0xAD,
            (char)0xF0, (char)0x9D, (char)0x84, (char)0x5E, // Invalid 0x5E
            (char)0xF4, (char)0x8F, (char)0xBF, (char)0xBF
        };

        EXPECT_TRUE(DCVM_FAILED(Utf8ToUtf16(srcStr, dstStr)));

        // Invalid first byte
        srcStr = {
            (char)0x90, (char)0x9F, (char)0xD1, (char)0x80, (char)0xD0, (char)0xB8
        };

        EXPECT_TRUE(DCVM_FAILED(Utf8ToUtf16(srcStr, dstStr)));

        // Invalid first byte
        srcStr = {
            (char)0xF8, (char)0x9F, (char)0xD1, (char)0x80, (char)0xD0, (char)0xB8
        };

        EXPECT_TRUE(DCVM_FAILED(Utf8ToUtf16(srcStr, dstStr)));
    }

    ASSERT_TRUE(0 == g_MemoryCounter);
}