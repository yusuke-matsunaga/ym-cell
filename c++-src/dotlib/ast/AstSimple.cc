
/// @file AstSimple.cc
/// @brief AstSimple の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstSimple.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstSimple
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstSimple::AstSimple(AttrType attr_type,         ///< [in] 属性の型
		     const FileRegion& attr_loc, ///< [in] 属性のファイル上の位置
		     const AstValue* value)      ///< [in] 値
  : mAttrType{attr_type},
    mAttrLoc{attr_loc},
    mValue{value}
{
}

// @brief 全体のファイル上の位置を返す．
FileRegion
AstSimple::loc() const
{
  return FileRegion(mAttrLoc, mValue->loc());
}

END_NAMESPACE_YM_DOTLIB
