#ifndef MOCK_RANDOM_H_
#define MOCK_RANDOM_H_

#include <random.h>

#include <cstdint>
#include <vector>

/**
 * Mock object for the random number generator.
 */
class MockRandom : public Brutucs::Random
{
    public:

        /**
         * @brief Adds to the numbers that will be returned.
         *
         * @param numbers The random numbers to add.
         */
        void addNumbers(const std::vector<uint8_t>& numbers);

        /**
         * Gets the given number of random bytes.
         *
         * @param amount The amount of random bytes to get.
         *
         * @return The amount of random bytes.
         */
        std::vector<uint8_t> getBytes(std::size_t amount) override;

    private:

        std::vector<uint8_t> m_numbers;
};

#endif // MOCK_RANDOM_H_
