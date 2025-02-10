#ifndef ADDRESS_GENERATOR_H_
#define ADDRESS_GENERATOR_H_

#include "address.h"

#include <vector>

namespace Brutucs
{

/**
 * Address generator interface.
 */
class AddressGenerator
{
    public:

        /**
         * Destroys an instance of the AddressGenerator class.
         */
        virtual ~AddressGenerator() = default;

        /**
         * Generates an address.
         *
         * @return The generated addresses. Usually one.
         */
        virtual std::vector<Address> generate() = 0;
};

} // namespace Brutucs

#endif // ADDRESS_GENERATOR_H_
