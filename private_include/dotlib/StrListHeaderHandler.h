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
/// @brief ( string, string, ... ) の形式のヘッダ用のハンドラ
//////////////////////////////////////////////////////////////////////
class StrListHeaderHandler :
  public HeaderHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  StrListHeaderHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~StrListHeaderHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 読み込んだ値を返す．
  ///
  /// といってもこれはこのクラス内のオブジェクトへの参照なので
  /// 永続的に保持するならコピーする必要がある．
  const vector<const AstString*>&
  value() const;


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
  /// @param[in] count 読み込んだ要素数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  end_header(int count) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 読み込んだ値
  vector<const AstString*> mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 読み込んだ値を返す．
inline
const vector<const AstString*>&
StrListHeaderHandler::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // STRLISTHEADERHANDLER_H
