#include "mock-random.h"

void
MockRandom::addNumbers(const std::vector<uint8_t>& numbers)
{
    m_numbers.insert(m_numbers.end(), numbers.cbegin(), numbers.cend());
}

std::vector<uint8_t>
MockRandom::getBytes(std::size_t amount)
{
    const size_t         size = std::min(amount, m_numbers.size());
    std::vector<uint8_t> result(size);

    std::copy(m_numbers.begin(), m_numbers.begin() + size, result.begin());

    return result;
}
