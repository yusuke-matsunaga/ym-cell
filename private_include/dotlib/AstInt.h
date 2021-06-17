#ifndef ASTINT_H
#define ASTINT_H

/// @file AstInt.h
/// @brief AstInt のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstInt AstInt.h "AstInt.h"
/// @brief 整数値のノードを表すクラス
//////////////////////////////////////////////////////////////////////
class AstInt :
  public AstValue
{
public:

  /// @brief コンストラクタ
  AstInt(int value,                  ///< [in] 値
	 const FileRegion& val_loc); ///< [in] 値のファイル上の位置

  /// @brief デストラクタ
  ~AstInt() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 整数値を返す．
  int
  int_value() const override;

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s) const override; ///< [in] 出力先のストリーム


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  int mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTINT_H
