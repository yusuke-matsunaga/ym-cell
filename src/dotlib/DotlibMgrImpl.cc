﻿
/// @file DotlibMgrImpl.cc
/// @brief DotlibMgrImpl の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibMgrImpl.h"
#include "DotlibNodeImpl.h"
#include "DotlibAttr.h"


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
  mListNum = 0;
  mGroupNum = 0;
  mAttrNum = 0;
}

// @brief 整数値を表す DotlibNode を生成する．
// @param[in] value 値
// @param[in] loc ファイル上の位置
DotlibNodeImpl*
DotlibMgrImpl::new_int(int value,
		       const FileRegion& loc)
{
  ++ mIntNum;
  void* p = mAlloc.get_memory(sizeof(DotlibInt));
  DotlibNodeImpl* node = new (p) DotlibInt(value, loc);
  return node;
}

// @brief 実数値を表す DotlibNode を生成する．
// @param[in] value 値
// @param[in] loc ファイル上の位置
DotlibNodeImpl*
DotlibMgrImpl::new_float(double value,
			 const FileRegion& loc)
{
  ++ mFloatNum;
  void* p = mAlloc.get_memory(sizeof(DotlibFloat));
  DotlibNodeImpl* node = new (p) DotlibFloat(value, loc);
  return node;
}

// @brief 定数シンボルを表す DotlibNode を生成する．
// @param[in] value 値
// @param[in] loc ファイル上の位置
DotlibNodeImpl*
DotlibMgrImpl::new_string(ShString value,
			  const FileRegion& loc)
{
  ++ mStrNum;
  void* p = mAlloc.get_memory(sizeof(DotlibString));
  DotlibNodeImpl* node = new (p) DotlibString(value, loc);
  return node;
}

// @brief ベクタを表す DotlibNode を生成する．
// @param[in] value_list 値のリスト
// @param[in] loc ファイル上の位置
DotlibNodeImpl*
DotlibMgrImpl::new_vector(const vector<double>& value_list,
			  const FileRegion& loc)
{
  ++ mVectNum;
  ymuint n = value_list.size();
  void* p = mAlloc.get_memory(sizeof(DotlibVector) + (n - 1) * sizeof(double));
  mVectElemSize += (n - 1);
  DotlibNodeImpl* node = new (p) DotlibVector(value_list, loc);
  return node;
}

// @brief + 演算子を表す DotlibNode を生成する．
// @param[in] opr1, opr2 オペランド
DotlibNodeImpl*
DotlibMgrImpl::new_plus(const DotlibNode* opr1,
			const DotlibNode* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibOpr));
  DotlibNodeImpl* node = new (p) DotlibOpr(DotlibNode::kPlus, opr1, opr2);
  return node;
}

// @brief - 演算子を表す DotlibNode を生成する．
// @param[in] opr1, opr2 オペランド
DotlibNodeImpl*
DotlibMgrImpl::new_minus(const DotlibNode* opr1,
			 const DotlibNode* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibOpr));
  DotlibNodeImpl* node = new (p) DotlibOpr(DotlibNode::kMinus, opr1, opr2);
  return node;
}

// @brief * 演算子を表す DotlibNode を生成する．
// @param[in] opr1, opr2 オペランド
DotlibNodeImpl*
DotlibMgrImpl::new_mult(const DotlibNode* opr1,
			const DotlibNode* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibOpr));
  DotlibNodeImpl* node =  new (p) DotlibOpr(DotlibNode::kMult, opr1, opr2);
  return node;
}

// @brief / 演算子を表す DotlibNode を生成する．
// @param[in] opr1, opr2 オペランド
DotlibNodeImpl*
DotlibMgrImpl::new_div(const DotlibNode* opr1,
		       const DotlibNode* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibOpr));
  DotlibNodeImpl* node = new (p) DotlibOpr(DotlibNode::kDiv, opr1, opr2);
  return node;
}

// @brief NOT 演算子を表す DotlibNode を生成する．
// @param[in] opr オペランド
// @param[in] loc ファイル上の位置
DotlibNodeImpl*
DotlibMgrImpl::new_not(const DotlibNode* opr,
		       const FileRegion& loc)
{
  ++ mNotNum;
  void* p = mAlloc.get_memory(sizeof(DotlibNot));
  DotlibNodeImpl* node = new (p) DotlibNot(opr, loc);
  return node;
}

// @brief AND 演算子を表す DotlibNode を生成する．
// @param[in] opr1, opr2 オペランド
DotlibNodeImpl*
DotlibMgrImpl::new_and(const DotlibNode* opr1,
		       const DotlibNode* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibOpr));
  DotlibNodeImpl* node = new (p) DotlibOpr(DotlibNode::kAnd, opr1, opr2);
  return node;
}

// @brief OR 演算子を表す DotlibNode を生成する．
// @param[in] opr1, opr2 オペランド
DotlibNodeImpl*
DotlibMgrImpl::new_or(const DotlibNode* opr1,
		      const DotlibNode* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibOpr));
  DotlibNodeImpl* node = new (p) DotlibOpr(DotlibNode::kOr, opr1, opr2);
  return node;
}

// @brief XOR 演算子を表す DotlibNode を生成する．
// @param[in] opr1, opr2 オペランド
DotlibNodeImpl*
DotlibMgrImpl::new_xor(const DotlibNode* opr1,
		       const DotlibNode* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(DotlibOpr));
  DotlibNodeImpl* node = new (p) DotlibOpr(DotlibNode::kXor, opr1, opr2);
  return node;
}

// @brief リストを表す DotlibNode を生成する．
DotlibNodeImpl*
DotlibMgrImpl::new_list()
{
  ++ mListNum;
  void* p = mAlloc.get_memory(sizeof(DotlibList));
  DotlibNodeImpl* node =  new (p) DotlibList();
  return node;
}

// @brief グループを表す DotlibNode を生成する．
// @param[in] value 値
// @param[in] loc ファイル上の位置
DotlibNodeImpl*
DotlibMgrImpl::new_group(const DotlibNode* value,
			 const FileRegion& loc)
{
  ++ mGroupNum;
  void* p = mAlloc.get_memory(sizeof(DotlibGroup));
  DotlibNodeImpl* node =  new (p) DotlibGroup(value, loc);
  return node;
}

// @brief DotlibAttr を生成する．
DotlibAttr*
DotlibMgrImpl::new_attr(const ShString& attr_name,
			const DotlibNode* value,
			const FileRegion& loc)
{
  ++ mAttrNum;
  void* p = mAlloc.get_memory(sizeof(DotlibAttr));
  DotlibAttr* attr =  new (p) DotlibAttr(attr_name, value, loc);
  return attr;
}

// @brief 根のノードを設定する．
void
DotlibMgrImpl::set_root_node(DotlibNode* root)
{
  mRoot = root;
}

// @brief 根のノードを返す．
const DotlibNode*
DotlibMgrImpl::root_node() const
{
  return mRoot;
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
    << " x " << setw(3) << sizeof(DotlibVector)
    << " = " << setw(10) << mVectNum * sizeof(DotlibVector) << endl

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

    << "DotlibGroup:        " << setw(7) << mGroupNum
    << " x " << setw(3) << sizeof(DotlibGroup)
    << " = " << setw(10) << mGroupNum * sizeof(DotlibGroup) << endl

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
