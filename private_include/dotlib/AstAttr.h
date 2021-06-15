#ifndef ASTATTR_H
#define ASTATTR_H

/// @file AstAttr.h
/// @brief AstAttr のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib_nsdef.h"
#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstAttr AstAttr.h "AstAttr.h"
/// @brief 属性を表すクラス
//////////////////////////////////////////////////////////////////////
class AstAttr :
  public AstNode
{
  friend class AstMgr;

private:

  /// @brief コンストラクタ
  AstAttr(const FileRegion& loc, ///< [in] ファイル上の位置
	  AttrType attr_type,    ///< [in] 属性
	  const AstNode* value); ///< [in] 値

  /// @brief デストラクタ
  ~AstAttr();


public:
  //////////////////////////////////////////////////////////////////////
  // 内容を参照する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 属性を得る．
  AttrType
  attr_type() const
  {
    return mAttrType;
  }

  /// @brief 属性の値を得る．
  const AstNode*
  attr_value() const
  {
    return mValue;
  }

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s,      ///< [in] 出力先のストリーム
       int indent = 0)  ///< [in] インデント量
    const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 属性
  AttrType mAttrType;

  // 値
  const AstNode* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBNODEIMPL_H
