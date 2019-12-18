#ifndef MISLIBNOT_H
#define MISLIBNOT_H

/// @file MislibNot.h
/// @brief MislibNot のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "MislibExpr.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
/// @class MislibNot MislibNot.h "MislibNot.h"
/// @brief NOT論理式を表すクラス
//////////////////////////////////////////////////////////////////////
class MislibNot :
  public MislibExpr
{
  friend class MislibParser;

private:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  /// @param[in] child1 1番目の子供
  MislibNot(const FileRegion& loc,
	    const MislibExpr* child1);

  /// @brief デストラクタ
  ~MislibNot();


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

  /// @brief 1番目の子供を取り出す．
  const MislibExpr*
  child1() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 子供
  const MislibExpr* mChild1;

};

END_NAMESPACE_YM_MISLIB

#endif // MISLIBNOT_H
