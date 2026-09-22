cmake_minimum_required(VERSION 3.20)
project(ModernCppCompressor LANGUAGES CXX)

# Экспорт базы компиляции для clang-tidy и clang-format
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Установка стандарта C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Подключение модуля путей установки
include(GNUInstallDirs)

# Создание интерфейсной библиотеки для флагов компилятора
add_library(project_warnings INTERFACE)
target_compile_options(project_warnings INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

# Генерация документации Doxygen
find_package(Doxygen)
if(Doxygen_FOUND)
    set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/docs")
    set(DOXYGEN_EXTRACT_ALL YES)
    doxygen_add_docs(docs
        ${CMAKE_CURRENT_SOURCE_DIR}/libcompressor/include
        COMMENT "Generating API documentation with Doxygen"
    )
endif()

# Включение CTest
enable_testing()

# Подключение поддиректорий по структуре проекта
add_subdirectory(libcompressor)
add_subdirectory(compressor)
add_subdirectory(libcompressor/tests)