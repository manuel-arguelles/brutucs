#ifndef RANDOM_H_
#define RANDOM_H_

#include <vector>

namespace Brutucs
{

/**
 * Random interface.
 *
 * Provides random bytes.
 */
class Random
{
    public:

        /**
         * Finalizes an instance of the Random class.
         */
        virtual ~Random() = default;

        /**
         * Gets the given amount of random bytes.
         *
         * @param amount The number of bytes to get.
         *
         * @return The collection of random bytes.
         */
        virtual std::vector<unsigned char> getBytes(std::size_t amount) = 0;
};

} // namespace Brutucs

#endif // RANDOM_H_
