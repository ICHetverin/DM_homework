add_executable(regex_tests
    main.cpp
    parser_tests.cpp
    ast_builder.h
    test_framework.h
)

target_include_directories(regex_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(regex_tests PRIVATE
    regex_lib
)