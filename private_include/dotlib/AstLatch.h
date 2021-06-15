#ifndef ASTLATCH_H
#define ASTLATCH_H

/// @file AstLatch.h
/// @brief AstLatch のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
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
  AstLatch(const FileRegion& attr_loc,  ///< [in] 属性のファイル上の位置
	   const StrStrHandler& header, ///< [in] ヘッダを読み込んだハンドラ
	   const LatchHandler& group);  ///< [in] グループ本体を読み込んだハンドラ

  /// @brief コンストラクタ
  AstLatch(const FileRegion& attr_loc,     ///< [in] 属性のファイル上の位置
	   const StrStrIntHandler& header, ///< [in] ヘッダを読み込んだハンドラ
	   const LatchHandler& group);     ///< [in] グループ本体を読み込んだハンドラ

  /// @brief デストラクタ
  ~AstLatch();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief "enable" を返す．
  const AstExpr*
  enable() const
  {
    return mEnable;
  }

  /// @brief "enable_also" を返す．
  const AstExpr*
  enable_also() const
  {
    return mEnableAlso;
  }

  /// @brief "data_in" を返す．
  const AstExpr*
  data_in() const
  {
    return mDataIn;
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

  // enable
  const AstExpr* mEnable;

  // enable_also
  const AstExpr* mEnableAlso;

  // data_in
  const AstExpr* mDataIn;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTLATCH_H
