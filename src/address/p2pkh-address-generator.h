#ifndef P2PKH_ADDRESS_GENERATOR_H_
#define P2PKH_ADDRESS_GENERATOR_H_

// #include <random.h>
#include "../random/random.h"

#include "address-generator.h"

#include <memory>

namespace Brutucs
{

/**
 * P2PKH address generator.
 */
class P2pkhAddressGenerator : public AddressGenerator
{
    public:

        /**
         * Initializes a new P2PKH address generator
         *
         * @param random The random number generator to use.
         */
        explicit P2pkhAddressGenerator(std::unique_ptr<Random>&& random);

        /**
         * Generates an address.
         *
         * @return The generated addresses. Usually one.
         */
        std::vector<Address> generate() override;

    private:

        std::unique_ptr<Random> m_random;
};

} // namespace Brutucs

#endif // P2PKH_ADDRESS_GENERATOR_H_
