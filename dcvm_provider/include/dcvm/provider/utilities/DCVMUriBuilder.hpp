#ifndef DCVM_PROVIDER_DCVMURIBUILDER_HPP_
#define DCVM_PROVIDER_DCVMURIBUILDER_HPP_

#include <dcvm/cpp/base/DCVMTypes.hpp>

namespace dcvm      {
namespace provider  {
namespace utilities {
namespace details   {

/*!
 * @class DCVMUriComponents aggregates all uri parts except(for a while) fragment, port, user information. 
*/
class DCVMUriComponents final
{
    base::DCVMString_t m_scheme;
    base::DCVMString_t m_userInfo;
    base::DCVMString_t m_host;
    base::DCVMString_t m_port;
    base::DCVMString_t m_path;
    base::DCVMString_t m_query;
    base::DCVMString_t m_fragment;
public:
    void SetScheme(const base::DCVMString_t &scheme);

    void SetScheme(base::DCVMString_t &&scheme);

    const base::DCVMString_t& Scheme() const;

    void SetUserInfo(const base::DCVMString_t &userInfo);

    void SetUserInfo(base::DCVMString_t &&userInfo);

    const base::DCVMString_t& UserInfo() const;

    void SetHost(const base::DCVMString_t &host);

    void SetHost(base::DCVMString_t &&host);

    const base::DCVMString_t& Host() const;

    void SetFragment(const base::DCVMString_t &fragment);

    void SetFragment(base::DCVMString_t &&fragment);

    const base::DCVMString_t& Fragment() const;

    void AppendPath(const base::DCVMString_t &subPath);

    const base::DCVMString_t& Path() const;

    void AppendQuery(const base::DCVMString_t &subQuery);

    const base::DCVMString_t& Query() const;

    base::DCVMString_t ToString() const;
private:
    dcvm_size_t UriStringSize() const;
};

} // namespace details

/*!
 * @class DCVMUriBuilder build uri from parts(Peep into cpprestsdk uri_builder).
*/
class DCVMUriBuilder final
{
    details::DCVMUriComponents m_uriComponents;
public:
    DCVMUriBuilder() noexcept = default;

    ~DCVMUriBuilder() noexcept = default;

    /*!
     * @brief Set new uri schema.
     * @param [in] schema new uri host.
     * @return DCVMUriBuilder instance.
    */
    DCVMUriBuilder& SetScheme(const base::DCVMString_t &scheme) noexcept;

    /*!
     * @brief Set new uri host.
     * @param [in] host new uri host.
     * @return DCVMUriBuilder instance.
    */
    DCVMUriBuilder& SetHost(const base::DCVMString_t &host, const bool bEncode = false) noexcept;

    /*!
     * @brief Append new path to existing.
     * @param [in] path new uri path to append.
     * @param [in] bEncoding encode appened uri path?
     * @return DCVMUriBuilder instance.
    */
    DCVMUriBuilder& AppendPath(const base::DCVMString_t &path, const bool bEncoding = false) noexcept;

    /*!
     * @brief Append new query to existing.
     * @param [in] query new uri query to append.
     * @param [in] bEncoding encode uri path?
     * @return DCVMUriBuilder instance.
    */
    DCVMUriBuilder& AppendQuery(const base::DCVMString_t &query, const bool bEncoding = false) noexcept;

    /*!
     * @brief Buil uri from specified parts.
     * @return Built uri.
    */
    base::DCVMString_t Build() const noexcept;
};

} // namespace utilities
} // namespace provider
} // namespace dcvm

#endif