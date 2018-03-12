#ifndef VALUESHANDLER_H
#define VALUESHANDLER_H

/// @file ValuesHandler.h
/// @brief ValuesHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ComplexHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class ValuesHandler ValuesHandler.h "ValuesHandler.h"
/// @brief LUT の values 属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class ValuesHandler :
  public ComplexHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  ValuesHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~ValuesHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を表すノードを作る．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value_list 値のリスト
  ///
  /// 多次元の場合でも1次元の FloatVector に変換する．
  virtual
  DotlibNode*
  gen_value(const FileRegion& loc,
	    const vector<DotlibNode*>& value_list) override;


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

#endif // VALUESHANDLER_H
