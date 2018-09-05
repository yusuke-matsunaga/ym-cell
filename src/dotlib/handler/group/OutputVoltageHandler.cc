
/// @file OutputVoltageHandler.cc
/// @brief OutputVoltageHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/OutputVoltageHandler.h"
#include "dotlib/AstMgr.h"
#include "dotlib/AstExpr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス OutputVoltageHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
OutputVoltageHandler::OutputVoltageHandler(DotlibParser& parser) :
  Str1GroupHandler(parser)
{
}

// @brief デストラクタ
OutputVoltageHandler::~OutputVoltageHandler()
{
}

// @breif input_voltage group statement の記述をパースする．
// @return 読み込んだ値を返す．
const AstOutputVoltage*
OutputVoltageHandler::parse_value()
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
OutputVoltageHandler::begin_group()
{
  mVol = nullptr;
  mVoh = nullptr;
  mVomin = nullptr;
  mVomax = nullptr;

  mValue = nullptr;
}

// @brief attr_type に対応する属性を読み込む．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
OutputVoltageHandler::read_group_attr(AttrType attr_type,
				      const FileRegion& attr_loc)
{
  switch ( attr_type ) {
  case AttrType::vol:   return parse_expr(mVol, attr_type, attr_loc);
  case AttrType::voh:   return parse_expr(mVoh, attr_type, attr_loc);
  case AttrType::vomin: return parse_expr(mVomin, attr_type, attr_loc);
  case AttrType::vomax: return parse_expr(mVomax, attr_type, attr_loc);
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
OutputVoltageHandler::end_group(const FileRegion& group_loc)
{
  if ( !check_attr(mVol, AttrType::vol, group_loc) ||
       !check_attr(mVoh, AttrType::voh, group_loc) ||
       !check_attr(mVomin, AttrType::vomin, group_loc) ||
       !check_attr(mVomax, AttrType::vomax, group_loc) ) {
    return false;
  }
  else {
    mValue = mgr().new_output_voltage(group_loc,
				      header_value(),
				      mVol, mVoh, mVomin, mVomax);
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
