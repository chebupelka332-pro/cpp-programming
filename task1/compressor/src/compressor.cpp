#include <spdlog/spdlog.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "libcompressor/libcompressor.hpp"

auto main(int argc, char** argv) -> int {
  spdlog::set_level(spdlog::level::err);

  if (argc < 3) {
    spdlog::error("Too few arguments. Usage: {} <zlib|bzip> <string>", argv[0]);
    return EXIT_FAILURE;
  }

  char* input_buffer = argv[2];
  const int input_size = static_cast<int>(std::strlen(input_buffer));
  if (input_size <= 0) {
    spdlog::error("Input buffer is empty.");
    return EXIT_FAILURE;
  }

  char* algo = argv[1];
  libcompressor_CompressionAlgorithm algorithm;
  if (std::strcmp(algo, "zlib") == 0) {
    algorithm = libcompressor_Zlib;
  } else if (std::strcmp(algo, "bzip") == 0) {
    algorithm = libcompressor_Bzip;
  } else {
    spdlog::error("Unknown compression algorithm: {}. Supported algorithms: zlib, bzip", algo);
    return EXIT_FAILURE;
  }

  const libcompressor_Buffer input{input_buffer, input_size};

  const libcompressor_Buffer compressed = libcompressor_compress(algorithm, input);
  if (compressed.data == nullptr || compressed.size <= 0) {
    spdlog::error("Compression failed.");
    return EXIT_FAILURE;
  }

  for (int i = 0; i < compressed.size; ++i) {
    std::printf("%.2hhx", static_cast<unsigned char>(compressed.data[i]));
  }
  std::printf("\n");

  std::free(compressed.data);

  return EXIT_SUCCESS;
}