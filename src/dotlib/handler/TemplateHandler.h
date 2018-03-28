#ifndef TEMPLATEHANDLER_H
#define TEMPLATEHANDLER_H

/// @file TemplateHandler.h
/// @brief TemplateHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "GroupHandler.h"


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
  virtual
  ~TemplateHandler();


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
  /// @return 読み込んだ AstTemplate を返す．
  ///
  /// エラーの場合には nullptr を返す．
  const AstTemplate*
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

  // VarType ハンドラ
  VarTypeHandler* mVarTypeHandler;

  // index ハンドラ
  IndexHandler* mIndexHandler;

  // gen_group ハンドラ
  GenGroupHandler* mGenGroupHandler;

  // variable_1
  const AstVarType* mVar1;

  // variable_2
  const AstVarType* mVar2;

  // variable_3
  const AstVarType* mVar3;

  // index_1
  const AstFloatVector* mIndex1;

  // index_2
  const AstFloatVector* mIndex2;

  // index_3
  const AstFloatVector* mIndex3;

};

END_NAMESPACE_YM_DOTLIB

#endif // TEMPLATEHANDLER_H
