#ifndef COMPLEXHANDLER_H
#define COMPLEXHANDLER_H

/// @file ComplexHandler.h
/// @brief ComplexHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "CGHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class ComplexHandler ComplexHandler.h "ComplexHandler.h"
/// @brief complex attribute 用のハンドラ
///
/// このクラスで DotlibHandler の仮想関数である parse_attr_value()
/// を実装している．
//////////////////////////////////////////////////////////////////////
class ComplexHandler :
  public CGHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  ComplexHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~ComplexHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // DotlibHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 属性値を読み込む．
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  virtual
  bool
  parse_attr_value(AttrType attr_type,
		   const FileRegion& attr_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

};

END_NAMESPACE_YM_DOTLIB

#endif // COMPLEXHANDLER_H
