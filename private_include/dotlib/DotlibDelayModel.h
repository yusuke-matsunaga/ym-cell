#ifndef DOTLIBDELAYMODEL_H
#define DOTLIBDELAYMODEL_H

/// @file DotlibDelayModel.h
/// @brief DotlibDelayModel の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibDelayModel DotlibDelayModel.h "DotlibDelayModel.h"
/// @brief delay modelを表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibDelayModel :
  public DotlibNode
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  DotlibDelayModel(const FileRegion& loc,
		   ClibDelayModel value);

  /// @brief デストラクタ
  virtual
  ~DotlibDelayModel();


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
DotlibDelayModel::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBDELAYMODEL_H
