/**
 * Copyright Soramitsu Co., Ltd. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <scale/buffer/hexutil.hpp>
#include <scale/scale_decoder_stream.hpp>
#include <scale/scale_encoder_stream.hpp>
#include <scale/types.hpp>

using scale::ByteArray;
using scale::ScaleDecoderStream;
using scale::ScaleEncoderStream;

template <typename T>
class EnumTest : public ::testing::Test {
 public:
 protected:
  const static std::string enum_name;
  const static std::vector<T> values;
};

enum class Foo : uint16_t { A = 0, B = 1, C = 2 };

enum class Bar : int64_t { A = -32, B = 42, C = 0 };

using MyTypes = ::testing::Types<Foo, Bar>;
TYPED_TEST_CASE(EnumTest, MyTypes);

template <>
const std::string EnumTest<Foo>::enum_name{"Foo"};
template <>
const std::vector<Foo> EnumTest<Foo>::values{Foo::A, Foo::B, Foo::C};

template <>
const std::string EnumTest<Bar>::enum_name{"Bar"};
template <>
const std::vector<Bar> EnumTest<Bar>::values{Bar::A, Bar::B, Bar::C};

TYPED_TEST(EnumTest, ConsistentEncodingDecoding) {
  SCOPED_TRACE(TestFixture::enum_name);
  for (auto const &param : TestFixture::values) {
    ScaleEncoderStream encoder{};
    ASSERT_NO_THROW((encoder << param));

    ScaleDecoderStream decoder{encoder.to_vector()};
    TypeParam decoded_value;
    ASSERT_NO_THROW((decoder >> decoded_value));

    EXPECT_EQ(decoded_value, param);
  }
}

TYPED_TEST(EnumTest, CorrectEncoding) {
  for (auto const &param : TestFixture::values) {
    SCOPED_TRACE(TestFixture::enum_name);
    ScaleEncoderStream encoder{};
    ASSERT_NO_THROW((encoder << param));
    ScaleDecoderStream decoder{encoder.to_vector()};
    std::underlying_type_t<TypeParam> decoded_value;
    ASSERT_NO_THROW((decoder >> decoded_value));
    EXPECT_EQ(decoded_value,
              static_cast<std::underlying_type_t<TypeParam>>(param));
  }
}
