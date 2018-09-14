#ifndef FLOAT2HEADERHANDLER_H
#define FLOAT2HEADERHANDLER_H

/// @file Float2HeaderHandler.h
/// @brief Float2HeaderHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HeaderHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class Float2Float2HeaderHandler Float2HeaderHandler.h "Float2HeaderHandler.h"
/// @brief 2つの float 型をとる complex attribute ハンドラ
//////////////////////////////////////////////////////////////////////
class Float2HeaderHandler :
  public HeaderHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  Float2HeaderHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~Float2HeaderHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 2つの float 型を取る complex attribute の記述をパースする．
  /// @param[in] dst1, dst2 結果を格納する変数
  /// @retval true 正しくパースした．
  /// @retval false エラーが怒った．
  bool
  parse_value(const AstFloat*& dst1,
	      const AstFloat*& dst2);


protected:
  //////////////////////////////////////////////////////////////////////
  // HeaderHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの開始処理
  ///
  /// '(' を読み込んだ時に呼ばれる．
  void
  begin_header() override;

  /// @brief 値を読み込む処理
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

  // 読み込んだ値
  const AstFloat* mValue1;
  const AstFloat* mValue2;

};

END_NAMESPACE_YM_DOTLIB

#endif // FLOAT2HEADERHANDLER_H
