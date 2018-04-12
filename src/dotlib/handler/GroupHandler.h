#ifndef GROUPHANDLER_H
#define GROUPHANDLER_H

/// @file GroupHandler.h
/// @brief GroupHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class GroupHandler GroupHandler.h "GroupHandler.h"
/// @brief group statement 用のハンドラ
//////////////////////////////////////////////////////////////////////
class GroupHandler :
  public DotlibHandler
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
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @return 読み込んだ値を表す AstNode を返す．
  ///
  /// エラーの場合には nullptr を返す．
  virtual
  const AstNode*
  parse_attr_value(AttrType attr_type,
		   const FileRegion& attr_loc);


public:
  //////////////////////////////////////////////////////////////////////
  // GroupHandler の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ハンドラの登録を行う．
  /// @param[in] attr_type 属性
  /// @param[in] handler 対応付けるハンドラ
  /// @param[in] singleton 単一要素の時に true にするフラグ
  void
  reg_handler(AttrType attr_type,
	      DotlibHandler* handler);


protected:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ開始の処理を行う．
  virtual
  void
  begin_group();

  /// @brief attr_type に対応する属性を読み込む．
  /// @param[in] attr_type 対象の属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  /// @retval 0 処理しなかった．
  /// @retval 1 正常に処理した．
  /// @retval 2 処理中にエラーが起こった．
  virtual
  int
  parse_attr(AttrType attr_type,
	     const FileRegion& attr_loc);

  /// @brief group statement の引数のチェックを行う仮想関数
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @param[in] value_loc 値全体のファイル上の位置
  /// @param[in] value_list 値を表すトークンのリスト
  /// @note begin_group() の中で呼ばれる．
  ///
  /// デフォルトの実装はなにもしないで true を返す．
  virtual
  bool
  check_value(AttrType attr_type,
	      const FileRegion& attr_loc,
	      const FileRegion& value_loc,
	      const vector<const AstNode*>& value_list);

  /// @brief 値を作る．
  /// @param[in] loc 全体のファイル上の位置
  /// @param[in] value_list 値のリスト
  /// @param[in] attr_list 属性のリスト
  virtual
  const AstNode*
  gen_node(const FileRegion& loc,
	   const vector<const AstNode*>& value_list,
	   const vector<const AstAttr*>& attr_list);

  /// @brief ハンドラを取り出す．
  /// @param[in] attr_type 属性
  ///
  /// なければ nullptr を返す．
  DotlibHandler*
  find_handler(AttrType attr_type);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ハンドラのリスト
  vector<pair<AttrType, DotlibHandler*> > mHandlerList;

  // 読み込んだ属性のリスト
  vector<const AstAttr*> mAttrList;

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
  // 内部で用いられる GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief group statement の引数のチェックを行う仮想関数
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @param[in] value_loc 値全体のファイル上の位置
  /// @param[in] value_list 値を表すトークンのリスト
  /// @note begin_group() の中で呼ばれる．
  /// @note デフォルトの実装はなにもしないで true を返す．
  virtual
  bool
  check_value(AttrType attr_type,
	      const FileRegion& attr_loc,
	      const FileRegion& value_loc,
	      const vector<const AstNode*>& value_list) override;

  /// @brief 値を作る．
  /// @param[in] loc 全体のファイル上の位置
  /// @param[in] value_list 値のリスト
  /// @param[in] attr_list 属性のリスト
  virtual
  const AstNode*
  gen_node(const FileRegion& loc,
	   const vector<const AstNode*>& value_list,
	   const vector<const AstAttr*>& attr_list) override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる EmptyGroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を作る．
  /// @param[in] loc 全体のファイル上の位置
  /// @param[in] attr_list 属性のリスト
  virtual
  const AstNode*
  gen_node(const FileRegion& loc,
	   const vector<const AstAttr*>& attr_list);


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
  // 内部で用いられる GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief group statement の引数のチェックを行う仮想関数
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @param[in] value_loc 値全体のファイル上の位置
  /// @param[in] value_list 値を表すトークンのリスト
  /// @note begin_group() の中で呼ばれる．
  /// @note デフォルトの実装はなにもしないで true を返す．
  virtual
  bool
  check_value(AttrType attr_type,
	      const FileRegion& attr_loc,
	      const FileRegion& value_loc,
	      const vector<const AstNode*>& value_list) override;

  /// @brief 値を作る．
  virtual
  const AstNode*
  gen_node(const FileRegion& loc,
	   const vector<const AstNode*>& value_list,
	   const vector<const AstAttr*>& attr_list) override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いる Str1GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を作る．
  virtual
  const AstNode*
  gen_node(const FileRegion& loc,
	   const AstString* value,
	   const vector<const AstAttr*>& attr_list);

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
  // 内部で用いられる GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief group statement の引数のチェックを行う仮想関数
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @param[in] value_loc 値全体のファイル上の位置
  /// @param[in] value_list 値を表すトークンのリスト
  /// @note begin_group() の中で呼ばれる．
  /// @note デフォルトの実装はなにもしないで true を返す．
  virtual
  bool
  check_value(AttrType attr_type,
	      const FileRegion& attr_loc,
	      const FileRegion& value_loc,
	      const vector<const AstNode*>& value_list) override;

  /// @brief 値を作る．
  virtual
  const AstNode*
  gen_node(const FileRegion& loc,
	   const vector<const AstNode*>& value_list,
	   const vector<const AstAttr*>& attr_list) override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いる Str2GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を作る．
  virtual
  const AstNode*
  gen_node(const FileRegion& loc,
	   const AstString* value1,
	   const AstString* value2,
	   const vector<const AstAttr*>& attr_list);

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
  // 内部で用いられる GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief group statement の引数のチェックを行う仮想関数
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @param[in] value_loc 値全体のファイル上の位置
  /// @param[in] value_list 値を表すトークンのリスト
  /// @note begin_group() の中で呼ばれる．
  /// @note デフォルトの実装はなにもしないで true を返す．
  virtual
  bool
  check_value(AttrType attr_type,
	      const FileRegion& attr_loc,
	      const FileRegion& value_loc,
	      const vector<const AstNode*>& value_list) override;

  /// @brief 値を作る．
  virtual
  const AstNode*
  gen_node(const FileRegion& loc,
	   const vector<const AstNode*>& value_list,
	   const vector<const AstAttr*>& attr_list) override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いる Str2IntGroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を作る．
  virtual
  const AstNode*
  gen_node(const FileRegion& loc,
	   const AstString* value1,
	   const AstString* value2,
	   const AstInt* value3,
	   const vector<const AstAttr*>& attr_list);

};

END_NAMESPACE_YM_DOTLIB

#endif // GROUPHANDLER_H
