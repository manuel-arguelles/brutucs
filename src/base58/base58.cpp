#include "base58.h"

#include <algorithm>
#include <array>
#include <cstddef>

namespace
{

constexpr std::array<char, 58> ALPHABET { '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
constexpr std::size_t          MAX_LIMIT { 256 };

/**
 * Gets the number of zeroes at the beginning of the given data.
 *
 * @param data The data to evaluate.
 *
 * @return The number of zeroes at the beginning of the data.
 */
template<typename T>
std::size_t
getStartingZeroes(const std::vector<T>& data)
{
    return std::distance(data.cbegin(), std::find_if(data.cbegin(), data.cend(), [](const auto value) { return value != 0x00; }));
}

} // namespace

namespace Brutucs::Base58
{

std::string
encode(const std::vector<unsigned char>& data)
{
    const std::size_t zeroCounter = getStartingZeroes(data);
    const std::size_t size        = (data.size() - zeroCounter) * 138 / 100 + 1;

    std::string      result;
    std::size_t      j     = 0;
    std::size_t      carry = 0;
    std::vector<int> buffer(size, 0x00);

    for (std::size_t i = zeroCounter, high = size - 1; i < data.size(); ++i, high = j) {
        for (carry = data[i], j = size - 1; (j > high) || carry != 0x00; --j) {
            carry     += MAX_LIMIT * buffer[j];
            buffer[j]  = static_cast<unsigned char>(carry % ALPHABET.size());
            carry     /= ALPHABET.size();

            if (j == 0) {
                break;
            }
        }
    }

    result.insert(result.begin(), zeroCounter, '1');

    for (std::size_t i = getStartingZeroes(buffer); i < buffer.size(); ++i) {
        result += ALPHABET[buffer[i]];
    }

    return result;
}

} // namespace Brutucs::Base58
