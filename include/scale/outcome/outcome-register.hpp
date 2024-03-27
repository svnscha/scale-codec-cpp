/**
 * Copyright Quadrivium LLC
 * All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <string>
#include <system_error>  // bring in std::error_code et al

#include <boost/config.hpp>  // for BOOST_SYMBOL_EXPORT
#include <typeinfo>

#ifndef SCALE_EXPORT
#if defined(BOOST_SYMBOL_EXPORT)
#define SCALE_EXPORT BOOST_SYMBOL_EXPORT
#else
#define SCALE_EXPORT
#endif
#endif

#define OUTCOME_USE_STD_IN_PLACE_TYPE 1

namespace scale::__outcome_detail {

  template <typename T>
  class Category : public std::error_category {
   public:
    const char *name() const noexcept final {
      return typeid(T).name();  // enum Errc -> 4Errc
    }

    std::string message(int c) const final {
      return toString(static_cast<T>(c));
    }

    static std::string toString(T t) {
      static_assert(
          !std::is_same<T, T>::value,
          "toString<T>() was not specialised for the type T supplied");
      return "";
    }

    SCALE_EXPORT static const Category<T> &get() {
      static const Category<T> c;
      return c;
    }

    ~Category() override = default;
    Category(const Category &) = delete;
    Category &operator=(const Category &) = delete;
    Category(Category &&) = delete;
    Category &operator=(Category &&) = delete;

   private:
    Category() = default;
  }; /* end of class */

}  // namespace scale::__outcome_detail

#define __OUTCOME_DEFINE_MAKE_ERROR_CODE(Enum)               \
  extern std::error_code make_error_code(Enum e) {           \
    return {static_cast<int>(e),                             \
            scale::__outcome_detail::Category<Enum>::get()}; \
  }

#define __OUTCOME_DECLARE_MAKE_ERROR_CODE(Enum) \
  std::error_code make_error_code(Enum e);

/// MUST BE EXECUTED A FILE LEVEL (no namespace) in HPP
// ns - fully qualified enum namespace. Example: libp2p::common
// Enum - enum name. Example: EncodeError
#define OUTCOME_HPP_DECLARE_ERROR(ns, Enum) \
  namespace ns {                            \
    __OUTCOME_DECLARE_MAKE_ERROR_CODE(Enum) \
  }                                         \
                                            \
  template <>                               \
  struct std::is_error_code_enum<ns::Enum> : std::true_type {};

/// MUST BE EXECUTED AT FILE LEVEL(no namespace) IN CPP
// ns - fully qualified enum namespace. Example: libp2p::common
// Enum - enum name. Example: EncodeError
// Name - variable name. Example: e
#define OUTCOME_CPP_DEFINE_CATEGORY(ns, Enum, Name)                  \
  namespace ns {                                                     \
    __OUTCOME_DEFINE_MAKE_ERROR_CODE(Enum)                           \
  };                                                                 \
  template <>                                                        \
  std::string scale::__outcome_detail::Category<ns::Enum>::toString( \
      ns::Enum Name)
