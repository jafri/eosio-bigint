#include <test.hpp>

void test::create ( const eosio::checksum512& hash ) {
    auto hashed_index = _hashes.get_index<eosio::name("byhash")>();
    auto existing_hash = hashed_index.find(hash);
    check(existing_hash != hashed_index.end(), "hash does not exist.");
}
