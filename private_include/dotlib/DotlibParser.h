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
  /// @param[in] ido 入力データオブジェクト
  /// @param[in] mgr AstNode を管理するオブジェクト
  /// @param[in] debug デバッグモード
  /// @param[in] allow_no_semi 行末のセミコロンなしを許すかどうか
  DotlibParser(IDO& ido,
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

  /// @brief 'coefs' Complex attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_coefs(const AstFloatVector*& dst,
	      AttrType attr_type,
	      const FileRegion& attr_loc);

  /// @brief 'default_part' Complex attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_default_part(const AstStr2*& dst,
		     AttrType attr_type,
		     const FileRegion& attr_loc);

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

  /// @brief 'define_cell_area' Complex attribute のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  bool
  parse_define_cell_area(vector<const AstStr2*>& dst_list,
			 AttrType attr_type,
			 const FileRegion& attr_loc);

  /// @brief 'define_group' Complex attribute のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  bool
  parse_define_group(vector<const AstStr2*>& dst_list,
		     AttrType attr_type,
		     const FileRegion& attr_loc);

  /// @brief index 型の Complex attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_index(const AstFloatVector*& dst,
	      AttrType attr_type,
	      const FileRegion& attr_loc);

  /// @brief 'library_features' Complex attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_library_features(const AstString*& dst,
			 AttrType attr_type,
			 const FileRegion& attr_loc);

  /// @brief 'orders' Complex attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_orders(const AstIntVector*& dst,
	       AttrType attr_type,
	       const FileRegion& attr_loc);

  /// @brief 'piece_define' Complex attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_piece_define(const AstFloatVector*& dst,
		     AttrType attr_type,
		     const FileRegion& attr_loc);

  /// @brief piecewise 型の Complex attribute のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_piecewise(vector<const AstPieceWise*>& dst_list,
		  AttrType attr_type,
		  const FileRegion& attr_loc);

  /// @brief 'routing_layers' Complex attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_routing_layers(const AstStringVector*& dst,
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

  /// @brief 'capacitive_load_unit' Complex attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_unit(const AstFloatStr*& dst,
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

  /// @brief 'variable_n_range' Complex attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_variable_range(const AstFloat2*& dst,
		       AttrType attr_type,
		       const FileRegion& attr_loc);

  /// @brief 'voltage_map' Complex attribute のパースを行う．
  /// @param[in] dst_list 結果を格納するリスト
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// この属性は重複チェックは行わない．
  bool
  parse_voltage_map(vector<const AstStrFloat*>& dst_list,
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
  parse_latch_bank(const AstLatch* dst,
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

  /// @brief 引数の種類のトークンでなければエラーメッセージを出力する．
  bool
  expect(TokenType type);

  /// @brief 行末まで読み込む．
  bool
  expect_nl();

  /// @brief expression を読み込む．
  AstExpr*
  read_expr(TokenType end_marker);

  /// @brief トークンを一つ読み込む．
  /// @param[out] loc ファイル上の位置情報を格納する変数
  /// @param[in] symbol_mode 数字も文字とみなすモード
  /// @return トークンの型を返す．
  TokenType
  read_token(FileRegion& loc,
	     bool symbol_mode = false);

  /// @brief 直前の read_token() に対応する文字列を返す．
  const char*
  cur_string() const;

  /// @brief 直前の read_token() に対応する整数値を返す．
  ///
  /// 型が INT_NUM でなかったときの値は不定
  int
  cur_int() const;

  /// @brief 直前の read_token() に対応する実数値を返す．
  ///
  /// 型が FLOAT_NUM/INT_NUM でなかったときの値は不定
  double
  cur_float() const;

  /// @brief 直前の read_token() に対応する位置を返す．
  FileRegion
  cur_loc() const;

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

  /// @brief Simple Attribute を読み込む．
  /// @param[in] handler ハンドラ (SimpleHandler の継承クラス)
  /// @retval true 正しく読み込めた．
  /// @retval false エラーが起こった．
  bool
  parse_simple_attribute(SimpleHandler& handler);

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
  AstExpr*
  read_primary();

  /// @brief prudct を読み込む．
  AstExpr*
  read_product();

  /// @brief トークンを読み込む．
  /// @param[out] loc 対応するファイル上の位置情報を格納する変数
  ///
  /// read_token() との違いは mUngetToken を考慮すること．
  TokenType
  _read_token(FileRegion& loc);


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

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief トークンを一つ読み込む．
// @param[out] loc ファイル上の位置情報を格納する変数
// @param[in] symbol_mode 数字も文字とみなすモード
// @return トークンの型を返す．
inline
TokenType
DotlibParser::read_token(FileRegion& loc,
			 bool symbol_mode)
{
  auto ans = mScanner.read_token(loc, symbol_mode);
  mCurLoc = loc;
  return ans;
}

// @brief 直前の read_token() に対応する文字列を返す．
inline
const char*
DotlibParser::cur_string() const
{
  return mScanner.cur_string();
}

// @brief 直前の read_token() に対応する整数値を返す．
// @note 型が INT_NUM でなかったときの値は不定
inline
int
DotlibParser::cur_int() const
{
  return mScanner.cur_int();
}

// @brief 直前の read_token() に対応する実数値を返す．
// @note 型が FLOAT_NUM/INT_NUM でなかったときの値は不定
inline
double
DotlibParser::cur_float() const
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
