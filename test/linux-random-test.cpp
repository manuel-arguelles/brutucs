#include <linux-random.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

using namespace Brutucs;
using namespace Catch::Matchers;

TEST_CASE("getRandomByes_withOneParameter_returnOneRandomByte", "[linux-random]")
{
    LinuxRandom generator;

    REQUIRE(generator.getBytes(1).size() == 1);
}

TEST_CASE("getTwoRandomCollections_withFiveElements_collectionsAreDifferent", "[linux-random]")
{
    const std::size_t amount = 5;
    LinuxRandom       generator;

    std::vector<unsigned char> first  = generator.getBytes(amount);
    std::vector<unsigned char> second = generator.getBytes(amount);

    REQUIRE_THAT(first, !Equals(second));
}
