add_library(regex_lib STATIC
    ast.cpp
    ast.h
    grammar.cpp
    grammar.h
    lexer.cpp
    lexer.h
    nonterminal.h
    parser.cpp
    parser.h
    token.h
)

target_include_directories(regex_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
