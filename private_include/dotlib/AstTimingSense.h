#ifndef ASTTIMINGSENSE_H
#define ASTTIMINGSENSE_H

/// @file AstTimingSense.h
/// @brief AstNode の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
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
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  AstTimingSense(const FileRegion& loc,
		 ClibTimingSense value);

  /// @brief デストラクタ
  ~AstTimingSense();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief TimingSense を返す．
  ClibTimingSense
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
  ClibTimingSense mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief TimingSense を返す．
inline
ClibTimingSense
AstTimingSense::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTTIMINGSENSE_H
