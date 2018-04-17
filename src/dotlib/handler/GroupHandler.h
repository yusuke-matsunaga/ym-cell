#ifndef GROUPHANDLER_H
#define GROUPHANDLER_H

/// @file GroupHandler.h
/// @brief GroupHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "CGHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class GroupHandler GroupHandler.h "GroupHandler.h"
/// @brief group statement 用のハンドラ
///
/// このクラスではなにもパーズしない．
/// 正しく処理させるためには継承クラスで対象の属性を
/// parse_attr() で処理しなければならない．
//////////////////////////////////////////////////////////////////////
class GroupHandler :
  public CGHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  GroupHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~GroupHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // DotlibHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 属性値を読み込む．
  /// @param[in] attr_name 属性名
  /// @param[in] attr_loc ファイル上の位置
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  virtual
  bool
  parse_attr_value(AttrType attr_type,
		   const FileRegion& attr_loc) override;


protected:
  //////////////////////////////////////////////////////////////////////
  // GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ記述の始まり
  virtual
  void
  begin_group() = 0;

  /// @brief attr_type に対応する属性を読み込む．
  /// @param[in] attr_type 対象の属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  virtual
  bool
  parse_attr(AttrType attr_type,
	     const FileRegion& attr_loc) = 0;

  /// @brief グループ記述の終わり
  /// @param[in] attr_type 対象の属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  virtual
  bool
  end_group(AttrType attr_type,
	    const FileRegion& attr_loc) = 0;


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いられる GroupHandler の関数
  //////////////////////////////////////////////////////////////////////


protected:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

};


//////////////////////////////////////////////////////////////////////
/// @class EmptyGroupHandler GroupHandler.h "GroupHadler.h"
/// @brief 値をとらないグループ用のハンドラ
//////////////////////////////////////////////////////////////////////
class EmptyGroupHandler :
  public GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  EmptyGroupHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~EmptyGroupHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // CGHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの開始処理
  ///
  /// '(' を読み込んだ時に呼ばれる．
  virtual
  void
  begin_header();

  /// @brief 値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  /// @param[in] count read_value() の呼ばれた回数
  virtual
  bool
  read_value(TokenType value_type,
	     const FileRegion& value_loc,
	     int count) override;

  /// @brief 読み込みが終了した時の処理を行う．
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  /// @param[in] header_loc '(' から ')' までのファイル上の位置
  /// @param[in] count 読み込んだ要素数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  virtual
  bool
  end_header(AttrType attr_type,
	     const FileRegion& attr_loc,
	     const FileRegion& header_loc,
	     int count) override;

};


//////////////////////////////////////////////////////////////////////
/// @class Str1GroupHandler GroupHandler.h "GroupHadler.h"
/// @brief 1つの文字列型をとるグループ用のハンドラ
//////////////////////////////////////////////////////////////////////
class Str1GroupHandler :
  public GroupHandler
{
public:

  /// @brief 親を持たないハンドラ用のコンストラクタ
  /// @param[in] parser パーサー
  Str1GroupHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~Str1GroupHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの値をクリアする．
  void
  clear_header();

  /// @brief ヘッダの値を取り出す．
  const AstString*
  header_value() const;


protected:
  //////////////////////////////////////////////////////////////////////
  // CGHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの開始処理
  ///
  /// '(' を読み込んだ時に呼ばれる．
  virtual
  void
  begin_header();

  /// @brief 値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  /// @param[in] count read_value() の呼ばれた回数
  virtual
  bool
  read_value(TokenType value_type,
	     const FileRegion& value_loc,
	     int count) override;

  /// @brief 読み込みが終了した時の処理を行う．
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  /// @param[in] header_loc '(' から ')' までのファイル上の位置
  /// @param[in] count 読み込んだ要素数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  virtual
  bool
  end_header(AttrType attr_type,
	     const FileRegion& attr_loc,
	     const FileRegion& header_loc,
	     int count) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ヘッダの値
  AstString* mHeaderValue;

};


//////////////////////////////////////////////////////////////////////
/// @class Str2GroupHandler GroupHandler.h "GroupHadler.h"
/// @brief 2つの文字列型をとるグループ用のハンドラ
//////////////////////////////////////////////////////////////////////
class Str2GroupHandler :
  public GroupHandler
{
public:

  /// @brief 親を持つハンドラ用のコンストラクタ
  /// @param[in] parser パーサー
  Str2GroupHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~Str2GroupHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの値をクリアする．
  void
  clear_header();

  /// @brief ヘッダの値1を取り出す．
  const AstString*
  header_value1() const;

  /// @brief ヘッダの値2を取り出す．
  const AstString*
  header_value2() const;


protected:
  //////////////////////////////////////////////////////////////////////
  // CHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの開始処理
  ///
  /// '(' を読み込んだ時に呼ばれる．
  virtual
  void
  begin_header();

  /// @brief 値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  /// @param[in] count read_value() の呼ばれた回数
  virtual
  bool
  read_value(TokenType value_type,
	     const FileRegion& value_loc,
	     int count) override;

  /// @brief 読み込みが終了した時の処理を行う．
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  /// @param[in] header_loc '(' から ')' までのファイル上の位置
  /// @param[in] count 読み込んだ要素数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  virtual
  bool
  end_header(AttrType attr_type,
	     const FileRegion& attr_loc,
	     const FileRegion& header_loc,
	     int count) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ヘッダの値1
  AstStr* mHeaderValue1;

  // ヘッダの値2
  AstStr* mHeaderValue2;

};


//////////////////////////////////////////////////////////////////////
/// @class Str2IntGroupHandler GroupHandler.h "GroupHadler.h"
/// @brief 2つの文字列型と1つの整数型をとるグループ用のハンドラ
//////////////////////////////////////////////////////////////////////
class Str2IntGroupHandler :
  public GroupHandler
{
public:

  /// @brief 親を持つハンドラ用のコンストラクタ
  /// @param[in] parser パーサー
  Str2IntGroupHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~Str2IntGroupHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの値をクリアする．
  void
  clear_header();

  /// @brief ヘッダの値1を取り出す．
  const AstString*
  header_value1() const;

  /// @brief ヘッダの値2を取り出す．
  const AstString*
  header_value2() const;

  /// @brief ヘッダの値3を取り出す．
  const AstInt*
  header_value3() const;


protected:
  //////////////////////////////////////////////////////////////////////
  // CGHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの開始処理
  ///
  /// '(' を読み込んだ時に呼ばれる．
  virtual
  void
  begin_header();

  /// @brief 値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  /// @param[in] count read_value() の呼ばれた回数
  virtual
  bool
  read_value(TokenType value_type,
	     const FileRegion& value_loc,
	     int count) override;

  /// @brief 読み込みが終了した時の処理を行う．
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  /// @param[in] header_loc '(' から ')' までのファイル上の位置
  /// @param[in] count 読み込んだ要素数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  virtual
  bool
  end_header(AttrType attr_type,
	     const FileRegion& attr_loc,
	     const FileRegion& header_loc,
	     int count) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ヘッダの値1
  AstStr* mHeaderValue1;

  // ヘッダの値2
  AstStr* mHeaderValue2;

  // ヘッダの値3
  AstStr* mHeaderValue3;

};

END_NAMESPACE_YM_DOTLIB

#endif // GROUPHANDLER_H
