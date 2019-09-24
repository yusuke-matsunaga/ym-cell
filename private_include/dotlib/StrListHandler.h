#ifndef STRLISTHANDLER_H
#define STRLISTHANDLER_H

/// @file StrListHandler.h
/// @brief StrListHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HeaderHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class StrListHandler StrListHandler.h "dotlib/StrListHandler.h"
/// @brief ( string, string, ... ) の形式のヘッダ用のハンドラ
//////////////////////////////////////////////////////////////////////
class StrListHandler :
  public HeaderHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  StrListHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~StrListHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 読み込んだ値を返す．
  vector<const AstString*>
  value() const;


private:
  //////////////////////////////////////////////////////////////////////
  // Handler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの開始処理
  ///
  /// '(' を読み込んだ時に呼ばれる．
  void
  _begin_header() override;

  /// @brief 値を読み込む処理
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
vector<const AstString*>
StrListHandler::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // STRLISTHANDLER_H
