#ifndef ASTTECHNOLOGY_H
#define ASTTECHNOLOGY_H

/// @file AstTechnology.h
/// @brief AstTechnology のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
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
  AstTechnology(const FileRegion& loc, ///< [in] ファイル上の位置
		ClibTechnology value); ///< [in] 値

  /// @brief デストラクタ
  ~AstTechnology();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief Technology を返す．
  ClibTechnology
  value() const
  {
    return mValue;
  }

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s,     ///< [in] 出力先のストリーム
       int indent = 0) ///< [in] インデント量
    const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  ClibTechnology mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTTECHNOLOGY_H
