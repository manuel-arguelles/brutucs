#include "base58.h"

#include <algorithm>

namespace Base58
{

static const std::string alphabet {"123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz"};

std::string
encode(const std::vector<unsigned char>& data)
{
    std::string result;
    size_t zero_counter = 0;
    size_t size = 0;
    size_t j = 0;
    int carry = 0;
    std::vector<int> buffer;

    for (size_t i = 0; i < data.size() && data[i] == 0x00; ++i) {
        ++zero_counter;
    }

    size = (data.size() - zero_counter) * 138 / 100 + 1;

    buffer.assign(size, 0);

    for (size_t i = zero_counter, high = size - 1; i < data.size(); ++i, high = j) {
        for (carry = data[i], j = size - 1; (j > high) || carry != 0; --j) {
           carry += 256 * buffer[j];
           buffer[j] = carry % 58;
           carry /= 58;

           if (j == 0) {
               break;
           }
        }
    }

    for (j = 0; j < size && buffer[j] == 0; ++j) {
    }

    if (zero_counter > 0) {
        result.insert(result.begin(), zero_counter, '1');
    }

    for (size_t i = zero_counter; j < buffer.size(); ++i, ++j) {
        result += alphabet[buffer[j]];
    }

    return result;
}

std::vector<unsigned char>
decode(const std::string&)
{
    // TODO: Implement

    return {};
}

} // namespace Base58
