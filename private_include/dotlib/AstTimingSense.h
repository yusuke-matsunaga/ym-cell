#ifndef ASTTIMINGSENSE_H
#define ASTTIMINGSENSE_H

/// @file AstTimingSense.h
/// @brief AstNode の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstTimingSense AstTimingSense.h "AstTimingSense.h"
/// @brief timing sense のノードを表すクラス
//////////////////////////////////////////////////////////////////////
class AstTimingSense :
  public AstValue
{
public:

  /// @brief コンストラクタ
  AstTimingSense(ClibTimingSense value,       ///< [in] 値
		 const FileRegion& val_loc)   ///< [in] 値のファイル上の位置
    : AstValue(val_loc),
      mValue{value}
  {
  }

  /// @brief デストラクタ
  ~AstTimingSense() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief TimingSense を返す．
  ClibTimingSense
  timing_sense_value() const override;

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s) const override; ///< [in] 出力先のストリーム


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  ClibTimingSense mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTTIMINGSENSE_H
