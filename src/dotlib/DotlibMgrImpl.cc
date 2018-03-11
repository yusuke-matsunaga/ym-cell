
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
#include "dotlib/DotlibExpr.h"
#include "dotlib/DotlibList.h"
#include "dotlib/DotlibTechnology.h"
#include "dotlib/DotlibDelayModel.h"
#include "dotlib/DotlibPinDirection.h"
#include "dotlib/DotlibTimingSense.h"
#include "dotlib/DotlibTimingType.h"
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

// @brief + 演算子を表す DotlibExpr を生成する．
// @param[in] opr1, opr2 オペランド
DotlibExpr*
DotlibMgrImpl::new_plus(const DotlibExpr* opr1,
			const DotlibExpr* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibOpr));
  return new (p) DotlibOpr(DotlibExpr::kPlus, opr1, opr2);
}

// @brief - 演算子を表す DotlibExpr を生成する．
// @param[in] opr1, opr2 オペランド
DotlibExpr*
DotlibMgrImpl::new_minus(const DotlibExpr* opr1,
			 const DotlibExpr* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibOpr));
  return new (p) DotlibOpr(DotlibExpr::kMinus, opr1, opr2);
}

// @brief * 演算子を表す DotlibExpr を生成する．
// @param[in] opr1, opr2 オペランド
DotlibExpr*
DotlibMgrImpl::new_mult(const DotlibExpr* opr1,
			const DotlibExpr* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibOpr));
  return new (p) DotlibOpr(DotlibExpr::kMult, opr1, opr2);
}

// @brief / 演算子を表す DotlibExpr を生成する．
// @param[in] opr1, opr2 オペランド
DotlibExpr*
DotlibMgrImpl::new_div(const DotlibExpr* opr1,
		       const DotlibExpr* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibOpr));
  return new (p) DotlibOpr(DotlibExpr::kDiv, opr1, opr2);
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
  return new (p) DotlibOpr(DotlibExpr::kAnd, opr1, opr2);
}

// @brief OR 演算子を表す DotlibExpr を生成する．
// @param[in] opr1, opr2 オペランド
DotlibExpr*
DotlibMgrImpl::new_or(const DotlibExpr* opr1,
		      const DotlibExpr* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibOpr));
  return new (p) DotlibOpr(DotlibExpr::kOr, opr1, opr2);
}

// @brief XOR 演算子を表す DotlibExpr を生成する．
// @param[in] opr1, opr2 オペランド
DotlibExpr*
DotlibMgrImpl::new_xor(const DotlibExpr* opr1,
		       const DotlibExpr* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibOpr));
  return new (p) DotlibOpr(DotlibExpr::kXor, opr1, opr2);
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
  return new (p) DotlibSymbolExpr(loc, DotlibExpr::kVDD);
}

// @brief VSSを表す DotlibExpr を生成する．
// @param[in] loc ファイル上の位置
DotlibExpr*
DotlibMgrImpl::new_vss_expr(const FileRegion& loc)
{
  ++ mSymbolExprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibSymbolExpr));
  return new (p) DotlibSymbolExpr(loc, DotlibExpr::kVSS);
}

// @brief VCCを表す DotlibExpr を生成する．
// @param[in] loc ファイル上の位置
DotlibExpr*
DotlibMgrImpl::new_vcc_expr(const FileRegion& loc)
{
  ++ mSymbolExprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibSymbolExpr));
  return new (p) DotlibSymbolExpr(loc, DotlibExpr::kVCC);
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
DotlibMgrImpl::new_list(const vector<const DotlibNode*>& elem_list)
{
  int n = elem_list.size();
  ++ mListNum;
  mListElemSize += (n - 1);
  void* p = mAlloc.get_memory(sizeof(DotlibList) + sizeof(const DotlibNode*) * (n - 1));
  return new (p) DotlibList(elem_list);
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
