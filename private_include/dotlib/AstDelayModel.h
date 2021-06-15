#ifndef ASTDELAYMODEL_H
#define ASTDELAYMODEL_H

/// @file AstDelayModel.h
/// @brief AstDelayModel の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstDelayModel AstDelayModel.h "AstDelayModel.h"
/// @brief delay modelを表すクラス
//////////////////////////////////////////////////////////////////////
class AstDelayModel :
  public AstNode
{
public:

  /// @brief コンストラクタ
  AstDelayModel(const FileRegion& loc, ///< [in] ファイル上の位置
		ClibDelayModel value); ///< [in] 値

  /// @brief デストラクタ
  ~AstDelayModel();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief DelayModel を返す．
  ClibDelayModel
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
  ClibDelayModel mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTDELAYMODEL_H
