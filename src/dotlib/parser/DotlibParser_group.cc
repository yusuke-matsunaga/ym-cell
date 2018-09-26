
/// @file DotlibParser.cc
/// @brief DotlibParser の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibParser.h"
#include "FuncParser.h"

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
    StrHandler header_handler(*this);
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
    StrStrHandler header_handler(*this);
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
    StrStrIntHandler header_handler(*this);
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
    StrStrHandler header_handler(*this);
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
    StrStrIntHandler header_handler(*this);
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
    StrHandler header_handler(*this);
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
    StrHandler header_handler(*this);
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
  StrHandler header_handler(*this);
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

END_NAMESPACE_YM_DOTLIB
