#ifndef ASTFFBANK_H
#define ASTFFBANK_H

/// @file AstFFBank.h
/// @brief AstFFBank のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
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
  AstFFBank(const FileRegion& attr_loc,     ///< [in] 属性のファイル上の位置
	    const StrStrIntHandler& header, ///< [in] ヘッダを読み込んだハンドラ
	    const FFHandler& group);        ///< [in] グループ本体を読み込んだハンドラ

  /// @brief デストラクタ
  ~AstFFBank();


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

  // bits
  const AstInt* mBits;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTFF_H
