#ifndef ASTINTFLOATVECTOR_H
#define ASTINTFLOATVECTOR_H

/// @file AstIntFloatVector.h
/// @brief AstIntFloatVector のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstIntFloatVector AstIntFloatVector.h "dotlib/AstIntFloatVector.h"
/// @brief integer, float_vector のペアを表す AstNode の派生クラス
//////////////////////////////////////////////////////////////////////
class AstIntFloatVector :
  public AstNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] handler ハンドラ
  AstIntFloatVector(const IntFloatVectorHandler& handler);

  /// @brief デストラクタ
  ~AstIntFloatVector();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値1を得る．
  const AstInt*
  value1() const;

  /// @brief 値2を得る．
  const AstFloatVector*
  value2() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  void
  dump(ostream& s,
       int indent = 0) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値1
  const AstInt* mVal1;

  // 値2
  const AstFloatVector* mVal2;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 値1を得る．
inline
const AstInt*
AstIntFloatVector::value1() const
{
  return mVal1;
}

// @brief 値2を得る．
inline
const AstFloatVector*
AstIntFloatVector::value2() const
{
  return mVal2;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTINTFLOATVECTOR_H
