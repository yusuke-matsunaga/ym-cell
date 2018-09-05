#ifndef PIECEWISEHANDLER_H
#define PIECEWISEHANDLER_H

/// @file PieceWiseHandler.h
/// @brief PieceWiseHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/ComplexHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class PieceWiseHandler PieceWiseHandler.h "PieceWiseHandler.h"
/// @brief 折れ線近似モデル用ののcomplex attribute ハンドラ
//////////////////////////////////////////////////////////////////////
class PieceWiseHandler :
  public ComplexHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  PieceWiseHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~PieceWiseHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief piece_wise attribute の記述をパースする．
  ///
  /// エラーが起きた場合には nullptr が返される．
  const AstPieceWise*
  parse_value();


protected:
  //////////////////////////////////////////////////////////////////////
  // ComplexHandler の仮想関数
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

  // 第1パラメータ
  int mVal1;

  // 第2パラメータ
  double mVal2;

  // 読み込んだ値
  AstPieceWise* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // PIECEWISEHANDLER_H
