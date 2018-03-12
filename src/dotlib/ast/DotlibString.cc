
/// @file DotlibString.cc
/// @brief DotlibString の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibString.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// クラス DotlibString
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
DotlibString::DotlibString(const FileRegion& loc,
			   ShString value) :
  DotlibNode(loc),
  mValue(value)
{
}

// @brief デストラクタ
DotlibString::~DotlibString()
{
}

// @brief 文字列を取り出す．
//
// 型が違ったらエラーを MsgMgr に出力する．
bool
DotlibString::expect_string(ShString& value) const
{
  value = mValue;
  return true;
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibString::dump(ostream& s,
		   int indent) const
{
  dump_string(s, value());
}

END_NAMESPACE_YM_DOTLIB
