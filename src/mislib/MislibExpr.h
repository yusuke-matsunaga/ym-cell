#ifndef MISLIBEXPR_H
#define MISLIBEXPR_H

/// @file MislibExpr.h
/// @brief MislibExpr のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "MislibNode.h"

#include "ym/ShString.h"
#include "ym/Expr.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
/// @class MislibExpr MislibExpr.h "MislibExpr.h"
/// @brief 式を表す AST
//////////////////////////////////////////////////////////////////////
class MislibExpr :
  public MislibNode
{
public:

  /// @brief ノードの種類
  enum Type {
    /// @brief 変数名
    VarName,
    /// @brief 定数0
    Const0,
    /// @brief 定数1
    Const1,
    /// @brief NOT論理式
    Not,
    /// @brief AND論理式
    And,
    /// @brief OR論理式
    Or,
    /// @brief XOR論理式
    Xor,
  };

protected:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  MislibExpr(const FileRegion& loc);

  /// @brief デストラクタ
  virtual
  ~MislibExpr();


public:
  //////////////////////////////////////////////////////////////////////
  // 共通な関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 種類を取り出す．
  virtual
  Type
  type() const = 0;

  /// @brief 対応する論理式を生成する．
  /// @param[in] name_map 端子名をキーにして端子番号を取り出す連想配列
  virtual
  Expr
  to_expr(const HashMap<ShString, int>& name_map) const = 0;

  /// @brief 内容を出力する．
  /// デバッグ用
  virtual
  void
  dump(ostream& s) const = 0;


public:
  //////////////////////////////////////////////////////////////////////
  // 変数名型(kVarName)のときに意味のある関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 変数名を取り出す
  ///
  /// デフォルトの実装ではエラー(アボート)となる．
  virtual
  ShString
  varname() const;


public:
  //////////////////////////////////////////////////////////////////////
  // 論理演算型(kNot, kAnd, kOr, kXor)のときに意味のある関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 1番目の子供を取り出す．
  ///
  /// デフォルトの実装ではエラー(アボート)となる．
  virtual
  const MislibExpr*
  child1() const;

  /// @brief 2番目の子供を取り出す．
  ///
  /// デフォルトの実装ではエラー(アボート)となる．
  virtual
  const MislibExpr*
  child2() const;

};

END_NAMESPACE_YM_MISLIB

#endif // MISLIBEXPR_H
