#ifndef LINUX_RANDOM_H_
#define LINUX_RANDOM_H_

#include "random.h"

namespace Brutucs
{

/**
 * Linux random generator.
 *
 * Implements a random number generator using the Linux's kernel random device.
 */
class LinuxRandom : public Random
{
    public:

        /**
         * Gets the given number of random bytes.
         *
         * @param amount The amount of random bytes to get.
         *
         * @return The amount of random bytes.
         *
         * @throw runtime_error If the requested amount of random bytes couldn't be obtained.
         */
        std::vector<unsigned char> getBytes(std::size_t amount) override;
};

} // namespace Brutucs

#endif // LINUX_RANDOM_H_
