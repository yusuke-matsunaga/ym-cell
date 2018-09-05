
/// @file IoVoltageHandler.cc
/// @brief IoVoltageHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/IoVoltageHandler.h"
#include "dotlib/ExprHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス IoVoltageHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
IoVoltageHandler::IoVoltageHandler(DotlibParser& parser) :
  Str1GroupHandler(parser)
{
}

// @brief デストラクタ
IoVoltageHandler::~IoVoltageHandler()
{
}

// @brief 式を読んでセットする．
// @param[in] dst 値を格納する変数
// @param[in] attr_type 属性の型(エラー出力に用いる)
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正しく読み込んだ．
// @retval false エラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
IoVoltageHandler::parse_expr(const AstExpr*& dst,
			     AttrType attr_type,
			     const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    ostringstream buf;
    buf << attr_type << " appear more than once.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    attr_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }
  else {
    ExprHandler handler(parser());
    dst = handler.parse_value();
    if ( dst ) {
      return true;
    }
    else {
      return false;
    }
  }
}

// @brief 属性がセットされているかチェックする．
bool
IoVoltageHandler::check_attr(const AstExpr* val,
			     AttrType attr_type,
			     const FileRegion& group_loc)
{
  if ( val == nullptr ) {
    ostringstream buf;
    buf << attr_type << " is missing.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    group_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }
  else {
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
