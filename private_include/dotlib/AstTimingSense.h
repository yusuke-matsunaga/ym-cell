#ifndef ASTTIMINGSENSE_H
#define ASTTIMINGSENSE_H

/// @file AstTimingSense.h
/// @brief AstNode の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstTimingSense AstTimingSense.h "AstTimingSense.h"
/// @brief timing sense を表すクラス
//////////////////////////////////////////////////////////////////////
class AstTimingSense :
  public AstNode
{
public:

  /// @brief コンストラクタ
  AstTimingSense(const FileRegion& loc,  ///< [in] ファイル上の位置
		 ClibTimingSense value); ///< [in] 値

  /// @brief デストラクタ
  ~AstTimingSense();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief TimingSense を返す．
  ClibTimingSense
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
  ClibTimingSense mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTTIMINGSENSE_H
