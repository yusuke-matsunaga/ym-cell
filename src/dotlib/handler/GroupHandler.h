#ifndef GROUPHANDLER_H
#define GROUPHANDLER_H

/// @file GroupHandler.h
/// @brief GroupHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibHandler.h"
#include "ym/HashMap.h"


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
  /// @return 読み込んだ値を表す DotlibNode を返す．
  ///
  /// エラーの場合には nullptr を返す．
  virtual
  DotlibNode*
  read_attr(AttrType attr_type,
	    const FileRegion& attr_loc);


public:
  //////////////////////////////////////////////////////////////////////
  // GroupHandler の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ハンドラの登録を行う．
  /// @param[in] attr_type 属性
  /// @param[in] handler 対応付けるハンドラ
  /// @note エラーが起きたら false を返す．
  bool
  reg_handler(AttrType attr_type,
	      DotlibHandler* handler);

  /// @brief ハンドラを取り出す．
  /// @param[in] attr_type 属性
  /// @note なければ nullptr を返す．
  DotlibHandler*
  find_handler(AttrType attr_type);


protected:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief group statement の引数のチェックを行う仮想関数
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @param[in] value_list 値を表すトークンのリスト
  /// @note begin_group() の中で呼ばれる．
  /// @note デフォルトの実装はなにもしないで true を返す．
  virtual
  bool
  check_group_value(AttrType attr_type,
		    const FileRegion& attr_loc,
		    const vector<DotlibNode*>& value_list);

  /// @brief 値を作る．
  /// @param[in] loc 全体のファイル上の位置
  /// @param[in] value_list 値のリスト
  /// @param[in] attr_list 属性のリスト
  virtual
  DotlibNode*
  gen_value(const FileRegion& loc,
	    const vector<DotlibNode*>& value_list,
	    const vector<DotlibAttr*>& attr_list);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ハンドラの連想配列
  HashMap<AttrType, DotlibHandler*> mHandlerMap;

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
  /// @param[in] value_list 値を表すトークンのリスト
  /// @note begin_group() の中で呼ばれる．
  /// @note デフォルトの実装はなにもしないで true を返す．
  virtual
  bool
  check_group_value(AttrType attr_type,
		    const FileRegion& attr_loc,
		    const vector<DotlibNode*>& value_list) override;

  /// @brief 値を作る．
  /// @param[in] loc 全体のファイル上の位置
  /// @param[in] value_list 値のリスト
  /// @param[in] attr_list 属性のリスト
  virtual
  DotlibNode*
  gen_value(const FileRegion& loc,
	    const vector<DotlibNode*>& value_list,
	    const vector<DotlibAttr*>& attr_list) override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる EmptyGroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を作る．
  /// @param[in] loc 全体のファイル上の位置
  /// @param[in] attr_list 属性のリスト
  virtual
  DotlibNode*
  gen_value(const FileRegion& loc,
	    const vector<DotlibAttr*>& attr_list);


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
  /// @param[in] value_list 値を表すトークンのリスト
  /// @note begin_group() の中で呼ばれる．
  /// @note デフォルトの実装はなにもしないで true を返す．
  virtual
  bool
  check_group_value(AttrType attr_type,
		    const FileRegion& attr_loc,
		    const vector<DotlibNode*>& value_list) override;

  /// @brief 値を作る．
  virtual
  DotlibNode*
  gen_value(const FileRegion& loc,
	    const vector<DotlibNode*>& value_list,
	    const vector<DotlibAttr*>& attr_list) override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いる Str1GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を作る．
  virtual
  DotlibNode*
  gen_value(const FileRegion& loc,
	    const DotlibString* value,
	    const vector<DotlibAttr*>& attr_list);

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
  /// @param[in] value_list 値を表すトークンのリスト
  /// @note begin_group() の中で呼ばれる．
  /// @note デフォルトの実装はなにもしないで true を返す．
  virtual
  bool
  check_group_value(AttrType attr_type,
		    const FileRegion& attr_loc,
		    const vector<DotlibNode*>& value_list) override;

  /// @brief 値を作る．
  virtual
  DotlibNode*
  gen_value(const FileRegion& loc,
	    const vector<DotlibNode*>& value_list,
	    const vector<DotlibAttr*>& attr_list) override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いる Str2GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を作る．
  virtual
  DotlibNode*
  gen_value(const FileRegion& loc,
	    const DotlibString* value1,
	    const DotlibString* value2,
	    const vector<DotlibAttr*>& attr_list);

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
  /// @param[in] value_list 値を表すトークンのリスト
  /// @note begin_group() の中で呼ばれる．
  /// @note デフォルトの実装はなにもしないで true を返す．
  virtual
  bool
  check_group_value(AttrType attr_type,
		    const FileRegion& attr_loc,
		    const vector<DotlibNode*>& value_list) override;

  /// @brief 値を作る．
  virtual
  DotlibNode*
  gen_value(const FileRegion& loc,
	    const vector<DotlibNode*>& value_list,
	    const vector<DotlibAttr*>& attr_list) override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いる Str2IntGroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を作る．
  virtual
  DotlibNode*
  gen_value(const FileRegion& loc,
	    const DotlibString* value1,
	    const DotlibString* value2,
	    const DotlibInt* value3,
	    const vector<DotlibAttr*>& attr_list);

};

END_NAMESPACE_YM_DOTLIB

#endif // GROUPHANDLER_H
