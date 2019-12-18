
/// @file AstDirection.cc
/// @brief AstDirection の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstMgr.h"
#include "dotlib/AstDirection.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief cell_pin_direction を表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
const AstDirection*
AstMgr::new_direction(const FileRegion& loc,
		      ClibDirection value)
{
  ++ mDirectionNum;
  auto node = new AstDirection(loc, value);
  mNodeList.push_back(node);
  return node;
}


//////////////////////////////////////////////////////////////////////
// クラス AstDirection
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
AstDirection::AstDirection(const FileRegion& loc,
			   ClibDirection value) :
  AstNode(loc),
  mValue(value)
{
}

// @brief デストラクタ
AstDirection::~AstDirection()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstDirection::dump(ostream& s,
		   int indent) const
{
  const char* tmp = "---";
  switch ( mValue ) {
  case ClibDirection::Input:    tmp = "input";    break;
  case ClibDirection::Output:   tmp = "output";   break;
  case ClibDirection::Inout:    tmp = "inout";    break;
  case ClibDirection::Internal: tmp = "internal"; break;
  }
  dump_string(s, tmp);
}

END_NAMESPACE_YM_DOTLIB
