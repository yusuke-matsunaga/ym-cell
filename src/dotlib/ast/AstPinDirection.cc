
/// @file AstPinDirection.cc
/// @brief AstPinDirection の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "AstMgr.h"
#include "AstPinDirection.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief cell_pin_direction を表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
AstPinDirection*
AstMgr::new_pin_direction(const FileRegion& loc,
			  ClibCellPinDirection value)
{
  ++ mCellPinDirectionNum;
  void* p = mAlloc.get_memory(sizeof(AstPinDirection));
  return new (p) AstPinDirection(loc, value);
}


//////////////////////////////////////////////////////////////////////
// クラス AstPinDirection
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
AstPinDirection::AstPinDirection(const FileRegion& loc,
				 ClibCellPinDirection value) :
  AstNode(loc),
  mValue(value)
{
}

// @brief デストラクタ
AstPinDirection::~AstPinDirection()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstPinDirection::dump(ostream& s,
		      int indent) const
{
  switch ( mValue ) {
  case kClibCellPinInput:    dump_string(s, "input");    break;
  case kClibCellPinOutput:   dump_string(s, "output");   break;
  case kClibCellPinInout:    dump_string(s, "inout");    break;
  case kClibCellPinInternal: dump_string(s, "internal"); break;
  }
}

END_NAMESPACE_YM_DOTLIB
