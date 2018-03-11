#ifndef DOTLIBTECHNOLOGY_H
#define DOTLIBTECHNOLOGY_H

/// @file DotlibTechnology.h
/// @brief DotlibTechnology のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibTechnology DotlibTechnology.h "DotlibTechnology.h"
/// @brief technologyを表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibTechnology :
  public DotlibNode
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  DotlibTechnology(const FileRegion& loc,
		   ClibTechnology value);

  /// @brief デストラクタ
  virtual
  ~DotlibTechnology();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief Technology を返す．
  ClibTechnology
  value() const;

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

  // 値
  ClibTechnology mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief Technology を返す．
inline
ClibTechnology
DotlibTechnology::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBTECHNOLOGY_H
