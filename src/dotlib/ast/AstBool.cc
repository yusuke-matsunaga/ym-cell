
/// @file AstBool.cc
/// @brief AstBool の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstBool.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief ブール値を表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
AstBool*
AstMgr::new_bool(const FileRegion& loc,
		 bool value)
{
  ++ mBoolNum;
  void* p = mAlloc.get_memory(sizeof(AstBool));
  return new (p) AstBool(loc, value);
}


//////////////////////////////////////////////////////////////////////
/// クラス AstBool
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
AstBool::AstBool(const FileRegion& loc,
		 bool value) :
  AstNode(loc),
  mValue(value)
{
}

// @brief デストラクタ
AstBool::~AstBool()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstBool::dump(ostream& s,
	      int indent) const
{
  if ( value() ) {
    s << "true";
  }
  else {
    s << "false";
  }
}

END_NAMESPACE_YM_DOTLIB
