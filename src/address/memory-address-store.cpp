#include "memory-address-store.h"

#include <algorithm>
#include <fstream>

namespace
{

constexpr std::size_t ADDRESS_SIZE = 35;

} // namespace

namespace Brutucs
{

void
MemoryAddressStore::loadAddresses(const std::filesystem::path& file)
{
    const std::size_t fileSize = std::filesystem::file_size(file);
    std::ifstream     stream(file);
    std::string       address;

    m_addresses.reserve(fileSize / ADDRESS_SIZE);

    while (std::getline(stream, address)) {
        m_addresses.push_back(address);
    }
}

bool
MemoryAddressStore::isPresent(const Address& address)
{
    return std::binary_search(m_addresses.cbegin(), m_addresses.cend(), address.pub);
}

} // namespace Brutucs
