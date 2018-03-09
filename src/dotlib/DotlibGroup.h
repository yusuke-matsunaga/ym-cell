#ifndef DOTLIBGROUP_H
#define DOTLIBGROUP_H

/// @file DotlibGroup.h
/// @brief DotlibNode の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibBase.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibGroup DotlibGroup.h "DotlibGroup.h"
/// @brief group statement を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibGroup :
  public DotlibBase
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  DotlibGroup(const FileRegion& loc,
	      const DotlibNode* value);

  /// @brief デストラクタ
  ~DotlibGroup();


public:
  //////////////////////////////////////////////////////////////////////
  // 内容を参照する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループの値を得る．
  const DotlibNode*
  value() const;

  /// @brief 先頭の属性を得る．
  const DotlibAttr*
  attr_top() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  void
  dump(ostream& s,
       int indent = 0) const;


public:
  //////////////////////////////////////////////////////////////////////
  // 内容を設定する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief attribute を設定する．
  /// @param[in] attr 属性
  void
  add_attr(DotlibAttr* attr);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  const DotlibNode* mValue;

  // 属性の先頭
  DotlibAttr* mAttrTop;

  // 属性の末尾
  DotlibAttr* mAttrTail;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief グループの値を得る．
inline
const DotlibNode*
DotlibGroup::value() const
{
  return mValue;
}

// @brief 先頭の属性を得る．
inline
const DotlibAttr*
DotlibGroup::attr_top() const
{
  return mAttrTop;
}

// @brief attribute を設定する．
// @param[in] attr 属性
inline
void
DotlibGroup::add_attr(DotlibAttr* attr)
{
  if ( mAttrTop != nullptr ) {
    mAttrTail->mNext = attr;
    mAttrTail = attr;
  }
  else {
    mAttrTop = mAttrTail = attr;
  }
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBGROUP_H
