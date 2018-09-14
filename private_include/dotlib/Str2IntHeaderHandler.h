#ifndef STR2INTHEADERHANDLER_H
#define STR2INTHEADERHANDLER_H

/// @file Str2IntHeaderHandler.h
/// @brief Str2IntHeaderHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HeaderHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class Str2IntHeaderHandler HeaderHandler.h "dotlib/HeaderHadler.h"
/// @brief ( string, string, integer ) の形式のヘッダ用のハンドラ
//////////////////////////////////////////////////////////////////////
class Str2IntHeaderHandler :
  public HeaderHandler
{
public:

  /// @brief 親を持つハンドラ用のコンストラクタ
  /// @param[in] parser パーサー
  Str2IntHeaderHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~Str2IntHeaderHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 1番目の値を取り出す．
  const AstString*
  value1() const;

  /// @brief 2番目の値を取り出す．
  const AstString*
  value2() const;

  /// @brief 3番目の値を取り出す．
  const AstInt*
  value3() const;


protected:
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


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ヘッダの値1
  const AstString* mValue1;

  // ヘッダの値2
  const AstString* mValue2;

  // ヘッダの値3
  const AstInt* mValue3;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 1番目の値を取り出す．
inline
const AstString*
Str2IntHeaderHandler::value1() const
{
  return mValue1;
}

// @brief 2番目の値を取り出す．
inline
const AstString*
Str2IntHeaderHandler::value2() const
{
  return mValue2;
}

// @brief 3番目の値を取り出す．
inline
const AstInt*
Str2IntHeaderHandler::value3() const
{
  return mValue3;
}

END_NAMESPACE_YM_DOTLIB

#endif // STR2INTHEADERHANDLER_H
