project(test_project)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( test test test.cpp div.cpp )
target_include_directories( test PUBLIC ${CMAKE_SOURCE_DIR}/../include )

target_ricardian_directory( test ${CMAKE_SOURCE_DIR}/../ricardian )