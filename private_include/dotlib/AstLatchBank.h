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
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @param[in] header ヘッダを読み込んだハンドラ
  /// @param[in] group グループ本体を読み込んだハンドラ
  AstLatchBank(const FileRegion& attr_loc,
	       const StrStrIntHandler& header,
	       const LatchHandler& group);

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
