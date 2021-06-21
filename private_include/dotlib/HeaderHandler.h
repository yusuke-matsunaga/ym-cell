#ifndef HEADERHANDLER_H
#define HEADERHANDLER_H

/// @file HeaderHandler.h
/// @brief HeaderHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"


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
/// 継承クラスは
/// * 要素数が固定
/// * 要素数が可変
/// の２種類に分類される．
/// 前者は FixedElemHeader の継承クラスで以下の通り．
/// * EmptyHeader
/// * FloatFloatHeader
/// * FloatStrHeader
/// * FloatVectorHeader
/// * IntFloatHeader
/// * IntFloatVectorHeader
/// * IntVectorHeader
/// * StrStrHeader
/// * StrStrIntHeader
/// * StrStrStrHeader
/// * TechnologyHeader
/// 後者は以下の通り．
/// * FloatVectorListHeader
/// * StrListHeader
//////////////////////////////////////////////////////////////////////
class HeaderHandler
{
public:

  /// @brief コンストラクタ
  HeaderHandler() = default;

  /// @brief デストラクタ
  ~HeaderHandler() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの開始処理
  ///
  /// '(' を読み込んだ時に呼ばれる．
  void
  begin_header(const FileRegion& loc); ///< [in] '(' のファイル上の位置

  /// @brief ヘッダの値を読み込む処理
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  read_header_value(Scanner& scanner, ///< [in] 字句解析器
		    int count);       ///< [in] read_header_value() の呼ばれた回数

  /// @brief 読み込みが終了した時の処理を行う．
  /// @retrun 結果の AstValue を返す．
  ///
  /// - ')' を読み込んだ直後に呼ばれる．
  /// - エラーの時は nullptr を返す．
  AstValuePtr
  end_header(const FileRegion& loc, ///< [in] ')' のファイル上の位置
	     int count);            ///< [in] 読み込んだ要素数


protected:
  //////////////////////////////////////////////////////////////////////
  // 派生クラスから用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief '(' の位置を返す．
  const FileRegion&
  lp_loc() const { return mLpLoc; }

  /// @brief ')' の位置を返す．
  const FileRegion&
  rp_loc() const { return mRpLoc; }


private:
  //////////////////////////////////////////////////////////////////////
  // HeaderHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの開始処理
  ///
  /// '(' を読み込んだ時に呼ばれる．
  virtual
  void
  _begin_header();

  /// @brief ヘッダの値を読み込む処理
  /// @return 読み込んだ値を返す．
  virtual
  AstValuePtr
  _read_header_value(Scanner& scanner, ///< [in] 字句解析器
		     int count) = 0;   ///< [in] read_header_value() の呼ばれた回数

  /// @brief 読み込みが終了した時の処理を行う．
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起こった．
  ///
  /// - ')' を読み込んだ直後に呼ばれる．
  virtual
  bool
  _end_header(int count) = 0; ///< [in] 読み込んだ要素数


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // '(' の位置
  FileRegion mLpLoc;

  // ')' の位置
  FileRegion mRpLoc;

  // 読み込んだ値
  vector<AstValuePtr> mValueList;

};


//////////////////////////////////////////////////////////////////////
/// @class FixedElemHeader HeaderHandler.h "dotlib/HeaderHadler.h"
/// @brief 固定形式のヘッダ用ハンドラ
//////////////////////////////////////////////////////////////////////
class FixedElemHeader :
  public HeaderHandler
{
public:

  /// @brief コンストラクタ
  FixedElemHeader(int num); ///< [in] ヘッダ内の要素数

  /// @brief デストラクタ
  ~FixedElemHeader() = default;


private:
  //////////////////////////////////////////////////////////////////////
  // HeaderHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの値を読み込む処理
  AstValuePtr
  _read_header_value(Scanner& scanner,    ///< [in] 字句解析器
		     int count) override; ///< [in] read_header_value() の呼ばれた回数

  /// @brief 読み込みが終了した時の処理を行う．
  bool
  _end_header(int count) override;   ///< [in] 読み込んだ要素数


private:
  //////////////////////////////////////////////////////////////////////
  // FixedElemHeader の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief read_header_value() 内で呼ばれる関数
  virtual
  AstValuePtr
  read_value(Scanner& scanner,    ///< [in] 字句解析器
	     int count) = 0; ///< [in] ヘッダ中の位置


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 予想される要素数
  int mNum;

};


//////////////////////////////////////////////////////////////////////
/// @class EmptyHeader HeaderHandler.h "dotlib/HeaderHadler.h"
/// @brief 値をとらないヘッダ用のハンドラ
///
/// 当然，何の値も返せない．
/// ただ単にシンタックスチェックをしている．
//////////////////////////////////////////////////////////////////////
class EmptyHeader :
  public FixedElemHeader
{
public:

  /// @brief コンストラクタ
  EmptyHeader();

  /// @brief デストラクタ
  ~EmptyHeader() = default;


private:
  //////////////////////////////////////////////////////////////////////
  // FixedElemHeader の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの値を読み込む処理
  AstValuePtr
  read_value(Scanner& scanner,    ///< [in] 字句解析器
	     int count) override; ///< [in] read_value() の呼ばれた回数

};


//////////////////////////////////////////////////////////////////////
/// @class FloatFloatHeader HeaderHandler.h "dotlib/HeaderHadler.h"
/// @brief ( float, float ) の形式のヘッダ用ハンドラ
//////////////////////////////////////////////////////////////////////
class FloatFloatHeader :
  public FixedElemHeader
{
public:

  /// @brief コンストラクタ
  FloatFloatHeader();

  /// @brief デストラクタ
  ~FloatFloatHeader() = default;


private:
  //////////////////////////////////////////////////////////////////////
  // ElemHeader の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの値を読み込む処理
  AstValuePtr
  read_value(Scanner& scanner,    ///< [in] 字句解析器
	     int count) override; ///< [in] read_value() の呼ばれた回数

};


//////////////////////////////////////////////////////////////////////
/// @class FloatStrHeader HeaderHandler.h "dotlib/HeaderHadler.h"
/// @brief ( float, string ) の形式のヘッダ用ハンドラ
//////////////////////////////////////////////////////////////////////
class FloatStrHeader :
  public FixedElemHeader
{
public:

  /// @brief コンストラクタ
  FloatStrHeader();

  /// @brief デストラクタ
  ~FloatStrHeader() = default;


private:
  //////////////////////////////////////////////////////////////////////
  // ElemHeader の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの値を読み込む処理
  AstValuePtr
  read_value(Scanner& scanner,    ///< [in] 字句解析器
	     int count) override; ///< [in] read_value() の呼ばれた回数

};


//////////////////////////////////////////////////////////////////////
/// @class FloatVectorHeader HeaderHandler.h "dotlib/HeaderHadler.h"
/// @brief ( "float, float, ..." ) ; の形のヘッダ用のハンドラ
///
/// つまり全体は文字列だが，内容がコンマで区切られた浮動小数点数
//////////////////////////////////////////////////////////////////////
class FloatVectorHeader :
  public FixedElemHeader
{
public:

  /// @brief コンストラクタ
  FloatVectorHeader();

  /// @brief デストラクタ
  ~FloatVectorHeader() = default;


private:
  //////////////////////////////////////////////////////////////////////
  // ElemHeader の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの値を読み込む処理
  AstValuePtr
  read_value(Scanner& scanner,    ///< [in] 字句解析器
	     int count) override; ///< [in] read_value() の呼ばれた回数

};


//////////////////////////////////////////////////////////////////////
/// @class FloatVectorListHeader HeaderHandler.h "dotlib/HeaderHadler.h"
/// @brief ("float, float, ...", "float, float, ...", ... ) の形式のヘッダ用のハンドラ
///
/// 意味的には２次元の配列だが結果は AstFloatVector で返す．
//////////////////////////////////////////////////////////////////////
class FloatVectorListHeader :
  public HeaderHandler
{
public:

  /// @brief コンストラクタ
  FloatVectorListHeader() = default;

  /// @brief デストラクタ
  ~FloatVectorListHeader() = default;


private:
  //////////////////////////////////////////////////////////////////////
  // HeaderHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む処理
  AstValuePtr
  _read_header_value(Scanner& scanner,    ///< [in] 字句解析器
		     int count) override; ///< [in] read_value() の呼ばれた回数

  /// @brief 読み込みが終了した時の処理を行う．
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起こった．
  bool
  _end_header(int count) override; ///< [in] 読み込んだ要素数

};


//////////////////////////////////////////////////////////////////////
/// @class IntFloatHeader HeaderHandler.h "dotlib/HeaderHadler.h"
/// @brief ( integer, float ) の形式のヘッダ用ハンドラ
//////////////////////////////////////////////////////////////////////
class IntFloatHeader :
  public FixedElemHeader
{
public:

  /// @brief コンストラクタ
  IntFloatHeader();

  /// @brief デストラクタ
  ~IntFloatHeader() = default;


private:
  //////////////////////////////////////////////////////////////////////
  // ElemHeader の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの値を読み込む処理
  AstValuePtr
  read_value(Scanner& scanner,    ///< [in] 字句解析器
	     int count) override;

};


//////////////////////////////////////////////////////////////////////
/// @class IntFloatVectorHeader HeaderHandler.h "dotlib/HeaderHadler.h"
/// @brief ( integer, "float, float, ..." ) の形のヘッダ用のハンドラ
//////////////////////////////////////////////////////////////////////
class IntFloatVectorHeader :
  public FixedElemHeader
{
public:

  /// @brief コンストラクタ
  IntFloatVectorHeader();

  /// @brief デストラクタ
  ~IntFloatVectorHeader() = default;


private:
  //////////////////////////////////////////////////////////////////////
  // ElemHeader の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの値を読み込む処理
  AstValuePtr
  read_value(Scanner& scanner,    ///< [in] 字句解析器
	     int count) override;

};


//////////////////////////////////////////////////////////////////////
/// @class IntVectorHeader HeaderHandler.h "dotlib/HeaderHadler.h"
/// @brief "integer, integer, ..." の形のヘッダ用のハンドラ
///
/// つまり全体は文字列だが，内容がコンマで区切られた浮動小数点数
//////////////////////////////////////////////////////////////////////
class IntVectorHeader :
  public FixedElemHeader
{
public:

  /// @brief コンストラクタ
  IntVectorHeader();

  /// @brief デストラクタ
  ~IntVectorHeader() = default;


private:
  //////////////////////////////////////////////////////////////////////
  // ElemHeader の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの値を読み込む処理
  AstValuePtr
  read_value(Scanner& scanner,    ///< [in] 字句解析器
	     int count) override; ///< [in] read_value() の呼ばれた回数

};


//////////////////////////////////////////////////////////////////////
/// @class StrFloatHeader HeaderHandler.h "dotlib/HeaderHadler.h"
/// @brief ( string, float ) の形式のヘッダ用ハンドラ
//////////////////////////////////////////////////////////////////////
class StrFloatHeader :
  public FixedElemHeader
{
public:

  /// @brief コンストラクタ
  StrFloatHeader();

  /// @brief デストラクタ
  ~StrFloatHeader() = default;


private:
  //////////////////////////////////////////////////////////////////////
  // ElemHeader の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの値を読み込む処理
  AstValuePtr
  read_value(Scanner& scanner,    ///< [in] 字句解析器
	     int count) override; ///< [in] read_value() の呼ばれた回数

};


//////////////////////////////////////////////////////////////////////
/// @class StrListHeader HeaderHandler.h "dotlib/HeaderHadler.h"
/// @brief ( string, string, ... ) の形式のヘッダ用のハンドラ
//////////////////////////////////////////////////////////////////////
class StrListHeader :
  public HeaderHandler
{
public:

  /// @brief コンストラクタ
  StrListHeader() = default;

  /// @brief デストラクタ
  ~StrListHeader() = default;


private:
  //////////////////////////////////////////////////////////////////////
  // HeaderHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む処理
  AstValuePtr
  _read_header_value(Scanner& scanner,    ///< [in] 字句解析器
		     int count) override; ///< [in] read_value() の呼ばれた回数

  /// @brief 読み込みが終了した時の処理を行う．
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  _end_header(int count) override; ///< [in] 読み込んだ要素数

};


//////////////////////////////////////////////////////////////////////
/// @class StrStrHeader HeaderHandler.h "dotlib/HeaderHadler.h"
/// @brief ( string ) の形式のヘッダ用のハンドラ
//////////////////////////////////////////////////////////////////////
class StrHeader :
  public FixedElemHeader
{
public:

  /// @brief コンストラクタ
  StrHeader();

  /// @brief デストラクタ
  ~StrHeader() = default;


private:
  //////////////////////////////////////////////////////////////////////
  // ElemHeader の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの値を読み込む処理
  AstValuePtr
  read_value(Scanner& scanner,    ///< [in] 字句解析器
	     int count) override; ///< [in] read_value() の呼ばれた回数

};

//////////////////////////////////////////////////////////////////////
/// @class StrIntHeader HeaderHandler.h "dotlib/HeaderHadler.h"
/// @brief ( string, integer ) の形式のヘッダ用ハンドラ
//////////////////////////////////////////////////////////////////////
class StrIntHeader :
  public FixedElemHeader
{
public:

  /// @brief コンストラクタ
  StrIntHeader();

  /// @brief デストラクタ
  ~StrIntHeader() = default;


private:
  //////////////////////////////////////////////////////////////////////
  // ElemHeader の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの値を読み込む処理
  AstValuePtr
  read_value(Scanner& scanner,    ///< [in] 字句解析器
	     int count) override; ///< [in] read_value() の呼ばれた回数

};


//////////////////////////////////////////////////////////////////////
/// @class StrStrStrStrHeader HeaderHandler.h "dotlib/HeaderHadler.h"
/// @brief ( string, string ) の形式のヘッダ用のハンドラ
//////////////////////////////////////////////////////////////////////
class StrStrHeader :
  public FixedElemHeader
{
public:

  /// @brief コンストラクタ
  StrStrHeader();

  /// @brief デストラクタ
  ~StrStrHeader() = default;


private:
  //////////////////////////////////////////////////////////////////////
  // ElemHeader の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの値を読み込む処理
  AstValuePtr
  read_value(Scanner& scanner,    ///< [in] 字句解析器
	     int count) override; ///< [in] read_value() の呼ばれた回数

};


//////////////////////////////////////////////////////////////////////
/// @class StrStrIntHeader HeaderHandler.h "dotlib/HeaderHadler.h"
/// @brief ( string, string, integer ) の形式のヘッダ用のハンドラ
//////////////////////////////////////////////////////////////////////
class StrStrIntHeader :
  public FixedElemHeader
{
public:

  /// @brief 親を持つハンドラ用のコンストラクタ
  StrStrIntHeader();

  /// @brief デストラクタ
  ~StrStrIntHeader() = default;


private:
  //////////////////////////////////////////////////////////////////////
  // ElemHeader の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの値を読み込む処理
  AstValuePtr
  read_value(Scanner& scanner,    ///< [in] 字句解析器
	     int count) override; ///< [in] read_value() の呼ばれた回数

};


//////////////////////////////////////////////////////////////////////
/// @class StrStrStrSHeader HeaderHandler.h "dotlib/HeaderHadler.h"
/// @brief ( string, string, string ) の形式のヘッダ用のハンドラ
//////////////////////////////////////////////////////////////////////
class StrStrStrHeader :
  public FixedElemHeader
{
public:

  /// @brief コンストラクタ
  StrStrStrHeader();

  /// @brief デストラクタ
  ~StrStrStrHeader() = default;


private:
  //////////////////////////////////////////////////////////////////////
  // ElemHeader の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの値を読み込む処理
  AstValuePtr
  read_value(Scanner& scanner,    ///< [in] 字句解析器
	     int count) override; ///< [in] read_value() の呼ばれた回数

};


//////////////////////////////////////////////////////////////////////
/// @class TechnologyHeader HeaderHandler.h "dotlib/HeaderHadler.h"
/// @brief ( string ) の形式のヘッダ用のハンドラ
///
/// ただし，string は technology を表すキーワード．
//////////////////////////////////////////////////////////////////////
class TechnologyHeader :
  public FixedElemHeader
{
public:

  /// @brief コンストラクタ
  TechnologyHeader();

  /// @brief デストラクタ
  ~TechnologyHeader() = default;


private:
  //////////////////////////////////////////////////////////////////////
  // ElemHeader の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの値を読み込む処理
  AstValuePtr
  read_value(Scanner& scanner,    ///< [in] 字句解析器
	     int count) override; ///< [in] read_value() の呼ばれた回数

};

END_NAMESPACE_YM_DOTLIB

#endif // HEADERHANDLER_H
