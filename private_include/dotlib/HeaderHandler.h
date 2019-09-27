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
/// * Float2HeaderHandler
/// * FloatStrHeaderHandler
/// * FloatVectorHeaderHandler
/// * FloatVectorListHeaderHandler
/// * IntFloatHeaderHandler
/// * IntFloatVectorHeaderHandler
/// * IntVectorHeaderHandler
/// * Str1HeaderHandler
/// * Str2HeaderHandler
/// * Str2IntHeaderHandler
/// * StrListHeaderHandler
//////////////////////////////////////////////////////////////////////
class HeaderHandler :
  public DotlibHandler
{
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

  /// @brief '(' のファイル上の位置を返す．
  const FileRegion&
  first_loc() const;

  /// @brief ')' のファイル上の位置を返す．
  const FileRegion&
  last_loc() const;


public:
  //////////////////////////////////////////////////////////////////////
  // DotlibParser から用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの開始処理
  /// @param[in] loc '(' のファイル上の位置
  ///
  /// '(' を読み込んだ時に呼ばれる．
  void
  begin_header(const FileRegion& loc);

  /// @brief ヘッダの値を読み込む処理
  /// @param[in] count read_header_value() の呼ばれた回数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  read_header_value(int count);

  /// @brief 読み込みが終了した時の処理を行う．
  /// @param[in] loc ')' のファイル上の位置
  /// @param[in] count 読み込んだ要素数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  ///
  /// ')' を読み込んだ直後に呼ばれる．
  bool
  end_header(const FileRegion& loc,
	     int count);


private:
  //////////////////////////////////////////////////////////////////////
  // HeaderHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの開始処理
  /// '(' を読み込んだ時に呼ばれる．
  virtual
  void
  _begin_header() = 0;

  /// @brief ヘッダの値を読み込む処理
  /// @param[in] count read_header_value() の呼ばれた回数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  virtual
  bool
  _read_header_value(int count) = 0;

  /// @brief 読み込みが終了した時の処理を行う．
  /// @param[in] count 読み込んだ要素数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  ///
  /// ')' を読み込んだ直後に呼ばれる．
  virtual
  bool
  _end_header(int count) = 0;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // '(' のファイル上の位置
  FileRegion mFirstLoc;

  // ')' のファイル上の位置
  FileRegion mLastLoc;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief '(' のファイル上の位置を返す．
inline
const FileRegion&
HeaderHandler::first_loc() const
{
  return mFirstLoc;
}

// @brief ')' のファイル上の位置を返す．
inline
const FileRegion&
HeaderHandler::last_loc() const
{
  return mLastLoc;
}

END_NAMESPACE_YM_DOTLIB

#endif // HEADERHANDLER_H
