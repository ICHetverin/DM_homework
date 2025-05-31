add_executable(regex_tests
    main.cpp
    ast_builder.h
    test_framework.h
    correctness_tests.cpp
    exception_tests.cpp
    vizualization_tests.cpp
    )

target_include_directories(regex_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(regex_tests PRIVATE
    regex_lib
)
