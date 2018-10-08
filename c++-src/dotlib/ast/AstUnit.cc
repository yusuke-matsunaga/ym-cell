
/// @file AstUnit.cc
/// @brief AstUnit の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstUnit.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 単位を表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] unit_val 数値
// @param[in] unit_str 単位を表す文字列
const AstUnit*
AstMgr::new_unit(const FileRegion& loc,
		 const AstFloat* unit_val,
		 const AstString* unit_str)
{
  void* p = mAlloc.get_memory(sizeof(AstUnit));
  return new (p) AstUnit(loc, unit_val, unit_str);
}


//////////////////////////////////////////////////////////////////////
// クラス AstUnit
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] unit_val 数値
// @param[in] unit_str 単位を表す文字列
AstUnit::AstUnit(const FileRegion& loc,
		 const AstFloat* unit_val,
		 const AstString* unit_str) :
  AstNode(loc),
  mVal(unit_val),
  mStr(unit_str)
{
}

// @brief デストラクタ
AstUnit::~AstUnit()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstUnit::dump(ostream& s,
	      int indent) const
{
  s << unit_val()->value() << unit_str()->value();
}

END_NAMESPACE_YM_DOTLIB
