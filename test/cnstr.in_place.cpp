// MPark.Variant
//
// Copyright Michael Park, 2015-2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <mpark/variant.hpp>

#include <string>

#include <gtest/gtest.h>

TEST(Cnstr_InPlace, IndexDirect) {
  mpark::variant<int, std::string> v(mpark::in_place_index_t<0>{}, 42);
  EXPECT_EQ(42, mpark::get<0>(v));

  /* constexpr */ {
    constexpr mpark::variant<int, const char *> cv(mpark::in_place_index_t<0>{},
                                                   42);
    static_assert(42 == mpark::get<0>(cv), "");
  }
}

TEST(Cnstr_InPlace, IndexDirectDuplicate) {
  mpark::variant<int, int> v(mpark::in_place_index_t<0>{}, 42);
  EXPECT_EQ(42, mpark::get<0>(v));

  /* constexpr */ {
    constexpr mpark::variant<int, int> cv(mpark::in_place_index_t<0>{}, 42);
    static_assert(42 == mpark::get<0>(cv), "");
  }
}

TEST(Cnstr_InPlace, IndexConversion) {
  mpark::variant<int, std::string> v(mpark::in_place_index_t<1>{}, "42");
  EXPECT_EQ("42", mpark::get<1>(v));

  /* constexpr */ {
    constexpr mpark::variant<int, const char *> cv(mpark::in_place_index_t<0>{},
                                                   1.1);
    static_assert(1 == mpark::get<0>(cv), "");
  }
}

#if 0
TEST(Cnstr_InPlace, IndexConversionDuplicateRef) {
  std::ostringstream strm;
  mpark::variant<std::ostream &, std::ostream &> v(mpark::in_place_index<0>, strm);
  EXPECT_EQ(&strm, &mpark::get<0>(v));
}
#endif

TEST(Cnstr_InPlace, IndexInitializerList) {
  mpark::variant<int, std::string> v(mpark::in_place_index_t<1>{}, {'4', '2'});
  EXPECT_EQ("42", mpark::get<1>(v));
}

TEST(Cnstr_InPlace, TypeDirect) {
  mpark::variant<int, std::string> v(mpark::in_place_type_t<std::string>{},
                                     "42");
  EXPECT_EQ("42", mpark::get<std::string>(v));

  /* constexpr */ {
    constexpr mpark::variant<int, const char *> cv(
        mpark::in_place_type_t<int>{}, 42);
    static_assert(42 == mpark::get<int>(cv), "");
  }
}

#if 0
TEST(Cnstr_InPlace, TypeDirectRef) {
  int expected = 42;
  mpark::variant<int &, std::ostream &> v(mpark::in_place_type_t<int &>{},
                                          expected);
  EXPECT_EQ(expected, mpark::get<int &>(v));
  EXPECT_EQ(&expected, &mpark::get<int &>(v));
}
#endif

TEST(Cnstr_InPlace, TypeConversion) {
  mpark::variant<int, std::string> v(mpark::in_place_type_t<int>{}, 42.5);
  EXPECT_EQ(42, mpark::get<int>(v));

  /* constexpr */ {
    constexpr mpark::variant<int, const char *> cv(
        mpark::in_place_type_t<int>{}, 42.5);
    static_assert(42 == mpark::get<int>(cv), "");
  }
}

#if 0
TEST(Cnstr_InPlace, TypeConversionRef) {
  std::ostringstream strm;
  mpark::variant<int, std::ostream &> v(mpark::in_place_type_t<std::ostream &>{},
                                        strm);
  EXPECT_EQ(&strm, &mpark::get<std::ostream &>(v));
}
#endif

TEST(Cnstr_InPlace, TypeInitializerList) {
  mpark::variant<int, std::string> v(mpark::in_place_type_t<std::string>{},
                                     {'4', '2'});
  EXPECT_EQ("42", mpark::get<std::string>(v));
}
