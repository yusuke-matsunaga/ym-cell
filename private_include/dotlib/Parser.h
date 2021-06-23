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
  parse_group_statement(const AttrKwd& attr,           ///< [in] 属性の型
			HeaderHandler& header_handler, ///< [in] ヘッダ読み込みハンドラ
			const AttrHandlerDict& attr_handler_dict); ///< [in] 要素のハンドラ辞書

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
  static FixedElemHeader sFloatStrHeader;
  static FixedElemHeader sFloatVectorHeader;
  static FixedElemHeader sIntFloatHeader;
  static FixedElemHeader sIntFloatVectorHeader;
  static FixedElemHeader sIntVectorHeader;
  static FixedElemHeader sStrFloatHeader;
  static FixedElemHeader sStrHeader;
  static FixedElemHeader sStrIntHeader;
  static FixedElemHeader sStrStrHeader;
  static FixedElemHeader sStrStrIntHeader;
  static FixedElemHeader sStrStrStrHeader;
  static FixedElemHeader sTechnologyHeader;
  static ListHeader sFloatVectorListHeader;
  static ListHeader sStrListHeader;

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
parse_int(Parser& parser,      ///< [in] パーサー
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
parse_float(Parser& parser,      ///< [in] パーサー
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
parse_string(Parser& parser,      ///< [in] パーサー
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
parse_bool(Parser& parser,      ///< [in] パーサー
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
parse_delay_model(Parser& parser,      ///< [in] パーサー
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
parse_direction(Parser& parser,      ///< [in] パーサー
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
parse_expr(Parser& parser,      ///< [in] パーサー
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
parse_function(Parser& parser,      ///< [in] パーサー
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
parse_timing_sense(Parser& parser,      ///< [in] パーサー
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
parse_timing_type(Parser& parser,      ///< [in] パーサー
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
parse_vartype(Parser& parser,      ///< [in] パーサー
	      const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_simple_attribute(attr, read_vartype);
}


//////////////////////////////////////////////////////////////////////
/// @{
/// @name complex attribute を読み込む関数
//////////////////////////////////////////////////////////////////////

/// @brief 'define' Complex attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
parse_define(Parser& parser,      ///< [in] パーサー
	     const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sStrStrStrHeader);
}

/// @brief ( float, float ) の形式の Complex attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
parse_float_float(Parser& parser,      ///< [in] パーサー
		  const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sFloatFloatHeader);
}

/// @brief ( float, string ) 型の Complex attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
parse_float_string(Parser& parser,      ///< [in] パーサー
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
parse_float_vector(Parser& parser,      ///< [in] パーサー
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
parse_int_float(Parser& parser,      ///< [in] パーサー
		const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sIntFloatHeader);
}

/// @brief ( integer, "float, float, ... " ) の形式の Complex attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
parse_int_float_vector(Parser& parser,      ///< [in] パーサー
		       const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sIntFloatVectorHeader);
}

/// @brief ( "integer, integer, ... " ) の形式の Complex attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
parse_int_vector(Parser& parser,      ///< [in] パーサー
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
parse_string_complex(Parser& parser,      ///< [in] パーサー
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
parse_string_float(Parser& parser,      ///< [in] パーサー
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
parse_string_int(Parser& parser,      ///< [in] パーサー
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
parse_string_list(Parser& parser,      ///< [in] パーサー
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
parse_string_string(Parser& parser,      ///< [in] パーサー
		    const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sStrStrHeader);
}

/// @brief 'Technology' Complex Attribute のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
inline
AstAttrPtr
parse_technology(Parser& parser,      ///< [in] パーサー
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
parse_values(Parser& parser,      ///< [in] パーサー
	     const AttrKwd& attr) ///< [in] 属性の型
{
  return parser.parse_complex_attribute(attr, Parser::sFloatVectorListHeader);
}


//////////////////////////////////////////////////////////////////////
/// @{
/// @name group statement を読み込む関数
//////////////////////////////////////////////////////////////////////

/// @brief 'base_curves' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_base_curves(Parser& parser,       ///< [in] パーサー
		  const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'bundle' group statement のパースを行なう．
/// @return パース結果を返す．
extern
AstAttrPtr
parse_bundle(Parser& parser,       ///< [in] パーサー
	     const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'bus' group statement のパースを行なう．
/// @return パース結果を返す．
extern
AstAttrPtr
parse_bus(Parser& parser,       ///< [in] パーサー
	  const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'cell' group statement のパースを行なう．
/// @return パース結果を返す．
extern
AstAttrPtr
parse_cell(Parser& parser,       ///< [in] パーサー
	   const AttrKwd& attr); ///< [in] 属性(cell)

/// @brief 'ccsn_XXX' group statement のパースを行なう．
/// @return パース結果を返す．
extern
AstAttrPtr
parse_ccsn(Parser& parser,       ///< [in] パーサー
	   const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'compact_lut_template' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_clut_template(Parser& parser,       ///< [in] パーサー
		    const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'dc_current' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_dc_current(Parser& parser,       ///< [in] パーサー
		 const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'XXX_degradation' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_degradation(Parser& parser,       ///< [in] パーサー
		  const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'domain' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_domain(Parser& parser,       ///< [in] パーサー
	     const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'electromigration' group statement のパースを行なう．
/// @return パース結果を返す．
extern
AstAttrPtr
parse_electromigration(Parser& parser,       ///< [in] パーサー
		       const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'ff' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_ff(Parser& parser,       ///< [in] パーサー
	 const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'ff_bank' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_ff_bank(Parser& parser,       ///< [in] パーサー
	      const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'fault_lut_template' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_flut_template(Parser& parser,       ///< [in] パーサー
		    const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'fpga_isd' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_fpga_isd(Parser& parser,       ///< [in] パーサー
	       const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'hyperbolic_noise' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_hyperbolic_noise(Parser& parser,       ///< [in] パーサー
		       const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'input_voltage' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_input_voltage(Parser& parser,       ///< [in] パーサー
		    const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'internal_power' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_internal_power(Parser& parser,       ///< [in] パーサー
		     const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'latch' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_latch(Parser& parser,       ///< [in] パーサー
	    const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'latch_bank' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_latch_bank(Parser& parser,       ///< [in] パーサー
		 const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'leakage_current' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_leakage_current(Parser& parser,       ///< [in] パーサー
		      const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'leakage_power' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_leakage_power(Parser& parser,       ///< [in] パーサー
		    const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'library' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_library(Parser& parser,       ///< [in] パーサー
	      const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'lut' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_lut(Parser& parser,       ///< [in] パーサー
	  const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'minimum_period' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_minimum_period(Parser& parser,       ///< [in] パーサー
		     const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'operating_conditions' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_operating_conditions(Parser& parser,       ///< [in] パーサー
			   const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'output_voltage' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_output_voltage(Parser& parser,       ///< [in] パーサー
		     const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'part' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_part(Parser& parser,       ///< [in] パーサー
	   const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'pin' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_pin(Parser& parser,       ///< [in] パーサー
	  const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'pin_capacitance' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_pin_capacitance(Parser& parser,       ///< [in] パーサー
		      const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'pin_group' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_pin_group(Parser& parser,       ///< [in] パーサー
		const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'poly_template' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_poly_template(Parser& parser,       ///< [in] パーサー
		    const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'power_supply' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_power_supply(Parser& parser,       ///< [in] パーサー
		   const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'min|max_pulse_width' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_pulse_width(Parser& parser,       ///< [in] パーサー
		  const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'scaled_cell' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_scaled_cell(Parser& parser,       ///< [in] パーサー
		  const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'scaling_factors' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_scaling_factors(Parser& parser,       ///< [in] パーサー
		      const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'sensitization' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_sensitization(Parser& parser,       ///< [in] パーサー
		    const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'signal_swing' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_signal_swing(Parser& parser,       ///< [in] パーサー
		   const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'statetable' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_statetable(Parser& parser,       ///< [in] パーサー
		 const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'table' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_table(Parser& parser,       ///< [in] パーサー
	    const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'lut_template' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_template(Parser& parser,       ///< [in] パーサー
	       const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'timing' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_timing(Parser& parser,       ///< [in] パーサー
	     const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'tlatch' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_tlatch(Parser& parser,       ///< [in] パーサー
	     const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'trans' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_trans(Parser& parser,       ///< [in] パーサー
	    const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'timing_range' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_timing_range(Parser& parser,       ///< [in] パーサー
		   const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'type' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_type(Parser& parser,       ///< [in] パーサー
	   const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'user_parameters' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_user_parameters(Parser& parser,       ///< [in] パーサー
		      const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'wire_load' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_wire_load(Parser& parser,       ///< [in] パーサー
		const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'wire_load_selection' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_wire_load_selection(Parser& parser,       ///< [in] パーサー
			  const AttrKwd& attr); ///< [in] 属性の型

/// @brief 'wire_load_table' Group Statement のパースを行う．
/// @return パース結果を返す．
///
/// エラーの時は nullptr を返す．
extern
AstAttrPtr
parse_wire_load_table(Parser& parser,       ///< [in] パーサー
		      const AttrKwd& attr); ///< [in] 属性の型

END_NAMESPACE_YM_DOTLIB

#endif // PARSER_H
