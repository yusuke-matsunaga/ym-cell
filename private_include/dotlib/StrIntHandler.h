#ifndef STRINTHANDLER_H
#define STRINTHANDLER_H

/// @file StrIntHandler.h
/// @brief StrIntHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/ElemHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class StrIntHandler StrIntHandler.h "dotlib/StrIntHandler.h"
/// @brief ( string, integer ) の形式のヘッダ用ハンドラ
//////////////////////////////////////////////////////////////////////
class StrIntHandler :
  public ElemHandler
{
public:

  /// @brief コンストラクタ
  StrIntHandler(DotlibParser& parser); ///< [in] パーサー

  /// @brief デストラクタ
  ~StrIntHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 1番目の要素を返す．
  const AstString*
  value1() const
  {
    return mValue1;
  }

  /// @brief 2番目の要素を返す．
  const AstInt*
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
  bool
  read_value(int count) override; ///< [in] read_value() の呼ばれた回数

  /// @brief end_header() 内で呼ばれる終了処理関数
  void
  finalize() override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 1番目の要素
  const AstString* mValue1;

  // 2番目の要素
  const AstInt* mValue2;

};

END_NAMESPACE_YM_DOTLIB

#endif // STRINTHANDLER_H
