#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <string>

namespace Brutucs
{

/**
 * Address pair of private and public.
 */
struct Address {
        /**
         * Public address.
         */
        std::string pub;

        /**
         * Private address in WIF format.
         */
        std::string priv;
};

} // namespace Brutucs

#endif // ADDRESS_H_
