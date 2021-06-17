#ifndef ASTVARTYPE_H
#define ASTVARTYPE_H

/// @file AstVarType.h
/// @brief AstVarType の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstVarType AstVarType.h "AstVarType.h"
/// @brief var type の simple attribute を表すクラス
//////////////////////////////////////////////////////////////////////
class AstVarType :
  public AstValue
{
public:

  /// @brief コンストラクタ
  AstVarType(ClibVarType value,           ///< [in] 値
	     const FileRegion& val_loc)   ///< [in] 値のファイル上の位置
    : AstValue(val_loc),
      mValue{value}
  {
  }

  /// @brief デストラクタ
  ~AstVarType() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief VarType を返す．
  ClibVarType
  vartype_value() const override;

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s) const override; ///< [in] 出力先のストリーム


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  ClibVarType mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTVARTYPE_H
