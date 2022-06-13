
/// @file MislibParserTest.cc
/// @brief MislibParserTest の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "gtest/gtest.h"
#include "MislibParser.h"
#include "MislibGate.h"


BEGIN_NAMESPACE_YM_MISLIB

TEST(MislibParserTest, parser)
{
  MislibParser parser;
  auto filename = string(DATA_DIR) + "/lib2.genlib";
  vector<MislibGatePtr> gate_list = parser.parse(filename);
  EXPECT_EQ( 29, gate_list.size() );
}

END_NAMESPACE_YM_MISLIB
