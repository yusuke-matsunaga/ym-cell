
/// @file OutputVoltageHandler.cc
/// @brief OutputVoltageHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HandlerFactory.h"
#include "OutputVoltageHandler.h"
#include "dotlib/AstMgr.h"
#include "dotlib/AstExpr.h"
#include "dotlib/AstAttr.h"
#include "dotlib/AstOutputVoltage.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief output_voltage group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_output_voltage(DotlibParser& parser)
{
  return new OutputVoltageHandler(parser);
}


//////////////////////////////////////////////////////////////////////
// クラス OutputVoltageHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
OutputVoltageHandler::OutputVoltageHandler(DotlibParser& parser) :
  Str1GroupHandler(parser),
  mVol(parser),
  mVoh(parser),
  mVomin(parser),
  mVomax(parser)

{
}

// @brief デストラクタ
OutputVoltageHandler::~OutputVoltageHandler()
{
}

// @brief 値をクリアする．
void
OutputVoltageHandler::clear_value()
{
  mValue = nullptr;
}

// @brief 読み込んだ値を返す．
const AstOutputVoltage*
OutputVoltageHandler::value() const
{
  return mValue;
}

// @brief グループ記述の始まり
void
OutputVoltageHandler::begin_group()
{
  mVol.clear_value();
  mVoh.clear_value();
  mVomin.clear_value();
  mVomax.clear_value();
}

// @brief attr_type に対応する属性を読み込む．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
OutputVoltageHandler::parse_attr(AttrType attr_type,
				 const FileRegion& attr_loc)
{
  switch ( attr_type ) {
  case AttrType::vol:   return mVol.parse_attr_value();
  case AttrType::voh:   return mVoh.parse_attr_value();
  case AttrType::vomin: return mVomin.parse_attr_value();
  case AttrType::vomax: return mVomax.parse_attr_value();
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
  mValue = mgr().new_output_voltage(group_loc,
				    header_value(),
				    mVol.value(),
				    mVoh.value(),
				    mVomin.value(),
				    mVomax.value());

  return true;
}

END_NAMESPACE_YM_DOTLIB
