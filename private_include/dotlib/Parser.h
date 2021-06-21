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

  /// @brief パーズする
  /// @return 読み込んだ library のASTを返す．
  ///
  /// エラーが起きたら nullptr を返す．
  AstAttrPtr
  parse();


public:
  //////////////////////////////////////////////////////////////////////
  // simple attribute を読み込む関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 整数値型の simple attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_int(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief float 値型の simple attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_float(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 文字列値の simple attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_string(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief ブール値型の simple attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_bool(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'delay_model' Simple Attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_delay_model(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'direction' Simple Attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_direction(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 式型の simple attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_expr(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief "式" 型の simple attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_function(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'timing_sense' Simple Attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_timing_sense(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'timing_type' Simple Attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_timing_type(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'var_type' Simple Attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_vartype(const AttrKwd& attr); ///< [in] 属性の型


public:
  //////////////////////////////////////////////////////////////////////
  // complex attribute を読み込む関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 'define' Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_define(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief ( float, float ) の形式の Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_float_float(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief ( float, string ) 型の Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_float_string(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief ( "float, float, ... " ) の形式の Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_float_vector(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief ( integer, float ) の形式の Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_int_float(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief ( integer, "float, float, ... " ) の形式の Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_int_float_vector(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief ( "integer, integer, ... " ) の形式の Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_int_vector(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief ( string ) 型の Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_string_complex(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief ( string, float ) の形式の Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_string_float(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief ( string, integer ) の形式の Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_string_int(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief ( string, string, ... ) の形式の Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_string_list(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief ( string, string ) の形式の Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_string_string(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'Technology' Complex Attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_technology(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'values' Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_values(const AttrKwd& attr); ///< [in] 属性の型


public:
  //////////////////////////////////////////////////////////////////////
  // group statement を読み込む関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 'base_curves' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_base_curves(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'cell' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_cell(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'compact_lut_template' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_clut_template(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'domain' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_domain(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'ff' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_ff(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'ff_bank' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_ff_bank(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'fault_lut_template' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_flut_template(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'fpga_isd' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_fpga_isd(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'input_voltage' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_input_voltage(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'latch' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_latch(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'latch_bank' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_latch_bank(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'library' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_library(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'operating_conditions' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_operating_conditions(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'output_voltage' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_output_voltage(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'part' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_part(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'pin' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_pin(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'poly_template' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_poly_template(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'power_supply' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_power_supply(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'scaled_cell' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_scaled_cell(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'scaling_factors' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_scaling_factors(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'sensitization' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_sensitization(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'table' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_table(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'lut_template' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_template(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'timing' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_timing(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'timing_range' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_timing_range(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'type' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_type(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'user_parameters' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_user_parameters(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'wire_load' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_wire_load(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'wire_load_selection' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_wire_load_selection(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief 'wire_load_table' Group Statement のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstAttrPtr
  parse_wire_load_table(const AttrKwd& attr); ///< [in] 属性の型

  /// @brief デバッグモードの時 true を返す．
  bool
  debug();


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる下請け関数
  //////////////////////////////////////////////////////////////////////

  // simple attribute を読み込む関数の型定義
  using SimpleHandler = std::function< AstValuePtr(Scanner&)>;

  // group statement の要素を読み込む関数の型定義
  using AttrHandler = std::function<AstAttrPtr(Parser&, const AttrKwd&)>;

  // AttrHandler の辞書
  using AttrHandlerDict = std::unordered_map<AttrType, AttrHandler>;

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

  // complex attribute/group statement header 用のハンドラ
  static EmptyHeader sEmptyHeader;
  static FloatFloatHeader sFloatFloatHeader;
  static FloatStrHeader sFloatStrHeader;
  static FloatVectorHeader sFloatVectorHeader;
  static FloatVectorListHeader sFloatVectorListHeader;
  static IntFloatHeader sIntFloatHeader;
  static IntFloatVectorHeader sIntFloatVectorHeader;
  static IntVectorHeader sIntVectorHeader;
  static StrFloatHeader sStrFloatHeader;
  static StrListHeader sStrListHeader;
  static StrHeader sStrHeader;
  static StrIntHeader sStrIntHeader;
  static StrStrHeader sStrStrHeader;
  static StrStrIntHeader sStrStrIntHeader;
  static StrStrStrHeader sStrStrStrHeader;
  static TechnologyHeader sTechnologyHeader;

  // 各 group statement のハンドラ辞書
  static AttrHandlerDict sCellGroupDict;
  static AttrHandlerDict sDomainGroupDict;
  static AttrHandlerDict sFFGroupDict;
  static AttrHandlerDict sInputVoltageGroupDict;
  static AttrHandlerDict sLatchGroupDict;
  static AttrHandlerDict sLibraryGroupDict;
  static AttrHandlerDict sOutputVoltageGroupDict;
  static AttrHandlerDict sPinGroupDict;
  static AttrHandlerDict sTableGroupDict;
  static AttrHandlerDict sTemplateGroupDict;
  static AttrHandlerDict sTimingGroupDict;

};

END_NAMESPACE_YM_DOTLIB

#endif // PARSER_H
