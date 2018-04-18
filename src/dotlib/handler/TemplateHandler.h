#ifndef TEMPLATEHANDLER_H
#define TEMPLATEHANDLER_H

/// @file TemplateHandler.h
/// @brief TemplateHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "GroupHandler.h"
#include "VarTypeHandler.h"
#include "IndexHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class TemplateHandler TemplateHandler.h "TemplateHandler.h"
/// @brief lut template 用のハンドラ
//////////////////////////////////////////////////////////////////////
class TemplateHandler :
  public Str1GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  TemplateHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~TemplateHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ記述の始まり
  void
  begin_group() override;

  /// @brief attr_type に対応する属性を読み込む．
  /// @param[in] attr_type 対象の属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  bool
  parse_attr(AttrType attr_type,
	     const FileRegion& attr_loc) override;

  /// @brief グループ記述の終わり
  /// @param[in] group_loc グループ全体のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  bool
  end_group(const FileRegion& group_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // variable_1
  VarTypeHandler mVar1;

  // variable_2
  VarTypeHandler mVar2;

  // variable_3
  VarTypeHandler mVar3;

  // index_1
  IndexHandler mIndex1;

  // index_2
  IndexHandler mIndex2;

  // index_3
  IndexHandler mIndex3;

};

END_NAMESPACE_YM_DOTLIB

#endif // TEMPLATEHANDLER_H
