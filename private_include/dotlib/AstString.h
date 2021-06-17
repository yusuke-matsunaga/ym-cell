#ifndef ASTSTRING_H
#define ASTSTRING_H

/// @file AstString.h
/// @brief AstString のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstString AstString.h "AstString.h"
/// @brief 文字列のノード を表すクラス
//////////////////////////////////////////////////////////////////////
class AstString :
  public AstValue
{
public:

  /// @brief コンストラクタ
  AstString(ShString value,             ///< [in] 値
	    const FileRegion& val_loc); ///< [in] 値のファイル上の位置

  /// @brief デストラクタ
  ~AstString();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 定数シンボルを返す．
  ShString
  string_value() const override;

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s) const override; ///< [in] 出力先のストリーム


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  ShString mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTSTRING_H
