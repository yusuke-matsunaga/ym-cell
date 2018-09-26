#ifndef EMPTYHANDLER_H
#define EMPTYHANDLER_H

/// @file EmptyHandler.h
/// @brief EmptyHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/ElemHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class EmptyHandler Handler.h "HeaderHadler.h"
/// @brief 値をとらないヘッダ用のハンドラ
///
/// 当然，何の値も返せない．
/// ただ単にシンタックスチェックをしている．
//////////////////////////////////////////////////////////////////////
class EmptyHandler :
  public ElemHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  EmptyHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~EmptyHandler();


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

};

END_NAMESPACE_YM_DOTLIB

#endif // EMPTYHANDLER_H
