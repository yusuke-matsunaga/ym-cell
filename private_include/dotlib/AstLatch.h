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
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @param[in] header ヘッダを読み込んだハンドラ
  /// @param[in] group グループ本体を読み込んだハンドラ
  AstLatch(const FileRegion& attr_loc,
	   const StrStrHandler& header,
	   const LatchHandler& group);

  /// @brief コンストラクタ
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @param[in] header ヘッダを読み込んだハンドラ
  /// @param[in] group グループ本体を読み込んだハンドラ
  AstLatch(const FileRegion& attr_loc,
	   const StrStrIntHandler& header,
	   const LatchHandler& group);

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
