
/// @file InputVoltageHandler.cc
/// @brief InputVoltageHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/InputVoltageHandler.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス InputVoltageHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
InputVoltageHandler::InputVoltageHandler(DotlibParser& parser) :
  IoVoltageHandler(parser)
{
}

// @brief デストラクタ
InputVoltageHandler::~InputVoltageHandler()
{
}

// @breif input_voltage group statement の記述をパースする．
// @return 読み込んだ値を返す．
const AstInputVoltage*
InputVoltageHandler::parse_value()
{
  bool stat = parse_group_statement();
  if ( stat ) {
    return mValue;
  }
  else {
    return nullptr;
  }
}

// @brief グループ記述の始まり
void
InputVoltageHandler::begin_group()
{
  mVil = nullptr;
  mVih = nullptr;
  mVimin = nullptr;
  mVimax = nullptr;

  mValue = nullptr;
}

// @brief attr_type に対応する属性を読み込む．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正常に処理した．
// @retval false 処理中にエラーが起こった．
bool
InputVoltageHandler::read_group_attr(AttrType attr_type,
				     const FileRegion& attr_loc)
{
  switch ( attr_type ) {
  case AttrType::vil:   return parse_expr(mVil, attr_type, attr_loc);
  case AttrType::vih:   return parse_expr(mVih, attr_type, attr_loc);
  case AttrType::vimin: return parse_expr(mVimin, attr_type, attr_loc);
  case AttrType::vimax: return parse_expr(mVimax, attr_type, attr_loc);
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
  if ( !check_attr(mVil, AttrType::vil, group_loc) ||
       !check_attr(mVih, AttrType::vih, group_loc) ||
       !check_attr(mVimin, AttrType::vimin, group_loc) ||
       !check_attr(mVimax, AttrType::vimax, group_loc) ) {
    return false;
  }
  else {
    mValue = mgr().new_input_voltage(group_loc,
				     header_value(),
				     mVil, mVih, mVimin, mVimax);

    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
