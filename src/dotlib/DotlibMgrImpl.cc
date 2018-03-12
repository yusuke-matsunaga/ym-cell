
/// @file DotlibMgrImpl.cc
/// @brief DotlibMgrImpl の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibMgrImpl.h"
#include "dotlib/DotlibInt.h"
#include "dotlib/DotlibFloat.h"
#include "dotlib/DotlibFloatVector.h"
#include "dotlib/DotlibString.h"
#include "dotlib/DotlibCell.h"
#include "dotlib/DotlibPin.h"
#include "dotlib/DotlibExpr.h"
#include "dotlib/DotlibList.h"
#include "dotlib/DotlibTemplate.h"
#include "dotlib/DotlibLut.h"
#include "dotlib/DotlibInputVoltage.h"
#include "dotlib/DotlibOutputVoltage.h"
#include "dotlib/DotlibTechnology.h"
#include "dotlib/DotlibDelayModel.h"
#include "dotlib/DotlibPinDirection.h"
#include "dotlib/DotlibTimingSense.h"
#include "dotlib/DotlibTimingType.h"
#include "dotlib/DotlibUnit.h"
#include "dotlib/DotlibVarType.h"
#include "dotlib/DotlibAttr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibMgrImpl
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
DotlibMgrImpl::DotlibMgrImpl() :
  mAlloc(4096)
{
  clear();
}

// @brief デストラクタ
DotlibMgrImpl::~DotlibMgrImpl()
{
}

// @brief 初期化する．
// @note 以前，生成されたオブジェクトは破壊される．
void
DotlibMgrImpl::clear()
{
  mAlloc.destroy();

  mIntNum = 0;
  mFloatNum = 0;
  mStrNum = 0;
  mVectNum = 0;
  mVectElemSize = 0;
  mOprNum = 0;
  mNotNum = 0;
  mBoolExprNum = 0;
  mFloatExprNum = 0;
  mSymbolExprNum = 0;
  mStrExprNum = 0;
  mListNum = 0;
  mListElemSize = 0;
  mTechnologyNum = 0;
  mDelayModelNum = 0;
  mCellPinDirectionNum = 0;
  mTimingSenseNum = 0;
  mTimingTypeNum = 0;
  mVarTypeNum = 0;
  mAttrNum = 0;
}

// @brief 整数値を表す DotlibNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
DotlibNode*
DotlibMgrImpl::new_int(const FileRegion& loc,
		       int value)
{
  ++ mIntNum;
  void* p = mAlloc.get_memory(sizeof(DotlibInt));
  return new (p) DotlibInt(loc, value);
}

// @brief 実数値を表す DotlibNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
DotlibNode*
DotlibMgrImpl::new_float(const FileRegion& loc,
			 double value)
{
  ++ mFloatNum;
  void* p = mAlloc.get_memory(sizeof(DotlibFloat));
  return new (p) DotlibFloat(loc, value);
}

// @brief 予約語シンボルを表す DotlibNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] token_type トークンの種類
DotlibNode*
DotlibMgrImpl::new_symbol(const FileRegion& loc,
			  TokenType token_type)
{
  return nullptr;
}

// @brief 定数シンボルを表す DotlibNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
DotlibNode*
DotlibMgrImpl::new_string(const FileRegion& loc,
			  ShString value)
{
  ++ mStrNum;
  void* p = mAlloc.get_memory(sizeof(DotlibString));
  return new (p) DotlibString(loc, value);
}

// @brief ベクタを表す DotlibNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value_list 値のリスト
DotlibNode*
DotlibMgrImpl::new_vector(const FileRegion& loc,
			  const vector<double>& value_list)
{
  int n = value_list.size();
  ++ mVectNum;
  mVectElemSize += (n - 1);
  void* p = mAlloc.get_memory(sizeof(DotlibFloatVector) + (n - 1) * sizeof(double));
  return new (p) DotlibFloatVector(loc, value_list);
}

// @brief セルを表す DotlibNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] name 名前
// @param[in] area 面積
// @param[in] bus_naming_style 'bus_naming_style' の値
// @param[in] pin_top ピンの先頭
// @param[in] bus_top バスの先頭
// @param[in] bundle_top バンドルの先頭
// @param[in] ff FFグループ
// @param[in] latch ラッチグループ
// @param[in] statetable StateTable グループ
DotlibNode*
DotlibMgrImpl::new_cell(const FileRegion& loc,
			const DotlibString* name,
			const DotlibFloat* area,
			const DotlibString* bus_naming_style,
			const DotlibPin* pin_top,
			const DotlibBus* bus_top,
			const DotlibBundle* bundle_top,
			const DotlibFF* ff,
			const DotlibLatch* latch,
			const DotlibStateTable* statetable)
{
  void* p = mAlloc.get_memory(sizeof(DotlibCell));
  return new (p) DotlibCell(loc,name, area, bus_naming_style,
			    pin_top, bus_top, bundle_top,
			    ff, latch, statetable);
}

// @brief ピンを表す DotlibNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] pin_direction 方向
// @param[in] capacitance 容量
// @param[in] rise_capacitance 立ち上がり容量
// @param[in] fall_capacitance 立ち下がり容量
// @param[in] max_fanout 最大ファンアウト
// @param[in] min_fanout 最小ファンアウト
// @param[in] max_capacitance 最大容量
// @param[in] min_capacitance 最小容量
// @param[in] max_transition 最大遷移時間
// @param[in] min_transition 最小遷移時間
// @param[in] function 関数
// @param[in] three_state スリーステート条件
// @param[in] internal_node 対応する内部ノード
// @param[in] pin_func_type 'pin_func_type'
// @param[in] timing_top タイミングの先頭
DotlibNode*
DotlibMgrImpl::new_pin(const FileRegion& loc,
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
		       const DotlibTiming* timing_top)
{
  void* p = mAlloc.get_memory(sizeof(DotlibPin));
  return new (p) DotlibPin(loc, pin_direction,
			   capacitance, rise_capacitance, fall_capacitance,
			   max_fanout, min_fanout,
			   max_capacitance, min_capacitance,
			   max_transition, min_transition,
			   function, three_state,
			   internal_node, pin_func_type, timing_top);
}

// @brief + 演算子を表す DotlibExpr を生成する．
// @param[in] opr1, opr2 オペランド
DotlibExpr*
DotlibMgrImpl::new_plus(const DotlibExpr* opr1,
			const DotlibExpr* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibOpr));
  return new (p) DotlibOpr(DotlibExprType::kPlus, opr1, opr2);
}

// @brief - 演算子を表す DotlibExpr を生成する．
// @param[in] opr1, opr2 オペランド
DotlibExpr*
DotlibMgrImpl::new_minus(const DotlibExpr* opr1,
			 const DotlibExpr* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibOpr));
  return new (p) DotlibOpr(DotlibExprType::kMinus, opr1, opr2);
}

// @brief * 演算子を表す DotlibExpr を生成する．
// @param[in] opr1, opr2 オペランド
DotlibExpr*
DotlibMgrImpl::new_mult(const DotlibExpr* opr1,
			const DotlibExpr* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibOpr));
  return new (p) DotlibOpr(DotlibExprType::kMult, opr1, opr2);
}

// @brief / 演算子を表す DotlibExpr を生成する．
// @param[in] opr1, opr2 オペランド
DotlibExpr*
DotlibMgrImpl::new_div(const DotlibExpr* opr1,
		       const DotlibExpr* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibOpr));
  return new (p) DotlibOpr(DotlibExprType::kDiv, opr1, opr2);
}

// @brief NOT 演算子を表す DotlibExpr を生成する．
// @param[in] loc ファイル上の位置
// @param[in] opr オペランド
DotlibExpr*
DotlibMgrImpl::new_not(const FileRegion& loc,
		       const DotlibExpr* opr)
{
  ++ mNotNum;
  void* p = mAlloc.get_memory(sizeof(DotlibNot));
  return new (p) DotlibNot(loc, opr);
}

// @brief AND 演算子を表す DotlibExpr を生成する．
// @param[in] opr1, opr2 オペランド
DotlibExpr*
DotlibMgrImpl::new_and(const DotlibExpr* opr1,
		       const DotlibExpr* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibOpr));
  return new (p) DotlibOpr(DotlibExprType::kAnd, opr1, opr2);
}

// @brief OR 演算子を表す DotlibExpr を生成する．
// @param[in] opr1, opr2 オペランド
DotlibExpr*
DotlibMgrImpl::new_or(const DotlibExpr* opr1,
		      const DotlibExpr* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibOpr));
  return new (p) DotlibOpr(DotlibExprType::kOr, opr1, opr2);
}

// @brief XOR 演算子を表す DotlibExpr を生成する．
// @param[in] opr1, opr2 オペランド
DotlibExpr*
DotlibMgrImpl::new_xor(const DotlibExpr* opr1,
		       const DotlibExpr* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibOpr));
  return new (p) DotlibOpr(DotlibExprType::kXor, opr1, opr2);
}

// @brief ブール値(0 or 1)を表す DotlibExpr を生成する．
// @param[in] loc ファイル上の位置
// @param[in] val 値
DotlibExpr*
DotlibMgrImpl::new_bool_expr(const FileRegion& loc,
			     bool val)
{
  ++ mBoolExprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibBoolExpr));
  return new (p) DotlibBoolExpr(loc, val);
}

// @brief 実数値を表す DotlibExpr を生成する．
// @param[in] loc ファイル乗の位置
// @param[in] val 値
DotlibExpr*
DotlibMgrImpl::new_float_expr(const FileRegion& loc,
			      double val)
{
  ++ mFloatExprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibFloatExpr));
  return new (p) DotlibFloatExpr(loc, val);
}

// @brief VDDを表す DotlibExpr を生成する．
// @param[in] loc ファイル上の位置
DotlibExpr*
DotlibMgrImpl::new_vdd_expr(const FileRegion& loc)
{
  ++ mSymbolExprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibSymbolExpr));
  return new (p) DotlibSymbolExpr(loc, DotlibExprType::kVDD);
}

// @brief VSSを表す DotlibExpr を生成する．
// @param[in] loc ファイル上の位置
DotlibExpr*
DotlibMgrImpl::new_vss_expr(const FileRegion& loc)
{
  ++ mSymbolExprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibSymbolExpr));
  return new (p) DotlibSymbolExpr(loc, DotlibExprType::kVSS);
}

// @brief VCCを表す DotlibExpr を生成する．
// @param[in] loc ファイル上の位置
DotlibExpr*
DotlibMgrImpl::new_vcc_expr(const FileRegion& loc)
{
  ++ mSymbolExprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibSymbolExpr));
  return new (p) DotlibSymbolExpr(loc, DotlibExprType::kVCC);
}

// @brief 文字列を表す DotlibExpr を生成する．
DotlibExpr*
DotlibMgrImpl::new_str_expr(const FileRegion& loc,
			    const ShString& str)
{
  ++ mStrExprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibStrExpr));
  return new (p) DotlibStrExpr(loc, str);
}

// @brief リストを表す DotlibNode を生成する．
DotlibList*
DotlibMgrImpl::new_list(const vector<DotlibNode*>& elem_list)
{
  int n = elem_list.size();
  ++ mListNum;
  mListElemSize += (n - 1);
  void* p = mAlloc.get_memory(sizeof(DotlibList) + sizeof(const DotlibNode*) * (n - 1));
  return new (p) DotlibList(elem_list);
}

// @brief LUT template を表す DotlibNode を生成する．
DotlibTemplate*
DotlibMgrImpl::new_template(const FileRegion& loc,
			    const DotlibString* name,
			    int dimension,
			    const DotlibVarType* var_1,
			    const DotlibVarType* var_2,
			    const DotlibVarType* var_3,
			    const DotlibFloatVector* index_1,
			    const DotlibFloatVector* index_2,
			    const DotlibFloatVector* index_3)
{
  ++ mTemplateNum;
  void* p = mAlloc.get_memory(sizeof(DotlibTemplate));
  return new (p) DotlibTemplate(loc, name, dimension, var_1, var_2, var_3, index_1, index_2, index_3);
}

// @brief LUT を表す DotlibNode を生成する．
DotlibLut*
DotlibMgrImpl::new_lut(const FileRegion& loc,
		       const DotlibString* name,
		       const DotlibFloatVector* index_1,
		       const DotlibFloatVector* index_2,
		       const DotlibFloatVector* index_3,
		       const DotlibList* value_list)
{
  ++ mLutNum;
  void* p = mAlloc.get_memory(sizeof(DotlibLut));
  return new (p) DotlibLut(loc, name, index_1, index_2, index_3, value_list);
}

// @brief input voltage を表す DotlibNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] vil 'vil'
// @param[in] vih 'vih'
// @param[in] vimin 'vimin'
// @param[in] vimax 'vimax'
DotlibInputVoltage*
DotlibMgrImpl::new_input_voltage(const FileRegion& loc,
				 const DotlibString* name,
				 const DotlibExpr* vil,
				 const DotlibExpr* vih,
				 const DotlibExpr* vimin,
				 const DotlibExpr* vimax)
{
  ++ mInputVolNum;
  void* p = mAlloc.get_memory(sizeof(DotlibInputVoltage));
  return new (p) DotlibInputVoltage(loc, name, vil, vih, vimin, vimax);
}

// @brief output voltage を表す DotlibNode を生成する．．
// @param[in] loc ファイル上の位置
// @param[in] vol 'voil'
// @param[in] voh 'voh'
// @param[in] vomin 'vomin'
// @param[in] vomax 'vomax'
DotlibOutputVoltage*
DotlibMgrImpl::new_output_voltage(const FileRegion& loc,
				  const DotlibString* name,
				  const DotlibExpr* vol,
				  const DotlibExpr* voh,
				  const DotlibExpr* vomin,
				  const DotlibExpr* vomax)
{
  ++ mOutputVolNum;
  void* p = mAlloc.get_memory(sizeof(DotlibOutputVoltage));
  return new (p) DotlibOutputVoltage(loc, name, vol, voh, vomin, vomax);
}

// @brief 汎用のグループ構造を表す DotlibNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value_list 値のリスト
// @param[in] attr_top 属性の先頭
DotlibGenGroup*
DotlibMgrImpl::new_gen_group(const FileRegion& loc,
			     const vector<DotlibNode*>& value_list,
			     const vector<DotlibAttr*>& attr_list)
{
#warning "TODO: 未完成"
  return nullptr;
}

// @brief 単位を表す DotlibNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] unit_val 数値
// @param[in] unit_str 単位を表す文字列
DotlibUnit*
DotlibMgrImpl::new_unit(const FileRegion& loc,
			double unit_val,
			const ShString& unit_str)
{
  void* p = mAlloc.get_memory(sizeof(DotlibUnit));
  return new (p) DotlibUnit(loc, unit_val, unit_str);
}

// @brief technology を表す DotlibNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
DotlibTechnology*
DotlibMgrImpl::new_technology(const FileRegion& loc,
			      ClibTechnology value)
{
  ++ mTechnologyNum;
  void* p = mAlloc.get_memory(sizeof(DotlibTechnology));
  return new (p) DotlibTechnology(loc, value);
}

// @brief delay model を表す DotlibNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
DotlibDelayModel*
DotlibMgrImpl::new_delay_model(const FileRegion& loc,
			       ClibDelayModel value)
{
  ++ mDelayModelNum;
  void* p = mAlloc.get_memory(sizeof(DotlibDelayModel));
  return new (p) DotlibDelayModel(loc, value);
}

// @brief cell_pin_direction を表す DotlibNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
DotlibPinDirection*
DotlibMgrImpl::new_cell_pin_direction(const FileRegion& loc,
				      ClibCellPinDirection value)
{
  ++ mCellPinDirectionNum;
  void* p = mAlloc.get_memory(sizeof(DotlibPinDirection));
  return new (p) DotlibPinDirection(loc, value);
}

// @brief timing_sense を表す DotlibNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
DotlibTimingSense*
DotlibMgrImpl::new_timing_sense(const FileRegion& loc,
				ClibTimingSense value)
{
  ++ mTimingSenseNum;
  void* p = mAlloc.get_memory(sizeof(DotlibTimingSense));
  return new (p) DotlibTimingSense(loc, value);
}

// @brief timing_type を表す DotlibNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
DotlibTimingType*
DotlibMgrImpl::new_timing_type(const FileRegion& loc,
			       ClibTimingType value)
{
  ++ mTimingTypeNum;
  void* p = mAlloc.get_memory(sizeof(DotlibTimingType));
  return new (p) DotlibTimingType(loc, value);
}

// @brief var_type を表す DotlibNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
DotlibVarType*
DotlibMgrImpl::new_var_type(const FileRegion& loc,
			    ClibVarType value)
{
  ++ mVarTypeNum;
  void* p = mAlloc.get_memory(sizeof(DotlibVarType));
  return new (p) DotlibVarType(loc, value);
}

// @brief DotlibAttr を生成する．
DotlibAttr*
DotlibMgrImpl::new_attr(const FileRegion& loc,
			AttrType attr_type,
			const DotlibNode* value)
{
  ++ mAttrNum;
  void* p = mAlloc.get_memory(sizeof(DotlibAttr));
  return new (p) DotlibAttr(loc, attr_type, value);
}

// @brief 使用メモリ量の一覧を出力する．
// @param[in] s 出力先のストリーム
void
DotlibMgrImpl::show_stats(ostream& s) const
{
  s << "DotlibInt:          " << setw(7) << mIntNum
    << " x " << setw(3) << sizeof(DotlibInt)
    << " = " << setw(10) << mIntNum * sizeof(DotlibInt) << endl

    << "DotlibFloat:        " << setw(7) << mFloatNum
    << " x " << setw(3) << sizeof(DotlibFloat)
    << " = " << setw(10) << mFloatNum * sizeof(DotlibFloat) << endl

    << "DotlibString:       " << setw(7) << mStrNum
    << " x " << setw(3) << sizeof(DotlibString)
    << " = " << setw(10) << mStrNum * sizeof(DotlibString) << endl

    << "DotlibVector:       " << setw(7) << mVectNum
    << " x " << setw(3) << sizeof(DotlibFloatVector)
    << " = " << setw(10) << mVectNum * sizeof(DotlibFloatVector) << endl

    << "Vector Elements:    " << setw(7) << mVectElemSize
    << " x " << setw(3) << sizeof(double)
    << " = " << setw(10) << mVectElemSize * sizeof(double) << endl

    << "DotlibOpr:          " << setw(7) << mOprNum
    << " x " << setw(3) << sizeof(DotlibOpr)
    << " = " << setw(10) << mOprNum * sizeof(DotlibOpr) << endl

    << "DotlibNot:          " << setw(7) << mNotNum
    << " x " << setw(3) << sizeof(DotlibNot)
    << " = " << setw(10) << mNotNum * sizeof(DotlibNot) << endl

    << "DotlibList:         " << setw(7) << mListNum
    << " x " << setw(3) << sizeof(DotlibList)
    << " = " << setw(10) << mListNum * sizeof(DotlibList) << endl

    << "DotlibAttr:         " << setw(7) << mAttrNum
    << " x " << setw(3) << sizeof(DotlibAttr)
    << " = " << setw(10) << mAttrNum * sizeof(DotlibAttr) << endl

    << "Total memory:                     = "
    << setw(10) << mAlloc.used_size() << endl
    << endl

    << "Allocated memory:                 = "
    << setw(10) << mAlloc.allocated_size() << endl

    << "ShString:                         = "
    << setw(10) << ShString::allocated_size() << endl;
}

END_NAMESPACE_YM_DOTLIB
