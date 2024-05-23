#ifndef CILIBOBJ_H
#define CILIBOBJ_H

/// @file CiLibObj.h
/// @brief CiLibObj のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCellLibrary;

//////////////////////////////////////////////////////////////////////
/// @class CiLibObj CiLibObj.h "CiLibObj.h"
/// @brief CiCellLibrary の子供の基底クラス
///
/// 参照回数を管理するが，実際には親のセルライブラリの参照回数を増減する．
//////////////////////////////////////////////////////////////////////
class CiLibObj
{
public:

  /// @brief コンストラクタ
  CiLibObj(
    CiCellLibrary* lib ///< [in] 親のライブラリオブジェクト
  );

  /// @brief デストラクタ
  ~CiLibObj();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 親のライブラリオブジェクトを返す．
  const CiCellLibrary*
  parent() const
  {
    return mParent;
  }

  /// @brief 参照数を増やす
  void
  inc_ref() const;

  /// @brief 参照数を減らす
  void
  dec_ref() const;


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 親のライブラリオブジェクトを返す．
  CiCellLibrary*
  _parent() const
  {
    return mParent;
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 親のライブラリオブジェクト
  CiCellLibrary* mParent;

};

END_NAMESPACE_YM_CLIB

#endif // CILIBOBJ_H
