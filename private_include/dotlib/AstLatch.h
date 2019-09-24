#ifndef ASTLATCH_H
#define ASTLATCH_H

/// @file AstLatch.h
/// @brief AstLatch のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "AstFL.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstLatch AstLatch.h "AstLatch.h"
/// @brief AstNode の木から取り出した Latch の情報を表すクラス
//////////////////////////////////////////////////////////////////////
class AstLatch :
  public AstFL
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
  AstLatch(const FileRegion& loc,
	   const AstString* var1,
	   const AstString* var2,
	   const AstExpr* clear,
	   const AstExpr* preset,
	   const AstCPType* clear_preset_var1,
	   const AstCPType* clear_preset_var2,
	   const AstExpr* data_in,
	   const AstExpr* enable,
	   const AstExpr* enable_also);

  /// @brief デストラクタ
  ~AstLatch();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief "enable" を返す．
  const AstExpr*
  enable() const;

  /// @brief "enable_also" を返す．
  const AstExpr*
  enable_also() const;

  /// @brief "data_in" を返す．
  const AstExpr*
  data_in() const;

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

  // enable
  const AstExpr* mEnable;

  // enable_also
  const AstExpr* mEnableAlso;

  // data_in
  const AstExpr* mDataIn;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief "enable" を返す．
inline
const AstExpr*
AstLatch::enable() const
{
  return mEnable;
}

// @brief "enable_also" を返す．
inline
const AstExpr*
AstLatch::enable_also() const
{
  return mEnableAlso;
}

// @brief "data_in" を返す．
inline
const AstExpr*
AstLatch::data_in() const
{
  return mDataIn;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTLATCH_H
