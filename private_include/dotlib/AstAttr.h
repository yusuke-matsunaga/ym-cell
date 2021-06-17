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
public:

  /// @brief コンストラクタ
  AstAttr(AttrType attr_type,                  ///< [in] 属性の型
	  const FileRegion& attr_loc,          ///< [in] 属性のファイル上の位置
	  unique_ptr<const AstValue>&& value); ///< [in] 値

  /// @brief デストラクタ
  ~AstAttr() = default;


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

  /// @brief 属性名のファイル上の位置を返す．
  FileRegion
  attr_loc() const
  {
    return mAttrLoc;
  }

  /// @brief 属性の値を得る．
  const AstValue*
  value() const
  {
    return mValue.get();
  }

  /// @brief 全体のファイル上の位置を返す．
  FileRegion
  loc() const override;

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s,                     ///< [in] 出力先のストリーム
       int indent = 0) const override; ///< [in] インデント量


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 属性
  AttrType mAttrType;

  // 属性のファイル上の位置
  FileRegion mAttrLoc;

  // 値
  unique_ptr<const AstValue> mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBNODEIMPL_H
