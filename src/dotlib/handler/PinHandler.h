#ifndef pinHANDLER_H
#define pinHANDLER_H

/// @file PinHandler.h
/// @brief PinHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

class TimingHandler;

//////////////////////////////////////////////////////////////////////
/// @class PinHandler PinHandler.h "PinHandler.h"
//////////////////////////////////////////////////////////////////////
class PinHandler :
  public GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  PinHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~PinHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ開始の処理を行う．
  virtual
  void
  begin_group() override;

  /// @brief attr_type に対応する属性を読み込む．
  /// @param[in] attr_type 対象の属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  /// @retval 0 処理しなかった．
  /// @retval 1 正常に処理した．
  /// @retval 2 処理中にエラーが起こった．
  virtual
  int
  parse_attr(AttrType attr_type,
	     const FileRegion& attr_loc) override;

  /// @brief 値を作る．
  virtual
  const AstNode*
  gen_node(const FileRegion& loc,
	   const vector<const AstNode*>& value_list,
	   const vector<const AstAttr*>& attr_list) override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 'timing' 属性のハンドラ
  TimingHandler* mTimingHandler;

  // 処理中の timing リスト
  vector<const AstTiming*> mTimingList;

};

END_NAMESPACE_YM_DOTLIB

#endif // pinHANDLER_H
