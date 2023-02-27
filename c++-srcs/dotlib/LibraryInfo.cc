
/// @file LibraryInfo.cc
/// @brief LibraryInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/Parser.h"
#include "dotlib/AstAttr.h"
#include "dotlib/LibraryInfo.h"
#include "dotlib/AstValue.h"
#include "dotlib/LuTemplInfo.h"
#include "dotlib/CellInfo.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス LibraryInfo
//////////////////////////////////////////////////////////////////////

// @brief 内容を設定する．
bool
LibraryInfo::set(
  const AstValue& lib_val
)
{
  { // ライブラリ名の設定
    auto& header_val = lib_val.group_header_value();
    mLibrary->set_name(header_val.string_value());
  }

  bool ok{true};

  // 属性の設定

  // 属性名をキーにした辞書を作る．
  // おなじ属性名の要素が複数ある場合もあるので値は vector<const AstValue*>
  // となる．
  mElemDict.set(&lib_val);

  { // 'technology' の設定
    ClibTechnology technology;
    switch ( mElemDict.get_technology("technology", technology) ) {
    case ElemDict::OK:
      mLibrary->set_technology(technology);
      break;
    case ElemDict::NOT_FOUND:
      // デフォルト値
      mLibrary->set_technology(ClibTechnology::cmos);
      break;
    case ElemDict::ERROR:
#warning "TODO: エラーメッセージ"
      ok = false;
      break;
    }
  }

  { // 'delay_model' の設定
    ClibDelayModel delay_model;
    switch ( mElemDict.get_delay_model("delay_model", delay_model) ) {
    case ElemDict::OK:
      mLibrary->set_delay_model(delay_model);
      break;
    case ElemDict::NOT_FOUND:
      break;
    case ElemDict::ERROR:
#warning "TODO: エラーメッセージ"
      ok = false;
    }
  }

  // 'bus_naming_style' の設定
  if ( !set_str_attr("bus_naming_style") ) {
    ok = false;
  }

  // 'comment' の設定
  if ( !set_str_attr("comment") ) {
    ok = false;
  }

  // 'date' の設定
  if ( !set_str_attr("date") ) {
    ok = false;
  }

  // 'revision' の設定
  if ( !set_str_attr("revision") ) {
    ok = false;
  }

  // 'time_unit' の設定
  if ( !set_str_attr("time_unit") ) {
    ok = false;
  }

  // 'voltage_unit' の設定
  if ( !set_str_attr("voltage_unit") ) {
    ok = false;
  }

  // 'current_unit' の設定
  if ( !set_str_attr("current_unit") ) {
    ok = false;
  }

  // 'pulling_resistance_unit' の設定
  if ( !set_str_attr("pulling_resistance_unit") ) {
    ok = false;
  }

  // 'capacitive_load_unit' の設定
  if ( !set_capacitive_load_unit() ) {
    ok = false;
  }

  // 'leakage_power_unit' の設定
  if ( !set_str_attr("leakage_power_unit") ) {
    ok = false;
  }

  // lu_table_template の設定
  if ( mElemDict.count("lu_table_template") > 0 ) {
    auto& vec = mElemDict.at("lu_table_template");
    for ( auto ast_templ: vec ) {
      LuTemplInfo info{mLibrary};
      if ( info.set(ast_templ) ) {
	auto tid = info.add_lu_template();
	mLutDict.emplace(info.name(), tid);
      }
      else {
	ok = false;
      }
    }
  }

  // セルの内容の設定
  if ( mElemDict.count("cell") > 0 ) {
    auto& v = mElemDict.at("cell");
    for ( auto ast_cell: v ) {
      CellInfo cell_info{*this};
      if ( cell_info.set(ast_cell) ) {
	cell_info.add_cell();
      }
      else {
	ok = false;
      }
    }
  }

  if ( ok ) {
    mLibrary->compile();
  }

  return ok;
}

// 文字列型の属性をセットする．
bool
LibraryInfo::set_str_attr(
  const char* keyword
)
{
  bool ok = true;
  ShString tmp_str;
  switch ( mElemDict.get_string(keyword, tmp_str) ) {
  case ElemDict::OK:
    mLibrary->set_attr(keyword, tmp_str);
    break;

  case ElemDict::NOT_FOUND:
    // 無視
    break;

  case ElemDict::ERROR:
    ok = false;
    break;
  }

  return ok;
}

// @brief capacitive_load_unit の属性をセットする．
bool
LibraryInfo::set_capacitive_load_unit()
{
  const char* keyword{"capacitive_load_unit"};
  const AstValue* val;
  bool ok = true;
  switch ( mElemDict.get_value(keyword, val) ) {
  case ElemDict::OK:
    {
      ASSERT_COND( val->complex_elem_size() == 2 );
      auto u = val->complex_elem_value(0).float_value();
      auto ustr = val->complex_elem_value(1).string_value();
      mLibrary->set_capacitive_load_unit(u, ustr);
    }
    break;

  case ElemDict::NOT_FOUND:
    break;

  case ElemDict::ERROR:
    ok = false;
    break;
  }
  return ok;
}

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

  LibraryInfo lib_info{lib_ptr.get()};

  // AstValue の内容をライブラリに設定する．
  lib_info.set(ast_library->value());

  auto lib = lib_ptr.get();
  lib_ptr.release();
  return lib;
}

END_NAMESPACE_YM_CLIB
