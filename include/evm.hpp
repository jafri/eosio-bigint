#pragma once

// EOSIO
#include <eosio/eosio.hpp>
#include <eosio/time.hpp>
#include <eosio/asset.hpp>
#include <eosio/transaction.hpp>
#include <eosio/crypto.hpp>

// Ethereum
#include <div.hpp>

using uint256_t = intx::uint256;
using uint512_t = intx::uint512;

#include "sha3/byte_order.c"
#include "sha3/sha3.c"
#include <bigint.h>
#include <disassembler.h>
#include <util.h>
#include <rlp.h>
// #include <transaction.h>
#include <stack.h>
#include <exception.h>
#include <opcode.h>
#include <stack.h>
#include <processor.h>

using namespace eosio;
using namespace std;

#define TOKEN_CONTRACT name("eosio.token")

CONTRACT evm : public contract {
  public:
    using contract::contract;

    evm( name receiver, name code, datastream<const char*> ds )
      : contract(receiver, code, ds),
        _accounts(receiver, receiver.value) {}

    ACTION withdraw ( const name& to,
                      const asset& quantity);

    ACTION create ( const name& account,
                    const string& data);

    [[eosio::on_notify("*::transfer")]]
    void transfer( name from,
                   name to,
                   asset quantity,
                   const std::string& memo );

    using withdraw_action = action_wrapper<"withdraw"_n,    &evm::withdraw>;
    using transfer_action = action_wrapper<"transfer"_n,    &evm::transfer>;

    TABLE Account {
      uint64_t id;
      asset balance;
      intx::uint256 nonce = 1;
      name eosaccount;
      uint64_t primary_key() const { return id; };

      EOSLIB_SERIALIZE(Account, (id)(balance)(nonce)(eosaccount));
    };
    typedef multi_index<"account"_n, Account> account_table;
    account_table _accounts;

  private:
    void sub_balance (
      const name& user,
      const asset& quantity
    );
    void add_balance (
      const name& user,
      const asset& quantity
    );
};