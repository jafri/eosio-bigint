project(evm)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( evm evm disassembler.cpp div.cpp evm.cpp processor.cpp stack.cpp transaction.cpp transfer.cpp util.cpp)
target_include_directories( evm PUBLIC ${CMAKE_SOURCE_DIR}/../include )

target_ricardian_directory( evm ${CMAKE_SOURCE_DIR}/../ricardian )