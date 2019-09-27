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
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @param[in] header ヘッダを読み込んだハンドラ
  /// @param[in] group グループ本体を読み込んだハンドラ
  AstFFBank(const FileRegion& attr_loc,
	    const StrStrIntHandler& header,
	    const FFHandler& group);

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
