#ifndef PARSE_SIMPLE_H
#define PARSE_SIMPLE_H

/// @file parse_simple.h
/// @brief simple attribute 用のパース関数のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"
#include "dotlib/Parser.h"


BEGIN_NAMESPACE_YM_DOTLIB


//////////////////////////////////////////////////////////////////////
/// @{
/// @name 値(AstValue) を読み込む関数
//////////////////////////////////////////////////////////////////////

/// @brief int 型を値を読み込む．
/// @return 生成した AstValue を返す．
///
/// エラーの時は nullptr を返す．
inline
AstValuePtr
read_int(Scanner& scanner) { return scanner.read_int(); }

/// @brief float 型の値を読み込む．
/// @return 生成した AstValue を返す．
///
/// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
inline
AstValuePtr
read_float(Scanner& scanner) { return scanner.read_float(); }

/// @brief string 型の値を読み込む．
/// @return 生成した AstValue を返す．
///
/// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
inline
AstValuePtr
read_string(Scanner& scanner) { return scanner.read_string(); }

/// @brief bool 型の値を読み込む．
/// @return 生成した AstValue を返す．
///
/// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
inline
AstValuePtr
read_bool(Scanner& scanner) { return scanner.read_bool(); }

/// @brief delay_model 型の値を読み込む．
/// @param[in] 生成した AstValue を返す．
///
/// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
inline
AstValuePtr
read_delay_model(Scanner& scanner) { return scanner.read_delay_model(); }

/// @brief direction 型の値を読み込む．
/// @param[in] 生成した AstValue を返す．
///
/// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
inline
AstValuePtr
read_direction(Scanner& scanner) { return scanner.read_direction(); }

/// @brief technology 型の値を読み込む．
/// @param[in] 生成した AstValue を返す．
///
/// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
inline
AstValuePtr
read_technology(Scanner& scanner) { return scanner.read_technology(); }

/// @brief timing_sense 型の値を読み込む．
/// @param[in] 生成した AstValue を返す．
///
/// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
inline
AstValuePtr
read_timing_sense(Scanner& scanner) { return scanner.read_timing_sense(); }

/// @brief timing_type 型の値を読み込む．
/// @param[in] 生成した AstValue を返す．
///
/// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
inline
AstValuePtr
read_timing_type(Scanner& scanner) { return scanner.read_timing_type(); }

/// @brief vartype 型の値を読み込む．
/// @param[in] 生成した AstValue を返す．
///
/// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
inline
AstValuePtr
read_vartype(Scanner& scanner) { return scanner.read_vartype(); }

/// @brief int vector 型の値を読み込む．
/// @return 生成した AstValue を返す．
///
/// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
inline
AstValuePtr
read_int_vector(Scanner& scanner) { return scanner.read_int_vector(); }

/// @brief float vector 型の値を読み込む．
/// @return 生成した AstValue を返す．
///
/// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
inline
AstValuePtr
read_float_vector(Scanner& scanner) { return scanner.read_float_vector(); }

/// @brief 式を表す AstValue を生成する．
/// @return 生成した AstValue を返す．
///
/// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
inline
AstValuePtr
read_expr(Scanner& scanner) { return scanner.read_expr(); }

/// @brief "式" を表す AstValue を生成する．
inline
AstValuePtr
read_function(Scanner& scanner) { return scanner.read_function(); }

//////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////

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

END_NAMESPACE_YM_DOTLIB

#endif // PARSE_SIMPLE_H
