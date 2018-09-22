
/// @file AstCPType.cc
/// @brief AstCPType の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstCPType.h"
#include "dotlib/AstMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief clear_preset_var の値を表す AstNode を生成する．
const AstCPType*
AstMgr::new_cptype(const FileRegion& loc,
		   AstCPType::Type value)
{
  void* p = mAlloc.get_memory(sizeof(AstCPType));
  return new (p) AstCPType(loc, value);
}


//////////////////////////////////////////////////////////////////////
// クラス AstCPType
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
AstCPType::AstCPType(const FileRegion& loc,
		     Type value) :
  AstNode(loc),
  mValue(value)
{
}

// @brief デストラクタ
AstCPType::~AstCPType()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstCPType::dump(ostream& s,
		int indent) const
{
  const char* tmp = nullptr;
  switch ( value() ) {
  case kL: tmp = "L"; break;
  case kH: tmp = "H"; break;
  case kN: tmp = "N"; break;
  case kT: tmp = "T"; break;
  case kX: tmp = "X"; break;
  }
  dump_string(s, tmp);
}

END_NAMESPACE_YM_DOTLIB
