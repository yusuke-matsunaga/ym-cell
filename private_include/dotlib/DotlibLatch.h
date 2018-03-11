#ifndef DOTLIBLATCH_H
#define DOTLIBLATCH_H

/// @file ym_dotlib/DotlibLatch.h
/// @brief DotlibLatch のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibFL.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibLatch DotlibLatch.h "DotlibLatch.h"
/// @brief DotlibNode の木から取り出した Latch の情報を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibLatch :
  public DotlibFL
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  /// @param[in] var1, var2 変数名
  /// @param[in] clear クリア条件
  /// @param[in] preset プリセット条件
  /// @param[in] clear_preset_var1 'clear_preset_var1'
  /// @param[in] clear_preset_var2 'clear_preset_var2'
  /// @param[in] data_in データ入力式
  /// @param[in] enable イネーブル条件式
  /// @param[in] enable_also 追加イネーブル条件式
  DotlibLatch(const FileRegion& loc,
	      const ShString var1,
	      const ShString var2,
	      const DotlibExpr* clear,
	      const DotlibExpr* preset,
	      int clear_preset_var1,
	      int clear_preset_var2,
	      const DotlibExpr* data_in,
	      const DotlibExpr* enable,
	      const DotlibExpr* enable_also);

  /// @brief デストラクタ
  virtual
  ~DotlibLatch();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

#if 0
  /// @brief 内容を初期化する．
  bool
  set_data(const DotlibNode* node);
#endif

  /// @brief "data_in" を返す．
  const DotlibExpr*
  data_in() const;

  /// @brief "enable" を返す．
  const DotlibExpr*
  enable() const;

  /// @brief "enable_also" を返す．
  const DotlibExpr*
  enable_also() const;

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

  // data_in
  const DotlibExpr* mDataIn;

  // enable
  const DotlibExpr* mEnable;

  // enable_also
  const DotlibExpr* mEnableAlso;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief "data_in" を返す．
inline
const DotlibExpr*
DotlibLatch::data_in() const
{
  return mDataIn;
}

// @brief "enable" を返す．
inline
const DotlibExpr*
DotlibLatch::enable() const
{
  return mEnable;
}

// @brief "enable_also" を返す．
inline
const DotlibExpr*
DotlibLatch::enable_also() const
{
  return mEnableAlso;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBLATCH_H
