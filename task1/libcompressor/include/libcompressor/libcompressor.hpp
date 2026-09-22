#pragma once

#include <cstddef>

/**
 * @brief Доступные алгоритмы сжатия данных.
 */
enum libcompressor_CompressionAlgorithm {
  libcompressor_Zlib, /**< Алгоритм zlib */
  libcompressor_Bzip  /**< Алгоритм bzip2 */
};

/**
 * @brief Структура буфера данных.
 */
struct libcompressor_Buffer {
  char* data; /**< Указатель на данные */
  int size;   /**< Размер данных в байтах */
};

/**
 * @brief Функция сжатия входного буфера.
 *
 * Выделяет память под выходной буфер через std::malloc (input.size + 1024 байта).
 * В случае ошибки возвращает буфер с data == NULL и size == 0.
 *
 * @param algo  Алгоритм сжатия.
 * @param input Входной буфер для сжатия.
 * @return      libcompressor_Buffer Сжатый буфер данных.
 */
libcompressor_Buffer libcompressor_compress(libcompressor_CompressionAlgorithm algo, libcompressor_Buffer input);