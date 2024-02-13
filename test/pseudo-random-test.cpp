#include <pseudo-random.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

using namespace Brutucs;
using namespace Catch::Matchers;

TEST_CASE("getRandomByes_withOneParameterSeeded_returnOneRandomByte", "[pseudo-random]")
{
    PseudoRandom generator(0);

    std::vector<unsigned char> random = generator.getBytes(1);

    REQUIRE(random.size() == 1);
    REQUIRE(random[0] == 0);
}

TEST_CASE("getTwoRandomCollections_withFiveElementsSeeded_collectionsAreEqual", "[pseudo-random]")
{
    const std::size_t                amount = 5;
    const std::vector<unsigned char> expected { 0x0, 0x15, 0x99, 0xe4, 0xf7 };
    PseudoRandom                     generator(0);

    std::vector<unsigned char> actual = generator.getBytes(amount);

    REQUIRE_THAT(actual, Equals(expected));
}

TEST_CASE("getTwoRandomCollections_withFiveElements_collectionsAreDifferent", "[pseudo-random]")
{
    const std::size_t                amount = 5;
    const std::vector<unsigned char> expected { 0x0, 0x15, 0x99, 0xe4, 0xf7 };
    PseudoRandom                     generator;

    std::vector<unsigned char> actual = generator.getBytes(amount);

    REQUIRE_THAT(actual, !Equals(expected));
}
