#ifndef ASTLUTEMPLINFO_H
#define ASTLUTEMPLINFO_H

/// @file AstLuTemplInfo.h
/// @brief AstLuTemplInfo のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"
#include "dotlib/AstElemDict.h"
#include "ym/ShString.h"
#include "ci/CiCellLibrary.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstLuTemplInfo AstLuTemplInfo.h "AstLuTemplInfo.h"
/// @brief lu_template のパース情報を表すクラス
//////////////////////////////////////////////////////////////////////
class AstLuTemplInfo
{
public:

  /// @brief コンストラクタ
  AstLuTemplInfo() = default;

  /// @brief デストラクタ
  ~AstLuTemplInfo() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を設定する．
  bool
  set(
    const AstValue* lut_val ///< [in] テンプレート情報のパース木
  );

  /// @brief テンプレートを作る．
  void
  add_lu_template(
    CiCellLibrary* library
  );


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 名前
  ShString mName;

  // 次元
  SizeType mDimension;

  // variable_1
  ClibVarType mVar1{ClibVarType::none};

  // variable_2
  ClibVarType mVar2{ClibVarType::none};

  // variable_3
  ClibVarType mVar3{ClibVarType::none};

  // index_1
  vector<double> mIndex1;

  // index_2
  vector<double> mIndex2;

  // index_3
  vector<double> mIndex3;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTLUTEMPLINFO_H
