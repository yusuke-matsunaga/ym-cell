#ifndef INTVECTORHANDLER_H
#define INTVECTORHANDLER_H

/// @file IntVectorHandler.h
/// @brief IntVectorHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/ElemHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class IntVectorHandler IntVectorHandler.h "dotlib/IntVectorHandler.h"
/// @brief "integer, integer, ..." の形のヘッダ用のハンドラ
///
/// つまり全体は文字列だが，内容がコンマで区切られた浮動小数点数
//////////////////////////////////////////////////////////////////////
class IntVectorHandler :
  public ElemHandler
{
public:

  /// @brief コンストラクタ
  IntVectorHandler(DotlibParser& parser); ///< [in] パーサー

  /// @brief デストラクタ
  ~IntVectorHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 読み込んだ値を返す．
  const AstIntVector*
  value() const
  {
    return mValue;
  }


private:
  //////////////////////////////////////////////////////////////////////
  // ElemHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief begin_header() 内で呼ばれる初期化関数
  void
  initialize() override;

  /// @brief ヘッダの値を読み込む処理
  bool
  read_value(int count) override; ///< [in] read_value() の呼ばれた回数

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

  // 読み込んだ値
  const AstIntVector* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // INTVECTORHANDLER_H
