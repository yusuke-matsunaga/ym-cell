#ifndef ASTLATCHBANK_H
#define ASTLATCHBANK_H

/// @file AstLatchBank.h
/// @brief AstLatchBank のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
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
  AstLatchBank(const FileRegion& attr_loc,     ///< [in] 属性のファイル上の位置
	       const StrStrIntHandler& header, ///< [in] ヘッダを読み込んだハンドラ
	       const LatchHandler& group);     ///< [in] グループ本体を読み込んだハンドラ

  /// @brief デストラクタ
  ~AstLatchBank();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief ビット数を返す．
  const AstInt*
  bits() const
  {
    return mBits;
  }

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s,     ///< [in] 出力先のストリーム
       int indent = 0) ///< [in] インデント量
    const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ビット数
  const AstInt* mBits;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTLATCHBANK_H
