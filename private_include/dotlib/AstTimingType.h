#ifndef ASTTIMINGTYPE_H
#define ASTTIMINGTYPE_H

/// @file AstTimingType.h
/// @brief AstTimingType の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
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
  AstTimingType(const FileRegion& loc, ///< [in] ファイル上の位置
		ClibTimingType value); ///< [in] 値

  /// @brief デストラクタ
  ~AstTimingType();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief TimingType を返す．
  ClibTimingType
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
  ClibTimingType mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTTIMINGTYPE_H
