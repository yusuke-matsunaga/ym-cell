#ifndef TEMPLATEHANDLER_H
#define TEMPLATEHANDLER_H

/// @file TemplateHandler.h
/// @brief TemplateHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/Str1GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class TemplateHandler TemplateHandler.h "TemplateHandler.h"
/// @brief 'lut_template' Group Statement 用のハンドラ
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


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @breif 'lut_template' Group Statement の記述をパースする．
  /// @param[in] dst_list 読み込んだ値を格納するリスト
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  parse_value(vector<const AstTemplate*>& dst_list);


public:
  //////////////////////////////////////////////////////////////////////
  // GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ記述の始まり
  void
  begin_group() override;

  /// @brief グループ記述の終わり
  /// @param[in] group_loc グループ全体のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  bool
  end_group(const FileRegion& group_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief VarType に共通の処理を行う．
  bool
  parse_vartype(const AstVarType*& dst,
		AttrType attr_type,
		const FileRegion& attr_loc);

  /// @brief Index に共通の処理を行う．
  bool
  parse_index(const AstFloatVector*& dst,
	      AttrType attr_type,
	      const FileRegion& attr_loc);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

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

  // domain
  const AstDomain* mDomain;

  // 読み込んだ値
  const AstTemplate* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // TEMPLATEHANDLER_H
