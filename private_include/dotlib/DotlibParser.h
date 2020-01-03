#ifndef DOTLIBPARSER_H
#define DOTLIBPARSER_H

/// @file DotlibParser.h
/// @brief DotlibParser のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "AttrType.h"
#include "AttrDic.h"
#include "DotlibScanner.h"

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
  /// @param[in] in 入力ファイルオブジェクト
  /// @param[in] mgr AstNode を管理するオブジェクト
  /// @param[in] debug デバッグモード
  /// @param[in] allow_no_semi 行末のセミコロンなしを許すかどうか
  DotlibParser(InputFileObj& in,
	       AstMgr& mgr,
	       bool debug,
	       bool allow_no_semi = true);

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

  /// @brief ブール値 のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_bool(const AstBool*& dst,
	     AttrType attr_type,
	     const FileRegion& attr_loc);

  /// @brief 整数値 のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_int(const AstInt*& dst,
	    AttrType attr_type,
	    const FileRegion& attr_loc);

  /// @brief float 値のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_float(const AstFloat*& dst,
	      AttrType attr_type,
	      const FileRegion& attr_loc);

  /// @brief 文字列値のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_string(const AstString*& dst,
	       AttrType attr_type,
	       const FileRegion& attr_loc);

  /// @brief 'delay_model' Simple Attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_delay_model(const AstDelayModel*& dst,
		    AttrType attr_type,
		    const FileRegion& attr_loc);

  /// @brief 'direction' Simple Attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_direction(const AstDirection*& dst,
		  AttrType attr_type,
		  const FileRegion& attr_loc);

  /// @brief 'timing_sense' Simple Attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_timing_sense(const AstTimingSense*& dst,
		     AttrType attr_type,
		     const FileRegion& attr_loc);

  /// @brief 'timing_type' Simple Attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_timing_type(const AstTimingType*& dst,
		    AttrType attr_type,
		    const FileRegion& attr_loc);

  /// @brief 'var_type' Simple Attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_vartype(const AstVarType*& dst,
		AttrType attr_type,
		const FileRegion& attr_loc);

  /// @brief 式のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_expr(const AstExpr*& dst,
	     AttrType attr_type,
	     const FileRegion& attr_loc);

  /// @brief 論理関数のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_function(const AstExpr*& dst,
		 AttrType attr_type,
		 const FileRegion& attr_loc);


public:
  //////////////////////////////////////////////////////////////////////
  // complex attribute を読み込む関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 'define' Complex attribute のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  bool
  parse_define(vector<const AstStr3*>& dst_list,
	       AttrType attr_type,
	       const FileRegion& attr_loc);

  /// @brief ( float, float ) の形式の Complex attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  /// - 'variable_n_range'
  bool
  parse_float_float(const AstFloat2*& dst,
		    AttrType attr_type,
		    const FileRegion& attr_loc);

  /// @brief ( float, string ) 型の Complex attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  /// - 'capacitive_load_unit'
  bool
  parse_float_string(const AstFloatStr*& dst,
		     AttrType attr_type,
		     const FileRegion& attr_loc);

  /// @brief ( "float, float, ... " ) の形式の Complex attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  /// - 'coefs'
  /// - 'curve_x'
  /// - 'index'
  /// - 'piece_define'
  bool
  parse_float_vector(const AstFloatVector*& dst,
		     AttrType attr_type,
		     const FileRegion& attr_loc);

  /// @brief ( integer, float ) の形式の Complex attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  /// - 'fanout_length'
  /// - 'fanout_area'
  /// - 'fanout_capacitance'
  /// - 'fanout_resistance'
  bool
  parse_int_float(const AstIntFloat*& dst,
		  AttrType attr_type,
		  const FileRegion& attr_loc);

  /// @brief ( integer, "float, float, ... " ) の形式の Complex attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  /// - 'curve_y'
  bool
  parse_int_float_vector(const AstIntFloatVector*& dst,
			 AttrType attr_type,
			 const FileRegion& attr_loc);

  /// @brief ( "integer, integer, ... " ) の形式の Complex attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  /// - 'orders'
  bool
  parse_int_vector(const AstIntVector*& dst,
		   AttrType attr_type,
		   const FileRegion& attr_loc);

  /// @brief ( integer, float ) 型の Complex attribute のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_int_float(vector<const AstIntFloat*>& dst_list,
		  AttrType attr_type,
		  const FileRegion& attr_loc);

  /// @brief ( string ) 型の Complex attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  /// - 'base_curve_type'
  /// - 'library_features'
  bool
  parse_string_complex(const AstString*& dst,
		       AttrType attr_type,
		       const FileRegion& attr_loc);

  /// @brief ( string, float ) の形式の Complex attribute のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  /// - 'power_rail'
  /// - 'voltage_map'
  bool
  parse_string_float(vector<const AstStrFloat*>& dst_list,
		     AttrType attr_type,
		     const FileRegion& attr_loc);

  /// @brief ( string, integer ) の形式の Complex attribute のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  /// - 'max_count'
  bool
  parse_string_int(vector<const AstStrInt*>& dst_list,
		   AttrType attr_type,
		   const FileRegion& attr_loc);

  /// @brief ( string, string, ... ) の形式の Complex attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  /// - 'routing_layers'
  /// - 'valid_speed_grade'
  /// - 'valid_step_levels'
  bool
  parse_string_list(const AstStrList*& dst,
		    AttrType attr_type,
		    const FileRegion& attr_loc);

  /// @brief ( string, string ) の形式の Complex attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  /// - 'default_part'
  bool
  parse_string_string(const AstStr2*& dst,
		      AttrType attr_type,
		      const FileRegion& attr_loc);

  /// @brief ( string, string ) の形式の Complex attribute のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// - 'define_cell_area'
  /// - 'define_group'
  /// - 'mapping'
  bool
  parse_string_string(vector<const AstStr2*>& dst_list,
		      AttrType attr_type,
		      const FileRegion& attr_loc);

  /// @brief 'Technology' Complex Attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_technology(const AstTechnology*& dst,
		   AttrType attr_type,
		   const FileRegion& attr_loc);

  /// @brief 'values' Complex attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_values(const AstFloatVector*& dst,
	       AttrType attr_type,
	       const FileRegion& attr_loc);


public:
  //////////////////////////////////////////////////////////////////////
  // group statement を読み込む関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 'base_curves' Group Statement のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_base_curves(vector<const AstBaseCurves*>& dst_list,
		    AttrType attr_type,
		    const FileRegion& attr_loc);

  /// @brief 'cell' Group Statement のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_cell(vector<const AstCell*>& dst_list,
	     AttrType attr_type,
	     const FileRegion& attr_loc);

  /// @brief 'compact_lut_template' Group Statement のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_clut_template(vector<const AstClutTemplate*>& dst_list,
		      AttrType attr_type,
		      const FileRegion& attr_loc);

  /// @brief 'domain' Group Statement のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_domain(const AstDomain*& dst,
	       AttrType attr_type,
	       const FileRegion& attr_loc);

  /// @brief 'ff' Group Statement のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_ff(const AstFF* dst,
	   AttrType attr_type,
	   const FileRegion& attr_loc);

  /// @brief 'ff_bank' Group Statement のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_ff_bank(const AstFFBank* dst,
		AttrType attr_type,
		const FileRegion& attr_loc);

  /// @brief 'fault_lut_template' Group Statement のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_flut_template(vector<const AstFlutTemplate*>& dst_list,
		      AttrType attr_type,
		      const FileRegion& attr_loc);

  /// @brief 'fpga_isd' Group Statement のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_fpga_isd(vector<const AstFpgaIsd>& dst_list,
		 AttrType attr_type,
		 const FileRegion& attr_loc);

  /// @brief 'input_voltage' Group Statement のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_input_voltage(vector<const AstInputVoltage*>& dst_list,
		      AttrType attr_type,
		      const FileRegion& attr_loc);

  /// @brief 'latch' Group Statement のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_latch(const AstLatch* dst,
	      AttrType attr_type,
	      const FileRegion& attr_loc);

  /// @brief 'latch_bank' Group Statement のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_latch_bank(const AstLatchBank* dst,
		   AttrType attr_type,
		   const FileRegion& attr_loc);

  /// @brief 'library' Group Statement のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_library(const AstLibrary*& dst,
		AttrType attr_type,
		const FileRegion& attr_loc);

  /// @brief 'operating_conditions' Group Statement のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_operating_conditions(vector<const AstOutputVoltage*>& dst_list,
			     AttrType attr_type,
			     const FileRegion& attr_loc);

  /// @brief 'output_voltage' Group Statement のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_output_voltage(vector<const AstOutputVoltage*>& dst_list,
		       AttrType attr_type,
		       const FileRegion& attr_loc);

  /// @brief 'part' Group Statement のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_part(vector<const AstPart*>& dst_list,
	     AttrType attr_type,
	     const FileRegion& attr_loc);

  /// @brief 'pin' Group Statement のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_pin(vector<const AstPin*>& dst_list,
	    AttrType attr_type,
	    const FileRegion& attr_loc);

  /// @brief 'table' Group Statement のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_table(const AstLut*& dst,
	      AttrType attr_type,
	      const FileRegion& attr_loc);

  /// @brief 'poly_template' Group Statement のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_poly_template(vector<const AstPolyTemplate*>& dst_list,
		      AttrType attr_type,
		      const FileRegion& attr_loc);

  /// @brief 'power_supply' Group Statement のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_power_supply(vector<const AstPowerSupply*>& dst_list,
		     AttrType attr_type,
		     const FileRegion& attr_loc);

  /// @brief 'scaled_cell' Group Statement のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_scaled_cell(vector<const AstScaledCell*>& dst_list,
		    AttrType attr_type,
		    const FileRegion& attr_loc);

  /// @brief 'scaling_factors' Group Statement のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_scaling_factors(vector<const AstScalingFactors*>& dst_list,
			AttrType attr_type,
			const FileRegion& attr_loc);

  /// @brief 'sensitization' Group Statement のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_sensitization(vector<const AstSensitization*>& dst_list,
		      AttrType attr_type,
		      const FileRegion& attr_loc);

  /// @brief 'table' Group Statement のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_table(vector<const AstLut*>& dst_list,
	      AttrType attr_type,
	      const FileRegion& attr_loc);

  /// @brief 'lut_template' Group Statement のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_template(vector<const AstTemplate*>& dst_list,
		 AttrType attr_type,
		 const FileRegion& attr_loc);

  /// @brief 'timing' Group Statement のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_timing(vector<const AstTiming*>& dst_list,
	       AttrType attr_type,
	       const FileRegion& attr_loc);

  /// @brief 'timing_range' Group Statement のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_timing_range(vector<const AstTimingRange*>& dst_list,
		     AttrType attr_type,
		     const FileRegion& attr_loc);

  /// @brief 'type' Group Statement のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_type(vector<const AstType*>& dst_list,
	     AttrType attr_type,
	     const FileRegion& attr_loc);

  /// @brief 'user_parameters' Group Statement のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_user_parameters(const AstUserParameters* dst,
			AttrType attr_type,
			const FileRegion& attr_loc);

  /// @brief 'wire_load' Group Statement のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_wire_load(vector<const AstWireLoad*>& dst_list,
		  AttrType attr_type,
		  const FileRegion& attr_loc);

  /// @brief 'wire_load_selection' Group Statement のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_wire_load_selection(vector<const AstWireLoadSelection*>& dst_list,
			    AttrType attr_type,
			    const FileRegion& attr_loc);

  /// @brief 'wire_load_table' Group Statement のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_wire_load_table(vector<const AstWireLoadTable*>& dst_list,
			AttrType attr_type,
			const FileRegion& attr_loc);


public:
  //////////////////////////////////////////////////////////////////////
  // DotlibHandler から用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 直前に読んだトークンから AstInt を生成する．
  /// @param[out] dst 結果を格納する変数
  /// @retval true 読み込みが成功した．
  /// @retval false 読み込みが失敗した．
  bool
  read_int(const AstInt*& dst);

  /// @brief 直前に読んだトークンから AstFloat を生成する．
  /// @param[out] dst 結果を格納する変数
  /// @retval true 読み込みが成功した．
  /// @retval false 読み込みが失敗した．
  bool
  read_float(const AstFloat*& dst);

  /// @brief 直前に読んだトークンから文字列を取り出す．
  /// @param[out] dst 結果を格納する変数
  /// @param[out] value_loc トークンのファイル上の位置
  /// @retval true 読み込みが成功した．
  /// @retval false 読み込みが失敗した．
  bool
  read_raw_string(const char*& dst,
		  FileRegion& value_loc);

  /// @brief 直前に読んだトークンから AstString を生成する．
  /// @param[out] dst 結果を格納する変数
  /// @retval true 読み込みが成功した．
  /// @retval false 読み込みが失敗した．
  bool
  read_string(const AstString*& dst);

  /// @brief 直前に読んだトークンから AstIntVector を生成する．
  /// @param[out] dst 結果を格納する変数
  /// @retval true 読み込みが成功した．
  /// @retval false 読み込みが失敗した．
  bool
  read_int_vector(const AstIntVector*& dst);

  /// @brief 直前に読んだトークンから AstFloatVector を生成する．
  /// @param[out] dst 結果を格納する変数
  /// @retval true 読み込みが成功した．
  /// @retval false 読み込みが失敗した．
  bool
  read_float_vector(const AstFloatVector*& dst);

  /// @brief 直前に読んだトークンから float のリストを生成する．
  /// @param[int] dst_list 値を格納するリスト
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起こった．
  ///
  /// dst_list は初期化せず，末尾に追加する．
  bool
  read_float_vector(FileRegion& loc,
		    vector<double>& dst_list);

  /// @brief 引数の種類のトークンでなければエラーメッセージを出力する．
  bool
  expect(TokenType type);

  /// @brief 行末まで読み込む．
  bool
  expect_nl();

  /// @brief expression を読み込む．
  const AstExpr*
  read_expr(TokenType end_marker);

  /// @brief トークンを一つ読み込む．
  /// @param[out] loc ファイル上の位置情報を格納する変数
  /// @param[in] symbol_mode 数字も文字とみなすモード
  /// @return トークンの型を返す．
  TokenType
  read_token(FileRegion& loc,
	     bool symbol_mode = false);

  /// @brief トークンを戻す．
  /// @param[in] token_type トークンの種類
  /// @param[in] token_loc トークンの場所
  void
  unget_token(TokenType token_type,
	      const FileRegion& token_loc);

  /// @brief 直前の read_token() に対応する文字列を返す．
  const char*
  cur_string();

  /// @brief 直前の read_token() に対応する整数値を返す．
  ///
  /// 型が INT_NUM でなかったときの値は不定
  int
  cur_int();

  /// @brief 直前の read_token() に対応する実数値を返す．
  ///
  /// 型が FLOAT_NUM/INT_NUM でなかったときの値は不定
  double
  cur_float();

  /// @brief 直前の read_token() に対応する位置を返す．
  FileRegion
  cur_loc();

  /// @brief 文字列を属性値に変換する．
  AttrType
  conv_to_attr(const char* str);

  /// @brief AstMgr を返す．
  AstMgr&
  mgr();

  /// @brief デバッグモードの時 true を返す．
  bool
  debug();


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる下請け関数
  //////////////////////////////////////////////////////////////////////

  using ParseFunc = std::function<bool(DotlibParser&)>;

  /// @brief Simple Attribute を読み込む．
  /// @param[in] parse_func パース関数
  /// @retval true 正しく読み込めた．
  /// @retval false エラーが起こった．
  bool
  parse_simple_attribute(ParseFunc parse_func);

  /// @brief Complex Attribute を読み込む．
  /// @param[in] handler ヘッダ読み込みハンドラ (HeaderHandler の継承クラス)
  /// @retval true 正しく読み込めた．
  /// @retval false エラーが起こった．
  bool
  parse_complex_attribute(HeaderHandler& handler);

  /// @brief Group Statement を読み込む．
  /// @param[in] header_handler ヘッダ読み込みハンドラ (HeaderHandler の継承クラス)
  /// @param[in] group_handler グループ読み込みハンドラ (GroupHandler の継承クラス)
  /// @retval true 正しく読み込めた．
  /// @retval false エラーが起こった．
  bool
  parse_group_statement(HeaderHandler& header_handler,
			GroupHandler& group_handler);

  /// @brief Complex Attribute, GroupStatement のヘッダを読み込む．
  /// @param[in] handler ハンドラ(HeaderHandler の継承クラス)
  /// @retval true 正しく読み込めた．
  /// @retval false エラーが起こった．
  bool
  parse_header(HeaderHandler& handler);


private:
  //////////////////////////////////////////////////////////////////////
  // read_expr() で用いられる下請け関数
  //////////////////////////////////////////////////////////////////////

  /// @brief primary を読み込む．
  const AstExpr*
  read_primary();

  /// @brief prudct を読み込む．
  const AstExpr*
  read_product();


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
  TokenType mUngetType;

  // 読み戻したトークンの位置
  FileRegion mUngetLoc;

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


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 直前の read_token() に対応する位置を返す．
inline
FileRegion
DotlibParser::cur_loc()
{
  return mCurLoc;
}

// @brief 直前の read_token() に対応する文字列を返す．
inline
const char*
DotlibParser::cur_string()
{
  return mScanner.cur_string();
}

// @brief 直前の read_token() に対応する整数値を返す．
// @note 型が INT_NUM でなかったときの値は不定
inline
int
DotlibParser::cur_int()
{
  return mScanner.cur_int();
}

// @brief 直前の read_token() に対応する実数値を返す．
// @note 型が FLOAT_NUM/INT_NUM でなかったときの値は不定
inline
double
DotlibParser::cur_float()
{
  return mScanner.cur_float();
}

// @brief AstMgr を返す．
inline
AstMgr&
DotlibParser::mgr()
{
  return mAstMgr;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBPARSER_H
