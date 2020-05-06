#include <dcvm/DCVMLogger.h>
#include <dcvm/provider/utilities/conversions/DCVMConversions.hpp>

//########################################################
// Based on cpprestsdk conversions implementation.
//########################################################

#define LOW_3BITS 0x7
#define LOW_4BITS 0xF
#define LOW_5BITS 0x1F
#define LOW_6BITS 0x3F
#define BIT4 0x8
#define BIT5 0x10
#define BIT6 0x20
#define BIT7 0x40
#define BIT8 0x80
#define L_SURROGATE_START 0xDC00
#define L_SURROGATE_END 0xDFFF
#define H_SURROGATE_START 0xD800
#define H_SURROGATE_END 0xDBFF
#define SURROGATE_PAIR_START 0x10000

namespace dcvm          {
namespace provider      {
namespace utilities     {
namespace conversions   {

namespace {

using UTF16String_t = base::DCVMUtf16String_t;
using UTF8String_t = base::DCVMUtf8String_t;

/* UTF-8 specification https://tools.ietf.org/html/rfc3629
Char. number range  |        UTF-8 octet sequence
   (hexadecimal)    |              (binary)
--------------------+-------------------------------------
0000 0000-0000 007F | 0xxxxxxx
0000 0080-0000 07FF | 110xxxxx 10xxxxxx
0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
*/

// Create a dedicated type for characters to avoid the issue
// of different platforms defaulting char to be either signed
// or unsigned.
using UtilCharInternal_t = signed char;

static DCVM_ERROR CountUtf8ToUtf16(const dcvm::base::DCVMUtf8String_t &s, dcvm_size_t &result) noexcept
{
    const dcvm_size_t sSize = s.size();
    auto const sData = reinterpret_cast<const UtilCharInternal_t*>(s.data());
    result = sSize;

    for (dcvm_size_t index = 0; index < sSize;)
    {
        if (sData[index] >= 0)
        {
            // use fast inner loop to skip single byte code points (which are
            // expected to be the most frequent)
            while ((++index < sSize) && (sData[index] >= 0));

            if (index >= sSize) break;
        }

        // start special handling for multi-byte code points
        const UtilCharInternal_t c {sData[index++]};

        if ((c & BIT7) == 0)
        {
            //UTF-8 string character can never start with 10xxxxxx
            return DCVM_ERR_UTF8_TO_UTF16_ERROR;
        }
        else if ((c & BIT6) == 0) // 2 byte character, 0x80 to 0x7FF
        {
            if (index == sSize)
            {
                // UTF-8 string is missing bytes in character
                return DCVM_ERR_UTF8_TO_UTF16_ERROR;
            }

            const UtilCharInternal_t c2 {sData[index++]};
            if ((c2 & 0xC0) != BIT8)
            {
                // UTF-8 continuation byte is missing leading bit mask
                return DCVM_ERR_UTF8_TO_UTF16_ERROR;
            }

            // can't require surrogates for 7FF
            --result;
        }
        else if ((c & BIT5) == 0) // 3 byte character, 0x800 to 0xFFFF
        {
            if (sSize - index < 2)
            {
                // UTF-8 string is missing bytes in character
                return DCVM_ERR_UTF8_TO_UTF16_ERROR;
            }

            const UtilCharInternal_t c2 {sData[index++]};
            const UtilCharInternal_t c3 {sData[index++]};
            if (((c2 | c3) & 0xC0) != BIT8)
            {
                // UTF-8 continuation byte is missing leading bit mask
                return DCVM_ERR_UTF8_TO_UTF16_ERROR;
            }

            result -= 2;
        }
        else if ((c & BIT4) == 0) // 4 byte character, 0x10000 to 0x10FFFF
        {
            if (sSize - index < 3)
            {
                // UTF-8 string is missing bytes in character
                return DCVM_ERR_UTF8_TO_UTF16_ERROR;
            }

            const UtilCharInternal_t c2 {sData[index++]};
            const UtilCharInternal_t c3 {sData[index++]};
            const UtilCharInternal_t c4 {sData[index++]};
            if (((c2 | c3 | c4) & 0xC0) != BIT8)
            {
                // UTF-8 continuation byte is missing leading bit mask
                return DCVM_ERR_UTF8_TO_UTF16_ERROR;
            }

            const dcvm_uint32_t codePoint =
                ((c & LOW_3BITS) << 18) | ((c2 & LOW_6BITS) << 12) | ((c3 & LOW_6BITS) << 6) | (c4 & LOW_6BITS);
            result -= (dcvm_size_t(3) - (codePoint >= SURROGATE_PAIR_START));
        }
        else
        {
            // UTF-8 string has invalid Unicode code point
            return DCVM_ERR_UTF8_TO_UTF16_ERROR;
        }
    }

    return DCVM_ERR_SUCCESS;
}

// UTF16 specification: https://tools.ietf.org/html/rfc2781
static DCVM_ERROR CountUtf16ToUtf8(const UTF16String_t& w, dcvm_size_t &result) noexcept
{
    const UTF16String_t::value_type* const srcData = &w[0];
    const dcvm_size_t srcSize = w.size();
    result = srcSize;

    for (size_t index = 0; index < srcSize; ++index)
    {
        const UTF16String_t::value_type ch{srcData[index]};
        if (ch <= 0x7FF)
        {
            if (ch > 0x7F) // 2 bytes needed (11 bits used)
            {
                ++result;
            }
        }
        // Check for high surrogate.
        else if (ch >= H_SURROGATE_START && ch <= H_SURROGATE_END) // 4 bytes needed (21 bits used)
        {
            ++index;
            if (index == srcSize)
            {
                // UTF-16 string is missing low surrogate
                return DCVM_ERR_UTF16_TO_UTF8_ERROR;
            }

            const auto lowSurrogate = srcData[index];
            if (lowSurrogate < L_SURROGATE_START || lowSurrogate > L_SURROGATE_END)
            {
                // UTF-16 string has invalid low surrogate
                return DCVM_ERR_UTF16_TO_UTF8_ERROR;
            }

            result += 2;
        }
        else // 3 bytes needed (16 bits used)
        {
            result += 2;
        }
    }

    return DCVM_ERR_SUCCESS;
}

} // namespace empty

//###################################### UTF-8 ---> UTF-16 ###########################################################

DCVM_ERROR Utf8ToUtf16(const dcvm::base::DCVMUtf8String_t &utf8Str, dcvm::base::DCVMUtf16String_t &utf16Str) noexcept
{
    if (utf8Str.empty())
    {
        return DCVM_ERR_SUCCESS;
    }

    DCVM_BEGIN_CATCH_HANDLER
    // Save repeated heap allocations, use the length of resulting sequence.
    const dcvm_size_t srcSize = utf8Str.size();
    auto const srcData = reinterpret_cast<const UtilCharInternal_t*>(utf8Str.data());

    dcvm_size_t dstSize = 0;
    auto err = CountUtf8ToUtf16(utf8Str, dstSize);
    if (DCVM_FAILED(err))
    {
        return err;
    }

    utf16Str = UTF16String_t(dstSize, L'\0');
    UTF16String_t::value_type* const destData = &utf16Str[0];
    dcvm_size_t destIndex = 0;

    for (dcvm_size_t index = 0; index < srcSize; ++index)
    {
        UtilCharInternal_t src = srcData[index];
        switch (src & 0xF0)
        {
            case 0xF0: // 4 byte character, 0x10000 to 0x10FFFF
            {
                const UtilCharInternal_t c2 {srcData[++index]};
                const UtilCharInternal_t c3 {srcData[++index]};
                const UtilCharInternal_t c4 {srcData[++index]};
                dcvm_uint32_t codePoint =
                    ((src & LOW_3BITS) << 18) | ((c2 & LOW_6BITS) << 12) | ((c3 & LOW_6BITS) << 6) | (c4 & LOW_6BITS);
                if (codePoint >= SURROGATE_PAIR_START)
                {
                    // In UTF-16 U+10000 to U+10FFFF are represented as two 16-bit code units, surrogate pairs.
                    //  - 0x10000 is subtracted from the code point
                    //  - high surrogate is 0xD800 added to the top ten bits
                    //  - low surrogate is 0xDC00 added to the low ten bits
                    codePoint -= SURROGATE_PAIR_START;
                    destData[destIndex++] = static_cast<UTF16String_t::value_type>((codePoint >> 10) | H_SURROGATE_START);
                    destData[destIndex++] =
                        static_cast<UTF16String_t::value_type>((codePoint & 0x3FF) | L_SURROGATE_START);
                }
                else
                {
                    // In UTF-16 U+0000 to U+D7FF and U+E000 to U+FFFF are represented exactly as the Unicode code point
                    // value. U+D800 to U+DFFF are not valid characters, for simplicity we assume they are not present
                    // but will encode them if encountered.
                    destData[destIndex++] = static_cast<UTF16String_t::value_type>(codePoint);
                }
            }
            break;
            case 0xE0: // 3 byte character, 0x800 to 0xFFFF
            {
                const UtilCharInternal_t c2 {srcData[++index]};
                const UtilCharInternal_t c3 {srcData[++index]};
                destData[destIndex++] = static_cast<UTF16String_t::value_type>(
                    ((src & LOW_4BITS) << 12) | ((c2 & LOW_6BITS) << 6) | (c3 & LOW_6BITS));
            }
            break;
            case 0xD0: // 2 byte character, 0x80 to 0x7FF
            case 0xC0:
            {
                const UtilCharInternal_t c2 {srcData[++index]};
                destData[destIndex++] =
                    static_cast<UTF16String_t::value_type>(((src & LOW_5BITS) << 6) | (c2 & LOW_6BITS));
            }
            break;
            default: // single byte character, 0x0 to 0x7F
                // try to use a fast inner loop for following single byte characters,
                // since they are quite probable
                do
                {
                    destData[destIndex++] = static_cast<UTF16String_t::value_type>(srcData[index++]);
                } while (index < srcSize && srcData[index] > 0);
                // adjust index since it will be incremented by the for loop
                --index;
        }
    }
    DCVM_END_CATCH_HANDLER

    return DCVM_ERR_SUCCESS;
}

DCVM_ERROR Utf8ToUtf16(const base::DCVMUtf16String_t &utf16StrIn, base::DCVMUtf16String_t &utf16StrOut) noexcept
{
    DCVM_BEGIN_CATCH_HANDLER

    utf16StrOut = utf16StrIn;
    return DCVM_ERR_SUCCESS;

    DCVM_END_CATCH_HANDLER
}

//###################################### UTF-16 ---> UTF-8 ###########################################################

DCVM_ERROR Utf16ToUtf8(const base::DCVMUtf16String_t &utf16Str, base::DCVMUtf8String_t &utf8Str) noexcept
{
    if (utf16Str.empty())
    {
        return DCVM_ERR_SUCCESS;
    }

    DCVM_BEGIN_CATCH_HANDLER 
    dcvm_size_t dstSize = 0;
    auto err = CountUtf16ToUtf8(utf16Str, dstSize);
    if (DCVM_FAILED(err))
    {
        return err;
    }

    const dcvm_size_t srcSize = utf16Str.size();
    const UTF16String_t::value_type* const srcData = &utf16Str[0];
    
    utf8Str = UTF8String_t(dstSize, '\0');
    UTF8String_t::value_type* const destData = &utf8Str[0];

    dcvm_size_t destIndex{0};

    for (dcvm_size_t index = 0; index < srcSize; ++index)
    {
        const UTF16String_t::value_type src = srcData[index];
        if (src <= 0x7FF)
        {
            if (src <= 0x7F) // single byte character
            {
                destData[destIndex++] = static_cast<char>(src);
            }
            else // 2 bytes needed (11 bits used)
            {
                destData[destIndex++] = static_cast<char>(char((src >> 6) | 0xC0));        // leading 5 bits
                destData[destIndex++] = static_cast<char>(char((src & LOW_6BITS) | BIT8)); // trailing 6 bits
            }
        }
        // Check for high surrogate.
        else if (src >= H_SURROGATE_START && src <= H_SURROGATE_END)
        {
            const auto highSurrogate = src;
            const auto lowSurrogate = srcData[++index];

            // To get from surrogate pair to Unicode code point:
            // - subtract 0xD800 from high surrogate, this forms top ten bits
            // - subtract 0xDC00 from low surrogate, this forms low ten bits
            // - add 0x10000
            // Leaves a code point in U+10000 to U+10FFFF range.
            dcvm_uint32_t codePoint = highSurrogate - H_SURROGATE_START;
            codePoint <<= 10;
            codePoint |= lowSurrogate - L_SURROGATE_START;
            codePoint += SURROGATE_PAIR_START;

            // 4 bytes needed (21 bits used)
            destData[destIndex++] = static_cast<char>((codePoint >> 18) | 0xF0);               // leading 3 bits
            destData[destIndex++] = static_cast<char>(((codePoint >> 12) & LOW_6BITS) | BIT8); // next 6 bits
            destData[destIndex++] = static_cast<char>(((codePoint >> 6) & LOW_6BITS) | BIT8);  // next 6 bits
            destData[destIndex++] = static_cast<char>((codePoint & LOW_6BITS) | BIT8);         // trailing 6 bits
        }
        else // 3 bytes needed (16 bits used)
        {
            destData[destIndex++] = static_cast<char>((src >> 12) | 0xE0);              // leading 4 bits
            destData[destIndex++] = static_cast<char>(((src >> 6) & LOW_6BITS) | BIT8); // middle 6 bits
            destData[destIndex++] = static_cast<char>((src & LOW_6BITS) | BIT8);        // trailing 6 bits
        }
    }
    DCVM_END_CATCH_HANDLER

    return DCVM_ERR_SUCCESS;
}

DCVM_ERROR Utf16ToUtf8(const base::DCVMUtf8String_t &utf8StrIn, base::DCVMUtf8String_t&utf8StrOut) noexcept
{
    DCVM_BEGIN_CATCH_HANDLER
    utf8StrOut = utf8StrIn;
    DCVM_END_CATCH_HANDLER

    return DCVM_ERR_SUCCESS;

}

} // namespace conversions
} // namespace utilities
} // namespace provider
} // namespace dcvm