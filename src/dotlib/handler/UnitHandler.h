﻿#ifndef UNITHANDLER_H
#define UNITHANDLER_H

/// @file UnitHandler.h
/// @brief UnitHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/ComplexHandler.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class UnitHandler UnitHandler.h "UnitHandler.h"
/// @brief 単位型のcomplex attribute ハンドラ
//////////////////////////////////////////////////////////////////////
class UnitHandler :
  public ComplexHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  UnitHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~UnitHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief unit attribute の記述をパースする．
  ///
  /// エラーが起きた場合には nullptr が返される．
  const AstUnit*
  parse_value();


protected:
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


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 単位の値
  double mUnitVal;

  // 単位の文字列
  ShString mUnitStr;

  // 読み込んだ値
  AstUnit* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // UNITHANDLER_H
