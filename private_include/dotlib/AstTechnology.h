#ifndef ASTTECHNOLOGY_H
#define ASTTECHNOLOGY_H

/// @file AstTechnology.h
/// @brief AstTechnology のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstTechnology AstTechnology.h "AstTechnology.h"
/// @brief technologyを表すクラス
//////////////////////////////////////////////////////////////////////
class AstTechnology :
  public AstNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  AstTechnology(const FileRegion& loc,
		ClibTechnology value);

  /// @brief デストラクタ
  ~AstTechnology();


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
  void
  dump(ostream& s,
       int indent = 0) const override;


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
AstTechnology::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTTECHNOLOGY_H
