
/// @file AstString.cc
/// @brief AstString の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "AstMgr.h"
#include "AstString.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 定数シンボルを表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
AstString*
AstMgr::new_string(const FileRegion& loc,
		   ShString value)
{
  ++ mStrNum;
  void* p = mAlloc.get_memory(sizeof(AstString));
  return new (p) AstString(loc, value);
}


//////////////////////////////////////////////////////////////////////
/// クラス AstString
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
AstString::AstString(const FileRegion& loc,
		     ShString value) :
  AstNode(loc),
  mValue(value)
{
}

// @brief デストラクタ
AstString::~AstString()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstString::dump(ostream& s,
		int indent) const
{
  dump_string(s, value());
}

END_NAMESPACE_YM_DOTLIB
