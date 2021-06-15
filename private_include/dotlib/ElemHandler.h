#ifndef ELEMHANDLER_H
#define ELEMHANDLER_H

/// @file ElemHandler.h
/// @brief ElemHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/HeaderHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class ElemHandler ElemHandler.h "ElemHandler.h"
/// @brief 固定形式のヘッダ用ハンドラ
//////////////////////////////////////////////////////////////////////
class ElemHandler :
  public HeaderHandler
{
public:

  /// @brief コンストラクタ
  ElemHandler(DotlibParser& parser, ///< [in] パーサー
	      int num);             ///< [in] ヘッダ内の要素数

  /// @brief デストラクタ
  ~ElemHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // HeaderHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの開始処理
  ///
  /// '(' を読み込んだ時に呼ばれる．
  void
  _begin_header() override;

  /// @brief ヘッダの値を読み込む処理
  /// @param[in] count read_value() の呼ばれた回数
  bool
  _read_header_value(int count) override;

  /// @brief 読み込みが終了した時の処理を行う．
  /// @param[in] count 読み込んだ要素数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  _end_header(int count) override;


private:
  //////////////////////////////////////////////////////////////////////
  // ElemHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief begin_header() 内で呼ばれる初期化関数
  virtual
  void
  initialize() = 0;

  /// @brief read_header_value() 内で呼ばれる関数
  /// @param[in] count read_value() の呼ばれた回数
  virtual
  bool
  read_value(int count) = 0;

  /// @brief end_header() 内で呼ばれる終了処理関数
  virtual
  void
  finalize() = 0;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 予想される要素数
  int mNum;

};

END_NAMESPACE_YM_DOTLIB

#endif // ELEM1HANDLER_H
