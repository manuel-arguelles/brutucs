#ifndef BASE58_H_
#define BASE58_H_

#include <string>
#include <vector>

namespace Brutucs::Base58
{

/*
 * Encodes the given data into a base58 string.
 *
 * @param data The data to encode.
 *
 * @return The base58 representation of the data.
 */
std::string encode(const std::vector<unsigned char>& data);

} // namespace Brutucs::Base58

#endif // BASE58_H_
