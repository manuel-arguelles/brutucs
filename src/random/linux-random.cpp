#include "linux-random.h"

#include <fstream>

namespace
{

constexpr const char* RANDOM_DEVICE        = "/dev/urandom";
constexpr const char* ERROR_READING_DEVICE = "Could not get random bytes.";

} // namespace

namespace Brutucs
{

std::vector<unsigned char>
LinuxRandom::getBytes(const std::size_t amount)
{
    std::vector<char> data(amount);
    std::ifstream     file(RANDOM_DEVICE, std::ios::binary);

    file.read(data.data(), static_cast<std::streamsize>(data.size()));

    if (!file.good()) {
        throw std::runtime_error(ERROR_READING_DEVICE);
    }

    return { data.begin(), data.end() };
}

} // namespace Brutucs
