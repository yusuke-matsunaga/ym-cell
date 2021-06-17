#ifndef ASTSIMPLE_H
#define ASTSIMPLE_H

/// @file AstSimple.h
/// @brief AstSimple のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstSimple AstSimple.h "AstSimple.h"
/// @brief simple attribute を表す AstNode の派生クラス
//////////////////////////////////////////////////////////////////////
class AstSimple :
  public AstNode
{
public:

  /// @brief コンストラクタ
  AstSimple(AttrType attr_type,         ///< [in] 属性の型
	    const FileRegion& attr_loc, ///< [in] 属性のファイル上の位置
	    const AstValue* value);     ///< [in] 値

  /// @brief デストラクタ
  ~AstSimple() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 全体のファイル上の位置を返す．
  FileRegion
  loc() const override;

  /// @brief 属性の型を返す．
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

  /// @brief 値のノードを返す．
  const AstValue*
  value_node() const
  {
    return mValue;
  }


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 属性の型
  AttrType mAttrType;

  // 属性名のファイル上の位置
  FileRegion mAttrLoc;

  // 値
  const AstValue* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTSIMPLE_H
