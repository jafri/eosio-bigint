#include <evm.hpp>

void evm::clearall () {
  require_auth(get_self());
  cleanTable<account_table>();
}

void evm::send (
  const name& contract,
  const name& to,
  const asset& quantity,
  const std::string& memo
) {
  evm::transfer_action t_action( contract, {get_self(), "active"_n} );
  t_action.send(get_self(), to, quantity, memo);
}
