#ifndef GROUPHANDLER_H
#define GROUPHANDLER_H

/// @file GroupHandler.h
/// @brief GroupHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class GroupHandler GroupHandler.h "GroupHandler.h"
/// @brief group statement 用のハンドラ
///
/// '(' <value>, <value>, ... ')' '{'
///     属性記述
///     ...
/// '}'
///
/// の形式のパースを行う．
/// このうちのヘッダ部分は HeaderHandler が行う．
/// 本体の部分は先頭の '{' を読んだ時点で仮想関数 begin_group() が呼び出されれ，
/// 個々の属性を読んだ時点で仮想関数 parse_attr() が呼び出される．
/// 最後の '}' を読んだ時点で仮想関数 end_group() が呼び出される．
/// 各継承クラスはこれらの仮想関数を実装する必要がある．
//////////////////////////////////////////////////////////////////////
class GroupHandler :
  public DotlibHandler
{

  // パース関数の型定義
  using ParseFunc = std::function<bool(DotlibParser&, AttrType, const FileRegion&)>;

  friend class DotlibParser;

public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  GroupHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~GroupHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 読み込んだグループ定義のファイル上の位置を返す．
  const FileRegion&
  group_loc() const;


public:
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
  read_group_attr(AttrType attr_type,
		  const FileRegion& attr_loc);

  /// @brief グループ記述の終わり
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  virtual
  bool
  end_group() = 0;


protected:
  //////////////////////////////////////////////////////////////////////
  // 便利関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 属性がセットされているかチェックする．
  /// @param[in] val 値を持つノード
  /// @param[in] attr_type 属性の型
  /// @param[in] group_loc グループ記述全体の位置
  /// @retval true val が値を持っていた．
  /// @retval false val が nullptr だった．
  ///
  /// val が nullptr の時にエラー出力を行う．
  bool
  check_attr(const AstNode* val,
	     AttrType attr_type,
	     const FileRegion& group_loc);

  /// @brief パース関数を登録する．
  /// @param[in] attr_type 属性
  /// @param[in] func パース関数
  void
  reg_func(AttrType attr_type,
	   ParseFunc func);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 各属性用のパース関数を登録する辞書
  HashMap<AttrType, ParseFunc> mFuncDict;

  // 読み込んだグループ定義のファイル位置
  FileRegion mGroupLoc;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 読み込んだグループ定義のファイル上の位置を返す．
inline
const FileRegion&
GroupHandler::group_loc() const
{
  return mGroupLoc;
}

END_NAMESPACE_YM_DOTLIB

#endif // GROUPHANDLER_H
