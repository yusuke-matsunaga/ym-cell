#ifndef ASTFFBANK_H
#define ASTFFBANK_H

/// @file AstFFBank.h
/// @brief AstFFBank のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "AstFF.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstFFBank AstFFBank.h "AstFFBank.h"
/// @brief ff_bank を表す AstNode
//////////////////////////////////////////////////////////////////////
class AstFFBank :
  public AstFF
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
  /// @param[in] clocked_on クロック条件
  /// @param[in] clocked_on_also 追加クロック条件
  /// @param[in] next_state 次状態遷移条件
  AstFFBank(const FileRegion& loc,
	    const AstString* var1,
	    const AstString* var2,
	    const AstInt* bits,
	    const AstExpr* clear,
	    const AstExpr* preset,
	    const AstCPType* clear_preset_var1,
	    const AstCPType* clear_preset_var2,
	    const AstExpr* clocked_on,
	    const AstExpr* clocked_on_also,
	    const AstExpr* next_state);

  /// @brief デストラクタ
  ~AstFFBank();


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

  // bits
  const AstInt* mBits;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief ビット数を返す．
inline
const AstInt*
AstFFBank::bits() const
{
  return mBits;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTFF_H
