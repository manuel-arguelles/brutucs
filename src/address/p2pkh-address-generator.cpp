#include "p2pkh-address-generator.h"

#include "../base58/base58.h"

#include <openssl/core_names.h>
#include <openssl/ec.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/param_build.h>
#include <openssl/provider.h>

static constexpr std::size_t KEY_SIZE          = 32;
static constexpr uint8_t     NETWORK_KEY_ID    = 0x80;
static constexpr uint8_t     NETWORK_PUBLIC_ID = 0x00;
static constexpr uint8_t     COMPRESSED_ID     = 0x01;

namespace
{

/**
 * Gets the compressed secp256k1 public key from the private key
 *
 * @param privateKey The private key.
 *
 * @return The public key.
 */
std::vector<uint8_t>
getPublicKeyCompressed(const std::vector<uint8_t>& privateKey)
{
    std::vector<uint8_t> publicKey;
    BIGNUM* const        key   = BN_bin2bn(privateKey.data(), static_cast<int>(privateKey.size()), nullptr);
    EC_GROUP* const      group = EC_GROUP_new_by_curve_name(NID_secp256k1);

    if ((key != nullptr) && (group != nullptr)) {
        EC_POINT* const point = EC_POINT_new(group);

        if (point != nullptr) {
            std::size_t keySize = 0;

            EC_POINT_mul(group, point, key, nullptr, nullptr, nullptr);

            keySize = EC_POINT_point2oct(group, point, POINT_CONVERSION_COMPRESSED, nullptr, 0, nullptr);
            publicKey.resize(keySize);
            EC_POINT_point2oct(group, point, POINT_CONVERSION_COMPRESSED, publicKey.data(), publicKey.size(), nullptr);

            EC_POINT_free(point);
        }
    }

    EC_GROUP_free(group);
    BN_free(key);

    return publicKey;
}

/**
 * Gets the uncompressed secp256k1 public key from the private key
 *
 * @param privateKey The private key.
 *
 * @return The public key.
 */
std::vector<uint8_t>
getPublicKey(const std::vector<uint8_t>& privateKey)
{
    std::vector<uint8_t> publicKey;
    BIGNUM* const        key   = BN_bin2bn(privateKey.data(), static_cast<int>(privateKey.size()), nullptr);
    EC_GROUP* const      group = EC_GROUP_new_by_curve_name(NID_secp256k1);

    if ((key != nullptr) && (group != nullptr)) {
        EC_POINT* const point = EC_POINT_new(group);

        if (point != nullptr) {
            std::size_t keySize = 0;

            EC_POINT_mul(group, point, key, nullptr, nullptr, nullptr);

            keySize = EC_POINT_point2oct(group, point, POINT_CONVERSION_UNCOMPRESSED, nullptr, 0, nullptr);
            publicKey.resize(keySize);
            EC_POINT_point2oct(group, point, POINT_CONVERSION_UNCOMPRESSED, publicKey.data(), publicKey.size(), nullptr);

            EC_POINT_free(point);
        }
    }

    EC_GROUP_free(group);
    BN_free(key);

    return publicKey;
}

/**
 * Gets the SHA256 hash of the given data.
 *
 * @param data The data to hash.
 *
 * @return The SHA256 hash.
 */
std::vector<uint8_t>
getSha256Hash(const std::vector<uint8_t>& data)
{
    std::vector<uint8_t> hash(EVP_MD_get_size(EVP_sha256()));

    EVP_Q_digest(nullptr, EVP_MD_name(EVP_sha256()), nullptr, data.data(), data.size(), hash.data(), nullptr);

    return hash;
}

/**
 * Gets the Ripemd160 hash of the given data.
 *
 * @param data The data to hash.
 *
 * @return The Ripemd160 hash.
 */
std::vector<uint8_t>
getRipemd160Hash(const std::vector<uint8_t>& data)
{
    std::vector<uint8_t> hash(EVP_MD_get_size(EVP_ripemd160()));

    OSSL_PROVIDER* legacy = OSSL_PROVIDER_load(nullptr, "legacy");

    EVP_Q_digest(nullptr, EVP_MD_name(EVP_ripemd160()), nullptr, data.data(), data.size(), hash.data(), nullptr);

    if (legacy != nullptr)
        OSSL_PROVIDER_unload(legacy);

    return hash;
}

/**
 * Adds the network bytes.
 *
 * @param address The address to add the network bytes.
 *
 * @return The address with he network bytes added.
 */
std::vector<uint8_t>
addNetworkBytes(const std::vector<uint8_t>& address)
{
    std::vector<uint8_t> result { address };

    result.insert(result.cbegin(), NETWORK_PUBLIC_ID);

    return result;
}

/**
 * Adds the checksum to the address.
 *
 * @param address The address to calculate and add the checksum.
 *
 * @return The address with the checksum.
 */
std::vector<uint8_t>
addChecksum(const std::vector<uint8_t>& address)
{
    const std::vector<uint8_t> firstHash  = getSha256Hash(address);
    const std::vector<uint8_t> secondHash = getSha256Hash(firstHash);
    const std::vector<uint8_t> checksum(secondHash.cbegin(), secondHash.cbegin() + 4);

    std::vector<uint8_t> result { address };

    result.insert(result.cend(), checksum.cbegin(), checksum.cend());

    return result;
}

/**
 * Gets the compressed private address (WIF encoded) of the given key.
 *
 * @param key The raw 32 bytes key for the secp256k1 curve.
 *
 * @return The WIF compressed private address.
 */
std::string
getPrivateWifCompressed(const std::vector<uint8_t>& key)
{
    std::vector<uint8_t> privateKey { NETWORK_KEY_ID };

    privateKey.insert(privateKey.cend(), key.cbegin(), key.cend());
    privateKey.insert(privateKey.cend(), COMPRESSED_ID);

    return Brutucs::Base58::encode(addChecksum(privateKey));
}

/**
 * Gets the private address (WIF encoded) of the given key.
 *
 * @param key The raw 32 bytes key for the secp256k1 curve.
 *
 * @return The WIF private address.
 */
std::string
getPrivateWif(const std::vector<uint8_t>& key)
{
    std::vector<uint8_t> privateKey { NETWORK_KEY_ID };

    privateKey.insert(privateKey.cend(), key.cbegin(), key.cend());

    return Brutucs::Base58::encode(addChecksum(privateKey));
}

/**
 * Gets the P2PKH public address for the given public key.
 *
 * @param key The public key.
 *
 * @return The public address.
 */
std::string
getPublicAddress(const std::vector<uint8_t>& publicKey)
{
    const std::vector<uint8_t> sha256ed   = getSha256Hash(publicKey);
    const std::vector<uint8_t> ripemded   = getRipemd160Hash(sha256ed);
    const std::vector<uint8_t> networked  = addNetworkBytes(ripemded);
    const std::vector<uint8_t> checksumed = addChecksum(networked);

    return Brutucs::Base58::encode(checksumed);
}

} // namespace

namespace Brutucs
{

P2pkhAddressGenerator::P2pkhAddressGenerator(std::unique_ptr<Random>&& random)
: m_random(std::move(random))
{
}

std::vector<Address>
P2pkhAddressGenerator::generate()
{
    const std::vector<uint8_t> random                   = m_random->getBytes(KEY_SIZE);
    const std::vector<uint8_t> publicKey                = getPublicKey(random);
    const std::vector<uint8_t> publicKeyCompressed      = getPublicKeyCompressed(random);
    const std::string          privateAddress           = getPrivateWif(random);
    const std::string          privateAddressCompressed = getPrivateWifCompressed(random);
    const std::string          publicAddress            = getPublicAddress(publicKey);
    const std::string          publicAddressCompressed  = getPublicAddress(publicKeyCompressed);

    Address compressedAddress;
    Address address;

    compressedAddress.pub  = publicAddressCompressed;
    compressedAddress.priv = privateAddressCompressed;
    address.pub            = publicAddress;
    address.priv           = privateAddress;

    return { compressedAddress, address };
}

} // namespace Brutucs
