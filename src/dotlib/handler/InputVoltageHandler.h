#ifndef INPUTvolTAGEHANDLER_H
#define INPUTvolTAGEHANDLER_H

/// @file InputVoltageHandler.h
/// @brief InputVoltageHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class InputVoltageHandler InputVoltageHandler.h "InputVoltageHandler.h"
/// @brief input voltage 用のハンドラ
//////////////////////////////////////////////////////////////////////
class InputVoltageHandler :
  public Str1GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  InputVoltageHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~InputVoltageHandler();


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

  // 式のパーザー
  ExprHandler* mExprHandler;

  // vil
  const AstExpr* mVil;

  // vih
  const AstExpr* mVih;

  // vimin
  const AstExpr* mVimin;

  // vimax
  const AstExpr* mVimax;

};

END_NAMESPACE_YM_DOTLIB

#endif // INPUTvolTAGEHANDLER_H
