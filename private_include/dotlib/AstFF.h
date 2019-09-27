#ifndef ASTFF_H
#define ASTFF_H

/// @file AstFF.h
/// @brief AstFF のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
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

  /// @brief コンストラクタ
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @param[in] header ヘッダを読み込んだハンドラ
  /// @param[in] group グループ本体を読み込んだハンドラ
  AstFF(const FileRegion& attr_loc,
	const StrStrHandler& header,
	const FFHandler& group);

  /// @brief コンストラクタ
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @param[in] header ヘッダを読み込んだハンドラ
  /// @param[in] group グループ本体を読み込んだハンドラ
  AstFF(const FileRegion& attr_loc,
	const StrStrIntHandler& header,
	const FFHandler& group);

  /// @brief デストラクタ
  ~AstFF();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief "clocked_on" を返す．
  const AstExpr*
  clocked_on() const;

  /// @brief "clocked_on_also" を返す．
  const AstExpr*
  clocked_on_also() const;

  /// @brief "next_state" を返す．
  const AstExpr*
  next_state() const;

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

  // clocked_on
  const AstExpr* mClockedOn;

  // clocked_on_also
  const AstExpr* mClockedOnAlso;

  // next_state
  const AstExpr* mNextState;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief "clocked_on" を返す．
inline
const AstExpr*
AstFF::clocked_on() const
{
  return mClockedOn;
}

// @brief "clocked_on_also" を返す．
inline
const AstExpr*
AstFF::clocked_on_also() const
{
  return mClockedOnAlso;
}

// @brief "next_state" を返す．
inline
const AstExpr*
AstFF::next_state() const
{
  return mNextState;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTFF_H
