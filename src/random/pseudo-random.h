#ifndef PSEUDO_RANDOM_H_
#define PSEUDO_RANDOM_H_

#include "random.h"

#include <cstdint>
#include <random>

namespace Brutucs
{

/**
 * Implements a pseudo random generator.
 */
class PseudoRandom : public Random
{
    public:

        /**
         * Initializes a new instance of PseudoRandom class.
         */
        PseudoRandom();

        /**
         * @brief Initializes a new instance of PseudoRandom class.
         *
         * @param seed The seed to initialize the random sequence generator.
         */
        explicit PseudoRandom(std::uint32_t seed);

        /**
         * Gets the given number of random bytes.
         *
         * @param amount The amount of random bytes to get.
         *
         * @return The amount of random bytes.
         */
        std::vector<unsigned char> getBytes(std::size_t amount) override;

    private:

        std::minstd_rand                            m_engine;
        std::uniform_int_distribution<std::uint8_t> m_generator;
};

} // namespace Brutucs

#endif // PSEUDO_RANDOM_H_
