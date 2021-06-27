#ifndef PARSERTEST_H
#define PARSERTEST_H

/// @file ParserTest.h
/// @brief ParserTest のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "gtest/gtest.h"
#include "dotlib_nsdef.h"
#include "AttrKwd.h"
#include "ym/MsgMgr.h"
#include "ym/StrListMsgHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

class ParserTest :
  public ::testing::Test
{
public:

  ParserTest()
  {
    MsgMgr::attach_handler(&mh);
  }

  FileInfo info{"parser_test.lib"};
  AttrKwd attr;
  StrListMsgHandler mh;

};

END_NAMESPACE_YM_DOTLIB

#endif // PARSERTEST_H
