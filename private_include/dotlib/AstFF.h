#ifndef ASTFF_H
#define ASTFF_H

/// @file AstFF.h
/// @brief AstFF のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstFL.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstFF AstFF.h "AstFF.h"
/// @brief AstNode の木から取り出した ff の情報を表すクラス
//////////////////////////////////////////////////////////////////////
class AstFF :
  public AstFL
{
public:

  /// @brief コンストラクタ(ヘッダタイプ1)
  AstFF(const FileRegion& attr_loc,  ///< [in] 属性のファイル上の位置
	const StrStrHandler& header, ///< [in] ヘッダを読み込んだハンドラ
	const FFHandler& group);     ///< [in] グループ本体を読み込んだハンドラ

  /// @brief コンストラクタ(ヘッダタイプ2)
  AstFF(const FileRegion& attr_loc,     ///< [in] 属性のファイル上の位置
	const StrStrIntHandler& header, ///< [in] ヘッダを読み込んだハンドラ
	const FFHandler& group);        ///< [in] グループ本体を読み込んだハンドラ

  /// @brief デストラクタ
  ~AstFF();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief "clocked_on" を返す．
  const AstExpr*
  clocked_on() const
  {
    return mClockedOn;
  }

  /// @brief "clocked_on_also" を返す．
  const AstExpr*
  clocked_on_also() const
  {
    return mClockedOnAlso;
  }

  /// @brief "next_state" を返す．
  const AstExpr*
  next_state() const
  {
    return mNextState;
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

  // clocked_on
  const AstExpr* mClockedOn;

  // clocked_on_also
  const AstExpr* mClockedOnAlso;

  // next_state
  const AstExpr* mNextState;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTFF_H
