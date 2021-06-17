
/// @file LibraryHandler.cc
/// @brief LibraryHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/LibraryHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス LibraryHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
LibraryHandler::LibraryHandler(DotlibParser& parser) :
  GroupHandler(parser)
{
  // パース関数の登録
  reg_func(AttrType::technology,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_technology(mTechnology, attr_type, attr_loc); });
  reg_func(AttrType::delay_model,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.set_delay_model(mDelayModel, attr_type, attr_loc); });
  reg_func(AttrType::bus_naming_style,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.add_string(mStrList, attr_type, attr_loc); });
  reg_func(AttrType::comment,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.add_string(mStrList, attr_type, attr_loc); });
  reg_func(AttrType::date,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.add_string(mStrList, attr_type, attr_loc); });
  reg_func(AttrType::revision,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.add_string(mStrList, attr_type, attr_loc); });
  reg_func(AttrType::capacitive_load_unit,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float_string(mCapacitiveLoadUnit, attr_type, attr_loc); });
  reg_func(AttrType::current_unit,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.add_string(mStrList, attr_type, attr_loc); });
  reg_func(AttrType::leakage_power_unit,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.add_string(mStrList, attr_type, attr_loc); });
  reg_func(AttrType::pulling_resistance_unit,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.add_string(mStrList, attr_type, attr_loc); });
  reg_func(AttrType::time_unit,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.add_string(mStrList, attr_type, attr_loc); });
  reg_func(AttrType::voltage_unit,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.add_string(mStrList, attr_type, attr_loc); });
  reg_func(AttrType::lu_table_template,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_template(mLutTemplateList, attr_type, attr_loc); });
  reg_func(AttrType::cell,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_cell(mCellList, attr_type, attr_loc); });

}

// @brief デストラクタ
LibraryHandler::~LibraryHandler()
{
}

// @brief グループ記述の始まり
void
LibraryHandler::begin_group()
{
  mStrList.clear();

  mTechnology = nullptr;
  mDelayModel = nullptr;
  mCapacitiveLoadUnit = nullptr;
  mLutTemplateList.clear();
  mCellList.clear();
}

// @brief グループ記述の終わり
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
LibraryHandler::end_group()
{
  return false;
}

END_NAMESPACE_YM_DOTLIB
