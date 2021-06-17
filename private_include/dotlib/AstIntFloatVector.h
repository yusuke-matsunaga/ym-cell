#ifndef ASTINTFLOATVECTOR_H
#define ASTINTFLOATVECTOR_H

/// @file AstIntFloatVector.h
/// @brief AstIntFloatVector のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
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
  AstIntFloatVector(const AstInt* value1,          ///< [in] 値1
		    const AstFloatVector* value2); ///< [in] 値2

  /// @brief デストラクタ
  ~AstIntFloatVector();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値1を得る．
  const AstInt*
  value1() const
  {
    return mVal1;
  }

  /// @brief 値2を得る．
  const AstFloatVector*
  value2() const
  {
    return mVal2;
  }

  /// @brief ファイル上の位置を返す．
  FileRegion
  loc() const override;

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s,                     ///< [in] 出力先のストリーム
       int indent = 0) const override; ///< [in] インデント量


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

END_NAMESPACE_YM_DOTLIB

#endif // ASTINTFLOATVECTOR_H
