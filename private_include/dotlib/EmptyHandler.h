#ifndef EMPTYHANDLER_H
#define EMPTYHANDLER_H

/// @file EmptyHandler.h
/// @brief EmptyHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HeaderHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class EmptyHandler Handler.h "HeaderHadler.h"
/// @brief 値をとらないヘッダ用のハンドラ
///
/// 当然，何の値も返せない．
/// ただ単にシンタックスチェックをしている．
//////////////////////////////////////////////////////////////////////
class EmptyHandler :
  public HeaderHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  EmptyHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~EmptyHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // HeaderHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの開始処理
  ///
  /// '(' を読み込んだ時に呼ばれる．
  void
  begin_header() override;

  /// @brief ヘッダの値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  /// @param[in] count read_value() の呼ばれた回数
  bool
  read_header_value(TokenType value_type,
		    const FileRegion& value_loc,
		    int count) override;

  /// @brief 読み込みが終了した時の処理を行う．
  /// @param[in] count 読み込んだ要素数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  end_header(int count) override;

};

END_NAMESPACE_YM_DOTLIB

#endif // EMPTYHANDLER_H
