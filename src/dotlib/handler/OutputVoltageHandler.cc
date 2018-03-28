
/// @file OutputVoltageHandler.cc
/// @brief OutputVoltageHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "HandlerFactory.h"
#include "OutputVoltageHandler.h"
#include "AstMgr.h"
#include "AstExpr.h"
#include "AstAttr.h"
#include "AstOutputVoltage.h"
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
  Str1GroupHandler(parser)
{
  mExprHandler = HandlerFactory::new_expr(parser);
}

// @brief デストラクタ
OutputVoltageHandler::~OutputVoltageHandler()
{
}

// @brief 属性値を読み込む．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @return 読み込んだ値を表す AstNode を返す．
//
// エラーの場合には nullptr を返す．
const AstNode*
OutputVoltageHandler::parse_attr_value(AttrType attr_type,
				       const FileRegion& attr_loc)
{
  return parse(attr_type, attr_loc);
}

// @brief パーズする．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @return 読み込んだ InputVoltage を返す．
//
// エラーの場合には nullptr を返す．
const AstOutputVoltage*
OutputVoltageHandler::parse(AttrType attr_type,
			    const FileRegion& attr_loc)
{
  mVol = nullptr;
  mVoh = nullptr;
  mVomin = nullptr;
  mVomax = nullptr;

  const AstString* value;
  FileRegion value_loc;
  FileRegion end_loc;
  bool r = parse_common(attr_type, attr_loc, value, value_loc, end_loc);
  if ( !r ) {
    return nullptr;
  }

  FileRegion loc(attr_loc, end_loc);
  return mgr().new_output_voltage(loc, value, mVil, mVih, mVimin, mVimax);
}

// @brief attr_type に対応する属性を読み込む．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正常に処理した．
// @retval false 処理中にエラーが起こった．
bool
OutputVoltageHandler::parse_attr(AttrType attr_type,
				 const FileRegion& attr_loc)
{
  switch ( attr_type ) {
  case AttrType::vol:
    return mExprHandler->parse_and_assign(attr_type, attr_loc, mVol);

  case AttrType::voh:
    return mExprHandler->parse_and_assign(attr_type, attr_loc, mVoh);

  case AttrType::vomin:
    return mExprHandler->parse_and_assign(attr_type, attr_loc, mVomin);

  case AttrType::vomax:
    return mExprHandler->parse_and_assign(attr_type, attr_loc, mVomax);

  default:
    break;
  }
  return false;
}

END_NAMESPACE_YM_DOTLIB
