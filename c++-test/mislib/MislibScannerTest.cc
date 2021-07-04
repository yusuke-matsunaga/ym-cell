
/// @file MislibParserTest.cc
/// @brief MislibParserTest の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "gtest/gtest.h"
#include "MislibScanner.h"
#include <fstream>


BEGIN_NAMESPACE_YM_MISLIB

TEST(MislibScannerTest, parser)
{
  auto filename = string(DATA_DIR) + "/lib2.genlib";
  ifstream fin{filename};
  ASSERT_TRUE( fin );
  MislibScanner scanner(fin, {filename});

  int ntok = 0;
  for ( ; ; ) {
    auto tok = scanner.read_token();
    if ( tok.type() == MislibToken::END ) {
      break;
    }
    ++ ntok;
  }
  EXPECT_EQ( 1387, ntok );
}

END_NAMESPACE_YM_MISLIB
