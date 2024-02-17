#include <base58.h>

#include <catch2/catch_test_macros.hpp>

using namespace Brutucs;

TEST_CASE("encode_smallData_returnBase58", "[base58]")
{
    const std::vector<unsigned char> input { 't', 'e', 's', 't' };
    const std::string                expected { "3yZe7d" };

    const std::string actual = Base58::encode(input);

    REQUIRE(actual == expected);
}

TEST_CASE("encode_data_returnBase58", "[base58]")
{
    const std::vector<unsigned char> input { '3', '4', '9', ' ', ' ', '8', '2', 'h', 'f', 'y', ' ', 'w', 'e', 'j', 'k', 'I', 'O', 'N', 'l', 's', 'i', 'e', '9', '0', ';', 'n', 'm', 'w', 'i', 'h', 'o', 'p', 'w', 'e', '8', '3', '7', '9', ' ', '2', 'h', 'a', 's', 'd', 'f', 'c', 'z', '.', '/', ',', ';' };
    const std::string                expected { "3nWZaDJTzrTtzpuKn1znw3mkoYpoPnLJh6qK8BwMUu92C9Txtq3cMFKtQkdzUe7ZkqF4HY" };

    const std::string actual = Base58::encode(input);

    REQUIRE(actual == expected);
}

TEST_CASE("encode_hexData_returnBase58", "[base58]")
{
    const std::vector<unsigned char> input { 0x00, 0x45, 0x03, 0x38, 0x67, 0x00, 0x40, 0x00, 0x00, 0x45, 0x7f };
    const std::string                expected { "14st5Q1AJt3vp9C" };

    const std::string actual = Base58::encode(input);

    REQUIRE(actual == expected);
}
