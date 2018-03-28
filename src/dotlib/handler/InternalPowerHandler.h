#ifndef INTERNALpowerHANDLER_H
#define INTERNALpowerHANDLER_H

/// @file InternalPowerHandler.h
/// @brief InternalPowerHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class InternalPowerHandler InternalPowerHandler.h "InternalPowerHandler.h"
/// @brief internal power グループ用のハンドラ
//////////////////////////////////////////////////////////////////////
class InternalPowerHandler :
  public EmptyGroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  InternalPowerHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~InternalPowerHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // DotlibHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 属性値を読み込む．
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @return 読み込んだ値を表す AstNode を返す．
  ///
  /// エラーの場合には nullptr を返す．
  virtual
  const AstNode*
  parse_attr_value(AttrType attr_type,
		   const FileRegion& attr_loc) override;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief パーズする．
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @return 読み込んだ InputVoltage を返す．
  ///
  /// エラーの場合には nullptr を返す．
  const AstInputVoltage*
  parse(AttrType attr_type,
	const FileRegion& attr_loc);


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief attr_type に対応する属性を読み込む．
  /// @param[in] attr_type 対象の属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  /// @retval true 正常に処理した．
  /// @retval false 処理中にエラーが起こった．
  virtual
  bool
  parse_attr(AttrType attr_type,
	     const FileRegion& attr_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // string ハンドラ
  StrSimpleHandler* mStringHandler;

  // function ハンドラ
  FuncHandler* mFuncHandler;

  // power ハンドラ
  PowerHandler* mPowerHandler;

  // gen_group ハンドラ
  GenGroupHandler* mGenGroup;

};

END_NAMESPACE_YM_DOTLIB

#endif // INTERNALpowerHANDLER_H
