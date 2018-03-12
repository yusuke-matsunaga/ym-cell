#ifndef YM_DOTLIB_DOTLIBSTATETABLE_H
#define YM_DOTLIB_DOTLIBSTATETABLE_H

/// @file ym_dotlib/DotlibStateTable.h
/// @brief DotlibStateTable のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibFL.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibStateTable DotlibStateTable.h "DotlibStateTable.h"
/// @brief DotlibNode の木から取り出した状態遷移表の情報を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibStateTable :
  public DotlibFL
{
  friend class DotlibNode;

public:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  /// @param[in] var1, var2 変数名
  /// @param[in] clear クリア条件
  /// @param[in] preset プリセット条件
  /// @param[in] clear_preset_var1 'clear_preset_var1'
  /// @param[in] clear_preset_var2 'clear_preset_var2'
  /// @param[in] next_state 次状態遷移条件
  /// @param[in] clocked_on クロック条件
  /// @param[in] clocked_on_also 追加クロック条件
  DotlibStateTable(const FileRegion& loc,
		   const ShString var1,
		   const ShString var2,
		   const DotlibExpr* clear,
		   const DotlibExpr* preset,
		   int clear_preset_var1,
		   int clear_preset_var2,
		   const DotlibExpr* next_state,
		   const DotlibExpr* clocked_on,
		   const DotlibExpr* clocked_on_also);

  /// @brief デストラクタ
  virtual
  ~DotlibStateTable();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief "next_state" を返す．
  const DotlibExpr*
  next_state() const;

  /// @brief "clocked_on" を返す．
  const DotlibExpr*
  clocked_on() const;

  /// @brief "clocked_on_also" を返す．
  const DotlibExpr*
  clocked_on_also() const;

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

  // next_state
  const DotlibExpr* mNextState;

  // clocked_on
  const DotlibExpr* mClockedOn;

  // clocked_on_also
  const DotlibExpr* mClockedOnAlso;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief "next_state" を返す．
inline
const DotlibExpr*
DotlibStateTable::next_state() const
{
  return mNextState;
}

// @brief "clocked_on" を返す．
inline
const DotlibExpr*
DotlibStateTable::clocked_on() const
{
  return mClockedOn;
}

// @brief "clocked_on_also" を返す．
inline
const DotlibExpr*
DotlibStateTable::clocked_on_also() const
{
  return mClockedOnAlso;
}

END_NAMESPACE_YM_DOTLIB

#endif // YM_DOTLIB_DOTLIBSTATETABLE_H
