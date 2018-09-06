#ifndef VARIABLERANGEHANDLER_H
#define VARIABLERANGEHANDLER_H

/// @file VariableRangeHandler.h
/// @brief VariableRangeHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "Float2ComplexHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class VariableRangeHandler VariableRangeHandler.h "VariableRangeHandler.h"
/// @brief variable_n_range complex attributes を読み込むためのクラス
//////////////////////////////////////////////////////////////////////
class VariableRangeHandler :
  public Float2ComplexHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  VariableRangeHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~VariableRangeHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief vairable_n_range 属性を読み込む．
  /// @param[in] dst 結果を格納する変数
  /// @retval true 正しくパースした．
  /// @retval false エラーが怒った．
  bool
  parse_value(const AstVariableRange*& dst);


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////


};

END_NAMESPACE_YM_DOTLIB

#endif // VARIABLERANGEHANDLER_H
