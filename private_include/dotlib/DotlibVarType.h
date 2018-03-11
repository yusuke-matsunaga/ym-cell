#ifndef DOTLIBVARTYPE_H
#define DOTLIBVARTYPE_H

/// @file DotlibVarType.h
/// @brief DotlibVarType の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibVarType DotlibVarType.h "DotlibVarType.h"
/// @brief var typeを表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibVarType :
  public DotlibNode
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  DotlibVarType(const FileRegion& loc,
		ClibVarType value);

  /// @brief デストラクタ
  virtual
  ~DotlibVarType();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief VarType を返す．
  ClibVarType
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
  ClibVarType mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief VarType を返す．
inline
ClibVarType
DotlibVarType::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBVARTYPE_H
