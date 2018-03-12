
/// @file DotlibInt.cc
/// @brief DotlibInt の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibInt.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// クラス DotlibInt
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
DotlibInt::DotlibInt(const FileRegion& loc,
		     int value) :
  DotlibNum(loc),
  mValue(value)
{
}

// @brief デストラクタ
DotlibInt::~DotlibInt()
{
}

// @brief 数値を返す．
double
DotlibInt::float_value() const
{
  return static_cast<double>(mValue);
}

// @brief float 値を取り出す．
//
// 型が違ったらエラーを MsgMgr に出力する．
bool
DotlibInt::expect_float(double& value) const
{
  value = static_cast<double>(mValue);
  return true;
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibInt::dump(ostream& s,
		int indent) const
{
  s << value();
}

END_NAMESPACE_YM_DOTLIB
