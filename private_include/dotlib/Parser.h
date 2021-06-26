#ifndef PARSER_H
#define PARSER_H

/// @file Parser.h
/// @brief Parser のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"
#include "dotlib/AttrKwd.h"
#include "dotlib/HeaderHandler.h"
#include "dotlib/Scanner.h"
#include "dotlib/TokenType.h"

#include "ym/FileRegion.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class Parser Parser.h "dotlib/Parser.h"
/// @brief Parser の実装クラス
//////////////////////////////////////////////////////////////////////
class Parser
{
public:

  /// @brief コンストラクタ
  Parser(InputFileObj& in,           ///< [in] 入力ファイルオブジェクト
	 bool debug,                 ///< [in] デバッグモード
	 bool allow_no_semi = true); ///< [in] 行末のセミコロンなしを許すかどうか

  /// @brief デストラクタ
  ~Parser();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief パーズする
  /// @return 読み込んだ library のASTを返す．
  ///
  /// エラーが起きたら nullptr を返す．
  AstAttrPtr
  parse();


public:
  //////////////////////////////////////////////////////////////////////
  // ハンドラ関数から使われる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief Simple Attribute を読み込む．
  /// @retrun 結果の AstAttr を返す．
  ///
  /// エラーが起こったら nullptr を返す．
  AstAttrPtr
  parse_simple_attribute(const AttrKwd& attr,    ///< [in] 属性の型
			 SimpleHandler handler); ///< [in] simple 属性ハンドラ

  /// @brief Complex Attribute を読み込む．
  /// @retrun 結果の AstAttr を返す．
  ///
  /// エラーが起こったら nullptr を返す．
  AstAttrPtr
  parse_complex_attribute(const AttrKwd& attr,     ///< [in] 属性の型
			  HeaderHandler& handler); ///< [in] ヘッダ読み込みハンドラ

  /// @brief Group Statement を読み込む．
  /// @retrun 結果の AstAttr を返す．
  ///
  /// エラーが起こったら nullptr を返す．
  AstAttrPtr
  parse_group_statement(const AttrKwd& attr,            ///< [in] 属性の型
			const char* group_name,         ///< [in] 親のグループ名
			HeaderHandler& header_handler); ///< [in] ヘッダ読み込みハンドラ

  /// @brief デバッグモードの時 true を返す．
  bool
  debug();


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる下請け関数
  //////////////////////////////////////////////////////////////////////

  /// @brief Complex Attribute, GroupStatement のヘッダを読み込む．
  /// @retrun 結果の AstAttr を返す．
  ///
  /// エラーが起こったら nullptr を返す．
  AstValuePtr
  parse_header(HeaderHandler& handler); ///< [in] ハンドラ(HeaderHandler の継承クラス)

  /// @brief 行末まで読み込む．
  ///
  /// 具体的には ';' '/n' を確認する．
  /// ただし， mAllowNoSemi が true の場合には
  /// ';' を無視する．
  bool
  read_tail();


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 字句解析器
  Scanner mScanner;

  // デバッグモード
  bool mDebug;

  // 行末のセミコロンなしを許すかどうかのフラグ
  bool mAllowNoSemi;


public:

  // complex attribute/group statement header 用のハンドラ
  static FixedElemHeader sEmptyHeader;
  static FixedElemHeader sFloatFloatHeader;
  static FixedElemHeader sFloatFloatStrHeader;
  static FixedElemHeader sFloatStrHeader;
  static FixedElemHeader sFloatVectorHeader;
  static FixedElemHeader sIntFloatHeader;
  static FixedElemHeader sIntFloatVectorHeader;
  static FixedElemHeader sIntStrHeader;
  static FixedElemHeader sIntVectorHeader;
  static FixedElemHeader sStrFloatHeader;
  static FixedElemHeader sStrHeader;
  static FixedElemHeader sStrIntHeader;
  static FixedElemHeader sStrStrHeader;
  static FixedElemHeader sStrStrIntHeader;
  static FixedElemHeader sStrStrStrHeader;
  static FanoutLengthHeader sFanoutLengthHeader;
  static FixedElemHeader sTechnologyHeader;
  static ListHeader sFloatVectorListHeader;
  static ListHeader sIntListHeader;
  static ListHeader sStrListHeader;

  // グループハンドラの辞書
  static unordered_map<string, AttrHandler> sHandlerDict;

};


//////////////////////////////////////////////////////////////////////
/// @{
/// @name simple attribute を読み込む関数
//////////////////////////////////////////////////////////////////////

/// @brief 整数値型の simple attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
simple_int(Parser& parser,      ///< [in] パーサー
	   const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_simple_attribute(attr, read_int);
}

/// @brief float 値型の simple attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
simple_float(Parser& parser,      ///< [in] パーサー
	     const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_simple_attribute(attr, read_float);
}

/// @brief 文字列値の simple attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
simple_string(Parser& parser,      ///< [in] パーサー
	      const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_simple_attribute(attr, read_string);
}

/// @brief ブール値型の simple attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
simple_bool(Parser& parser,      ///< [in] パーサー
	    const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_simple_attribute(attr, read_bool);
}

/// @brief 'delay_model' Simple Attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
simple_delay_model(Parser& parser,      ///< [in] パーサー
		   const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_simple_attribute(attr, read_delay_model);
}

/// @brief 'direction' Simple Attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
simple_direction(Parser& parser,      ///< [in] パーサー
		 const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_simple_attribute(attr, read_direction);
}

/// @brief 式型の simple attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
simple_expr(Parser& parser,      ///< [in] パーサー
	    const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_simple_attribute(attr, read_expr);
}

/// @brief "式" 型の simple attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
simple_function(Parser& parser,      ///< [in] パーサー
		const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_simple_attribute(attr, read_function);
}

/// @brief 'timing_sense' Simple Attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
simple_timing_sense(Parser& parser,      ///< [in] パーサー
		    const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_simple_attribute(attr, read_timing_sense);
}

/// @brief 'timing_type' Simple Attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
simple_timing_type(Parser& parser,      ///< [in] パーサー
		   const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_simple_attribute(attr, read_timing_type);
}

/// @brief 'var_type' Simple Attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
simple_vartype(Parser& parser,      ///< [in] パーサー
	       const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_simple_attribute(attr, read_vartype);
}

//////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
/// @{
/// @name complex attribute を読み込む関数
//////////////////////////////////////////////////////////////////////

/// @brief ( float, float ) の形式の Complex attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
complex_float_float(Parser& parser,      ///< [in] パーサー
		    const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sFloatFloatHeader);
}

/// @brief ( float, float, string ) の形式の Complex attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
complex_float_float_string(Parser& parser,      ///< [in] パーサー
			   const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sFloatFloatStrHeader);
}

/// @brief ( float, string ) 型の Complex attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
complex_float_string(Parser& parser,      ///< [in] パーサー
		     const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sFloatStrHeader);
}

/// @brief ( "float, float, ... " ) の形式の Complex attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
complex_float_vector(Parser& parser,      ///< [in] パーサー
		     const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sFloatVectorHeader);
}

/// @brief ( integer, float ) の形式の Complex attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
complex_int_float(Parser& parser,      ///< [in] パーサー
		  const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sIntFloatHeader);
}

/// @brief ( integer, string ) の形式の Complex attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
complex_int_string(Parser& parser,      ///< [in] パーサー
		   const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sIntStrHeader);
}

/// @brief ( integer, "float, float, ... " ) の形式の Complex attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
complex_int_float_vector(Parser& parser,      ///< [in] パーサー
			 const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sIntFloatVectorHeader);
}

/// @brief ( integer, integer, ...  ) の形式の Complex attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
complex_int_list(Parser& parser,      ///< [in] パーサー
		 const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sIntListHeader);
}

/// @brief ( "integer, integer, ... " ) の形式の Complex attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
complex_int_vector(Parser& parser,      ///< [in] パーサー
		   const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sIntVectorHeader);
}

/// @brief ( string ) 型の Complex attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
complex_string(Parser& parser,      ///< [in] パーサー
	       const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sStrHeader);
}

/// @brief ( string, float ) の形式の Complex attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
complex_string_float(Parser& parser,      ///< [in] パーサー
		     const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sStrFloatHeader);
}

/// @brief ( string, integer ) の形式の Complex attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
complex_string_int(Parser& parser,      ///< [in] パーサー
		   const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sStrIntHeader);
}

/// @brief ( string, string, ... ) の形式の Complex attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
complex_string_list(Parser& parser,      ///< [in] パーサー
		    const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sStrListHeader);
}

/// @brief ( string, string ) の形式の Complex attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
complex_string_string(Parser& parser,      ///< [in] パーサー
		      const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sStrStrHeader);
}

/// @brief ( string, string, string ) の形式の Complex attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
complex_string_string_string(Parser& parser,      ///< [in] パーサー
			     const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sStrStrStrHeader);
}

/// @brief 'fanout_length' Complex Attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
complex_fanout_length(Parser& parser,      ///< [in] パーサー
		      const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sFanoutLengthHeader);
}

/// @brief 'Technology' Complex Attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
complex_technology(Parser& parser,      ///< [in] パーサー
		   const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sTechnologyHeader);
}

/// @brief 'values' Complex attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
complex_values(Parser& parser,      ///< [in] パーサー
	       const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sFloatVectorListHeader);
}

//////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
/// @{
/// @name group statement を読み込む関数
//////////////////////////////////////////////////////////////////////

/// @brief () タイプの group statment のパースを行なう．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
group_empty(Parser& parser,         ///< [in] パーサー
	    const AttrKwd& attr,    ///< [in] 属性の型
	    const char* group_name) ///< [in] 親のグループ名
{
  return parser.parse_group_statement(attr, group_name, Parser::sEmptyHeader);
}

/// @brief ( string ) タイプの group statment のパースを行なう．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
group_string(Parser& parser,         ///< [in] パーサー
	     const AttrKwd& attr,    ///< [in] 属性の型
	     const char* group_name) ///< [in] 親のグループ名
{
  return parser.parse_group_statement(attr, group_name, Parser::sStrHeader);
}

/// @brief ( string, string ) タイプの group statment のパースを行なう．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
group_string_string(Parser& parser,         ///< [in] パーサー
		    const AttrKwd& attr,    ///< [in] 属性の型
		    const char* group_name) ///< [in] 親のグループ名
{
  return parser.parse_group_statement(attr, group_name, Parser::sStrStrHeader);
}

/// @brief ( string, string, int ) タイプの group statment のパースを行なう．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
group_string_string_int(Parser& parser,         ///< [in] パーサー
			const AttrKwd& attr,    ///< [in] 属性の型
			const char* group_name) ///< [in] 親のグループ名
{
  return parser.parse_group_statement(attr, group_name, Parser::sStrStrIntHeader);
}

//////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////

END_NAMESPACE_YM_DOTLIB

#endif // PARSER_H
