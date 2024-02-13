#ifndef BASE58_H_
#define BASE58_H_

#include <string>
#include <vector>

namespace Base58
{

/// @brief Encodes the given data into a base58 string.
///
/// @param data The data to encode.
///
/// @return The base58 representation of the data.
///
std::string encode(const std::vector<unsigned char>& data);

/// @brief Decodes the given base58 encoded string.
///
/// @param data The base58 data to decode.
///
/// @return The decoded data.
///
std::vector<unsigned char> decode(const std::string& data);

} // namespace Base58

#endif // BASE58_H_
