#ifndef DOTLIBATTR_H
#define DOTLIBATTR_H

/// @file DotlibAttr.h
/// @brief DotlibAttr のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_int.h"
#include "DotlibNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibAttr DotlibAttr.h "DotlibAttr.h"
/// @brief 属性を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibAttr :
  public DotlibNode
{
  friend class DotlibMgrImpl;
  friend class GroupHandler;

private:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] attr_type 属性
  /// @param[in] value 値
  DotlibAttr(const FileRegion& loc,
	     AttrType attr_type,
	     const DotlibNode* value);

  /// @brief デストラクタ
  ~DotlibAttr();


public:
  //////////////////////////////////////////////////////////////////////
  // 内容を参照する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 属性を得る．
  AttrType
  attr_type() const;

  /// @brief 属性の値を得る．
  const DotlibNode*
  attr_value() const;

  /// @brief 次の属性を得る．
  const DotlibAttr*
  next() const;

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
  const DotlibNode* mValue;

  // 次の要素を指すリンクポインタ
  DotlibAttr* mNext;

};

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBNODEIMPL_H
