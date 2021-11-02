/**
* Copyright Soramitsu Co., Ltd. All Rights Reserved.
* SPDX-License-Identifier: Apache-2.0
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <scale/scale_encoder_stream.hpp>
#include <scale/scale_decoder_stream.hpp>
#include <scale/types.hpp>

using scale::ScaleEncoderStream;
using scale::ScaleDecoderStream;
using scale::ByteArray;

template <typename T>
class EnumTest : public ::testing::Test {
 public:

 protected:
  const static std::string enum_name;
  const static std::vector<T> values;

  ScaleEncoderStream encoder;
};

enum class Foo: uint16_t {
  A = 0,
  B = 1,
  C = 2
};

enum class Bar: int64_t {
  A = -32,
  B = 42,
  C = 0
};

using MyTypes = ::testing::Types<Foo, Bar>;
TYPED_TEST_CASE(EnumTest, MyTypes);

template<>
const std::string EnumTest<Foo>::enum_name {"Foo"};
template<>
const std::vector<Foo> EnumTest<Foo>::values {};

template<>
const std::string EnumTest<Bar>::enum_name {"Bar"};
template<>
const std::vector<Bar> EnumTest<Bar>::values {};

TYPED_TEST(EnumTest, ConsistentEncodingDecoding) {
  for(auto& param: TestFixture::values) {
    SCOPED_TRACE(TestFixture::enum_name);
    auto& value = param;
    ASSERT_NO_THROW((this->encoder << value));
    ScaleDecoderStream decoder{this->encoder.data()};
    TypeParam decoded_value;
    ASSERT_NO_THROW((decoder >> decoded_value));
    ASSERT_EQ(decoded_value, value);
  }
}

TYPED_TEST(EnumTest, CorrectEncoding) {
  for(auto& param: TestFixture::values) {
    SCOPED_TRACE(TestFixture::enum_name);
    auto& value = param;
    ASSERT_NO_THROW((this->encoder << value));
    ScaleDecoderStream decoder{this->encoder.data()};
    std::underlying_type_t<TypeParam> decoded_value;
    ASSERT_NO_THROW((decoder >> decoded_value));
    ASSERT_EQ(decoded_value, static_cast<std::underlying_type_t<TypeParam>>(param));
  }
}
