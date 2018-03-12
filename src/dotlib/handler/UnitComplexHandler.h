#ifndef UNITCOMPLEXHANDLER_H
#define UNITCOMPLEXHANDLER_H

/// @file UnitComplexHandler.h
/// @brief UnitComplexHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ComplexHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class UnitComplexHandler UnitComplexHandler.h "UnitComplexHandler.h"
/// @brief 単位型のcomplex attribute ハンドラ
//////////////////////////////////////////////////////////////////////
class UnitComplexHandler :
  public ComplexHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  UnitComplexHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~UnitComplexHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // ComplexHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を表すノードを作る．
  /// @param[in] value_loc ファイル上の位置
  /// @param[in] value_list 値のリスト
  virtual
  DotlibNode*
  gen_value(const FileRegion& value_loc,
	    const vector<DotlibNode*>& value_list) override;

};

END_NAMESPACE_YM_DOTLIB

#endif // UNITCOMPLEXHANDLER_H
