
/// @file DotlibFloat.cc
/// @brief DotlibNode の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibFloat.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// クラス DotlibFloat
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
DotlibFloat::DotlibFloat(const FileRegion& loc,
			 double value) :
  DotlibNode(loc),
  mValue(value)
{
}

// @brief デストラクタ
DotlibFloat::~DotlibFloat()
{
}

// @brief float 値を取り出す．
//
// 型が違ったらエラーを MsgMgr に出力する．
bool
DotlibFloat::expect_float(double& value) const
{
  value = mValue;
  return true;
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibFloat::dump(ostream& s,
		  int indent) const
{
  s << value();
}

END_NAMESPACE_YM_DOTLIB
