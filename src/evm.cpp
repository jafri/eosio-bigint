#include <evm.hpp>

    ACTION create ( const name& account,
                    const string& data);

void evm::create (
  const name& account,
  const string& data
) {
  auto account = _accounts.find(user.value);
  check(account == _accounts.end(), "account already exists.");

  const auto rlp_encoding = rlp::encode(account.value, data);

  uint8_t buffer[32u];
  keccak_256(
    rlp_encoding.data(),
    static_cast<unsigned int>(rlp_encoding.size()),
    buffer
  );

  auto result = from_big_endian(buffer + 12u, 20u);
  print(result);


  // _accounts.modify(account, same_payer, [&](auto& a) {
  //   a.balance += quantity;
  // });
}