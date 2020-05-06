#include <dcvm/DCVMLogger.h>
#include <dcvm/provider/utilities/DCVMUriBuilder.hpp>
#include <dcvm/provider/utilities/conversions/DCVMConversions.hpp>

//########################################################
// Based on cpprestsdk uri and uri_builder implementation.
//########################################################

namespace dcvm      {
namespace provider  {
namespace utilities {
namespace details   {
namespace
{

// URI specification: https://tools.ietf.org/html/rfc3986

enum class UriComponent : dcvm_uint8_t
{
    UserInfo,
    Host,
    Path,
    Query,
    Fragment
};

/*!
 * @brief Is character alpha numeric?
 * @param [in] uch character to check.
 * @return result
*/
inline bool __cdecl IsAlnum(const unsigned char uch) noexcept
{
    static constexpr bool isAlnumTable[DCVM_UCHAR_MAX + 1] = {
        /*        X0 X1 X2 X3 X4 X5 X6 X7 X8 X9 XA XB XC XD XE XF */
        /* 0X */   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* 1X */   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* 2X */   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* 3X */   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, /* 0-9 */
        /* 4X */   0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* A-Z */
        /* 5X */   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        /* 6X */   0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* a-z */
        /* 7X */   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0
        /* non-ASCII values initialized to 0 */
    };
    // clang-format on
    return (isAlnumTable[uch]);
}

/*!
 * @brief   Unreserved characters are those that are allowed in a URI but do not have a reserved purpose. They include:
 *          - A-Z
 *          - a-z
 *          - 0-9
 *          - '-' (hyphen)
 *          - '.' (period)
 *          - '_' (underscore)
 *          - '~' (tilde)
 * @param [in] c character to test.
 * @return result
*/
inline bool IsUnreserved(const char c) noexcept
{
    return IsAlnum(c) || c == '-' || c == '.' || c == '_' || c == '~';
}

/*!
 * @brief   General delimiters serve as the delimiters between different uri components.
 *          General delimiters include:
 *          - All of these :/?#[]@
 * @param [in] c character to test.
 * @return result
*/
inline bool IsGenDelim(const char c) noexcept
{
    switch(c)
    {
        case ':':
        case '/':
        case '?':
        case '#':
        case '[':
        case ']':
        case '@': return true;
        default : return false;
    }
}

/*!
 * @brief   Subdelimiters are those characters that may have a defined meaning within component
 *          of a uri for a particular scheme. They do not serve as delimiters in any case between
 *          uri segments. sub_delimiters include:
 *          - All of these !$&'()*+,;=
 * @param [in] c character to test.
 * @return result.
*/
inline bool IsSubDelim(const char c) noexcept
{
    switch (c)
    {
        case '!':
        case '$':
        case '&':
        case '\'':
        case '(':
        case ')':
        case '*':
        case '+':
        case ',':
        case ';':
        case '=': return true;
        default: return false;
    }
}

/*!
 * @brief   Reserved characters includes the general delimiters and sub delimiters. Some characters
 *          are neither reserved nor unreserved, and must be percent-encoded.
 * @param [in] c character to test.
 * @return result.
*/
inline bool IsReserved(const char c) noexcept
{ 
    return IsGenDelim(c) || IsSubDelim(c);
}

/*! <summary>
 * @brief   Legal characters in the scheme portion include:
 *          - Any alphanumeric character
 *          - '+' (plus)
 *          - '-' (hyphen)
 *          - '.' (period)
 *
 *          Note that the scheme must BEGIN with an alpha character.
 * @param [in] c character to test.
 * @return result.
*/
inline bool IsSchemeCharacter(const char c) noexcept
{
    return IsAlnum(c) || ('+' == c) || ('-' == c) || ('.' == c);
}

/*! <summary>
 * @brief   Legal characters in the user information portion include:
 *          - Any unreserved character
 *          - The percent character ('%'), and thus any percent-endcoded octet
 *          - The sub-delimiters
 *          - ':' (colon)
 * @param [in] c character to test.
 * @return result.
*/
inline bool IsUserInfoCharacter(const char c) noexcept
{
    return IsUnreserved(c) || IsSubDelim(c) || ('%' == c) || (':' == c);
}

/*!
 * @brief   Legal characters in the authority portion include:
 *          - Any unreserved character
 *          - The percent character ('%'), and thus any percent-endcoded octet
 *          - The sub-delimiters
 *          - ':' (colon)
 *          - IPv6 requires '[]' allowed for it to be valid URI and passed to underlying platform for IPv6 support
 * @param [in] c character to test.
 * @return result.
*/
inline bool IsAuthorityCharacter(const char c) noexcept
{
    return IsUnreserved(c) || IsSubDelim(c) || ('%' == c) || ('@' == c) || (':' == c) || ('[' == c) || (']' == c);
}

/*!
 * @brief   Legal characters in the path portion include:
 *          - Any unreserved character
 *          - The percent character ('%'), and thus any percent-endcoded octet
 *          - The sub-delimiters
 *          - ':' (colon)
 *          - '@' (at sign)
 * @param [in] c character to test.
 * @return result.
*/
inline bool IsPathCharacter(const char c) noexcept
{
    return IsUnreserved(c) || IsSubDelim(c) || ('%' == c) || ('/' == c) || (':' == c) || ('@' == c);
}

/*!
 * @brief   Legal characters in the query portion include:
 *          - Any path character
 *          - '?' (question mark)
 * @param [in] c character to test.
 * @return result.
*/
inline bool IsQueryCharacter(const char c) noexcept
{
    return IsPathCharacter(c) || ('?' == c); 
}

/*!
 * @brief   Legal characters in the fragment portion include:
 *          - Any path character
 *          - '?' (question mark)
 * @param [in] c character to test.
 * @return result.
*/
inline bool IsFragmentCharacter(const char c) noexcept
{
    // this is intentional, they have the same set of legal characters
    return IsQueryCharacter(c);
}

/*!
 * @brief Encode all characters
 * @param [in] str string to encode.
 * @param [in] ShouldEncode predicate to filter characters to encode.
 * @return encoded string
*/
template <class F>
base::DCVMString_t EncodeCharacters(const base::DCVMUtf8String_t &str, F ShouldEncode)
{
    const char* const hex = "0123456789ABCDEF";

    base::DCVMString_t encoded;
    for (auto iter = str.begin(); iter != str.end(); ++iter)
    {
        // for utf8 encoded string, char ASCII can be greater than 127.
        auto ch = static_cast<unsigned char>(*iter);
        // ch should be same under both utf8 and utf16.
        if (ShouldEncode(ch))
        {
            encoded.push_back(DCVM_TEXT('%'));
            encoded.push_back(hex[(ch >> 4) & 0xF]);
            encoded.push_back(hex[ch & 0xF]);
        }
        else
        {
            // ASCII don't need to be encoded, which should be same on both utf8 and utf16.
            encoded.push_back((dcvm_char_t)ch);
        }
    }

    return encoded;
}

base::DCVMString_t EncodeUri(const base::DCVMString_t &raw, const UriComponent component)
{
    base::DCVMUtf8String_t utf8{};
    auto err = conversions::Utf16ToUtf8(raw, utf8);
    if (DCVM_FAILED(err))
    {
        return base::DCVMString_t{};
    }

    // Note: we also encode the '+' character because some non-standard implementations
    // encode the space character as a '+' instead of %20. To better interoperate we encode
    // '+' to avoid any confusion and be mistaken as a space.
    switch (component)
    {
        case UriComponent::UserInfo:
            return EncodeCharacters(
                utf8
                , [](char ch) -> bool
                {
                    return !IsUserInfoCharacter(ch) || ('%' == ch) || ('+' == ch);
                }
            );
        case UriComponent::Host:
            return EncodeCharacters(
                utf8
                , [](char ch) -> bool
                {
                    // No encoding of ASCII characters in host name (RFC 3986 3.2.2)
                    return ch > 127;
                }
            );
        case UriComponent::Path:
            return EncodeCharacters(
                utf8
                , [](char ch) -> bool
                { 
                    return !IsPathCharacter(ch) || ('%' == ch) || ('+' == ch); 
                }
            );
        case UriComponent::Query:
            return EncodeCharacters(
                utf8
                , [](char ch) -> bool
                {
                    return !IsQueryCharacter(ch) || ('%' == ch) || ('+' == ch);
                }
            );
        case UriComponent::Fragment:
            return EncodeCharacters(
                utf8
                , [](char ch) -> bool
                { 
                    return !IsFragmentCharacter(ch) || ('%' == ch) || ('+' == ch); 
                }
            );
        default:
            return EncodeCharacters(
                utf8
                , [](char ch) -> bool 
                {
                    return !IsUnreserved(ch) && !IsReserved(ch);
                }
            );
    };
}

} // namespace empty

void DCVMUriComponents::SetScheme(const base::DCVMString_t &scheme)
{
    m_scheme = scheme;
}

void DCVMUriComponents::SetScheme(base::DCVMString_t &&scheme)
{
    m_scheme = scheme;
}

const base::DCVMString_t& DCVMUriComponents::Scheme() const
{
    return m_scheme;
}

void DCVMUriComponents::SetUserInfo(const base::DCVMString_t &userInfo)
{
    m_userInfo = userInfo;
}

void DCVMUriComponents::SetUserInfo(base::DCVMString_t &&userInfo)
{
    m_userInfo = userInfo;
}

const base::DCVMString_t& DCVMUriComponents::UserInfo() const
{
    return m_userInfo;
}

void DCVMUriComponents::SetHost(const base::DCVMString_t &host)
{
    m_host = host;
}

void DCVMUriComponents::SetHost(base::DCVMString_t &&host)
{
    m_host = host;
}

const base::DCVMString_t& DCVMUriComponents::Host() const
{
    return m_host;
}

void DCVMUriComponents::SetFragment(const base::DCVMString_t &fragment)
{
    m_fragment = fragment;
}

void DCVMUriComponents::SetFragment(base::DCVMString_t &&fragment)
{
    m_fragment = fragment;
}

const base::DCVMString_t& DCVMUriComponents::Fragment() const
{
    return m_fragment;
}

void DCVMUriComponents::AppendPath(const base::DCVMString_t &subPath)
{
    if (subPath.empty())
    {
        return;
    }

    if (!m_path.empty())
    {
        if ((DCVM_TEXT('/') == m_path.back()) && (DCVM_TEXT('/') == subPath.front()))
        {
            m_path.pop_back();
        }
        else if ((DCVM_TEXT('/') != m_path.back()) && (DCVM_TEXT('/') != subPath.front()))
        {
            m_path.push_back(DCVM_TEXT('/'));
        }
    }
    
    m_path.append(subPath);
}

const base::DCVMString_t& DCVMUriComponents::Path() const
{
    return m_path;
}

void DCVMUriComponents::AppendQuery(const base::DCVMString_t &subQuery)
{
    if (subQuery.empty())
    {
        return;
    }

    if (!m_query.empty())
    {
        if ((DCVM_TEXT('&') == m_query.back()) && (DCVM_TEXT('&') == subQuery.front()))
        {
            m_path.pop_back();
        }
        else if ((DCVM_TEXT('&') != m_query.back()) && (DCVM_TEXT('&') != subQuery.front()))
        {
            m_query.push_back(DCVM_TEXT('&'));
        }
    }

    m_query.append(subQuery);
}

const base::DCVMString_t& DCVMUriComponents::Query() const
{
    return m_query;
}

dcvm_size_t DCVMUriComponents::UriStringSize() const
{
    dcvm_size_t uriSize = 0;

    if (!m_scheme.empty())
    {
        uriSize += m_scheme.size();
        uriSize += 1; // ':'
    }

    if (!m_host.empty())
    {
        if (!m_scheme.empty())
        {
            uriSize += 2; // '/', '/'
        }

        if (!m_userInfo.empty())
        {
            uriSize += m_userInfo.size();
            uriSize += 1; // '@'
        }

        if (!m_port.empty())
        {
            uriSize += m_port.size();
            uriSize += 1; // ':'
        }

        uriSize += m_host.size();
    }

    if (!m_path.empty())
    {
        uriSize += m_path.size();
        uriSize += 1; // '/'
    }

    if (!m_query.empty())
    {
        uriSize += m_query.size();
        uriSize += 1; // '?'
    }

    if (!m_fragment.empty())
    {
        uriSize += m_fragment.size();
        uriSize += 1; // '#'
    }

    return uriSize;
}

base::DCVMString_t DCVMUriComponents::ToString() const
{
    base::DCVMString_t uri;
    uri.reserve(UriStringSize());

    if (!m_scheme.empty())
    {
        uri.append(m_scheme).append(DCVM_TEXT(":"));
    }

    if (!m_host.empty())
    {
        if (!m_scheme.empty())
        {
            uri.append(DCVM_TEXT("//"));
        }

        if (!m_userInfo.empty())
        {
            uri.append(m_userInfo).append(DCVM_TEXT("@"));
        }

        uri.append(m_host);

        if (!m_port.empty())
        {
            uri.append(DCVM_TEXT(":")).append(m_port);
        }
    }

    if (!m_path.empty())
    {
        uri.append(DCVM_TEXT("/")).append(m_path);
    }

    if (!m_query.empty())
    {
        uri.append(DCVM_TEXT("?")).append(m_query);
    }

    if (!m_fragment.empty())
    {
        uri.append(DCVM_TEXT("#")).append(m_fragment);
    }

    return uri;
}

} // namespace details

DCVMUriBuilder& DCVMUriBuilder::SetScheme(const base::DCVMString_t &scheme) noexcept
{
    DCVM_BEGIN_CATCH_HANDLER
    m_uriComponents.SetScheme(scheme);
    DCVM_END_CATCH_HANDLER_NO_RETURN

    return *this;
}

DCVMUriBuilder& DCVMUriBuilder::SetHost(const base::DCVMString_t &host, const bool bEncode) noexcept
{
    DCVM_BEGIN_CATCH_HANDLER

    if (bEncode)
    {
        m_uriComponents.SetHost(details::EncodeUri(host, details::UriComponent::Host));
    }
    else
    {
        m_uriComponents.SetHost(host);
    }

    DCVM_END_CATCH_HANDLER_NO_RETURN

    return *this;
}

DCVMUriBuilder& DCVMUriBuilder::AppendPath(const base::DCVMString_t &path, const bool bEncoding) noexcept
{
    DCVM_BEGIN_CATCH_HANDLER

    if (bEncoding)
    {
        m_uriComponents.AppendPath(details::EncodeUri(path, details::UriComponent::Path));
    }
    else
    {
        m_uriComponents.AppendPath(path);
    }

    DCVM_END_CATCH_HANDLER_NO_RETURN

    return *this;
}

DCVMUriBuilder& DCVMUriBuilder::AppendQuery(const base::DCVMString_t &query, const bool bEncoding) noexcept
{
    DCVM_BEGIN_CATCH_HANDLER

    if (bEncoding)
    {
        m_uriComponents.AppendQuery(details::EncodeUri(query, details::UriComponent::Query));
    }
    else
    {
        m_uriComponents.AppendQuery(query);
    }

    DCVM_END_CATCH_HANDLER_NO_RETURN

    return *this;
}

base::DCVMString_t DCVMUriBuilder::Build() const noexcept
{
    base::DCVMString_t uri;

    DCVM_BEGIN_CATCH_HANDLER
    uri = m_uriComponents.ToString();
    DCVM_END_CATCH_HANDLER_NO_RETURN

    return uri;
}

} // namespace utilities
} // namespace provider
} // namespace dcvm