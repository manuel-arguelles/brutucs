#ifndef ADDRESS_STORE_H_
#define ADDRESS_STORE_H_

#include "address.h"

namespace Brutucs
{

/**
 * Stores external address for comparison.
 */
class AddressStore
{
    public:

        /**
         * Destroys an instance of the AddressStore class.
         */
        virtual ~AddressStore() = default;

        /**
         * Indicates if the given address is present.
         *
         * @param address The address to evaluate.
         *
         * @return If the address is present or not.
         */
        virtual bool isPresent(const Address& address) = 0;
};

} // namespace Brutucs

#endif // ADDRESS_STORE_H_
