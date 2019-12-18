#ifndef MISLIBCONST_H
#define MISLIBCONST_H

/// @file MislibConst.h
/// @brief MislibConst0, MislibConst1 のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "MislibExpr.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
/// @class MislibConst0 MislibConst.h "MislibConst.h"
/// @brief 定数0を表すクラス
//////////////////////////////////////////////////////////////////////
class MislibConst0 :
  public MislibExpr
{
  friend class MislibParser;

private:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  explicit
  MislibConst0(const FileRegion& loc);

  /// @brief デストラクタ
  ~MislibConst0();


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

};


//////////////////////////////////////////////////////////////////////
/// @class MislibConst1 MislibConst.h "MislibConst.h"
/// @brief 定数1を表すクラス
//////////////////////////////////////////////////////////////////////
class MislibConst1 :
  public MislibExpr
{
  friend class MislibParser;

private:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  explicit
  MislibConst1(const FileRegion& loc);

  /// @brief デストラクタ
  ~MislibConst1();


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

};

END_NAMESPACE_YM_MISLIB

#endif // MISLIBCONST_H
