#ifndef STRHANDLER_H
#define STRHANDLER_H

/// @file StrHandler.h
/// @brief StrHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/ElemHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class StrStrHandler StrHandler.h "dotlib/StrHandler.h"
/// @brief ( string ) の形式のヘッダ用のハンドラ
//////////////////////////////////////////////////////////////////////
class StrHandler :
  public ElemHandler
{
public:

  /// @brief コンストラクタ
  StrHandler(DotlibParser& parser); ///< [in] パーサー

  /// @brief デストラクタ
  ~StrHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 読み込んだ値を返す．
  const AstString*
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
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 読み込んだ値
  const AstString* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // STRHANDLER_H
