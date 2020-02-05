#pragma once

#include <eosio/eosio.hpp>

using namespace eosio;
using namespace std;

CONTRACT test : public contract {
  public:
    using contract::contract;

    test( name receiver, name code, datastream<const char*> ds )
      : contract(receiver, code, ds),
        _hashes(receiver, receiver.value) {}

    ACTION create ( const checksum160& hash );

    TABLE Hashes {
      uint64_t index;
      checksum160 hash;
      uint64_t primary_key() const { return index; };
      eosio::checksum160 by_hash() const { return hash; };

      EOSLIB_SERIALIZE(Hashes, (index)(hash));
    };
    typedef multi_index<"hashes"_n, Hashes,
      indexed_by<name("byhash"), const_mem_fun<Hashes, checksum160, &Hashes::by_hash>>
    > hash_table;
    hash_table _hashes;
};