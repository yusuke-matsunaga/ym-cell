#ifndef DOTLIB_DOTLIBTEMPLATE_H
#define DOTLIB_DOTLIBTEMPLATE_H

/// @file DotlibTemplate.h
/// @brief DotlibTemplate のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibAttrMap.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibTemplate DotlibTemplate.h "DotlibTemplate.h"
/// @brief LUT 用のテンプレート情報を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibTemplate :
  public DotlibAttrMap
{
public:

  /// @brief コンストラクタ
  DotlibTemplate();

  /// @brief デストラクタ
  ~DotlibTemplate();


public:

  /// @brief 内容をセットする．
  bool
  set_data(const DotlibNode* template_node);

  /// @brief 名前を返す．
  ShString
  name() const;

  /// @brief 次元数を返す．
  int
  dimension() const;

  /// @brief 'variable_1' を返す．
  /// @note 未定義なら kClibVarNone を返す．
  ClibVarType
  variable_1() const;

  /// @brief 'variable_2' を返す．
  /// @note 未定義なら kClibVarNone を返す．
  ClibVarType
  variable_2() const;

  /// @brief 'variable_3' を返す．
  /// @note 未定義なら kClibVarNone を返す．
  ClibVarType
  variable_3() const;

  /// @brief 'index_1' を返す．
  /// @note 未定義なら nullptr を返す．
  const DotlibNode*
  index_1() const;

  /// @brief 'index_2' を返す．
  /// @note 未定義なら nullptr を返す．
  const DotlibNode*
  index_2() const;

  /// @brief 'index_3' を返す．
  /// @note 未定義なら nullptr を返す．
  const DotlibNode*
  index_3() const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 名前
  ShString mName;

  // 次元数
  int mDimension;

  // variable_1
  ClibVarType mVar1;

  // variable_2
  ClibVarType mVar2;

  // variable_3
  ClibVarType mVar3;

  // index_1
  const DotlibNode* mIndex1;

  // index_2
  const DotlibNode* mIndex2;

  // index_3
  const DotlibNode* mIndex3;

};


END_NAMESPACE_YM_DOTLIB

#endif // DOTLIB_DOTLIBTEMPLATE_H
