project(evm)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( evm evm div.cpp evm.cpp utils.cpp transfer.cpp disassembler.cpp util.cpp stack.cpp )
target_include_directories( evm PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( evm ${CMAKE_SOURCE_DIR}/../ricardian )