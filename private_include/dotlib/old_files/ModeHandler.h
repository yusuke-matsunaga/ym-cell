#ifndef MODEHANDLER_H
#define MODEHANDLER_H

/// @file ModeHandler.h
/// @brief ModeHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/Str1GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class ModeHandler ModeHandler.h "ModeHandler.h"
/// @brief 'mode_definition' Group Statement 用のハンドラ
///
/// 参考文献 : Library Compiler Reference Manual, Section 2
///           "cell and model Group Description and Syntax"
/// * Group Statements
///   - mode_value ( name_(string) ) { ... }
//////////////////////////////////////////////////////////////////////
class ModeHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  ModeHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~ModeHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @breif 'mode_definition' Group Statement の記述をパースする．
  /// @param[in] dst_list 読み込んだ値を格納するリスト
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  parse_value(vector<const AstMode*>& dst_list);


protected:
  //////////////////////////////////////////////////////////////////////
  // GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ記述の始まり
  void
  begin_group() override;

  /// @brief グループ記述の終わり
  /// @param[in] group_loc グループ全体のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  bool
  end_group(const FileRegion& group_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // mode_value
  vector<const AstModeValue*> mModeValueList;

};

END_NAMESPACE_YM_DOTLIB

#endif // MODEHANDLER_H
