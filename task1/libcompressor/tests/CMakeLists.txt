find_package(GTest REQUIRED)

add_executable(libcompressortest
    libcompressortest.cpp
)

target_link_libraries(libcompressortest
    PRIVATE
        project_warnings
        libcompressor
        GTest::gtest
        GTest::gtest_main
)

# Регистрация теста в CTest с флагом выгрузки XML отчета
add_test(
    NAME UnitTests
    COMMAND libcompressortest --gtest_output=xml:${CMAKE_BINARY_DIR}/test_results.xml
)