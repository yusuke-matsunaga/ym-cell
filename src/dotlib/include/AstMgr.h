#ifndef ASTMGR_H
#define ASTMGR_H

/// @file AstMgr.h
/// @brief AstMgr のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "AttrType.h"
#include "ym/ShString.h"
#include "ym/FileRegion.h"
#include "ym/SimpleAlloc.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstMgr AstMgr.h "AstMgr.h"
/// @brief dotlib の AST ノードを管理するクラス
//////////////////////////////////////////////////////////////////////
class AstMgr
{
public:

  /// @brief コンストラクタ
  AstMgr();

  /// @brief デストラクタ
  ~AstMgr();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 初期化する．
  /// @note 以前，生成されたオブジェクトは破壊される．
  void
  clear();

  /// @brief 根のノードを返す．
  const AstLibrary*
  library_node() const;

  /// @brief 整数値を表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  AstInt*
  new_int(const FileRegion& loc,
	  int value);

  /// @brief 実数値を表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  AstFloat*
  new_float(const FileRegion& loc,
	    double value);

  /// @brief 文字列シンボルを表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  AstString*
  new_string(const FileRegion& loc,
	     ShString value);

  /// @brief ベクタを表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value_list 値のリスト
  AstFloatVector*
  new_vector(const FileRegion& loc,
	     const vector<double>& value_list);

  /// @brief ライブラリを表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] name
  /// @param[in] technology
  /// @param[in] delay_model
  /// @param[in] bus_naming_style
  /// @param[in] comment
  /// @param[in] date
  /// @param[in] revision
  /// @param[in] capacitive_load_unit
  /// @param[in] current_unit
  /// @param[in] leakage_power_unit
  /// @param[in] pulling_resistance_unit
  /// @param[in] time_unit
  /// @param[in] voltage_unit
  /// @param[in] lut_template_list
  /// @param[in] cell_list
  AstLibrary*
  new_library(const FileRegion& loc,
	      const AstString* name,
	      const AstTechnology* technology,
	      const AstDelayModel* delay_model,
	      const AstString* bus_naming_style,
	      const AstString* comment,
	      const AstString* date,
	      const AstString* revision,
	      const AstUnit* capacitive_load_unit,
	      const AstString* current_unit,
	      const AstString* leakage_power_unit,
	      const AstString* pulling_resistance_unit,
	      const AstString* time_unit,
	      const AstString* voltage_unit,
	      const vector<const AstTemplate*>& lut_template_list,
	      const vector<const AstCell*>& cell_list);

  /// @brief セルを表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] name 名前
  /// @param[in] area 面積
  /// @param[in] bus_naming_style 'bus_naming_style' の値
  /// @param[in] pin_top ピンの先頭
  /// @param[in] bus_top バスの先頭
  /// @param[in] bundle_top バンドルの先頭
  /// @param[in] ff FFグループ
  /// @param[in] latch ラッチグループ
  /// @param[in] statetable StateTable グループ
  AstCell*
  new_cell(const FileRegion& loc,
	   const AstString* name,
	   const AstFloat* area,
	   const AstString* bus_naming_style,
	   const vector<const AstPin*>& pin_list,
	   const vector<const AstBus*>& bus_list,
	   const vector<const AstBundle*>& bundle_list,
	   const AstFF* ff,
	   const AstLatch* latch,
	   const AstStateTable* statetable);

  /// @brief ピンを表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] name_list ピン名のリスト
  /// @param[in] pin_direction 方向
  /// @param[in] capacitance 容量
  /// @param[in] rise_capacitance 立ち上がり容量
  /// @param[in] fall_capacitance 立ち下がり容量
  /// @param[in] max_fanout 最大ファンアウト
  /// @param[in] min_fanout 最小ファンアウト
  /// @param[in] max_capacitance 最大容量
  /// @param[in] min_capacitance 最小容量
  /// @param[in] max_transition 最大遷移時間
  /// @param[in] min_transition 最小遷移時間
  /// @param[in] function 関数
  /// @param[in] three_state スリーステート条件
  /// @param[in] internal_node 対応する内部ノード
  /// @param[in] pin_func_type 'pin_func_type'
  /// @param[in] timing_top タイミングの先頭
  AstPin*
  new_pin(const FileRegion& loc,
	  const vector<const AstString*>& name_list,
	  const AstPinDirection* pin_direction,
	  const AstFloat* capacitance,
	  const AstFloat* rise_capacitance,
	  const AstFloat* fall_capacitance,
	  const AstFloat* max_fanout,
	  const AstFloat* min_fanout,
	  const AstFloat* max_capacitance,
	  const AstFloat* min_capacitance,
	  const AstFloat* max_transition,
	  const AstFloat* min_transition,
	  const AstExpr* function,
	  const AstExpr* three_state,
	  const AstNode* internal_node,
	  const AstNode* pin_func_type,
	  const vector<const AstTiming*>& timing_list);


public:
  //////////////////////////////////////////////////////////////////////
  // AstExpr を生成する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief + 演算子を表す AstExpr を生成する．
  /// @param[in] opr1, opr2 オペランド
  AstExpr*
  new_plus(const AstExpr* opr1,
	   const AstExpr* opr2);

  /// @brief - 演算子を表す AstExpr を生成する．
  /// @param[in] opr1, opr2 オペランド
  AstExpr*
  new_minus(const AstExpr* opr1,
	    const AstExpr* opr2);

  /// @brief * 演算子を表す AstExpr を生成する．
  /// @param[in] opr1, opr2 オペランド
  AstExpr*
  new_mult(const AstExpr* opr1,
	   const AstExpr* opr2);

  /// @brief / 演算子を表す AstExpr を生成する．
  /// @param[in] opr1, opr2 オペランド
  AstExpr*
  new_div(const AstExpr* opr1,
	  const AstExpr* opr2);

  /// @brief NOT 演算子を表す AstExpr を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] opr オペランド
  AstExpr*
  new_not(const FileRegion& loc,
	  const AstExpr* opr);

  /// @brief AND 演算子を表す AstExpr を生成する．
  /// @param[in] opr1, opr2 オペランド
  AstExpr*
  new_and(const AstExpr* opr1,
	  const AstExpr* opr2);

  /// @brief OR 演算子を表す AstExpr を生成する．
  /// @param[in] opr1, opr2 オペランド
  AstExpr*
  new_or(const AstExpr* opr1,
	 const AstExpr* opr2);

  /// @brief XOR 演算子を表す AstExpr を生成する．
  /// @param[in] opr1, opr2 オペランド
  AstExpr*
  new_xor(const AstExpr* opr1,
	  const AstExpr* opr2);

  /// @brief ブール値(0 or 1)を表す AstExpr を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] val 値
  AstExpr*
  new_bool_expr(const FileRegion& loc,
		bool val);

  /// @brief 実数値を表す AstExpr を生成する．
  /// @param[in] loc ファイル乗の位置
  /// @param[in] val 値
  AstExpr*
  new_float_expr(const FileRegion& loc,
		 double val);

  /// @brief VDDを表す AstExpr を生成する．
  /// @param[in] loc ファイル上の位置
  AstExpr*
  new_vdd_expr(const FileRegion& loc);

  /// @brief VSSを表す AstExpr を生成する．
  /// @param[in] loc ファイル上の位置
  AstExpr*
  new_vss_expr(const FileRegion& loc);

  /// @brief VCCを表す AstExpr を生成する．
  /// @param[in] loc ファイル上の位置
  AstExpr*
  new_vcc_expr(const FileRegion& loc);

  /// @brief 文字列を表す AstExpr を生成する．
  AstExpr*
  new_str_expr(const FileRegion& loc,
	       const ShString& str);

  /// @brief LUT template を表す AstNode を生成する．
  AstTemplate*
  new_template(const FileRegion& loc,
	       const AstString* name,
	       int dimension,
	       const AstVarType* var_1,
	       const AstVarType* var_2,
	       const AstVarType* var_3,
	       const AstFloatVector* index_1,
	       const AstFloatVector* index_2,
	       const AstFloatVector* index_3);

  /// @brief LUT を表す AstNode を生成する．
  AstLut*
  new_lut(const FileRegion& loc,
	  const AstString* name,
	  const AstFloatVector* index_1,
	  const AstFloatVector* index_2,
	  const AstFloatVector* index_3,
	  const AstFloatVector* value_list);

  /// @brief input voltage を表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] vil 'vil'
  /// @param[in] vih 'vih'
  /// @param[in] vimin 'vimin'
  /// @param[in] vimax 'vimax'
  AstInputVoltage*
  new_input_voltage(const FileRegion& loc,
		    const AstString* name,
		    const AstExpr* vil,
		    const AstExpr* vih,
		    const AstExpr* vimin,
		    const AstExpr* vimax);

  /// @brief output voltage を表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] vol 'voil'
  /// @param[in] voh 'voh'
  /// @param[in] vomin 'vomin'
  /// @param[in] vomax 'vomax'
  AstOutputVoltage*
  new_output_voltage(const FileRegion& loc,
		     const AstString* name,
		     const AstExpr* vol,
		     const AstExpr* voh,
		     const AstExpr* vomin,
		     const AstExpr* vomax);

  /// @brief 汎用のグループ構造を表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value_list 値のリスト
  /// @param[in] attr_top 属性の先頭
  AstGenGroup*
  new_gen_group(const FileRegion& loc,
		const vector<const AstNode*>& value_list,
		const vector<const AstAttr*>& attr_list);

  /// @brief 単位を表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] unit_val 数値
  /// @param[in] unit_str 単位を表す文字列
  AstUnit*
  new_unit(const FileRegion& loc,
	   double unit_val,
	   const ShString& unit_str);

  /// @brief technology を表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  AstTechnology*
  new_technology(const FileRegion& loc,
		 ClibTechnology value);

  /// @brief delay model を表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  AstDelayModel*
  new_delay_model(const FileRegion& loc,
		  ClibDelayModel value);

  /// @brief cell_pin_direction を表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  AstPinDirection*
  new_pin_direction(const FileRegion& loc,
		    ClibCellPinDirection value);

  /// @brief timing を表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] related_pin
  /// @param[in] related_bus_pins
  /// @param[in] related_bus_equivalent
  /// @param[in] timing_sense
  /// @param[in] timing_type
  /// @param[in] when
  /// @param[in] when_start
  /// @param[in] when_end
  /// @param[in] rise_resistance
  /// @param[in] fall_resistance
  /// @param[in] intrinsic_rise
  /// @param[in] intrinsic_fall
  /// @param[in] slope_rise
  /// @param[in] slope_fall
  /// @param[in] rise_delay_intercept
  /// @param[in] fall_delay_intercept
  /// @param[in] rise_pin_resistance
  /// @param[in] fall_pin_resistance
  /// @param[in] cell_degradation
  /// @param[in] cell_rise
  /// @param[in] cell_fall
  /// @param[in] rise_constraint
  /// @param[in] fall_constraint
  /// @param[in] rise_propagation
  /// @param[in] fall_propagation
  /// @param[in] rise_transition
  /// @param[in] fall_transition
  /// @param[in] retaing_rise
  /// @param[in] retaing_fall
  /// @param[in] retain_rise_slew
  /// @param[in] retainfall_slew
  AstTiming*
  new_timing(const FileRegion& loc,
	     const AstString* related_pin,
	     const AstString* related_bus_pins,
	     const AstString* related_bus_equivalent,
	     const AstTimingSense* timing_sense,
	     const AstTimingType* timing_type,
	     const AstExpr* when,
	     const AstExpr* when_start,
	     const AstExpr* when_end,
	     const AstFloat* rise_resistance,
	     const AstFloat* fall_resistance,
	     const AstFloat* intrinsic_rise,
	     const AstFloat* intrinsic_fall,
	     const AstFloat* slope_rise,
	     const AstFloat* slope_fall,
	     const AstPieceWise* rise_delay_intercept,
	     const AstPieceWise* fall_delay_intercept,
	     const AstPieceWise* rise_pin_resistance,
	     const AstPieceWise* fall_pin_resistance,
	     const AstFloat* cell_degradation,
	     const AstLut* cell_rise,
	     const AstLut* cell_fall,
	     const AstLut* rise_constraint,
	     const AstLut* fall_constraint,
	     const AstLut* rise_propagation,
	     const AstLut* fall_propagation,
	     const AstLut* rise_transition,
	     const AstLut* fall_transition,
	     const AstFloat* retaining_rise,
	     const AstFloat* retaining_fall,
	     const AstFloat* retain_rise_slew,
	     const AstFloat* retain_fall_slew);

  /// @brief timing_sense を表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  AstTimingSense*
  new_timing_sense(const FileRegion& loc,
		   ClibTimingSense value);

  /// @brief timing_type を表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  AstTimingType*
  new_timing_type(const FileRegion& loc,
		  ClibTimingType value);

  /// @brief var_type を表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  AstVarType*
  new_var_type(const FileRegion& loc,
	       ClibVarType value);

  /// @brief AstAttr を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] attr_type 属性
  /// @param[in] value 値
  AstAttr*
  new_attr(const FileRegion& loc,
	   AttrType attr_type,
	   const AstNode* value);

  /// @brief 使用メモリ量の一覧を出力する．
  /// @param[in] s 出力先のストリーム
  void
  show_stats(ostream& s) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // メモリアロケータ
  SimpleAlloc mAlloc;

  // 根のノード
  AstLibrary* mLibraryNode;

  // 個々の要素の使用数
  int mIntNum;
  int mFloatNum;
  int mStrNum;
  int mVectNum;
  int mVectElemSize;
  int mOprNum;
  int mNotNum;
  int mBoolExprNum;
  int mFloatExprNum;
  int mSymbolExprNum;
  int mStrExprNum;
  int mListNum;
  int mListElemSize;
  int mTemplateNum;
  int mLutNum;
  int mInputVolNum;
  int mOutputVolNum;
  int mTechnologyNum;
  int mDelayModelNum;
  int mCellPinDirectionNum;
  int mTimingSenseNum;
  int mTimingTypeNum;
  int mVarTypeNum;
  int mAttrNum;
};

END_NAMESPACE_YM_DOTLIB

#endif // ASTMGR_H
