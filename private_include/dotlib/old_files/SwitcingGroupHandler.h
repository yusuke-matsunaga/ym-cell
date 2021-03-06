#ifndef SWITCINGGROUPHANDLER_H
#define SWITCINGGROUPHANDLER_H

/// @file SwitcingGroupHandler.h
/// @brief SwitcingGroupHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class SwitchingGroupHandler SwitchingGroupHandler.h "SwitchingGroupHandler.h"
/// @brief 'switching_group' Group Statement 用のハンドラ
///
/// 参考文献 : Library Compiler Reference Manual, Section 2
///           "cell and model Group Description and Syntax"
///
/// * この辺のマニュアルの記述はすごくいい加減．simple attribute と
///   complex attribute を混同している．
/// * input_switching_condition|output_swithing_condition の <enum(rise, fall)>
///   というのが何を表すのか不明
/// * Simple Attributes
///   - min_input_switching_count
///   - max_input_switching_count
/// * Complex Attributes
///   - input_switching_condition ( <enum(rise, fall)> ) ;
///   - output_switching_condition ( <enum(rise, fall)> ) ;
/// * Group Statements
///   - pg_current
//////////////////////////////////////////////////////////////////////
class SwitchingGroupHandler :
  public GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  SwitchingGroupHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~SwitchingGroupHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @breif switching_group Group Statement の記述をパースする．
  /// @param[in] dst_list 読み込んだ値を格納するリスト
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  parse_value(vector<const AstSwitchingGroup*>& dst_list);


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

  // min_switching_count
  const AstInt* mMinSwitchingCount;

  // max_switching_count
  const AstInt* mMaxSwitchingCount;

  // input_switching_condition

  // output _switching_condition

  // pg_current
  const AstPGCurrent* mPGCurrent;

};

END_NAMESPACE_YM_DOTLIB

#endif // SWITCINGGROUPHANDLER_H
