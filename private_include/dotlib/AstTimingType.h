#ifndef ASTTIMINGTYPE_H
#define ASTTIMINGTYPE_H

/// @file AstTimingType.h
/// @brief AstTimingType の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstTimingType AstTimingType.h "AstTimingType.h"
/// @brief timing typeを表すクラス
//////////////////////////////////////////////////////////////////////
class AstTimingType :
  public AstNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  AstTimingType(const FileRegion& loc,
		ClibTimingType value);

  /// @brief デストラクタ
  ~AstTimingType();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief TimingType を返す．
  ClibTimingType
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
  ClibTimingType mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief TimingType を返す．
inline
ClibTimingType
AstTimingType::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTTIMINGTYPE_H
