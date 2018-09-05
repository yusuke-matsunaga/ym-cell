#ifndef ASTBOOL_H
#define ASTBOOL_H

/// @file AstBool.h
/// @brief AstBool のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstBool AstBool.h "AstBool.h"
/// @brief 整数値を表すクラス
//////////////////////////////////////////////////////////////////////
class AstBool :
  public AstNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  AstBool(const FileRegion& loc,
	  bool value);

  /// @brief デストラクタ
  ~AstBool();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief ブール値を返す．
  bool
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
  bool mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数
//////////////////////////////////////////////////////////////////////

// @brief ブール値を返す．
inline
bool
AstBool::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTBOOL_H
