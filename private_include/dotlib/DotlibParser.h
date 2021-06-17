#ifndef DOTLIBPARSER_H
#define DOTLIBPARSER_H

/// @file DotlibParser.h
/// @brief DotlibParser のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib_nsdef.h"
#include "AttrType.h"
#include "AttrDic.h"
#include "DotlibScanner.h"
#include "TokenType.h"
#include "ym/FileRegion.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibParser DotlibParser.h "DotlibParser.h"
/// @brief DotlibParser の実装クラス
//////////////////////////////////////////////////////////////////////
class DotlibParser
{
public:

  /// @brief コンストラクタ
  DotlibParser(InputFileObj& in,           ///< [in] 入力ファイルオブジェクト
	       AstMgr& mgr,                ///< [in] AstNode を管理するオブジェクト
	       bool debug,                 ///< [in] デバッグモード
	       bool allow_no_semi = true); ///< [in] 行末のセミコロンなしを許すかどうか

  /// @brief デストラクタ
  ~DotlibParser();


public:

  /// @brief パーズする
  /// @return 読み込んだ AST を返す．
  ///
  /// エラーが起きたら nullptr を返す．
  const AstLibrary*
  parse();


public:
  //////////////////////////////////////////////////////////////////////
  // simple attribute を読み込む関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 整数値型の simple attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_int(AttrType attr_type,          ///< [in] 属性の型
	    const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置

  /// @brief float 値型の simple attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_float(AttrType attr_type,          ///< [in] 属性の型
	      const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置

  /// @brief 文字列値の simple attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_string(AttrType attr_type,          ///< [in] 属性の型
	       const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置

  /// @brief ブール値型の simple attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_bool(AttrType attr_type,          ///< [in] 属性の型
	     const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置

  /// @brief 'delay_model' Simple Attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_delay_model(AttrType attr_type,          ///< [in] 属性の型
		    const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置

  /// @brief 'direction' Simple Attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_direction(AttrType attr_type,          ///< [in] 属性の型
		  const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置

  /// @brief 式型の simple attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_expr(AttrType attr_type,          ///< [in] 属性の型
	     const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置

  /// @brief "式" 型の simple attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_function(AttrType attr_type,          ///< [in] 属性の型
		 const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置

  /// @brief 'timing_sense' Simple Attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_timing_sense(AttrType attr_type,          ///< [in] 属性の型
		     const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置

  /// @brief 'timing_type' Simple Attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_timing_type(AttrType attr_type,          ///< [in] 属性の型
		    const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置

  /// @brief 'var_type' Simple Attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_vartype(AttrType attr_type,          ///< [in] 属性の型
		const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置


public:
  //////////////////////////////////////////////////////////////////////
  // complex attribute を読み込む関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 'define' Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_define(AttrType attr_type,               ///< [in] 属性の型
	       const FileRegion& attr_loc);      ///< [in] 属性のファイル上の位置

  /// @brief ( float, float ) の形式の Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_float2(AttrType attr_type,          ///< [in] 属性の型
	       const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置

  /// @brief ( float, string ) 型の Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_float_string(AttrType attr_type,          ///< [in] 属性の型
		     const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置

  /// @brief ( "float, float, ... " ) の形式の Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_float_vector(AttrType attr_type,          ///< [in] 属性の型
		     const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置

  /// @brief ( integer, float ) の形式の Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_int_float(AttrType attr_type,          ///< [in] 属性の型
		  const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置

  /// @brief ( integer, "float, float, ... " ) の形式の Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_int_float_vector(AttrType attr_type,            ///< [in] 属性の型
			 const FileRegion& attr_loc);   ///< [in] 属性のファイル上の位置

  /// @brief ( "integer, integer, ... " ) の形式の Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_int_vector(AttrType attr_type,          ///< [in] 属性の型
		   const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置

  /// @brief ( string ) 型の Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_string_complex(AttrType attr_type,          ///< [in] 属性の型
		       const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置

  /// @brief ( string, float ) の形式の Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_string_float(AttrType attr_type,                   ///< [in] 属性の型
		     const FileRegion& attr_loc);          ///< [in] 属性のファイル上の位置

  /// @brief ( string, integer ) の形式の Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_string_int(AttrType attr_type,                 ///< [in] 属性の型
		   const FileRegion& attr_loc);        ///< [in] 属性のファイル上の位置

  /// @brief ( string, string, ... ) の形式の Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_string_list(AttrType attr_type,          ///< [in] 属性の型
		    const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置

  /// @brief ( string, string ) の形式の Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_string2(AttrType attr_type,	     ///< [in] 属性の型
		const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置

  /// @brief 'Technology' Complex Attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_technology(AttrType attr_type,		///< [in] 属性の型
		   const FileRegion& attr_loc);	///< [in] 属性のファイル上の位置

  /// @brief 'values' Complex attribute のパースを行う．
  /// @return パース結果を返す．
  ///
  /// エラーの時は nullptr を返す．
  const AstAttr*
  parse_values(AttrType attr_type,	    ///< [in] 属性の型
	       const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置


public:
  //////////////////////////////////////////////////////////////////////
  // group statement を読み込む関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 'base_curves' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// 読み込まれた結果は dst_list に追加される．
  /// この属性は重複チェックは行わない．
  bool
  parse_base_curves(vector<const AstBaseCurves*>& dst_list, ///< [out] 結果を格納するリスト
		    AttrType attr_type,                     ///< [in] 属性の型
		    const FileRegion& attr_loc);            ///< [in] 属性のファイル上の位置

  /// @brief 'cell' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// 読み込まれた結果は dst_list に追加される．
  /// この属性は重複チェックは行わない．
  bool
  parse_cell(vector<const AstCell*>& dst_list, ///< [out] 結果を格納するリスト
	     AttrType attr_type,	       ///< [in] 属性の型
	     const FileRegion& attr_loc);      ///< [in] 属性のファイル上の位置

  /// @brief 'compact_lut_template' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// 読み込まれた結果は dst_list に追加される．
  /// この属性は重複チェックは行わない．
  bool
  parse_clut_template(vector<const AstClutTemplate*>& dst_list, ///< [out] 結果を格納するリスト
		      AttrType attr_type,			///< [in] 属性の型
		      const FileRegion& attr_loc);		///< [in] 属性のファイル上の位置

  /// @brief 'domain' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_domain(const AstDomain*& dst,       ///< [out] 結果を格納する変数
	       AttrType attr_type,	    ///< [in] 属性の型
	       const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置

  /// @brief 'ff' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_ff(const AstFF*& dst,           ///< [out] 結果を格納する変数
	   AttrType attr_type,		///< [in] 属性の型
	   const FileRegion& attr_loc);	///< [in] 属性のファイル上の位置

  /// @brief 'ff_bank' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_ff_bank(const AstFFBank*& dst,       ///< [out] 結果を格納する変数
		AttrType attr_type,	     ///< [in] 属性の型
		const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置

  /// @brief 'fault_lut_template' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// 読み込まれた結果は dst_list に追加される．
  /// この属性は重複チェックは行わない．
  bool
  parse_flut_template(vector<const AstFlutTemplate*>& dst_list, ///< [out] 結果を格納するリスト
		      AttrType attr_type,			///< [in] 属性の型
		      const FileRegion& attr_loc);		///< [in] 属性のファイル上の位置

  /// @brief 'fpga_isd' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// 読み込まれた結果は dst_list に追加される．
  /// この属性は重複チェックは行わない．
  bool
  parse_fpga_isd(vector<const AstFpgaIsd>& dst_list, ///< [out] 結果を格納するリスト
		 AttrType attr_type,		     ///< [in] 属性の型
		 const FileRegion& attr_loc);	     ///< [in] 属性のファイル上の位置

  /// @brief 'input_voltage' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// 読み込まれた結果は dst_list に追加される．
  /// この属性は重複チェックは行わない．
  bool
  parse_input_voltage(vector<const AstInputVoltage*>& dst_list, ///< [out] 結果を格納するリスト
		      AttrType attr_type,			///< [in] 属性の型
		      const FileRegion& attr_loc);		///< [in] 属性のファイル上の位置

  /// @brief 'latch' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_latch(const AstLatch*& dst,        ///< [out] 結果を格納する変数
	      AttrType attr_type,	   ///< [in] 属性の型
	      const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置

  /// @brief 'latch_bank' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_latch_bank(const AstLatchBank*& dst,    ///< [out] 結果を格納する変数
		   AttrType attr_type,		///< [in] 属性の型
		   const FileRegion& attr_loc);	///< [in] 属性のファイル上の位置

  /// @brief 'library' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_library(const AstLibrary*& dst,      ///< [out] 結果を格納する変数
		AttrType attr_type,	     ///< [in] 属性の型
		const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置

  /// @brief 'operating_conditions' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// 読み込まれた結果は dst_list に追加される．
  /// この属性は重複チェックは行わない．
  bool
  parse_operating_conditions(vector<const AstOutputVoltage*>& dst_list, ///< [out] 結果を格納するリスト
			     AttrType attr_type,			///< [in] 属性の型
			     const FileRegion& attr_loc);		///< [in] 属性のファイル上の位置

  /// @brief 'output_voltage' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// 読み込まれた結果は dst_list に追加される．
  /// この属性は重複チェックは行わない．
  bool
  parse_output_voltage(vector<const AstOutputVoltage*>& dst_list, ///< [out] 結果を格納するリスト
		       AttrType attr_type,			  ///< [in] 属性の型
		       const FileRegion& attr_loc);		  ///< [in] 属性のファイル上の位置

  /// @brief 'part' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// 読み込まれた結果は dst_list に追加される．
  /// この属性は重複チェックは行わない．
  bool
  parse_part(vector<const AstPart*>& dst_list, ///< [out] 結果を格納するリスト
	     AttrType attr_type,	       ///< [in] 属性の型
	     const FileRegion& attr_loc);      ///< [in] 属性のファイル上の位置

  /// @brief 'pin' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// 読み込まれた結果は dst_list に追加される．
  /// この属性は重複チェックは行わない．
  bool
  parse_pin(vector<const AstPin*>& dst_list, ///< [out] 結果を格納するリスト
	    AttrType attr_type,		     ///< [in] 属性の型
	    const FileRegion& attr_loc);     ///< [in] 属性のファイル上の位置

  /// @brief 'table' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_table(const AstLut*& dst,          ///< [out] 結果を格納する変数
	      AttrType attr_type,	   ///< [in] 属性の型
	      const FileRegion& attr_loc); ///< [in] 属性のファイル上の位置

  /// @brief 'poly_template' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// 読み込まれた結果は dst_list に追加される．
  /// この属性は重複チェックは行わない．
  bool
  parse_poly_template(vector<const AstPolyTemplate*>& dst_list, ///< [out] 結果を格納するリスト
		      AttrType attr_type,			///< [in] 属性の型
		      const FileRegion& attr_loc);		///< [in] 属性のファイル上の位置

  /// @brief 'power_supply' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// 読み込まれた結果は dst_list に追加される．
  /// この属性は重複チェックは行わない．
  bool
  parse_power_supply(vector<const AstPowerSupply*>& dst_list, ///< [out] 結果を格納するリスト
		     AttrType attr_type,		      ///< [in] 属性の型
		     const FileRegion& attr_loc);	      ///< [in] 属性のファイル上の位置

  /// @brief 'scaled_cell' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// 読み込まれた結果は dst_list に追加される．
  /// この属性は重複チェックは行わない．
  bool
  parse_scaled_cell(vector<const AstScaledCell*>& dst_list, ///< [out] 結果を格納するリスト
		    AttrType attr_type,			    ///< [in] 属性の型
		    const FileRegion& attr_loc);	    ///< [in] 属性のファイル上の位置

  /// @brief 'scaling_factors' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// 読み込まれた結果は dst_list に追加される．
  /// この属性は重複チェックは行わない．
  bool
  parse_scaling_factors(vector<const AstScalingFactors*>& dst_list, ///< [out] 結果を格納するリスト
			AttrType attr_type,			    ///< [in] 属性の型
			const FileRegion& attr_loc);		    ///< [in] 属性のファイル上の位置

  /// @brief 'sensitization' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// 読み込まれた結果は dst_list に追加される．
  /// この属性は重複チェックは行わない．
  bool
  parse_sensitization(vector<const AstSensitization*>& dst_list, ///< [out] 結果を格納するリスト
		      AttrType attr_type,			 ///< [in] 属性の型
		      const FileRegion& attr_loc);		 ///< [in] 属性のファイル上の位置

  /// @brief 'table' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// 読み込まれた結果は dst_list に追加される．
  /// この属性は重複チェックは行わない．
  bool
  parse_table(vector<const AstLut*>& dst_list, ///< [out] 結果を格納するリスト
	      AttrType attr_type,	       ///< [in] 属性の型
	      const FileRegion& attr_loc);     ///< [in] 属性のファイル上の位置

  /// @brief 'lut_template' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// 読み込まれた結果は dst_list に追加される．
  /// この属性は重複チェックは行わない．
  bool
  parse_template(vector<const AstTemplate*>& dst_list, ///< [out] 結果を格納するリスト
		 AttrType attr_type,		       ///< [in] 属性の型
		 const FileRegion& attr_loc);	       ///< [in] 属性のファイル上の位置

  /// @brief 'timing' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// 読み込まれた結果は dst_list に追加される．
  /// この属性は重複チェックは行わない．
  bool
  parse_timing(vector<const AstTiming*>& dst_list, ///< [out] 結果を格納するリスト
	       AttrType attr_type,		   ///< [in] 属性の型
	       const FileRegion& attr_loc);	   ///< [in] 属性のファイル上の位置

  /// @brief 'timing_range' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// 読み込まれた結果は dst_list に追加される．
  /// この属性は重複チェックは行わない．
  bool
  parse_timing_range(vector<const AstTimingRange*>& dst_list, ///< [out] 結果を格納するリスト
		     AttrType attr_type,		      ///< [in] 属性の型
		     const FileRegion& attr_loc);	      ///< [in] 属性のファイル上の位置

  /// @brief 'type' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// 読み込まれた結果は dst_list に追加される．
  /// この属性は重複チェックは行わない．
  bool
  parse_type(vector<const AstType*>& dst_list, ///< [out] 結果を格納するリスト
	     AttrType attr_type,	       ///< [in] 属性の型
	     const FileRegion& attr_loc);      ///< [in] 属性のファイル上の位置

  /// @brief 'user_parameters' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_user_parameters(const AstUserParameters* dst, ///< [out] 結果を格納する変数
			AttrType attr_type,	      ///< [in] 属性の型
			const FileRegion& attr_loc);  ///< [in] 属性のファイル上の位置

  /// @brief 'wire_load' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// 読み込まれた結果は dst_list に追加される．
  /// この属性は重複チェックは行わない．
  bool
  parse_wire_load(vector<const AstWireLoad*>& dst_list, ///< [out] 結果を格納するリスト
		  AttrType attr_type,			///< [in] 属性の型
		  const FileRegion& attr_loc);		///< [in] 属性のファイル上の位置

  /// @brief 'wire_load_selection' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// 読み込まれた結果は dst_list に追加される．
  /// この属性は重複チェックは行わない．
  bool
  parse_wire_load_selection(vector<const AstWireLoadSelection*>& dst_list, ///< [out] 結果を格納するリスト
			    AttrType attr_type,				   ///< [in] 属性の型
			    const FileRegion& attr_loc);		   ///< [in] 属性のファイル上の位置

  /// @brief 'wire_load_table' Group Statement のパースを行う．
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// 読み込まれた結果は dst_list に追加される．
  /// この属性は重複チェックは行わない．
  bool
  parse_wire_load_table(vector<const AstWireLoadTable*>& dst_list, ///< [out] 結果を格納するリスト
			AttrType attr_type,			   ///< [in] 属性の型
			const FileRegion& attr_loc);		   ///< [in] 属性のファイル上の位置


public:
  //////////////////////////////////////////////////////////////////////
  // DotlibHandler から用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 直前に読んだトークンから AstInt を生成する．
  /// @return 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  unique_ptr<const AstValue>
  read_int();

  /// @brief 直前に読んだトークンから AstFloat を生成する．
  /// @return 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  unique_ptr<const AstValue>
  read_float();

  /// @brief 直前に読んだトークンから AstString を生成する．
  /// @return 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  unique_ptr<const AstValue>
  read_string();

  /// @brief 直前に読んだトークンから AstBool を生成する．
  /// @return 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  unique_ptr<const AstValue>
  read_bool();

  /// @brief 直前に読んだトークンから AstDelayModel を生成する．
  /// @param[in] 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  unique_ptr<const AstValue>
  read_delay_model();

  /// @brief 直前に読んだトークンから AstDirection を生成する．
  /// @param[in] 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  unique_ptr<const AstValue>
  read_direction();

  /// @brief 直前に読んだトークンから AstTechnology を生成する．
  /// @param[in] 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  unique_ptr<const AstValue>
  read_technology();

  /// @brief 直前に読んだトークンから AstTimingSense を生成する．
  /// @param[in] 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  unique_ptr<const AstValue>
  read_timing_sense();

  /// @brief 直前に読んだトークンから AstTimingType を生成する．
  /// @param[in] 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  unique_ptr<const AstValue>
  read_timing_type();

  /// @brief 直前に読んだトークンから AstVarType を生成する．
  /// @param[in] 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  unique_ptr<const AstValue>
  read_vartype();

  /// @brief 直前に読んだトークンから AstIntVector を生成する．
  /// @return 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  unique_ptr<const AstValue>
  read_int_vector();

  /// @brief 直前に読んだトークンから AstFloatVector を生成する．
  /// @return 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  unique_ptr<const AstValue>
  read_float_vector();

  /// @brief 式を表す AstExprValue を生成する．
  /// @return 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  unique_ptr<const AstValue>
  read_expr();

  /// @brief 直前に読んだトークンから float のリストを生成する．
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起こった．
  ///
  /// dst_list は初期化せず，末尾に追加する．
  bool
  read_raw_float_vector(vector<double>& dst_list, ///< [out] 値を格納するリスト
			FileRegion& loc);         ///< [out] ファイル上の位置

  /// @brief 直前に読んだトークンから文字列を取り出す．
  /// @return 文字列を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  const char*
  read_raw_string(FileRegion& value_loc);   ///< [out] トークンのファイル上の位置

  /// @brief expression を読み込む．
  /// @return 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  const AstExpr*
  _read_expr(TokenType end_marker); ///< [in] 末尾のトークンのタイプ

  /// @brief 引数の種類のトークンでなければエラーメッセージを出力する．
  bool
  expect(TokenType type); ///< [in] トークンのタイプ

  /// @brief 行末まで読み込む．
  bool
  expect_nl();

  /// @brief トークンを一つ読み込む．
  /// @return トークンの型を返す．
  ///
  /// 通常数字から始まるシンボルは数値とみなされるが，
  /// symbol_mode が true の時は数字も文字とみなす．
  TokenType
  read_token(FileRegion& loc,           ///< [out] ファイル上の位置情報を格納する変数
	     bool symbol_mode = false); ///< [in] 数字も文字とみなすモード

  /// @brief トークンを戻す．
  void
  unget_token(TokenType token_type,         ///< [in] トークンの種類
	      const FileRegion& token_loc); ///< [in] トークンの場所

  /// @brief 直前の read_token() に対応する文字列を返す．
  const char*
  cur_string()
  {
    return mScanner.cur_string();
  }

  /// @brief 直前の read_token() に対応する整数値を返す．
  ///
  /// 型が INT_NUM でなかったときの値は不定
  int
  cur_int()
  {
    return mScanner.cur_int();
  }

  /// @brief 直前の read_token() に対応する実数値を返す．
  ///
  /// 型が FLOAT_NUM/INT_NUM でなかったときの値は不定
  double
  cur_float()
  {
    return mScanner.cur_float();
  }

  /// @brief 直前の read_token() に対応する位置を返す．
  FileRegion
  cur_loc()
  {
    return mCurLoc;
  }

  /// @brief 文字列を属性値に変換する．
  AttrType
  conv_to_attr(const char* str); ///< [in] 文字列

  /// @brief AstMgr を返す．
  AstMgr&
  mgr()
  {
    return mAstMgr;
  }

  /// @brief デバッグモードの時 true を返す．
  bool
  debug();


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる下請け関数
  //////////////////////////////////////////////////////////////////////

  // 関数の型定義
  using SimpleHandler = std::function<bool(DotlibParser&)>;

  /// @brief Simple Attribute を読み込む．
  /// @retval true 正しく読み込めた．
  /// @retval false エラーが起こった．
  bool
  parse_simple_attribute(SimpleHandler handler); ///< [in] simple 属性ハンドラ

  /// @brief Complex Attribute を読み込む．
  /// @retval true 正しく読み込めた．
  /// @retval false エラーが起こった．
  bool
  parse_complex_attribute(HeaderHandler& handler); ///< [in] ヘッダ読み込みハンドラ (HeaderHandler の継承クラス)

  /// @brief Group Statement を読み込む．
  /// @retval true 正しく読み込めた．
  /// @retval false エラーが起こった．
  bool
  parse_group_statement(HeaderHandler& header_handler, ///< [in] ヘッダ読み込みハンドラ (HeaderHandler の継承クラス)
			GroupHandler& group_handler);  ///< [in] グループ読み込みハンドラ (GroupHandler の継承クラス)

  /// @brief Complex Attribute, GroupStatement のヘッダを読み込む．
  /// @retval true 正しく読み込めた．
  /// @retval false エラーが起こった．
  bool
  parse_header(HeaderHandler& handler); ///< [in] ハンドラ(HeaderHandler の継承クラス)


private:
  //////////////////////////////////////////////////////////////////////
  // read_expr() で用いられる下請け関数
  //////////////////////////////////////////////////////////////////////

  /// @brief primary を読み込む．
  const AstExpr*
  _read_primary();

  /// @brief prudct を読み込む．
  const AstExpr*
  _read_product();


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 字句解析器
  DotlibScanner mScanner;

  // AstNode を管理するオブジェクト
  AstMgr& mAstMgr;

  // 直前の位置
  FileRegion mCurLoc;

  // 属性用の辞書
  AttrDic mAttrDic;

  // デバッグモード
  bool mDebug;

  // 行末のセミコロンなしを許すかどうかのフラグ
  bool mAllowNoSemi;

  // 読み戻したトークンの型
  TokenType mUngetType{TokenType::ERROR};

  // 読み戻したトークンの位置
  FileRegion mUngetLoc{};

  // ヘッダ用のハンドラ
  unique_ptr<StrHandler> mStrHeader;
  unique_ptr<StrIntHandler> mStrIntHeader;
  unique_ptr<StrListHandler> mStrListHeader;
  unique_ptr<StrStrHandler> mStrStrHeader;
  unique_ptr<StrStrIntHandler> mStrStrIntHeader;

  // グループ本体用のハンドラ
  unique_ptr<CellHandler> mCellGroup;
  unique_ptr<DomainHandler> mDomainGroup;
  unique_ptr<FFHandler> mFFGroup;
  unique_ptr<InputVoltageHandler> mInputVoltageGroup;
  unique_ptr<LatchHandler> mLatchGroup;
  unique_ptr<LibraryHandler> mLibraryGroup;
  unique_ptr<OutputVoltageHandler> mOutputVoltageGroup;
  unique_ptr<PinHandler> mPinGroup;
  unique_ptr<TableHandler> mTableGroup;
  unique_ptr<TemplateHandler> mTemplateGroup;
  unique_ptr<TimingHandler> mTimingGroup;

};

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBPARSER_H
