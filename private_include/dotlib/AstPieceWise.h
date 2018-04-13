#ifndef ASTPIECEWISE_H
#define ASTPIECEWISE_H

/// @file AstPieceWise.h
/// @brief AstPieceWise のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstPieceWise AstPieceWise.h "AstPieceWise.h"
/// @brief 折れ線モデルを表すクラス
//////////////////////////////////////////////////////////////////////
class AstPieceWise :
  public AstNode
{
  friend class AstMgr;

private:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] value1
  /// @param[in] value2
  AstPieceWise(const FileRegion& loc,
	       const AstInt* value1,
	       const AstFloat* value2);

  /// @brief デストラクタ
  virtual
  ~AstPieceWise();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値１を返す．
  const AstInt*
  value1() const;

  /// @brief 値２を返す．
  const AstFloat*
  value2() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  virtual
  void
  dump(ostream& s,
       int indent = 0) const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値1
  const AstInt* mValue1;

  // 値2
  const AstFloat* mValue2;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 値１を返す．
inline
const AstInt*
AstPieceWise::value1() const
{
  return mValue1;
}

// @brief 値２を返す．
inline
const AstFloat*
AstPieceWise::value2() const
{
  return mValue2;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTPIECEWISE_H
