#ifndef HEADERHANDLER_H
#define HEADERHANDLER_H

/// @file HeaderHandler.h
/// @brief HeaderHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class HeaderHandler HeaderHandler.h "dotlib/HeaderHandler.h"
/// @brief complex attribute/group statement のヘッダ用のハンドラ
///
/// ヘッダ部分が
/// '(' <value>, <value>, <value>, ... ')'
/// の形を仮定してパーズを行う．
/// '(' を読んだ直後に begin_header() を呼び出し，
/// 個々の <value> を読む度に read_value() を呼び出す．
/// 最後の ')' を読んだ直後に end_header() を呼び出す．
/// 継承クラスで begin_header(), read_value(), end_header()
/// を実装する必要がある．
/// ここではヘッダと呼んでいるが complex attribute の場合はそれが
/// 本体となる．
///
/// このクラスは実体を持たない純粋仮想基底クラスである．
/// 継承クラスは以下の通り
/// * EmptyHeaderHandler
/// * FloatHeaderHandler
/// * FloatStrHeaderHandler
/// * FloatVectorHeaderHandler
/// * FloatVectorListHeaderHandler
/// * Str1HeaderHandler
/// * Str2HeaderHandler
/// * Str2IntHeaderHandler
/// * StrListHeaderHandler
//////////////////////////////////////////////////////////////////////
class HeaderHandler :
  public DotlibHandler
{
  friend class DotlibParser;

public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  HeaderHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~HeaderHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダ部分 ( '(' から ')' までの部分のファイル位置を返す．)
  ///
  /// 下記の 'end_header()' の呼び出し時には確定している．
  const FileRegion&
  header_loc() const;


public:
  //////////////////////////////////////////////////////////////////////
  // HeaderHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの開始処理
  ///
  /// '(' を読み込んだ時に呼ばれる．
  virtual
  void
  begin_header() = 0;

  /// @brief ヘッダの値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  /// @param[in] count read_value() の呼ばれた回数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  virtual
  bool
  read_header_value(TokenType value_type,
		    const FileRegion& value_loc,
		    int count) = 0;

  /// @brief 読み込みが終了した時の処理を行う．
  /// @param[in] count 読み込んだ要素数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  virtual
  bool
  end_header(int count) = 0;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ヘッダ部分の位置
  FileRegion mHeaderLoc;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief ヘッダ部分 ( '(' から ')' までの部分のファイル位置を返す．)
const FileRegion&
HeaderHandler::header_loc() const
{
  return mHeaderLoc;
}

END_NAMESPACE_YM_DOTLIB

#endif // HEADERHANDLER_H
