
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
  mVil   = HandlerFactory::new_expr(parser);
  mVih   = HandlerFactory::new_expr(parser);
  mVimin = HandlerFactory::new_expr(parser);
  mVimax = HandlerFactory::new_expr(parser);
}

// @brief デストラクタ
InputVoltageHandler::~InputVoltageHandler()
{
}

// @brief 読み込んだ値を返す．
const AstInputVoltage*
InputVoltageHandler::value() const
{
  return mValue;
}

// @brief グループ記述の始まり
void
InputVoltageHandler::begin_group()
{
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
    return mVil->parse_attr_value(attr_type, attr_loc);

  case AttrType::vih:
    return mVih->parse_attr_value(attr_type, attr_loc);

  case AttrType::vimin:
    return mVimin->parse_attr_value(attr_type, attr_loc);

  case AttrType::vimax:
    return mVimax->parse_attr_value(attr_type, attr_loc);

  default:
    break;
  }
  return false;
}

// @brief グループ記述の終わり
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
InputVoltageHandler::end_group(AttrType attr_type,
			       const FileRegion& attr_loc)
{
}

END_NAMESPACE_YM_DOTLIB
