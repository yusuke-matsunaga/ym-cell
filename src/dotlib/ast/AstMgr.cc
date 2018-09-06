
/// @file AstMgr.cc
/// @brief AstMgr の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstAttr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstMgr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstMgr::AstMgr() :
  mAlloc(4096)
{
  clear();
}

// @brief デストラクタ
AstMgr::~AstMgr()
{
}

// @brief 初期化する．
// @note 以前，生成されたオブジェクトは破壊される．
void
AstMgr::clear()
{
  mAlloc.destroy();

  mLibraryNode = nullptr;

  mIntNum = 0;
  mFloatNum = 0;
  mStrNum = 0;
  mVectNum = 0;
  mVectElemSize = 0;
  mBoolNum = 0;
  mOprNum = 0;
  mNotNum = 0;
  mBoolExprNum = 0;
  mDomainNum = 0;
  mFloatExprNum = 0;
  mSymbolExprNum = 0;
  mStrExprNum = 0;
  mListNum = 0;
  mListElemSize = 0;
  mTemplateNum = 0;
  mLutNum = 0;
  mInputVolNum = 0;
  mOutputVolNum = 0;
  mPieceWiseNum = 0;
  mTechnologyNum = 0;
  mDelayModelNum = 0;
  mCellPinDirectionNum = 0;
  mTimingSenseNum = 0;
  mTimingTypeNum = 0;
  mVarTypeNum = 0;
  mVarRangeNum = 0;
  mAttrNum = 0;
}

// @brief 根のノードを返す．
const AstLibrary*
AstMgr::library_node() const
{
  return mLibraryNode;
}

// @brief AstAttr を生成する．
AstAttr*
AstMgr::new_attr(const FileRegion& loc,
			AttrType attr_type,
			const AstNode* value)
{
  ++ mAttrNum;
  void* p = mAlloc.get_memory(sizeof(AstAttr));
  return new (p) AstAttr(loc, attr_type, value);
}

// @brief 使用メモリ量の一覧を出力する．
// @param[in] s 出力先のストリーム
void
AstMgr::show_stats(ostream& s) const
{
#if 0
  s << "AstInt:          " << setw(7) << mIntNum
    << " x " << setw(3) << sizeof(AstInt)
    << " = " << setw(10) << mIntNum * sizeof(AstInt) << endl

    << "AstFloat:        " << setw(7) << mFloatNum
    << " x " << setw(3) << sizeof(AstFloat)
    << " = " << setw(10) << mFloatNum * sizeof(AstFloat) << endl

    << "AstString:       " << setw(7) << mStrNum
    << " x " << setw(3) << sizeof(AstString)
    << " = " << setw(10) << mStrNum * sizeof(AstString) << endl

    << "AstVector:       " << setw(7) << mVectNum
    << " x " << setw(3) << sizeof(AstFloatVector)
    << " = " << setw(10) << mVectNum * sizeof(AstFloatVector) << endl

    << "Vector Elements:    " << setw(7) << mVectElemSize
    << " x " << setw(3) << sizeof(double)
    << " = " << setw(10) << mVectElemSize * sizeof(double) << endl

    << "AstOpr:          " << setw(7) << mOprNum
    << " x " << setw(3) << sizeof(AstOpr)
    << " = " << setw(10) << mOprNum * sizeof(AstOpr) << endl

    << "AstNot:          " << setw(7) << mNotNum
    << " x " << setw(3) << sizeof(AstNot)
    << " = " << setw(10) << mNotNum * sizeof(AstNot) << endl

    << "AstList:         " << setw(7) << mListNum
    << " x " << setw(3) << sizeof(AstList)
    << " = " << setw(10) << mListNum * sizeof(AstList) << endl

    << "AstAttr:         " << setw(7) << mAttrNum
    << " x " << setw(3) << sizeof(AstAttr)
    << " = " << setw(10) << mAttrNum * sizeof(AstAttr) << endl

    << "Total memory:                     = "
    << setw(10) << mAlloc.used_size() << endl
    << endl

    << "Allocated memory:                 = "
    << setw(10) << mAlloc.allocated_size() << endl

    << "ShString:                         = "
    << setw(10) << ShString::allocated_size() << endl;
#endif
}

END_NAMESPACE_YM_DOTLIB
