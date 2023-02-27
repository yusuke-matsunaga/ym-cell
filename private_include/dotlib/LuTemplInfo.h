#ifndef LUTEMPLINFO_H
#define LUTEMPLINFO_H

/// @file LuTemplInfo.h
/// @brief LuTemplInfo のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"
#include "dotlib/ElemDict.h"
#include "ym/ShString.h"
#include "ci/CiCellLibrary.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class LuTemplInfo LuTemplInfo.h "LuTemplInfo.h"
/// @brief lu_template のパース情報を表すクラス
//////////////////////////////////////////////////////////////////////
class LuTemplInfo
{
public:

  /// @brief コンストラクタ
  LuTemplInfo(
    CiCellLibrary* library
  ) : mLibrary{library}
  {
  }

  /// @brief デストラクタ
  ~LuTemplInfo() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を設定する．
  bool
  set(
    const AstValue* lut_val ///< [in] テンプレート情報のパース木
  );

  /// @brief 名前を得る．
  ShString
  name() const
  {
    return mName;
  }

  /// @brief テンプレートを作る．
  SizeType
  add_lu_template();


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ライブラリ
  CiCellLibrary* mLibrary{nullptr};

  // 要素の辞書
  ElemDict mElemDict;

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

#endif // LUTEMPLINFO_H
