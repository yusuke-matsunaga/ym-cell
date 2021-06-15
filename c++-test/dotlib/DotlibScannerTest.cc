
/// @file DotlibScannerTest.cc
/// @brief DotlibScannerTest の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "gtest/gtest.h"
#include "DotlibScanner.h"
#include "TokenType.h"
#include "ym/InputFileObj.h"


BEGIN_NAMESPACE_YM_DOTLIB

TEST(DotlibScannerTest, read_token1)
{
  istringstream buf{":;,+-*/(){}\n"};
  FileInfo info{};
  InputFileObj in{buf, info};
  DotlibScanner scanner{in};

  TokenType exp_list[] = {
    TokenType::COLON,
    TokenType::SEMI,
    TokenType::COMMA,
    TokenType::PLUS,
    TokenType::MINUS,
    TokenType::MULT,
    TokenType::DIV,
    TokenType::LP,
    TokenType::RP,
    TokenType::LCB,
    TokenType::RCB,
    TokenType::NL,
    TokenType::END
  };

  for ( auto exp: exp_list ) {
    FileRegion loc;
    auto token_type = scanner.read_token(loc);
    EXPECT_EQ ( exp, token_type );
  }
}

TEST(DotlibScannerTest, read_token2)
{
  istringstream buf{"abcdef xyz 123\t456.78"};
  FileInfo info{};
  InputFileObj in{buf, info};
  DotlibScanner scanner{in};

  FileRegion loc;
  auto token_type1 = scanner.read_token(loc);
  EXPECT_EQ( TokenType::SYMBOL, token_type1 );
  EXPECT_TRUE( strcmp(scanner.cur_string(), "abcdef") == 0 );

  auto token_type2 = scanner.read_token(loc);
  EXPECT_EQ( TokenType::SYMBOL, token_type2 );
  EXPECT_TRUE( strcmp(scanner.cur_string(), "xyz") == 0 );

  auto token_type3 = scanner.read_token(loc);
  EXPECT_EQ( TokenType::INT_NUM, token_type3 );
  EXPECT_EQ( 123, scanner.cur_int() );

  auto token_type4 = scanner.read_token(loc);
  EXPECT_EQ( TokenType::FLOAT_NUM, token_type4 );
  EXPECT_EQ( 456.78, scanner.cur_float() );
}

END_NAMESPACE_YM_DOTLIB
