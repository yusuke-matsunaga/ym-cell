
/// @file ParserTest_ast.cc
/// @brief Parser の総合テスト
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ParserTest.h"
#include "Parser.h"
#include "AstAttr.h"
#include "AstValue.h"

#include "parse_complex.h"


BEGIN_NAMESPACE_YM_DOTLIB

TEST_F(ParserTest, ast1)
{
  StreamMsgHandler handler(cout);
  MsgMgr::attach_handler(&handler);
  string filename = string(DATA_DIR) + string("/HIT018.typ.snp");
  ifstream fin{filename};
  ASSERT_TRUE( fin );
  Parser parser{fin, FileInfo{filename}, false, true};

  auto ast_library{parser.parse()};
  ast_library->dump(cout);
}

END_NAMESPACE_YM_DOTLIB
