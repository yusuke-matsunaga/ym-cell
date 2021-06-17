#ifndef ASTFLOAT_H
#define ASTFLOAT_H

/// @file AstFloat.h
/// @brief AstFloat のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstFloat AstFloat.h "AstFloat.h"
/// @brief 実数値のノードを表すクラス
//////////////////////////////////////////////////////////////////////
class AstFloat :
  public AstValue
{
public:

  /// @brief コンストラクタ
  AstFloat(double value,               ///< [in] 値
	   const FileRegion& val_loc); ///< [in] 値のファイル上の位置

  /// @brief デストラクタ
  ~AstFloat() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 数値を返す．
  double
  float_value() const override;

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s) const override; ///< [in] 出力先のストリーム


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  double mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTFLOAT_H
