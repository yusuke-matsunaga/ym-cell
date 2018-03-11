#ifndef DOTLIB_DOTLIBTEMPLATE_H
#define DOTLIB_DOTLIBTEMPLATE_H

/// @file DotlibTemplate.h
/// @brief DotlibTemplate のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "DotlibNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibTemplate DotlibTemplate.h "DotlibTemplate.h"
/// @brief LUT 用のテンプレート情報を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibTemplate :
  public DotlibNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] name 名前
  /// @param[in] dimension 次元数
  /// @param[in] var_1, var_2, var_3 変数のタイプ
  /// @param[in] index_1, index_2, index_3 インデックスのベクタ
  DotlibTemplate(const FileRegion& loc,
		 const DotlibString* name,
		 int dimension,
		 const DotlibVarType* var_1,
		 const DotlibVarType* var_2,
		 const DotlibVarType* var_3,
		 const DotlibFloatVector* index_1,
		 const DotlibFloatVector* index_2,
		 const DotlibFloatVector* index_3);

  /// @brief デストラクタ
  virtual
  ~DotlibTemplate();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前を返す．
  const DotlibString*
  name() const;

  /// @brief 次元数を返す．
  int
  dimension() const;

  /// @brief 'variable_1' を返す．
  const DotlibVarType*
  variable_1() const;

  /// @brief 'variable_2' を返す．
  const DotlibVarType*
  variable_2() const;

  /// @brief 'variable_3' を返す．
  const DotlibVarType*
  variable_3() const;

  /// @brief 'index_1' を返す．
  const DotlibFloatVector*
  index_1() const;

  /// @brief 'index_2' を返す．
  const DotlibFloatVector*
  index_2() const;

  /// @brief 'index_3' を返す．
  const DotlibFloatVector*
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
  const DotlibString* mName;

  // 次元数
  int mDimension;

  // variable_1
  const DotlibVarType* mVar1;

  // variable_2
  const DotlibVarType* mVar2;

  // variable_3
  const DotlibVarType* mVar3;

  // index_1
  const DotlibFloatVector* mIndex1;

  // index_2
  const DotlibFloatVector* mIndex2;

  // index_3
  const DotlibFloatVector* mIndex3;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 名前を返す．
inline
const DotlibString*
DotlibTemplate::name() const
{
  return mName;
}

// @brief 次元数を返す．
inline
int
DotlibTemplate::dimension() const
{
  return mDimension;
}

// @brief 'variable_1' を返す．
inline
const DotlibVarType*
DotlibTemplate::variable_1() const
{
  return mVar1;
}

// @brief 'variable_2' を返す．
inline
const DotlibVarType*
DotlibTemplate::variable_2() const
{
  return mVar2;
}

// @brief 'variable_3' を返す．
inline
const DotlibVarType*
DotlibTemplate::variable_3() const
{
  return mVar3;
}

// @brief 'index_1' を返す．
inline
const DotlibFloatVector*
DotlibTemplate::index_1() const
{
  return mIndex1;
}

/// @brief 'index_2' を返す．
inline
const DotlibFloatVector*
DotlibTemplate::index_2() const
{
  return mIndex2;
}

// @brief 'index_3' を返す．
inline
const DotlibFloatVector*
DotlibTemplate::index_3() const
{
  return mIndex3;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIB_DOTLIBTEMPLATE_H
