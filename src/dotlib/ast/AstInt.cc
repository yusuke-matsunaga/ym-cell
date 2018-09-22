
/// @file AstInt.cc
/// @brief AstInt の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstInt.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 整数値を表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
const AstInt*
AstMgr::new_int(const FileRegion& loc,
		int value)
{
  ++ mIntNum;
  void* p = mAlloc.get_memory(sizeof(AstInt));
  return new (p) AstInt(loc, value);
}


//////////////////////////////////////////////////////////////////////
/// クラス AstInt
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
AstInt::AstInt(const FileRegion& loc,
	       int value) :
  AstNode(loc),
  mValue(value)
{
}

// @brief デストラクタ
AstInt::~AstInt()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstInt::dump(ostream& s,
	     int indent) const
{
  s << value();
}

END_NAMESPACE_YM_DOTLIB
