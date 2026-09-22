find_package(ZLIB REQUIRED)
find_package(BZip2 REQUIRED)

add_library(libcompressor STATIC
    src/libcompressor.cpp
)

target_link_libraries(libcompressor
    PUBLIC
        project_warnings
    PRIVATE
        ZLIB::ZLIB
        BZip2::BZip2
)

target_include_directories(libcompressor
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Правила установки библиотеки и заголовочных файлов
install(TARGETS libcompressor
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/libcompressor
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)