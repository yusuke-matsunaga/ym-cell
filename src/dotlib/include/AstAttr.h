#ifndef ASTATTR_H
#define ASTATTR_H

/// @file AstAttr.h
/// @brief AstAttr のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
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
  /// @param[in] loc ファイル上の位置
  /// @param[in] attr_type 属性
  /// @param[in] value 値
  AstAttr(const FileRegion& loc,
	  AttrType attr_type,
	  const AstNode* value);

  /// @brief デストラクタ
  virtual
  ~AstAttr();


public:
  //////////////////////////////////////////////////////////////////////
  // 内容を参照する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 属性を得る．
  AttrType
  attr_type() const;

  /// @brief 属性の値を得る．
  const AstNode*
  attr_value() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  virtual
  void
  dump(ostream& s,
       int indent = 0) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 属性
  AttrType mAttrType;

  // 値
  const AstNode* mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 属性を得る．
inline
AttrType
AstAttr::attr_type() const
{
  return mAttrType;
}

// @brief 属性の値を得る．
inline
const AstNode*
AstAttr::attr_value() const
{
  return mValue;
}


END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBNODEIMPL_H
