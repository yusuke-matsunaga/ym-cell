
/// @file InputVoltageHandler.cc
/// @brief InputVoltageHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "InputVoltageHandler.h"
#include "dotlib/AstMgr.h"
#include "dotlib/AstInputVoltage.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス InputVoltageHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
InputVoltageHandler::InputVoltageHandler(DotlibParser& parser) :
  Str1GroupHandler(parser),
  mVil(parser),
  mVih(parser),
  mVimin(parser),
  mVimax(parser)
{
}

// @brief デストラクタ
InputVoltageHandler::~InputVoltageHandler()
{
}

// @brief 値をクリアする．
void
InputVoltageHandler::clear_value()
{
  mValue = nullptr;
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
  mVil.clear_value();
  mVih.clear_value();
  mVimin.clear_value();
  mVimax.clear_value();
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
  case AttrType::vil:   return mVil.parse_attr_value();
  case AttrType::vih:   return mVih.parse_attr_value();
  case AttrType::vimin: return mVimin.parse_attr_value();
  case AttrType::vimax: return mVimax.parse_attr_value();
  default: break;
  }
  syntax_error(attr_type, attr_loc);
  return false;
}

// @brief グループ記述の終わり
// @param[in] group_loc グループ全体のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
InputVoltageHandler::end_group(const FileRegion& group_loc)
{
  mValue = mgr().new_input_voltage(group_loc,
				   header_value(),
				   mVil.value(),
				   mVih.value(),
				   mVimin.value(),
				   mVimax.value());

  return true;
}

END_NAMESPACE_YM_DOTLIB
