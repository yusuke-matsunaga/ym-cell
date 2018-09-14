#ifndef STRLISTHEADERHANDLER_H
#define STRLISTHEADERHANDLER_H

/// @file StrListHeaderHandler.h
/// @brief StrListHeaderHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HeaderHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class StrListHeaderHandler StrListHeaderHandler.h "dotlib/StrListHeaderHandler.h"
/// @brief 文字列型のリストをとる complex attribute ハンドラ
//////////////////////////////////////////////////////////////////////
class StrListCompleHandler :
  public HeaderHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  StrListCompleHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~StrListCompleHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 文字列型のリストを取る complex attribute の記述をパースする．
  /// @param[in] dst_list 結果を格納するリスト
  /// @retval true 正しくパースした．
  /// @retval false エラーが怒った．
  bool
  parse_value(const AstString*& dst);


public:
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
  const AstString* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // STRLISTHEADERHANDLER_H
