#ifndef IOVOLTAGEHANDLER_H
#define IOVOLTAGEHANDLER_H

/// @file IoVoltageHandler.h
/// @brief IoVoltageHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "Str1GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class IoVoltageHandler IoVoltageHandler.h "IoVoltageHandler.h"
/// @brief input_voltage / output_voltage 用のハンドラ
//////////////////////////////////////////////////////////////////////
class IoVoltageHandler :
  public Str1GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  IoVoltageHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~IoVoltageHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスで用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 式を読んでセットする．
  /// @param[in] dst 値を格納する変数
  /// @param[in] attr_type 属性の型(エラー出力に用いる)
  /// @param[in] attr_loc attr_type のファイル上の位置
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_expr(const AstExpr*& dst,
	     AttrType attr_type,
	     const FileRegion& attr_loc);

  /// @brief 属性がセットされているかチェックする．
  bool
  check_attr(const AstExpr* val,
	     AttrType attr_type,
	     const FileRegion& group_loc);

};

END_NAMESPACE_YM_DOTLIB

#endif // IOVOLTAGEHANDLER_H
