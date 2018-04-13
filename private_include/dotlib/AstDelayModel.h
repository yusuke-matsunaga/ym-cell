#ifndef ASTDELAYMODEL_H
#define ASTDELAYMODEL_H

/// @file AstDelayModel.h
/// @brief AstDelayModel の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
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
  friend class AstMgr;

protected:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  AstDelayModel(const FileRegion& loc,
		ClibDelayModel value);

  /// @brief デストラクタ
  virtual
  ~AstDelayModel();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief DelayModel を返す．
  ClibDelayModel
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
  ClibDelayModel mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief DelayModel を返す．
inline
ClibDelayModel
AstDelayModel::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTDELAYMODEL_H
