#ifndef ASTTEMPLATE_H
#define ASTTEMPLATE_H

/// @file AstTemplate.h
/// @brief AstTemplate のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib_nsdef.h"
#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstTemplate AstTemplate.h "AstTemplate.h"
/// @brief lut 用のテンプレート情報を表すクラス
//////////////////////////////////////////////////////////////////////
class AstTemplate :
  public AstNode
{
public:

  /// @brief コンストラクタ
  AstTemplate(const FileRegion& attr_loc,    ///< [in] ファイル上の位置
	      const StrHandler& header,	     ///< [in] ヘッダのハンドラ
	      const TemplateHandler& group); ///< [in] グループ本体のハンドラ

  /// @brief デストラクタ
  ~AstTemplate();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前を返す．
  const AstString*
  name() const
  {
    return mName;
  }

  /// @brief 次元数を返す．
  int
  dimension() const
  {
    return mDimension;
  }

  /// @brief 'variable_1' を返す．
  const AstVarType*
  variable_1() const
  {
    return mVar1;
  }

  /// @brief 'variable_2' を返す．
  const AstVarType*
  variable_2() const
  {
    return mVar2;
  }

  /// @brief 'variable_3' を返す．
  const AstVarType*
  variable_3() const
  {
    return mVar3;
  }

  /// @brief 'index_1' を返す．
  const AstFloatVector*
  index_1() const
  {
    return mIndex1;
  }

  /// @brief 'index_2' を返す．
  const AstFloatVector*
  index_2() const
  {
    return mIndex2;
  }

  /// @brief 'index_3' を返す．
  const AstFloatVector*
  index_3() const
  {
    return mIndex3;
  }

  /// @brief 'domain' のノードを返す．
  ///
  /// 未定義なら nullptr を返す．
  const AstDomain*
  domain() const
  {
    return mDomain;
  }

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s,     ///< [in] 出力先のストリーム
       int indent = 0) ///< [in] インデント量
    const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 名前
  const AstString* mName;

  // 次元数
  int mDimension;

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

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTTEMPLATE_H
