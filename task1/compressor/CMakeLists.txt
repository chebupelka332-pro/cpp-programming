find_package(spdlog REQUIRED)

add_executable(compressor
    src/compressor.cpp
)

target_link_libraries(compressor
    PRIVATE
        project_warnings
        libcompressor
        spdlog::spdlog
)

install(TARGETS compressor RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})