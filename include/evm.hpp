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
#include <disassembler.h>
#include <util.h>
#include <rlp.h>
// #include <transaction.h>
#include <stack.h>
#include <exception.h>

using namespace eosio;
using namespace std;

CONTRACT evm : public contract {
  public:
    using contract::contract;

    evm( name receiver, name code, datastream<const char*> ds )
      : contract(receiver, code, ds),
        _accounts(receiver, receiver.value) {}

    // Transfer
    ACTION withdraw (const name& account,
                     const extended_asset& withdrawal);

    [[eosio::on_notify("*::transfer")]]
    void transfer( name from,
                   name to,
                   asset quantity,
                   const std::string& memo );

    using withdraw_action    = action_wrapper<"withdraw"_n,    &evm::withdraw>;
    using transfer_action    = action_wrapper<"transfer"_n,    &evm::transfer>;

    // Utils
    ACTION clearall ();
    template <typename T>
    void cleanTable(){
      T db(get_self(), get_self().value);
      auto itr = db.end();
      while(db.begin() != itr){
        itr = db.erase(--itr);
      }
    }

    TABLE Account {
      name account;
      std::map<extended_symbol, int64_t> balances;
      uint64_t primary_key() const { return account.value; };
    };
    typedef multi_index<"account"_n, Account> account_table;
    account_table _accounts;

  private:
    void sub_balance (
      const name& user,
      const extended_symbol& symbolAndAccount,
      const uint64_t& amount
    );
    void add_balance (
      const name& user,
      const extended_symbol& symbolAndAccount,
      const uint64_t& amount
    );
    void send (
      const name& contract,
      const name& to,
      const asset& quantity,
      const std::string& memo
    );
};