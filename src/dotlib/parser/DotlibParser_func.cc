
/// @file DotlibParser_func.cc
/// @brief DotlibParser の実装ファイル ( function 関連 )
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibParser.h"
#include "dotlib/AstMgr.h"
#include "dotlib/AstExpr.h"
#include "ym/MsgMgr.h"

#include "FuncParser.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 論理関数のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_function(const AstExpr*& dst,
			     AttrType attr_type,
			     const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
#if 0
    FuncHandler handler(*this);
    bool stat = parse_simple_attribute(handler);
    if ( stat ) {
      dst = handler.value();
    }
    return stat;
#else
    const char* tmp_str;
    FileRegion value_loc;
    bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
				       { return parser.read_raw_string(tmp_str, value_loc); });
    if ( stat ) {
      FuncParser read(tmp_str, value_loc, mgr());
      stat = read(dst);
    }

    return stat;
#endif
  }
}

END_NAMESPACE_YM_DOTLIB
