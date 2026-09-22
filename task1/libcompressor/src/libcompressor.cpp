#include "libcompressor/libcompressor.hpp"

#include <bzlib.h>
#include <zlib.h>

#include <cstdlib>

libcompressor_Buffer libcompressor_compress(libcompressor_CompressionAlgorithm algo, libcompressor_Buffer input) {
    libcompressor_Buffer error_buf{nullptr, 0};

    if (input.data == nullptr || input.size <= 0) {
        return error_buf;
    }

    int initial_dest_size = input.size + 1024;
    char* out_data = static_cast<char*>(std::malloc(initial_dest_size));
    if (out_data == nullptr) {
        return error_buf;
    }

    if (algo == libcompressor_Zlib) {
        uLongf dest_len = static_cast<uLongf>(initial_dest_size);

        int res = compress2(reinterpret_cast<Bytef*>(out_data), &dest_len, reinterpret_cast<const Bytef*>(input.data),
                            static_cast<uLong>(input.size), Z_DEFAULT_COMPRESSION);

        if (res != Z_OK) {
            std::free(out_data);
            return error_buf;
        }

        return libcompressor_Buffer{out_data, static_cast<int>(dest_len)};
    } else if (algo == libcompressor_Bzip) {
        unsigned int dest_len = static_cast<unsigned int>(initial_dest_size);

        int res =
            BZ2_bzBuffToBuffCompress(out_data, &dest_len, input.data, static_cast<unsigned int>(input.size), 1, 0, 0);

        if (res != BZ_OK) {
            std::free(out_data);
            return error_buf;
        }

        return libcompressor_Buffer{out_data, static_cast<int>(dest_len)};
    }

    std::free(out_data);
    return error_buf;
}