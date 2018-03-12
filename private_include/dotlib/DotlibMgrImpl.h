#ifndef DOTLIBMGRIMPL_H
#define DOTLIBMGRIMPL_H

/// @file DotlibMgrImpl.h
/// @brief DotlibMgrImpl のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/dotlib_int.h"
#include "dotlib/AttrType.h"
#include "ym/ShString.h"
#include "ym/FileRegion.h"
#include "ym/SimpleAlloc.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibMgrImpl DotlibMgrImpl.h "DotlibMgrImpl.h"
/// @brief DotlibMgr の実装クラス
//////////////////////////////////////////////////////////////////////
class DotlibMgrImpl
{
public:

  /// @brief コンストラクタ
  DotlibMgrImpl();

  /// @brief デストラクタ
  ~DotlibMgrImpl();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 初期化する．
  /// @note 以前，生成されたオブジェクトは破壊される．
  void
  clear();

  /// @brief 整数値を表す DotlibNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  DotlibNode*
  new_int(const FileRegion& loc,
	  int value);

  /// @brief 実数値を表す DotlibNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  DotlibNode*
  new_float(const FileRegion& loc,
	    double value);

  /// @brief 予約語シンボルを表す DotlibNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] token_type トークンの種類
  DotlibNode*
  new_symbol(const FileRegion& loc,
	     TokenType token_type);

  /// @brief 文字列シンボルを表す DotlibNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  DotlibNode*
  new_string(const FileRegion& loc,
	     ShString value);

  /// @brief ベクタを表す DotlibNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value_list 値のリスト
  DotlibNode*
  new_vector(const FileRegion& loc,
	     const vector<double>& value_list);

  /// @brief セルを表す DotlibNode を生成する．
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
  DotlibNode*
  new_cell(const FileRegion& loc,
	   const DotlibString* name,
	   const DotlibFloat* area,
	   const DotlibString* bus_naming_style,
	   const DotlibPin* pin_top,
	   const DotlibBus* bus_top,
	   const DotlibBundle* bundle_top,
	   const DotlibFF* ff,
	   const DotlibLatch* latch,
	   const DotlibStateTable* statetable);

  /// @brief ピンを表す DotlibNode を生成する．
  /// @param[in] loc ファイル上の位置
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
  DotlibNode*
  new_pin(const FileRegion& loc,
	  const DotlibPinDirection* pin_direction,
	  const DotlibFloat* capacitance,
	  const DotlibFloat* rise_capacitance,
	  const DotlibFloat* fall_capacitance,
	  const DotlibFloat* max_fanout,
	  const DotlibFloat* min_fanout,
	  const DotlibFloat* max_capacitance,
	  const DotlibFloat* min_capacitance,
	  const DotlibFloat* max_transition,
	  const DotlibFloat* min_transition,
	  const DotlibExpr* function,
	  const DotlibExpr* three_state,
	  const DotlibNode* internal_node,
	  const DotlibNode* pin_func_type,
	  const DotlibTiming* timing_top);


public:
  //////////////////////////////////////////////////////////////////////
  // DotlibExpr を生成する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief + 演算子を表す DotlibExpr を生成する．
  /// @param[in] opr1, opr2 オペランド
  DotlibExpr*
  new_plus(const DotlibExpr* opr1,
	   const DotlibExpr* opr2);

  /// @brief - 演算子を表す DotlibExpr を生成する．
  /// @param[in] opr1, opr2 オペランド
  DotlibExpr*
  new_minus(const DotlibExpr* opr1,
	    const DotlibExpr* opr2);

  /// @brief * 演算子を表す DotlibExpr を生成する．
  /// @param[in] opr1, opr2 オペランド
  DotlibExpr*
  new_mult(const DotlibExpr* opr1,
	   const DotlibExpr* opr2);

  /// @brief / 演算子を表す DotlibExpr を生成する．
  /// @param[in] opr1, opr2 オペランド
  DotlibExpr*
  new_div(const DotlibExpr* opr1,
	  const DotlibExpr* opr2);

  /// @brief NOT 演算子を表す DotlibExpr を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] opr オペランド
  DotlibExpr*
  new_not(const FileRegion& loc,
	  const DotlibExpr* opr);

  /// @brief AND 演算子を表す DotlibExpr を生成する．
  /// @param[in] opr1, opr2 オペランド
  DotlibExpr*
  new_and(const DotlibExpr* opr1,
	  const DotlibExpr* opr2);

  /// @brief OR 演算子を表す DotlibExpr を生成する．
  /// @param[in] opr1, opr2 オペランド
  DotlibExpr*
  new_or(const DotlibExpr* opr1,
	 const DotlibExpr* opr2);

  /// @brief XOR 演算子を表す DotlibExpr を生成する．
  /// @param[in] opr1, opr2 オペランド
  DotlibExpr*
  new_xor(const DotlibExpr* opr1,
	  const DotlibExpr* opr2);

  /// @brief ブール値(0 or 1)を表す DotlibExpr を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] val 値
  DotlibExpr*
  new_bool_expr(const FileRegion& loc,
		bool val);

  /// @brief 実数値を表す DotlibExpr を生成する．
  /// @param[in] loc ファイル乗の位置
  /// @param[in] val 値
  DotlibExpr*
  new_float_expr(const FileRegion& loc,
		 double val);

  /// @brief VDDを表す DotlibExpr を生成する．
  /// @param[in] loc ファイル上の位置
  DotlibExpr*
  new_vdd_expr(const FileRegion& loc);

  /// @brief VSSを表す DotlibExpr を生成する．
  /// @param[in] loc ファイル上の位置
  DotlibExpr*
  new_vss_expr(const FileRegion& loc);

  /// @brief VCCを表す DotlibExpr を生成する．
  /// @param[in] loc ファイル上の位置
  DotlibExpr*
  new_vcc_expr(const FileRegion& loc);

  /// @brief 文字列を表す DotlibExpr を生成する．
  DotlibExpr*
  new_str_expr(const FileRegion& loc,
	       const ShString& str);

  /// @brief リストを表す DotlibNode を生成する．
  /// @param[in] elem_list 要素のリスト
  DotlibList*
  new_list(const vector<DotlibNode*>& elem_list);

  /// @brief LUT template を表す DotlibNode を生成する．
  DotlibTemplate*
  new_template(const FileRegion& loc,
	       const DotlibString* name,
	       int dimension,
	       const DotlibVarType* var_1,
	       const DotlibVarType* var_2,
	       const DotlibVarType* var_3,
	       const DotlibFloatVector* index_1,
	       const DotlibFloatVector* index_2,
	       const DotlibFloatVector* index_3);

  /// @brief LUT を表す DotlibNode を生成する．
  DotlibLut*
  new_lut(const FileRegion& loc,
	  const DotlibString* name,
	  const DotlibFloatVector* index_1,
	  const DotlibFloatVector* index_2,
	  const DotlibFloatVector* index_3,
	  const DotlibFloatVector* value_list);

  /// @brief input voltage を表す DotlibNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] vil 'vil'
  /// @param[in] vih 'vih'
  /// @param[in] vimin 'vimin'
  /// @param[in] vimax 'vimax'
  DotlibInputVoltage*
  new_input_voltage(const FileRegion& loc,
		    const DotlibString* name,
		    const DotlibExpr* vil,
		    const DotlibExpr* vih,
		    const DotlibExpr* vimin,
		    const DotlibExpr* vimax);

  /// @brief output voltage を表す DotlibNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] vol 'voil'
  /// @param[in] voh 'voh'
  /// @param[in] vomin 'vomin'
  /// @param[in] vomax 'vomax'
  DotlibOutputVoltage*
  new_output_voltage(const FileRegion& loc,
		     const DotlibString* name,
		     const DotlibExpr* vol,
		     const DotlibExpr* voh,
		     const DotlibExpr* vomin,
		     const DotlibExpr* vomax);

  /// @brief 汎用のグループ構造を表す DotlibNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value_list 値のリスト
  /// @param[in] attr_top 属性の先頭
  DotlibGenGroup*
  new_gen_group(const FileRegion& loc,
		const vector<DotlibNode*>& value_list,
		const vector<DotlibAttr*>& attr_list);

  /// @brief 単位を表す DotlibNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] unit_val 数値
  /// @param[in] unit_str 単位を表す文字列
  DotlibUnit*
  new_unit(const FileRegion& loc,
	   double unit_val,
	   const ShString& unit_str);

  /// @brief technology を表す DotlibNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  DotlibTechnology*
  new_technology(const FileRegion& loc,
		 ClibTechnology value);

  /// @brief delay model を表す DotlibNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  DotlibDelayModel*
  new_delay_model(const FileRegion& loc,
		  ClibDelayModel value);

  /// @brief cell_pin_direction を表す DotlibNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  DotlibPinDirection*
  new_cell_pin_direction(const FileRegion& loc,
			 ClibCellPinDirection value);

  /// @brief timing_sense を表す DotlibNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  DotlibTimingSense*
  new_timing_sense(const FileRegion& loc,
		   ClibTimingSense value);

  /// @brief timing_type を表す DotlibNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  DotlibTimingType*
  new_timing_type(const FileRegion& loc,
		  ClibTimingType value);

  /// @brief var_type を表す DotlibNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  DotlibVarType*
  new_var_type(const FileRegion& loc,
	       ClibVarType value);

  /// @brief DotlibAttr を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] attr_type 属性
  /// @param[in] value 値
  DotlibAttr*
  new_attr(const FileRegion& loc,
	   AttrType attr_type,
	   const DotlibNode* value);

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

#endif // DOTLIBMGRIMPL_H
