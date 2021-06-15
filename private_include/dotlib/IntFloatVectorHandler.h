#ifndef INTFLOATVECTORHANDLER_H
#define INTFLOATVECTORHANDLER_H

/// @file IntFloatVectorHandler.h
/// @brief IntFloatVectorHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/ElemHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class IntFloatVectorHandler IntFloatVectorHandler.h "dotlib/IntFloatVectorHandler.h"
/// @brief ( integer, "float, float, ..." ) の形のヘッダ用のハンドラ
//////////////////////////////////////////////////////////////////////
class IntFloatVectorHandler :
  public ElemHandler
{
public:

  /// @brief コンストラクタ
  IntFloatVectorHandler(DotlibParser& parser); ///< [in] パーサー

  /// @brief デストラクタ
  ~IntFloatVectorHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 読み込んだ1番目の値を返す．
  const AstInt*
  value1() const
  {
    return mValue1;
  }

  /// @brief 読み込んだ2番目の値を返す．
  const AstFloatVector*
  value2() const
  {
    return mValue2;
  }


private:
  //////////////////////////////////////////////////////////////////////
  // ElemHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief begin_header() 内で呼ばれる初期化関数
  void
  initialize() override;

  /// @brief ヘッダの値を読み込む処理
  /// @param[in] count read_value() の呼ばれた回数
  bool
  read_value(int count) override;

  /// @brief end_header() 内で呼ばれる終了処理関数
  void
  finalize() override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 1番目の値
  const AstInt* mValue1;

  // 2番目の値
  const AstFloatVector* mValue2;

};

END_NAMESPACE_YM_DOTLIB

#endif // INTFLOATVECTORHANDLER_H
