﻿#ifndef EMPTYGROUPHANDLER_H
#define EMPTYGROUPHANDLER_H

/// @file EmptyGroupHandler.h
/// @brief EmptyGroupHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class EmptyGroupHandler GroupHandler.h "GroupHadler.h"
/// @brief 値をとらないグループ用のハンドラ
///
/// 継承クラスは以下の通り
///   * InternalPowerHandler
///   * TimingHandler
//////////////////////////////////////////////////////////////////////
class EmptyGroupHandler :
  public GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  EmptyGroupHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~EmptyGroupHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // CGHandler の仮想関数
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
  /// @param[in] header_loc '(' から ')' までのファイル上の位置
  /// @param[in] count 読み込んだ要素数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  end_header(const FileRegion& header_loc,
	     int count) override;

};

END_NAMESPACE_YM_DOTLIB

#endif // EMPTYGROUPHANDLER_H