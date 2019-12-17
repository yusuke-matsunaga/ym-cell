#ifndef YM_CLIBLUTTEMPLATE_H
#define YM_CLIBLUTTEMPLATE_H

/// @file ym/ClibLutTemplate.h
/// @brief ClibLutTemplate のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
/// All rights reserved.


#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroup
/// @class ClibLutTemplate ClibLutTemplate.h "ym/ClibLutTemplate.h"
/// @brief ルックアップテーブルのテンプレートを表すクラス
//////////////////////////////////////////////////////////////////////
class ClibLutTemplate
{
protected:

  /// @brief デストラクタ
  virtual
  ~ClibLutTemplate() { }


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号の取得
  virtual
  int
  id() const = 0;

  /// @brief 名前の取得
  virtual
  const char*
  name() const = 0;

  /// @brief 次元数の取得
  virtual
  int
  dimension() const = 0;

  /// @brief 変数型の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  virtual
  ClibVarType
  variable_type(int var) const = 0;

  /// @brief インデックス数の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  virtual
  int
  index_num(int var) const = 0;

  /// @brief デフォルトインデックス値の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  /// @param[in] pos 位置番号 ( 0 <= pos < index_num(var) )
  virtual
  double
  index(int var,
	int pos) const = 0;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  /// @param[in] s 出力先のストリーム
  virtual
  void
  dump(ostream& s) const = 0;

};

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBLUTTEMPLATE_H
