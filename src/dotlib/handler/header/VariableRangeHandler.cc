
/// @file VariableRangeHandler.cc
/// @brief VariableRangeHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/VariableRangeHandler.h"
#include "dotlib/AstMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス VariableRangeHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
VariableRangeHandler::VariableRangeHandler(DotlibParser& parser) :
  Float2ComplexHandler(parser)
{
}

// @brief デストラクタ
VariableRangeHandler::~VariableRangeHandler()
{
}

// @brief vairable_n_range 属性を読み込む．
// @param[in] dst 結果を格納する変数
// @retval true 正しくパースした．
// @retval false エラーが怒った．
bool
VariableRangeHandler::parse_value(const AstVariableRange*& dst)
{
  const AstFloat* val1;
  const AstFloat* val2;
  bool stat = Float2ComplexHandler::parse_value(val1, val2);
  if ( stat ) {
    dst = mgr().new_variable_range(val1, val2);
  }
  return stat;
}

END_NAMESPACE_YM_DOTLIB
