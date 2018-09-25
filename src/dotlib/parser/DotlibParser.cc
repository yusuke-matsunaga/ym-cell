
/// @file DotlibParser.cc
/// @brief DotlibParser の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibParser.h"

#include "dotlib/SimpleHandler.h"
#include "dotlib/BoolHandler.h"
#include "dotlib/IntHandler.h"
#include "dotlib/FloatHandler.h"
#include "dotlib/StringHandler.h"
#include "dotlib/DelayModelHandler.h"
#include "dotlib/DirectionHandler.h"
#include "dotlib/TimingSenseHandler.h"
#include "dotlib/TimingTypeHandler.h"
#include "dotlib/VarTypeHandler.h"
#include "dotlib/FuncHandler.h"

#include "dotlib/Float2Handler.h"
#include "dotlib/FloatStrHandler.h"
#include "dotlib/FloatVectorHandler.h"
#include "dotlib/FloatVectorListHandler.h"
#include "dotlib/IntFloatHandler.h"
#include "dotlib/IntVectorHandler.h"
#include "dotlib/Str1Handler.h"
#include "dotlib/Str2Handler.h"
#include "dotlib/Str2IntHandler.h"
#include "dotlib/Str3Handler.h"
#include "dotlib/StrFloatHandler.h"
#include "dotlib/StrListHandler.h"

#include "dotlib/GroupHandler.h"
//#include "dotlib/CellHandler.h"
//#include "dotlib/DomainHandler.h"
//#include "dotlib/InputVoltageHandler.h"
//#include "dotlib/LibraryHandler.h"
//#include "dotlib/OutputVoltageHandler.h"
//#include "dotlib/PinHandler.h"
//#include "dotlib/TableHandler.h"
//#include "dotlib/TemplateHandler.h"
//#include "dotlib/TimingHandler.h"

#include "dotlib/AstMgr.h"
#include "dotlib/AstBool.h"
//#include "dotlib/AstCell.h"
#include "dotlib/AstDelayModel.h"
#include "dotlib/AstDirection.h"
//#include "dotlib/AstDomain.h"
#include "dotlib/AstExpr.h"
#include "dotlib/AstFloat.h"
#include "dotlib/AstFloat2.h"
#include "dotlib/AstFloatStr.h"
#include "dotlib/AstFloatVector.h"
//#include "dotlib/AstInputVoltage.h"
#include "dotlib/AstInt.h"
#include "dotlib/AstIntFloat.h"
#include "dotlib/AstIntVector.h"
//#include "dotlib/AstLibrary.h"
//#include "dotlib/AstLut.h"
//#include "dotlib/AstPin.h"
//#include "dotlib/AstOutputVoltage.h"
#include "dotlib/AstStr2.h"
#include "dotlib/AstStr3.h"
#include "dotlib/AstStrFloat.h"
#include "dotlib/AstString.h"
#include "dotlib/AstStrList.h"
#include "dotlib/AstTechnology.h"
//#include "dotlib/AstTemplate.h"
//#include "dotlib/AstTiming.h"
#include "dotlib/AstTimingSense.h"
#include "dotlib/AstTimingType.h"
#include "dotlib/AstVarType.h"

#include "dotlib/TokenType.h"
#include "ym/FileIDO.h"
#include "ym/MsgMgr.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief コンストラクタ
// @param[in] ido 入力データオブジェクト
// @param[in] mgr AstNode を管理するオブジェクト
// @param[in] debug デバッグモード
// @param[in] allow_no_semi 行末のセミコロンなしを許すかどうか
DotlibParser::DotlibParser(IDO& ido,
			   AstMgr& mgr,
			   bool debug,
			   bool allow_no_semi) :
  mScanner(ido),
  mAstMgr(mgr)
{
}

// デストラクタ
DotlibParser::~DotlibParser()
{
}

// @brief パーズする
// @return 読み込んだ AST を返す．
//
// エラーが起きたら nullptr を返す．
const AstLibrary*
DotlibParser::parse()
{
  // goto 文を使う関係で変数はここで宣言しておかなければならない．
  const AstLibrary* library = nullptr;
  TokenType type;
  FileRegion loc;
  bool stat = false;

  // 空行を読み飛ばす．
  for ( type = read_token(loc); type == TokenType::NL; type = read_token(loc) ) { }

  // 先頭のトークンが "library" であるかチェックする．
  if ( type != TokenType::SYMBOL || strcmp(cur_string(), "library") != 0 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "'library' keyword is expected "
		    "on the top of the structure");
    goto last;
  }

  stat = parse_library(library, AttrType::library, loc);
  if ( !stat ) {
    goto last;
  }

  if ( !expect_nl() ) {
    library = nullptr;
    goto last;
  }
  for ( ; ; ) {
    TokenType type = read_token(loc);
    if ( type == TokenType::END ) {
      break;
    }
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    MsgType::Warning,
		    "DOTLIB_PARSER",
		    "contents after library group are ignored.");
  }

 last:

  return library;
}

// @brief ブール値 のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_bool(const AstBool*& dst,
			 AttrType attr_type,
			 const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    BoolHandler handler(*this);
    bool stat = parse_simple_attribute(handler);
    if ( stat ) {
      dst = handler.value();
    }
    return stat;
  }
}

// @brief 整数値 のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_int(const AstInt*& dst,
			AttrType attr_type,
			const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    IntHandler handler(*this);
    bool stat = parse_simple_attribute(handler);
    if ( stat ) {
      dst = handler.value();
    }
    return stat;
  }
}

// @brief float 値のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_float(const AstFloat*& dst,
			  AttrType attr_type,
			  const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    FloatHandler handler(*this);
    bool stat = parse_simple_attribute(handler);
    if ( stat ) {
      dst = handler.value();
    }
    return stat;
  }
}

// @brief 文字列値のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_string(const AstString*& dst,
			   AttrType attr_type,
			   const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    StringHandler handler(*this);
    bool stat = parse_simple_attribute(handler);
    if ( stat ) {
      dst = handler.value();
    }
    return stat;
  }
}

// @brief 'delay_model' Simple Attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_delay_model(const AstDelayModel*& dst,
				AttrType attr_type,
				const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    DelayModelHandler handler(*this);
    bool stat = parse_simple_attribute(handler);
    if ( stat ) {
      dst = handler.value();
    }
    return stat;
  }
}

// @brief 'direction' Simple Attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_direction(const AstDirection*& dst,
			      AttrType attr_type,
			      const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    DirectionHandler handler(*this);
    bool stat = parse_simple_attribute(handler);
    if ( stat ) {
      dst = handler.value();
    }
    return stat;
  }
}

// @brief 'timing_sense' Simple Attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_timing_sense(const AstTimingSense*& dst,
				 AttrType attr_type,
				 const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    TimingSenseHandler handler(*this);
    bool stat = parse_simple_attribute(handler);
    if ( stat ) {
      dst = handler.value();
    }
    return stat;
  }
}

// @brief 'timing_type' Simple Attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_timing_type(const AstTimingType*& dst,
				AttrType attr_type,
				const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    TimingTypeHandler handler(*this);
    bool stat = parse_simple_attribute(handler);
    if ( stat ) {
      dst = handler.value();
    }
    return stat;
  }
}

// @brief 'var_type' Simple Attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_vartype(const AstVarType*& dst,
			    AttrType attr_type,
			    const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    VarTypeHandler handler(*this);
    bool stat = parse_simple_attribute(handler);
    if ( stat ) {
      dst = handler.value();
    }
    return stat;
  }
}

// @brief 式のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_expr(const AstExpr*& dst,
			 AttrType attr_type,
			 const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    // ちょっと例外的に DotlibParse 自ら処理する．
    if ( !expect(TokenType::COLON) ) {
      return false;
    }

    const AstExpr* value = read_expr(TokenType::SEMI);
    if ( value != nullptr ) {
      if ( expect_nl() ) {
	dst = value;
	return true;
      }
    }

    return false;
  }
}

// @brief 論理関数のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_function(const AstExpr*& dst,
			     AttrType attr_type,
			     const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    FuncHandler handler(*this);
    bool stat = parse_simple_attribute(handler);
    if ( stat ) {
      dst = handler.value();
    }
    return stat;
  }
}

// @brief coefs attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_coefs(const AstFloatVector*& dst,
			  AttrType attr_type,
			  const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    FloatVectorHandler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      dst = mgr().new_float_vector(handler.header_loc(), handler.value_list());
    }
    return stat;
  }
}

// @brief 'default_part' Complex attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_default_part(const AstStr2*& dst,
				 AttrType attr_type,
				 const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    Str2Handler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      dst = mgr().new_str2(handler);
    }
    return stat;
  }
}

// @brief 'define' Complex attribute のパースを行う．
// @param[in] dst_list 結果を格納するリスト
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
DotlibParser::parse_define(vector<const AstStr3*>& dst_list,
			   AttrType attr_type,
			   const FileRegion& attr_loc)
{
  Str3Handler handler(*this);
  bool stat = parse_complex_attribute(handler);
  if ( stat ) {
    dst_list.push_back(mgr().new_str3(handler));
  }
  return stat;
}

// @brief 'define_cell_area' Complex attribute のパースを行う．
// @param[in] dst_list 結果を格納するリスト
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
DotlibParser::parse_define_cell_area(vector<const AstStr2*>& dst_list,
				     AttrType attr_type,
				     const FileRegion& attr_loc)
{
  Str2Handler handler(*this);
  bool stat = parse_complex_attribute(handler);
  if ( stat ) {
    dst_list.push_back(mgr().new_str2(handler));
  }
  return stat;
}

// @brief 'define_group' Complex attribute のパースを行う．
// @param[in] dst_list 結果を格納するリスト
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
DotlibParser::parse_define_group(vector<const AstStr2*>& dst_list,
				 AttrType attr_type,
				 const FileRegion& attr_loc)
{
  Str2Handler handler(*this);
  bool stat = parse_complex_attribute(handler);
  if ( stat ) {
    dst_list.push_back(mgr().new_str2(handler));
  }
  return stat;
}

// @brief 'index' complex attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_index(const AstFloatVector*& dst,
			  AttrType attr_type,
			  const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    FloatVectorHandler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      dst = mgr().new_float_vector(handler.header_loc(), handler.value_list());
    }
    return stat;
  }
}

// @brief 'library_features' Complex attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_library_features(const AstString*& dst,
				     AttrType attr_type,
				     const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    Str1Handler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      dst = handler.value();
    }
    return stat;
  }
}

// @brief orders attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_orders(const AstIntVector*& dst,
			   AttrType attr_type,
			   const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    IntVectorHandler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      dst = handler.value();
    }
    return stat;
  }
}

// @brief 'piece_define' Complex attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_piece_define(const AstFloatVector*& dst,
				 AttrType attr_type,
				 const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    FloatVectorHandler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      dst = mgr().new_float_vector(handler.header_loc(), handler.value_list());
    }
    return stat;
  }
}

// @brief piecewise attribute のパースを行う．
// @param[in] dst_list 結果を格納するリスト
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// この属性は重複チェックは行わない．
bool
DotlibParser::parse_piecewise(vector<const AstIntFloat*>& dst_list,
			      AttrType attr_type,
			      const FileRegion& attr_loc)
{
  IntFloatHandler handler(*this);
  bool stat = parse_complex_attribute(handler);
  if ( stat ) {
    dst_list.push_back(mgr().new_int_float(handler));
  }
  return stat;
}

// @brief 'routing_layers' Complex attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_routing_layers(const AstStrList*& dst,
				   AttrType attr_type,
				   const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    StrListHandler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      dst = mgr().new_str_list(handler);
    }
    return stat;
  }
}

// @brief 'technology' Complex Attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_technology(const AstTechnology*& dst,
			       AttrType attr_type,
			       const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    Str1Handler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      // handler.value() から dst に値を設定する．
      ShString str = handler.value()->value();
      ClibTechnology tech = ClibTechnology::cmos;
      if ( strcmp(str, "cmos") == 0 ) {
	tech = ClibTechnology::cmos;
      }
      else if ( strcmp(str, "fpga") == 0 ) {
	tech = ClibTechnology::fpga;
      }
      else {
	ostringstream buf;
	buf << "Syntax error. Unexpected value: " << str << ".";
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr_loc,
			MsgType::Error,
			"DOTLIB_PARSER",
			buf.str());
	return false;
      }
      dst = mgr().new_technology(handler.header_loc(), tech);
    }
    return stat;
  }
}

// @brief 単位型 attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_unit(const AstFloatStr*& dst,
			 AttrType attr_type,
			 const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    FloatStrHandler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      dst = mgr().new_float_str(handler);
    }
    return stat;
  }
}

// @brief 'values' complex attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_values(const AstFloatVector*& dst,
			   AttrType attr_type,
			   const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    FloatVectorListHandler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      dst = mgr().new_float_vector(handler.header_loc(), handler.value_list());
    }
    return stat;
  }
}

// @brief variable_n_range attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_variable_range(const AstFloat2*& dst,
				   AttrType attr_type,
				   const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    Float2Handler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      dst = mgr().new_float2(handler);
    }
    return stat;
  }
}

// @brief 'voltage_map' Complex attribute のパースを行う．
// @param[in] dst_list 結果を格納するリスト
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// この属性は重複チェックは行わない．
bool
DotlibParser::parse_voltage_map(vector<const AstStrFloat*>& dst_list,
				AttrType attr_type,
				const FileRegion& attr_loc)
{
  StrFloatHandler handler(*this);
  bool stat = parse_complex_attribute(handler);
  if ( stat ) {
    dst_list.push_back(mgr().new_str_float(handler));
  }
  return stat;
}

#if 0
// @brief 'cell' Group Statement のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// この属性は重複チェックは行わない．
bool
DotlibParser::parse_cell(vector<const AstCell*>& dst_list,
			 AttrType attr_type,
			 const FileRegion& attr_loc)
{
  Str1Handler header_handler(*this);
  static CellHandler group_handler(*this);
  bool stat = parse_group_statement(header_handler, group_handler);
  if ( stat ) {
    const AstCell* value = mgr().new_cell(header_handler, group_handler);
    dst_list.push_back(value);
  }
  return stat;
}

// @brief 'domain' Group Statement のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_domain(const AstDomain*& dst,
			   AttrType attr_type,
			   const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    Str1Handler header_handler(*this);
    static DomainHandler group_handler(*this);
    bool stat = parse_group_statement(header_handler, group_handler);
    if ( stat ) {
      dst = mgr().new_domain(header_handler, group_handler);
    }
    return stat;
  }
}

// @brief 'ff' Group Statement のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_ff(const AstFF* dst,
		       AttrType attr_type,
		       const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    Str2Handler header_handler(*this);
    static FFHandler group_handler(*this);
    bool stat = parse_group_statement(header_handler, group_handler);
    if ( stat ) {
      dst = mgr().new_ff(header_handler, group_handler);
    }
    return stat;
  }
}

// @brief 'ff_bank' Group Statement のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_ff_bank(const AstFFBank* dst,
			    AttrType attr_type,
			    const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    Str2IntHandler header_handler(*this);
    static FFHandler group_handler(*this);
    bool stat = parse_group_statement(header_handler, group_handler);
    if ( stat ) {
      dst = mgr().new_ff_bank(header_handler, group_handler);
    }
    return stat;
  }
}

// @brief 'input_voltage' Group Statement のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_input_voltage(const AstInputVoltage*& dst,
				  AttrType attr_type,
				  const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    static InputVoltageHandler handler(*this);
    return handler.parse_value(dst);
  }
}

// @brief 'latch' Group Statement のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_latch(const AstLatch* dst,
		       AttrType attr_type,
		       const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    Str2Handler header_handler(*this);
    static LatchHandler group_handler(*this);
    bool stat = parse_group_statement(header_handler, group_handler);
    if ( stat ) {
      dst = mgr().new_latch(header_handler, group_handler);
    }
    return stat;
  }
}

// @brief 'latch_bank' Group Statement のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_latch_bank(const AstLatchBank* dst,
			    AttrType attr_type,
			    const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    Str2IntHandler header_handler(*this);
    static LatchHandler group_handler(*this);
    bool stat = parse_group_statement(header_handler, group_handler);
    if ( stat ) {
      dst = mgr().new_latch_bank(header_handler, group_handler);
    }
    return stat;
  }
}

// @brief 'Library' Group Statement のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_library(const AstLibrary*& dst,
			    AttrType attr_type,
			    const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    Str1Handler header_handler(*this);
    static LibraryHandler group_handler(*this);
    bool stat = parse_group_statement(header_handler, group_handler);
    if ( stat ) {
      dst = mgr().new_library(header_handler, group_handler);
    }
    return stat;
  }
}

// @brief 'OutputVoltage' Group Statement のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_output_voltage(const AstOutputVoltage*& dst,
				   AttrType attr_type,
				   const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    static OutputVoltageHandler handler(*this);
    return handler.parse_value(dst);
  }
}

// @brief 'pin' Group Statement のパースを行う．
// @param[in] dst_list 結果を格納するリスト
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// この属性は重複チェックは行わない．
bool
DotlibParser::parse_pin(vector<const AstPin*>& dst_list,
			AttrType attr_type,
			const FileRegion& attr_loc)
{
  StrListHandler header_handler(*this);
  static PinHandler group_handler(*this);
  bool stat = parse_group_statement(header_handler, group_handler);
  if ( stat ) {
    const AstPin* value = mgr().new_pin(header_handler, group_handler);
    dst_list.push_back(value);
  }
  return stat;
}

// @brief 'table' Group Statement のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_table(const AstLut*& dst,
			  AttrType attr_type,
			  const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    Str1Handler header_handler(*this);
    static TableHandler group_handler(*this);nnnnn
    bool stat = parse_group_statement(header_handler, group_handler);
    if ( stat ) {
      dst = mgr().new_lut(header_handler, group_handler);
    }
    return stat;
  }
}

// @brief 'lut_template' Group Statement のパースを行う．
// @param[in] dst_list 結果を格納するリスト
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// この属性は重複チェックは行わない．
bool
DotlibParser::parse_template(vector<const AstTemplate*>& dst_list,
			     AttrType attr_type,
			     const FileRegion& attr_loc)
{
  Str1Handler header_handler(*this);
  static TemplateHandler handler(*this);
  bool stat = parse_group_statement(header_handler, group_handler);
  if ( stat ) {
    const AstTemplate* value = mgr().new_template(header_handler, group_handler);
    dst_list.push_back(value);
  }
  return stat;
}

// @brief 'timing' Group Statement のパースを行う．
// @param[in] dst_list 結果を格納するリスト
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// この属性は重複チェックは行わない．
bool
DotlibParser::parse_timing(vector<const AstTiming*>& dst_list,
			   AttrType attr_type,
			   const FileRegion& attr_loc)
{
  StrListHandler header_handler(*this);
  static TimingHandler group_handler(*this);
  bool stat = parse_group_statement(header_handler, group_handler);
  if ( stat ) {
    const AstTiming* value = mgr().new_timing(header_handler, group_handler);
    dst_list.push_back(value);
  }
  return stat;
}
#endif

// @brief Simple Attribute を読み込む．
// @param[in] handler ハンドラ
// @retval true 正しく読み込めた．
// @retval false エラーが起こった．
bool
DotlibParser::parse_simple_attribute(SimpleHandler& handler)
{
  if ( !expect(TokenType::COLON) ) {
    return false;
  }

  FileRegion value_loc;
  TokenType value_type = read_token(value_loc, handler.symbol_mode());
  if ( !handler.read_value(value_type, value_loc) ) {
    return false;
  }

  if ( !expect_nl() ) {
    return false;
  }

  return true;
}

// @brief Complex Attribute を読み込む．
// @param[in] handler ヘッダ読み込みハンドラ (HeaderHandler の継承クラス)
// @retval true 正しく読み込めた．
// @retval false エラーが起こった．
bool
DotlibParser::parse_complex_attribute(HeaderHandler& handler)
{
  if ( !parse_header(handler) ) {
    return false;
  }

  return expect_nl();
}

// @brief Group Statement を読み込む．
// @param[in] header_handler ヘッダ読み込みハンドラ (HeaderHandler の継承クラス)
// @param[in] group_handler グループ読み込みハンドラ (GroupHandler の継承クラス)
// @retval true 正しく読み込めた．
// @retval false エラーが起こった．
bool
DotlibParser::parse_group_statement(HeaderHandler& header_handler,
				    GroupHandler& group_handler)
{
  if ( !parse_header(header_handler) ) {
    return false;
  }

  // グループ本体の始まり
  if ( !expect(TokenType::LCB) ) {
    return false;
  }

  // 仮想関数の呼び出し
  group_handler.begin_group();

  FileRegion first_loc = cur_loc();
  for ( ; ; ) {
    FileRegion loc;
    TokenType type = read_token(loc);
    if ( type == TokenType::NL ) {
      // 改行は読み飛ばす．
      continue;
    }
    if ( type == TokenType::RCB ) {
      // グループ本体の終わり．
      group_handler.mGroupLoc = FileRegion(first_loc, loc);
      if ( !group_handler.end_group() ) {
	return false;
      }

      if ( !expect(TokenType::NL) ) {
	return false;
      }

      return true;
    }
    if ( type != TokenType::SYMBOL ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "string value is expected.");
      return false;
    }
    // 一般のトークンの処理
    const char* name = cur_string();
    AttrType name_type = conv_to_attr(name);
    if ( name_type == AttrType::none ) {
      ostringstream buf;
      buf << name << ": syntax error.";
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      buf.str());
      return false;
    }
    bool r = group_handler.read_group_attr(name_type, loc);
    if ( !r ) {
      return false;
    }
  }
}

// @brief Complex Attribute, GroupStatement のヘッダを読み込む．
// @param[in] handler ハンドラ(CGHandler の継承クラス)
// @retval true 正しく読み込めた．
// @retval false エラーが起こった．
bool
DotlibParser::parse_header(HeaderHandler& handler)
{
  if ( !expect(TokenType::LP) ) {
    return false;
  }

  handler.begin_header();

  FileRegion first_loc = cur_loc();

  FileRegion loc;
  TokenType type = read_token(loc);
  int count = 0;
  if ( type != TokenType::RP ) {
    for ( ; ; ) {
      if ( !handler.read_header_value(type, loc, count) ) {
	return false;
      }
      ++ count;

      TokenType type1 = read_token(loc);
      if ( type1 == TokenType::RP ) {
	break;
      }
      if ( type1 != TokenType::COMMA ) {
	MsgMgr::put_msg(__FILE__, __LINE__,
			loc,
			MsgType::Error,
			"DOTLIB_PARSER",
			"syntax error. ',' is expected.");
	return false;
      }
      type = read_token(loc);
    }
  }

  handler.mHeaderLoc = FileRegion(first_loc, loc);
  if ( !handler.end_header(count) ) {
    return false;
  }

  return true;
}

// @brief 引数の種類のトークンでなければエラーメッセージを出力する．
bool
DotlibParser::expect(TokenType req_type)
{
  FileRegion loc;
  TokenType type = read_token(loc);
  if ( type == req_type ) {
    return true;
  }

  const char* type_str = nullptr;
  switch ( req_type ) {
  case TokenType::COLON:      type_str = "':'"; break;
  case TokenType::SEMI:       type_str = "';'"; break;
  case TokenType::COMMA:      type_str = "','"; break;
  case TokenType::PLUS:       type_str = "'+'"; break;
  case TokenType::MINUS:      type_str = "'-'"; break;
  case TokenType::MULT:       type_str = "'*'"; break;
  case TokenType::DIV:        type_str = "'/'"; break;
  case TokenType::NOT:        type_str = "'!'"; break;
  case TokenType::AND:        type_str = "'&'"; break;
  case TokenType::OR:         type_str = "'|'"; break;
  case TokenType::XOR:        type_str = "'^'"; break;
  case TokenType::PRIME:      type_str = "'"; break;
  case TokenType::LP:         type_str = "'('"; break;
  case TokenType::RP:         type_str = "')'"; break;
  case TokenType::LCB:        type_str = "'{'"; break;
  case TokenType::RCB:        type_str = "'}'"; break;
  case TokenType::SYMBOL:     type_str = "STR"; break;
  case TokenType::INT_NUM:    type_str = "INT"; break;
  case TokenType::FLOAT_NUM:  type_str = "FLOAT"; break;
  case TokenType::EXPRESSION: type_str = "EXPRESSION"; break;
  case TokenType::NL:         type_str = "new-line"; break;
  default:                    ASSERT_NOT_REACHED;
  }
  ostringstream buf;
  buf << "syntax error. " << type_str << " is expected.";
  MsgMgr::put_msg(__FILE__, __LINE__,
		  loc,
		  MsgType::Error,
		  "DOTLIB_PARSER",
		  buf.str());
  return false;
}

// @brief 行末まで読み込む．
bool
DotlibParser::expect_nl()
{
  if ( mAllowNoSemi ) {
    FileRegion loc;
    TokenType type = read_token(loc);
    if ( type == TokenType::SEMI ) {
      type = read_token(loc);
    }
    if ( type == TokenType::NL || type == TokenType::END ) {
      return true;
    }
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. Semicolon is expected.");
    return false;
  }
  else {
    if ( !expect(TokenType::SEMI) ) {
      return false;
    }
    if ( !expect(TokenType::NL) ) {
      return false;
    }
  }
  return true;
}

// @brief 直前の read_token() に対応する位置を返す．
FileRegion
DotlibParser::cur_loc() const
{
  return mCurLoc;
}

// @brief 文字列を属性値に変換する．
AttrType
DotlibParser::conv_to_attr(const char* str)
{
  return mAttrDic.get(str);
}

// @brief デバッグモードの時 true を返す．
bool
DotlibParser::debug()
{
  return mDebug;
}

// @brief primary を読み込む．
const AstExpr*
DotlibParser::read_primary()
{
  FileRegion loc;
  TokenType type = read_token(loc);
  if ( type == TokenType::LP ) {
    return read_expr(TokenType::RP);
  }
  if ( type == TokenType::SYMBOL ) {
    const char* name =  cur_string();
    if ( strcmp(name, "VDD") == 0 ) {
      return mgr().new_vdd_expr(loc);
    }
    else if ( strcmp(name, "VSS") == 0 ) {
      return mgr().new_vss_expr(loc);
    }
    else if ( strcmp(name, "VCC") == 0 ) {
      return mgr().new_vcc_expr(loc);
    }
    else {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error. "
		      "Only 'VDD', 'VSS', and 'VCC' are allowed.");
      return nullptr;
    }
  }
  if ( type == TokenType::FLOAT_NUM || type == TokenType::INT_NUM ) {
    double val = cur_float();
    return mgr().new_float_expr(loc, val);
  }

  MsgMgr::put_msg(__FILE__, __LINE__,
		  loc,
		  MsgType::Error,
		  "DOTLIB_PARSER",
		  "Syntax error. number is expected.");
  return nullptr;
}

// @brief prudct を読み込む．
const AstExpr*
DotlibParser::read_product()
{
  const AstExpr* opr1 = read_primary();
  if ( opr1 == nullptr ) {
    return nullptr;
  }

  for ( ; ; ) {
    FileRegion loc;
    TokenType type = read_token(loc);
    if ( type == TokenType::MULT || type == TokenType::DIV ) {
      const AstExpr* opr2 = read_primary();
      if ( opr2 == nullptr ) {
	return nullptr;
      }
      if ( type == TokenType::MULT ) {
	opr1 = mgr().new_mult(opr1, opr2);
      }
      else {
	opr1 = mgr().new_div(opr1, opr2);
      }
    }
    else {
      // token を戻す．
      mUngetType = type;
      mUngetLoc = loc;
      return opr1;
    }
  }
}

// @brief expression を読み込む．
const AstExpr*
DotlibParser::read_expr(TokenType end_marker)
{
  // ここだけ mUngetType, mUngetLoc を考慮する必要があるので
  // じかに read_token() を呼んではいけない．

  const AstExpr* opr1 = read_product();
  if ( opr1 == nullptr ) {
    return nullptr;
  }
  for ( ; ; ) {
    FileRegion loc;
    TokenType type = _read_token(loc);
    if ( type == end_marker ) {
      return opr1;
    }
    if ( type == TokenType::PLUS || type == TokenType::MINUS ) {
      const AstExpr* opr2 = read_product();
      if ( opr2 == nullptr ) {
	return nullptr;
      }
      if ( type == TokenType::PLUS ) {
	opr1 = mgr().new_plus(opr1, opr2);
      }
      else {
	opr1 = mgr().new_minus(opr1, opr2);
      }
    }
    else {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error.");
      return nullptr;
    }
  }
}

// @brief トークンを読み込む．
// @param[out] loc 対応するファイル上の位置情報を格納する変数
TokenType
DotlibParser::_read_token(FileRegion& loc)
{
  if ( mUngetType != TokenType::ERROR ) {
    TokenType ans = mUngetType;
    loc = mUngetLoc;
    mUngetType = TokenType::ERROR;
    return ans;
  }
  else {
    return read_token(loc);
  }
}


//////////////////////////////////////////////////////////////////////
// エラー出力用の便利関数
//////////////////////////////////////////////////////////////////////

// @brief 未対応の属性名に対するエラーメッセージを出力する．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
void
syntax_error(AttrType attr_type,
	     const FileRegion& attr_loc)
{
  ostringstream buf;
  buf << "Syntax error. Unexpected keyword: " << attr_type;
  MsgMgr::put_msg(__FILE__, __LINE__,
		  attr_loc,
		  MsgType::Error,
		  "DOTLIB_PARSER",
		  buf.str());
}

// @brief 同じ属性が重複して定義されている時のエラーを出力する．
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] prev_node 以前に定義されたノード
void
duplicate_error(AttrType attr_type,
		const FileRegion& attr_loc,
		const AstNode* prev_node)
{
  ostringstream buf;
  buf << attr_type << " appear more than once."
      << " Previously appears at " << prev_node->loc();
  MsgMgr::put_msg(__FILE__, __LINE__,
		    attr_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    buf.str());
}


//////////////////////////////////////////////////////////////////////
// TokenType に関する関数
//////////////////////////////////////////////////////////////////////

// @brief TokenType 内容をストリームに出力する．
ostream&
operator<<(ostream& s,
	   TokenType type)
{
  const char* type_str = nullptr;
  switch ( type ) {
  case TokenType::COLON:      type_str = "':'"; break;
  case TokenType::SEMI:       type_str = "';'"; break;
  case TokenType::COMMA:      type_str = "','"; break;
  case TokenType::PLUS:       type_str = "'+'"; break;
  case TokenType::MINUS:      type_str = "'-'"; break;
  case TokenType::MULT:       type_str = "'*'"; break;
  case TokenType::DIV:        type_str = "'/'"; break;
  case TokenType::LP:         type_str = "'('"; break;
  case TokenType::RP:         type_str = "')'"; break;
  case TokenType::LCB:        type_str = "'{'"; break;
  case TokenType::RCB:        type_str = "'}'"; break;
  case TokenType::INT_NUM:    type_str = "INT"; break;
  case TokenType::FLOAT_NUM:  type_str = "FLOAT"; break;
  case TokenType::SYMBOL:     type_str = "SYMBOL"; break;
  case TokenType::EXPRESSION: type_str = "EXPRESSION"; break;
  case TokenType::NL:         type_str = "new-line"; break;
  case TokenType::ERROR :     type_str = "error"; break;
  case TokenType::END:        type_str = "end-of-file"; break;
  default:
    ASSERT_NOT_REACHED;
  }
  s << type_str;
  return s;
}

END_NAMESPACE_YM_DOTLIB
