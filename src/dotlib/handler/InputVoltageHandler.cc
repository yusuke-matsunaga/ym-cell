
/// @file InputVoltageHandler.cc
/// @brief InputVoltageHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HandlerFactory.h"
#include "InputVoltageHandler.h"
#include "dotlib/AstMgr.h"
#include "dotlib/AstExpr.h"
#include "dotlib/AstAttr.h"
#include "dotlib/AstInputVoltage.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief input_voltage group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_input_voltage(DotlibParser& parser)
{
  return new InputVoltageHandler(parser);
}


//////////////////////////////////////////////////////////////////////
// クラス InputVoltageHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
InputVoltageHandler::InputVoltageHandler(DotlibParser& parser) :
  Str1GroupHandler(parser)
{
  mExprHandler = HandlerFactory::new_expr(parser);
}

// @brief デストラクタ
InputVoltageHandler::~InputVoltageHandler()
{
}

// @brief 属性値を読み込む．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @return 読み込んだ値を表す AstNode を返す．
//
// エラーの場合には nullptr を返す．
const AstNode*
InputVoltageHandler::parse_attr_value(AttrType attr_type,
				      const FileRegion& attr_loc)
{
  return parse(attr_type, attr_loc);
}

// @brief パーズする．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @return 読み込んだ InputVoltage を返す．
bool
InputVoltageHandler::parse(AttrType attr_type,
			   const FileRegion& attr_loc)
{
  mVil = nullptr;
  mVih = nullptr;
  mVimin = nullptr;
  mVimax = nullptr;

  const AstString* value;
  FileRegion value_loc;
  FileRegion end_loc;
  bool r = parse_common(attr_type, attr_loc, value, value_loc, end_loc);
  if ( !r ) {
    return nullptr;
  }

  FileRegion loc(attr_loc, end_loc);
  return mgr().new_input_voltage(loc, value, mVil, mVih, mVimin, mVimax);
}

// @brief attr_type に対応する属性を読み込む．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正常に処理した．
// @retval false 処理中にエラーが起こった．
bool
InputVoltageHandler::parse_attr(AttrType attr_type,
				const FileRegion& attr_loc)
{
  switch ( attr_type ) {
  case AttrType::vil:
    return mExprHandler->parse_and_assign(attr_type, attr_loc, mVil);

  case AttrType::vih:
    return mExprHandler->parse_and_assign(attr_type, attr_loc, mVih);

  case AttrType::vimin:
    return mExprHandler->parse_and_assign(attr_type, attr_loc, mVimin);

  case AttrType::vimax:
    return mExprHandler->parse_and_assign(attr_type, attr_loc, mVimax);

  default:
    break;
  }
  return false;
}

END_NAMESPACE_YM_DOTLIB
