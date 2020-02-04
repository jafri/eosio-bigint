#include <evm.hpp>

void evm::transfer (name from, name to, asset quantity, const std::string& memo) {
  auto token_contract = get_first_receiver();

  // Do not process deposits from a contract other than as specified
  if (token_contract != TOKEN_CONTRACT) {
    return;
  }

  // Do not process deposits from system accounts
  if (from == "eosio.stake"_n || from == "eosio.ram"_n || from == "eosio"_n) {
    return;
  }

  // Do not process deposits to anyone but self
  if (to != get_self()) {
    return;
  }

  // process deposit
  add_balance(from, quantity);
}

void evm::withdraw (
  const name& to,
  const asset& quantity
) {
  require_auth( to );

  // Substract account
  sub_balance(to, quantity);

  // Withdraw
  evm::transfer_action t_action( TOKEN_CONTRACT, {get_self(), "active"_n} );
  t_action.send(get_self(), to, quantity, std::string("Withdraw balance for: " + to.to_string()));
}

void evm::add_balance (
  const name& user,
  const asset& quantity
) {
  auto account = _accounts.find(user.value);
  check(account != _accounts.end(), "account does not have a balance.");
  check(quantity.amount > 0, "asset must be positive");

  _accounts.modify(account, same_payer, [&](auto& a) {
    a.balance += quantity;
  });
}

void evm::sub_balance (
  const name& user,
  const asset& quantity
) {
  auto account = _accounts.find(user.value);
  check(account != _accounts.end(), "account does not have a balance.");
  check(quantity.amount > 0, "asset must be positive");
  check(account.balance.amount >= quantity.amount, "account balance too low.");

  _accounts.modify(account, same_payer, [&](auto& a) {
    a.balance -= quantity;
  });
}