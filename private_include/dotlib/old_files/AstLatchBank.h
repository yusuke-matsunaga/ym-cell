#ifndef ASTLATCHBANK_H
#define ASTLATCHBANK_H

/// @file AstLatchBank.h
/// @brief AstLatchBank のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "AstLatch.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstLatchBank AstLatchBank.h "AstLatchBank.h"
/// @brief latch_bank を表す AstNode
//////////////////////////////////////////////////////////////////////
class AstLatchBank :
  public AstLatch
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  /// @param[in] var1, var2 変数名
  /// @param[in] bits ビット数
  /// @param[in] clear クリア条件
  /// @param[in] preset プリセット条件
  /// @param[in] clear_preset_var1 'clear_preset_var1'
  /// @param[in] clear_preset_var2 'clear_preset_var2'
  /// @param[in] data_in データ入力式
  /// @param[in] enable イネーブル条件式
  /// @param[in] enable_also 追加イネーブル条件式
  AstLatchBank(const FileRegion& loc,
	       const AstString* var1,
	       const AstString* var2,
	       const AstInt* bits,
	       const AstExpr* clear,
	       const AstExpr* preset,
	       const AstCPType* clear_preset_var1,
	       const AstCPType* clear_preset_var2,
	       const AstExpr* enable,
	       const AstExpr* enable_also,
	       const AstExpr* data_in);

  /// @brief デストラクタ
  ~AstLatchBank();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief ビット数を返す．
  const AstInt*
  bits() const;


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

  // ビット数
  const AstInt* mBits;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief ビット数を返す．
inline
const AstInt*
AstLatchBank::bits() const
{
  return mBits;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTLATCHBANK_H
