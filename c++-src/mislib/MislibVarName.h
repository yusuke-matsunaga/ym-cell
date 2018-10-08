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
  friend class MislibMgr;

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
  virtual
  Type
  type() const;

  /// @brief 対応する論理式を生成する．
  /// @param[in] name_map 端子名をキーにして端子番号を取り出す連想配列
  virtual
  Expr
  to_expr(const HashMap<ShString, int>& name_map) const;

  /// @brief 内容を出力する．
  /// デバッグ用
  virtual
  void
  dump(ostream& s) const;

  /// @brief 変数名を取り出す
  virtual
  ShString
  varname() const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 変数名
  ShString mVarName;

};

END_NAMESPACE_YM_MISLIB

#endif // MISLIBVARNAME_H
