#ifndef MEMORY_ADDRESS_STORE_H_
#define MEMORY_ADDRESS_STORE_H_

#include "address-store.h"

#include <filesystem>
#include <string>
#include <vector>

namespace Brutucs
{

/**
 * Address store in memory.
 */
class MemoryAddressStore : public AddressStore
{
    public:

        /**
         * Loads the addresses in memory from the file.
         *
         * @param file The file with the adddresses to load.
         * One address per line.
         *
         * @throw runtime_error if file could not be loaded.
         */
        void loadAddresses(const std::filesystem::path& file);

        /**
         * Indicates if the given address is present.
         *
         * @param address The address to evaluate.
         *
         * @return If the address is present or not.
         */
        bool isPresent(const Address& address) override;

    private:

        std::vector<std::string> m_addresses;
};

} // namespace Brutucs

#endif // MEMORY_ADDRESS_STORE_H_
