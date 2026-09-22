#include <cstdlib>
#include <cstring>
#include <vector>

#include "gtest/gtest.h"
#include "libcompressor/libcompressor.hpp"

namespace {

libcompressor_Buffer MakeInput(const char* str) {
  libcompressor_Buffer buf{};
  buf.data = const_cast<char*>(str);
  buf.size = static_cast<int>(std::strlen(str));
  return buf;
}

void FreeOutput(libcompressor_Buffer& buf) {
  std::free(buf.data);
  buf.data = nullptr;
  buf.size = 0;
}

}  // namespace

TEST(Compress, ZlibNonEmptyGivesNonEmpty) {
  const char* text = "hello world";
  libcompressor_Buffer input = MakeInput(text);
  libcompressor_Buffer out = libcompressor_compress(libcompressor_Zlib, input);
  EXPECT_NE(out.data, nullptr);
  EXPECT_GT(out.size, 0);
  FreeOutput(out);
}

TEST(Compress, BzipNonEmptyGivesNonEmpty) {
  const char* text = "hello world";
  libcompressor_Buffer input = MakeInput(text);
  libcompressor_Buffer out = libcompressor_compress(libcompressor_Bzip, input);
  EXPECT_NE(out.data, nullptr);
  EXPECT_GT(out.size, 0);
  FreeOutput(out);
}

TEST(Compress, EmptyInputGivesEmpty) {
  libcompressor_Buffer null_input{nullptr, 11};
  libcompressor_Buffer out1 = libcompressor_compress(libcompressor_Zlib, null_input);
  EXPECT_EQ(out1.data, nullptr);
  EXPECT_EQ(out1.size, 0);

  libcompressor_Buffer out2 = libcompressor_compress(libcompressor_Bzip, null_input);
  EXPECT_EQ(out2.data, nullptr);
  EXPECT_EQ(out2.size, 0);

  char dummy = 'x';
  libcompressor_Buffer zero_input{&dummy, 0};
  libcompressor_Buffer out3 = libcompressor_compress(libcompressor_Zlib, zero_input);
  EXPECT_EQ(out3.data, nullptr);
  EXPECT_EQ(out3.size, 0);

  libcompressor_Buffer out4 = libcompressor_compress(libcompressor_Bzip, zero_input);
  EXPECT_EQ(out4.data, nullptr);
  EXPECT_EQ(out4.size, 0);

  libcompressor_Buffer empty_str{const_cast<char*>(""), 0};
  libcompressor_Buffer out5 = libcompressor_compress(libcompressor_Zlib, empty_str);
  EXPECT_EQ(out5.data, nullptr);
  EXPECT_EQ(out5.size, 0);
}

TEST(Compress, ZlibTestStringExactBytes) {
  const char* text = "test_string";
  libcompressor_Buffer input = MakeInput(text);
  libcompressor_Buffer out = libcompressor_compress(libcompressor_Zlib, input);

  const std::vector<unsigned char> expected = {0x78, 0x9c, 0x2b, 0x49, 0x2d, 0x2e, 0x89, 0x2f, 0x2e, 0x29,
                                               0xca, 0xcc, 0x4b, 0x07, 0x00, 0x1c, 0x79, 0x04, 0xb7};

  ASSERT_NE(out.data, nullptr);
  ASSERT_EQ(out.size, static_cast<int>(expected.size()));
  for (std::size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(static_cast<unsigned char>(out.data[i]), expected[i]) << "mismatch at byte " << i;
  }
  FreeOutput(out);
}

TEST(Compress, BzipTestStringExactBytes) {
  const char* text = "test_string";
  libcompressor_Buffer input = MakeInput(text);
  libcompressor_Buffer out = libcompressor_compress(libcompressor_Bzip, input);

  const std::vector<unsigned char> expected = {0x42, 0x5a, 0x68, 0x31, 0x31, 0x41, 0x59, 0x26, 0x53, 0x59, 0x4a, 0x7c,
                                               0x69, 0x05, 0x00, 0x00, 0x04, 0x83, 0x80, 0x00, 0x00, 0x82, 0xa1, 0x1c,
                                               0x00, 0x20, 0x00, 0x22, 0x03, 0x68, 0x84, 0x30, 0x22, 0x50, 0xdf, 0x04,
                                               0x99, 0xe2, 0xee, 0x48, 0xa7, 0x0a, 0x12, 0x09, 0x4f, 0x8d, 0x20, 0xa0};

  ASSERT_NE(out.data, nullptr);
  ASSERT_EQ(out.size, static_cast<int>(expected.size()));
  for (std::size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(static_cast<unsigned char>(out.data[i]), expected[i]) << "mismatch at byte " << i;
  }
  FreeOutput(out);
}
