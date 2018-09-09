#ifndef ASTCPTYPE_H
#define ASTCPTYPE_H

/// @file AstCPType.h
/// @brief AstNode の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstCellPinDirection AstCPType.h "AstCPType.h"
/// @brief clear_preset_var1, clear_preset_var2 のを表すクラス
//////////////////////////////////////////////////////////////////////
class AstCPType :
  public AstNode
{
public:

  // 値
  enum Type { kL, kH, kN, kT, kX };


public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  AstCPType(const FileRegion& loc,
	    Type value);

  /// @brief デストラクタ
  ~AstCPType();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を返す．
  Type
  value() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  void
  dump(ostream& s,
       int indent = 0) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  Type mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief CellPinDirection を返す．
inline
AstCPType::Type
AstCPType::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTCPTYPE_H
