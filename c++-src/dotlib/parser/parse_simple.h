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
