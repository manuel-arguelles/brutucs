#include "pseudo-random.h"

#include <algorithm>

namespace
{

constexpr std::uint8_t MAX_VALUE = 255;

} // namespace

namespace Brutucs
{

PseudoRandom::PseudoRandom()
: m_generator(0, MAX_VALUE)
{
    std::random_device random;

    m_engine.seed(random());
}

PseudoRandom::PseudoRandom(const std::uint32_t seed)
: m_engine(seed)
, m_generator(0, MAX_VALUE)
{
}

std::vector<unsigned char>
PseudoRandom::getBytes(const std::size_t amount)
{
    std::vector<unsigned char> numbers(amount);

    std::generate(numbers.begin(), numbers.end(), [this]() { return m_generator(m_engine); });

    return numbers;
}

} // namespace Brutucs
