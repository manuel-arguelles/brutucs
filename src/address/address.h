#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <string>
#include <vector>

namespace Brutucs
{

/// @brief BTC Address.
///
class Address
{
    public:

    /// @brief Gets the public address.
    ///
    /// @return The public address.
    ///
    std::string getPublic() const;

    /// @brief Gets the prikvate key.
    ///
    /// @return The private key.
    ///
    std::vector<unsigned char> getPrivate() const;

    private:

    /// @brief Sets the public address.
    ///
    /// @param publicKey The public key of the address.
    ///
    void setPublic(const std::string& publicKey);

    /// @brief Sets the private key.
    ///
    /// @param privateKey The private key of the address.
    ///
    void setPrivate(const std::vector<unsigned char>& privateKey);

    private:

    std::string                m_public;
    std::vector<unsigned char> m_private;
};

} // namespace Brutucs


#endif // ADDRESS_H_
