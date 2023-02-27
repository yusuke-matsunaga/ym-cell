
/// @file read_liberty.cc
/// @brief read_liberty の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 201, 2022, 2023 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"

#include "ci/CiCellLibrary.h"
#include "ci/CiCell.h"
#include "ci/CiTiming.h"
#include "ci/CiLutTemplate.h"

#include "ym/ClibPin.h"
#include "ym/ClibTiming.h"
#include "ym/ClibArea.h"
#include "ym/ClibResistance.h"
#include "ym/ClibCapacitance.h"
#include "ym/ClibTime.h"
#include "ym/ClibLut.h"

#include "dotlib/Parser.h"
#include "dotlib/AstAttr.h"
#include "dotlib/AstExpr.h"
#include "dotlib/AstElemDict.h"
#include "dotlib/LuTemplInfo.h"
#include "dotlib/CellInfo.h"

#include "ym/Expr.h"
#include "ym/TvFunc.h"
#include "ym/MsgMgr.h"
#include "ym/Range.h"
#include "ym/split.h"


BEGIN_NAMESPACE_YM_DOTLIB

BEGIN_NONAMESPACE

bool debug = true;


// @brief AstValue から CiCellLibrary を生成する．
bool
set_library(
  const AstValue& library_val,
  unique_ptr<CiCellLibrary>& library
)
{
  { // ライブラリ名の設定
    auto& header_val = library_val.group_header_value();
    library->set_name(header_val.string_value());
  }

  bool ok{true};

  // 属性の設定

  // 属性名をキーにした辞書を作る．
  // おなじ属性名の要素が複数ある場合もあるので値は vector<const AstValue*>
  // となる．
  auto elem_dict = library_val.gen_group_elem_dict();

  // 'technology' の設定
  {
    ClibTechnology technology;
    switch ( elem_dict.get_technology("technology", technology) ) {
    case AstElemDict::OK:
      library->set_technology(technology);
      break;
    case AstElemDict::NOT_FOUND:
      // デフォルト値
      library->set_technology(ClibTechnology::cmos);
      break;
    case AstElemDict::ERROR:
#warning "TODO: エラーメッセージ"
      ok = false;
      break;
    }
  }

  { // 'delay_model' の設定
    ClibDelayModel delay_model;
    switch ( elem_dict.get_delay_model("delay_model", delay_model) ) {
    case AstElemDict::OK:
      library->set_delay_model(delay_model);
      break;
    case AstElemDict::NOT_FOUND:
      break;
    case AstElemDict::ERROR:
#warning "TODO: エラーメッセージ"
      ok = false;
    }
  }

  { // 'bus_naming_style' の設定
    const char* keyword{"bus_naming_style"};
    ShString tmp_str;
    switch ( elem_dict.get_string(keyword, tmp_str) ) {
    case AstElemDict::OK:
      library->set_attr(keyword, tmp_str);
      break;
    case AstElemDict::NOT_FOUND:
      break;
    case AstElemDict::ERROR:
      ok = false;
      break;
    }
  }

  { // 'comment' の設定
    const char* keyword{"comment"};
    ShString tmp_str;
    switch ( elem_dict.get_string(keyword, tmp_str) ) {
    case AstElemDict::OK:
      library->set_attr(keyword, tmp_str);
      break;
    case AstElemDict::NOT_FOUND:
      break;
    case AstElemDict::ERROR:
      ok = false;
      break;
    }
  }

  { // 'date' の設定
    const char* keyword{"date"};
    ShString tmp_str;
    switch ( elem_dict.get_string(keyword, tmp_str) ) {
    case AstElemDict::OK:
      library->set_attr(keyword, tmp_str);
      break;
    case AstElemDict::NOT_FOUND:
      break;
    case AstElemDict::ERROR:
      ok = false;
      break;
    }
  }

  { // 'revision' の設定
    const char* keyword{"revision"};
    ShString tmp_str;
    switch ( elem_dict.get_string(keyword, tmp_str) ) {
    case AstElemDict::OK:
      library->set_attr(keyword, tmp_str);
      break;
    case AstElemDict::NOT_FOUND:
      break;
    case AstElemDict::ERROR:
      ok = false;
      break;
    }
  }

  { // 'time_unit' の設定
    const char* keyword{"time_unit"};
    ShString tmp_str;
    switch ( elem_dict.get_string(keyword, tmp_str) ) {
    case AstElemDict::OK:
      library->set_attr(keyword, tmp_str);
      break;
    case AstElemDict::NOT_FOUND:
      break;
    case AstElemDict::ERROR:
      ok = false;
      break;
    }
  }

  { // 'voltage_unit' の設定
    const char* keyword{"voltage_unit"};
    ShString tmp_str;
    switch ( elem_dict.get_string(keyword, tmp_str) ) {
    case AstElemDict::OK:
      library->set_attr(keyword, tmp_str);
      break;
    case AstElemDict::NOT_FOUND:
      break;
    case AstElemDict::ERROR:
      ok = false;
      break;
    }
  }

  { // 'current_unit' の設定
    const char* keyword{"current_unit"};
    ShString tmp_str;
    switch ( elem_dict.get_string(keyword, tmp_str) ) {
    case AstElemDict::OK:
      library->set_attr(keyword, tmp_str);
      break;
    case AstElemDict::NOT_FOUND:
      break;
    case AstElemDict::ERROR:
      ok = false;
      break;
    }
  }

  { // 'pulling_resistance_unit' の設定
    const char* keyword{"pulling_resistance_unit"};
    ShString tmp_str;
    switch ( elem_dict.get_string(keyword, tmp_str) ) {
    case AstElemDict::OK:
      library->set_attr(keyword, tmp_str);
      break;
    case AstElemDict::NOT_FOUND:
      break;
    case AstElemDict::ERROR:
      ok = false;
      break;
    }
  }

  { // 'capacitive_load_unit' の設定
    const char* keyword{"capacitive_load_unit"};
    const AstValue* val;
    switch ( elem_dict.get_value(keyword, val) ) {
    case AstElemDict::OK:
      {
	ASSERT_COND( val->complex_elem_size() == 2 );
	auto u = val->complex_elem_value(0).float_value();
	auto ustr = val->complex_elem_value(1).string_value();
	library->set_capacitive_load_unit(u, ustr);
      }
      break;
    case AstElemDict::NOT_FOUND:
      break;
    case AstElemDict::ERROR:
      ok = false;
      break;
    }
  }

  { // 'leakage_power_unit' の設定
    const char* keyword{"leakage_power_unit"};
    ShString tmp_str;
    switch ( elem_dict.get_string(keyword, tmp_str) ) {
    case AstElemDict::OK:
      library->set_attr(keyword, tmp_str);
      break;
    case AstElemDict::NOT_FOUND:
      break;
    case AstElemDict::ERROR:
      ok = false;
      break;
    }
  }

  // lu_table_template の設定
  if ( elem_dict.count("lu_table_template") > 0 ) {
    auto& vec = elem_dict.at("lu_table_template");
    for ( auto ast_templ: vec ) {
      LuTemplInfo info;
      if ( info.set(ast_templ) ) {
	info.add_lu_template(library);
      }
    }
  }

  // セルの内容の設定
  if ( elem_dict.count("cell") > 0 ) {
    auto& v = elem_dict.at("cell");
    for ( auto ast_cell: v ) {
      CellInfo cell_info{library.get()};
      if ( cell_info.set(ast_cell) ) {
	cell_info.add_cell();
      }
    }
  }

  library->compile();

  return true;
}

END_NONAMESPACE

END_NAMESPACE_YM_DOTLIB


BEGIN_NAMESPACE_YM_CLIB

// @brief liberty 形式のファイルを読み込んでライブラリに設定する．
CiCellLibrary*
CiCellLibrary::read_liberty(
  const string& filename
)
{
  using namespace nsDotlib;

  // ファイルを開く
  ifstream fin{filename};
  if ( !fin ) {
    ostringstream buf;
    buf << filename << ": Could not open.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    FileRegion(),
		    MsgType::Failure,
		    "DOTLIB_PARSER",
		    buf.str());
    // ファイルが開けなかった．
    throw std::invalid_argument{buf.str()};
  }

  // 読み込んでASTを作る．
  Parser parser{fin, {filename}, false};
  auto ast_library = parser.parse();

  ASSERT_COND( ast_library->kwd() == "library" );

  unique_ptr<CiCellLibrary> lib_ptr{new CiCellLibrary{}};

  // AstValue の内容をライブラリに設定する．
  set_library(ast_library->value(), lib_ptr);

  auto lib = lib_ptr.get();
  lib_ptr.release();
  return lib;
}

END_NAMESPACE_YM_CLIB
