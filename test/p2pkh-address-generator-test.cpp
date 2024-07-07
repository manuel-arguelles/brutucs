#include <p2pkh-address-generator.h>

#include "mocks/mock-random.h"

#include <catch2/catch_test_macros.hpp>

#include <array>
#include <cstdint>
#include <memory>
#include <vector>

using namespace Brutucs;

constexpr std::array KEY { 0x0f, 0xad, 0xff, 0x2d, 0x0f, 0x43, 0x1c, 0xf4, 0x05, 0x1e, 0xdc, 0xa5, 0x8c, 0x9f, 0x0f, 0x59, 0x21, 0xbd, 0xda, 0x5d, 0x14, 0x88, 0x56, 0x48, 0x95, 0x1e, 0xee, 0x27, 0xf4, 0x34, 0x8a, 0x49 };

TEST_CASE("generate_p2phkAddress_returnCompressedAddress", "[address]")
{
    const std::string           expectedPublic { "1LJMQNCfoJ5bsqThG3V6yiHAagiFWXtRsR" };
    const std::string           expectedPrivate { "KwkBypRpFEGcAi6zPF4H8wo2G5RkVeEi8JGcW2zJLLqkSvcGavtx" };
    std::unique_ptr<MockRandom> random = std::make_unique<MockRandom>();
    std::vector<Address>        addresses;

    random->addNumbers(std::vector<uint8_t>(KEY.cbegin(), KEY.cend()));

    P2pkhAddressGenerator generator(std::move(random));

    addresses = generator.generate();

    REQUIRE(addresses.size() == 2);
    REQUIRE(addresses[0].pub == expectedPublic);
    REQUIRE(addresses[0].priv == expectedPrivate);
}

TEST_CASE("generate_p2phkAddress_returnUncompressedAddress", "[address]")
{
    const std::string           expectedPublic { "1NauqZmuUgNhi1wX3ogWaosMUHT7d1a2qF" };
    const std::string           expectedPrivate { "5HwC6d7yvXCErn7LoGsb1tqVNzeKvALsZ1jxd2oy37m88J5ijg8" };
    std::unique_ptr<MockRandom> random = std::make_unique<MockRandom>();
    std::vector<Address>        addresses;

    random->addNumbers(std::vector<uint8_t>(KEY.cbegin(), KEY.cend()));

    P2pkhAddressGenerator generator(std::move(random));

    addresses = generator.generate();

    REQUIRE(addresses.size() == 2);
    REQUIRE(addresses[1].pub == expectedPublic);
    REQUIRE(addresses[1].priv == expectedPrivate);
}
