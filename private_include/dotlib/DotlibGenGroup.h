#ifndef DOTLIBGENGROUP_H
#define DOTLIBGENGROUP_H

/// @file DotlibGenGroup.h
/// @brief DotlibGenGroup のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/DotlibNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibGenGroup DotlibGenGroup.h "DotlibGenGroup.h"
/// @brief 一般的なグループ構造を表す DotlibNode の継承クラス
//////////////////////////////////////////////////////////////////////
class DotlibGenGroup :
  public DotlibNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  DotlibGenGroup(const FileRegion& loc,
		 const DotlibList* value_list,
		 const DotlibAttr* attr_top);

  /// @brief デストラクタ
  virtual
  ~DotlibGenGroup();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値のリストを返す．
  const DotlibList*
  value_list() const;

  /// @brief 属性の先頭を返す．
  const DotlibAttr*
  attr_top() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  virtual
  void
  dump(ostream& s,
       int indent = 0) const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値のリスト
  const DotlibList* mValueList;

  // 属性の先頭
  const DotlibAttr* mAttrTop;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 値のリストを返す．
inline
const DotlibList*
DotlibGenGroup::value_list() const
{
  return mValueList;
}

// @brief 属性の先頭を返す．
inline
const DotlibAttr*
DotlibGenGroup::attr_top() const
{
  return mAttrTop;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBGENGROUP_H
