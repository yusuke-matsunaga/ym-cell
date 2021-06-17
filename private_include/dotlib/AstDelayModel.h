#ifndef ASTDELAYMODEL_H
#define ASTDELAYMODEL_H

/// @file AstDelayModel.h
/// @brief AstDelayModel の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstDelayModel AstDelayModel.h "AstDelayModel.h"
/// @brief delay model のノードを表すクラス
//////////////////////////////////////////////////////////////////////
class AstDelayModel :
  public AstValue
{
public:

  /// @brief コンストラクタ
  AstDelayModel(ClibDelayModel value,       ///< [in] 値
		const FileRegion& val_loc); ///< [in] 値のファイル上の位置

  /// @brief デストラクタ
  ~AstDelayModel() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief DelayModel を返す．
  ClibDelayModel
  delay_model_value() const override;

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s) const override; ///< [in] 出力先のストリーム


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  ClibDelayModel mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTDELAYMODEL_H
