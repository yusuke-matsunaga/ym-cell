
/// @file AstTechnology.cc
/// @brief AstTechnology の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstTechnology.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief technology を表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
const AstTechnology*
AstMgr::new_technology(const FileRegion& loc,
		       ClibTechnology value)
{
  ++ mTechnologyNum;
  void* p = mAlloc.get_memory(sizeof(AstTechnology));
  return new (p) AstTechnology(loc, value);
}


//////////////////////////////////////////////////////////////////////
// クラス AstTechnology
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
AstTechnology::AstTechnology(const FileRegion& loc,
			     ClibTechnology value) :
  AstNode(loc),
  mValue(value)
{
}

// @brief デストラクタ
AstTechnology::~AstTechnology()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstTechnology::dump(ostream& s,
		    int indent) const
{
  const char* tmp = "---";
  switch ( mValue ) {
  case ClibTechnology::cmos: tmp = "cmos"; break;
  case ClibTechnology::fpga: tmp = "fpga"; break;
  default: break;
  }
  dump_string(s, tmp);
}

END_NAMESPACE_YM_DOTLIB
