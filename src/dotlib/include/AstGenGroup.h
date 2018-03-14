#ifndef ASTGENGROUP_H
#define ASTGENGROUP_H

/// @file AstGenGroup.h
/// @brief AstGenGroup のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstGenGroup AstGenGroup.h "AstGenGroup.h"
/// @brief 一般的なグループ構造を表す AstNode の継承クラス
//////////////////////////////////////////////////////////////////////
class AstGenGroup :
  public AstNode
{
  friend class AstMgr;

protected:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  AstGenGroup(const FileRegion& loc,
	      const vector<const AstNode*>& value_list,
	      const vector<const AstAttr*>& attr_list,
	      Alloc& alloc);

  /// @brief デストラクタ
  virtual
  ~AstGenGroup();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値のリストの要素数を返す．
  int
  value_num() const;

  /// @brief 値のリストの要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < value_num() )
  const AstNode*
  value_elem(int pos) const;

  /// @brief 属性のリストの要素数を返す．
  int
  attr_num() const;

  /// @brief 属性のリストの要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < attr_num() )
  const AstAttr*
  attr_elem(int pos) const;

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

  // 値のリストの要素数
  int mValueNum;

  // 値のリスト
  const AstNode** mValueList;

  // 属性のリストの要素数
  int mAttrNum;

  // 属性のリスト
  const AstAttr** mAttrList;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 値のリストの要素数を返す．
inline
int
AstGenGroup::value_num() const
{
  return mValueNum;
}

// @brief 値のリストの要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < value_num() )
inline
const AstNode*
AstGenGroup::value_elem(int pos) const
{
  ASSERT_COND( pos >= 0 && pos < value_num() );

  return mValueList[pos];
}

// @brief 属性のリストの要素数を返す．
inline
int
AstGenGroup::attr_num() const
{
  return mAttrNum;
}

// @brief 属性のリストの要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < attr_num() )
inline
const AstAttr*
AstGenGroup::attr_elem(int pos) const
{
  ASSERT_COND( pos >= 0 && pos < attr_num() );

  return mAttrList[pos];
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTGENGROUP_H
