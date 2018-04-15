﻿#ifndef ASTTEMPLATE_H
#define ASTTEMPLATE_H

/// @file AstTemplate.h
/// @brief AstTemplate のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
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
  friend class AstMgr;

private:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] name 名前
  /// @param[in] dimension 次元数
  /// @param[in] var_1, var_2, var_3 変数のタイプ
  /// @param[in] index_1, index_2, index_3 インデックスのベクタ
  AstTemplate(const FileRegion& loc,
	      const AstString* name,
	      int dimension,
	      const AstVarType* var_1,
	      const AstVarType* var_2,
	      const AstVarType* var_3,
	      const AstFloatVector* index_1,
	      const AstFloatVector* index_2,
	      const AstFloatVector* index_3);

  /// @brief デストラクタ
  virtual
  ~AstTemplate();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前を返す．
  const AstString*
  name() const;

  /// @brief 次元数を返す．
  int
  dimension() const;

  /// @brief 'variable_1' を返す．
  const AstVarType*
  variable_1() const;

  /// @brief 'variable_2' を返す．
  const AstVarType*
  variable_2() const;

  /// @brief 'variable_3' を返す．
  const AstVarType*
  variable_3() const;

  /// @brief 'index_1' を返す．
  const AstFloatVector*
  index_1() const;

  /// @brief 'index_2' を返す．
  const AstFloatVector*
  index_2() const;

  /// @brief 'index_3' を返す．
  const AstFloatVector*
  index_3() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  virtual
  void
  dump(ostream& s,
       int indent = 0) const;


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

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 名前を返す．
inline
const AstString*
AstTemplate::name() const
{
  return mName;
}

// @brief 次元数を返す．
inline
int
AstTemplate::dimension() const
{
  return mDimension;
}

// @brief 'variable_1' を返す．
inline
const AstVarType*
AstTemplate::variable_1() const
{
  return mVar1;
}

// @brief 'variable_2' を返す．
inline
const AstVarType*
AstTemplate::variable_2() const
{
  return mVar2;
}

// @brief 'variable_3' を返す．
inline
const AstVarType*
AstTemplate::variable_3() const
{
  return mVar3;
}

// @brief 'index_1' を返す．
inline
const AstFloatVector*
AstTemplate::index_1() const
{
  return mIndex1;
}

/// @brief 'index_2' を返す．
inline
const AstFloatVector*
AstTemplate::index_2() const
{
  return mIndex2;
}

// @brief 'index_3' を返す．
inline
const AstFloatVector*
AstTemplate::index_3() const
{
  return mIndex3;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTTEMPLATE_H