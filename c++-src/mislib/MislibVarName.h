#ifndef MISLIBVARNAME_H
#define MISLIBVARNAME_H

/// @file MislibVarName.h
/// @brief MislibVarName のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "MislibExpr.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
/// @class MislibVarName MislibVarName.h "MislibVarName.h"
/// @brief 変数名を表すクラス
//////////////////////////////////////////////////////////////////////
class MislibVarName :
  public MislibExpr
{
  friend class MislibParser;

private:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  /// @param[in] str 共有された文字列のID
  MislibVarName(const FileRegion& loc,
		ShString str);

  /// @brief デストラクタ
  ~MislibVarName();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 種類を取り出す．
  Type
  type() const override;

  /// @brief 対応する論理式を生成する．
  /// @param[in] name_map 端子名をキーにして端子番号を取り出す連想配列
  Expr
  to_expr(const unordered_map<ShString, int>& name_map) const override;

  /// @brief 内容を出力する．
  /// デバッグ用
  void
  dump(ostream& s) const override;

  /// @brief 変数名を取り出す
  ShString
  varname() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 変数名
  ShString mVarName;

};

END_NAMESPACE_YM_MISLIB

#endif // MISLIBVARNAME_H
