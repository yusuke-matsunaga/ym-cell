
/// @file InputVoltageHandler.cc
/// @brief InputVoltageHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/InputVoltageHandler.h"
#include "dotlib/AstMgr.h"
#include "dotlib/AstExpr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス InputVoltageHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
InputVoltageHandler::InputVoltageHandler(DotlibParser& parser) :
  Str1GroupHandler(parser)
{
  // パース関数の登録
  reg_func(AttrType::vil,
	   [=](DotlibParser& parser,
	       AttrType attr_type,
	       const FileRegion& attr_loc) -> bool
	   {
	     return parser.parse_expr(mVil, attr_type, attr_loc);
	   });
  reg_func(AttrType::vih,
	   [=](DotlibParser& parser,
	       AttrType attr_type,
	       const FileRegion& attr_loc) -> bool
	   {
	     return parser.parse_expr(mVih, attr_type, attr_loc);
	   });
  reg_func(AttrType::vimin,
	   [=](DotlibParser& parser,
	       AttrType attr_type,
	       const FileRegion& attr_loc) -> bool
	   {
	     return parser.parse_expr(mVimin, attr_type, attr_loc);
	   });
  reg_func(AttrType::vimax,
	   [=](DotlibParser& parser,
	       AttrType attr_type,
	       const FileRegion& attr_loc) -> bool
	   {
	     return parser.parse_expr(mVimax, attr_type, attr_loc);
	   });
}

// @brief デストラクタ
InputVoltageHandler::~InputVoltageHandler()
{
}

// @breif 'input_voltage' Group Statement の記述をパースする．
// @param[in] dst 読み込んだ値を格納する変数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
InputVoltageHandler::parse_value(const AstInputVoltage*& dst)
{
  bool stat = parse_group_statement();
  if ( stat ) {
    dst = mValue;
  }
  return stat;
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

// @brief グループ記述の終わり
// @param[in] group_loc グループ全体のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
InputVoltageHandler::end_group(const FileRegion& group_loc)
{
  if ( !check_attr(mVil,   AttrType::vil, group_loc) ||
       !check_attr(mVih,   AttrType::vih, group_loc) ||
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
