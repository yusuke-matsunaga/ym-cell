#ifndef CICELLGROUP_H
#define CICELLGROUP_H

/// @file CiCellGroup.h
/// @brief CiCellGroup のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibCellGroup.h"
#include "ym/ClibIOMap.h"
#include "ym/Expr.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiCellGroup CiCellGroup.h "CiCellGroup.h"
/// @brief ClibCellGroup の実装クラス
//////////////////////////////////////////////////////////////////////
class CiCellGroup
{
  friend class CiCellLibrary;

public:

  /// @brief コンストラクタ
  CiCellGroup(
    SizeType rep_class,    ///< [in] 親のセルクラス
    const ClibIOMap& iomap ///< [in] 変換マップ
  ) : mRepClass{rep_class},
      mIoMap{iomap}
  {
  }

  /// @brief デストラクタ
  ~CiCellGroup() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 一般的な情報を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 親のセルクラスを返す．
  SizeType
  rep_class() const
  {
    return mRepClass;
  }

  /// @brief 代表クラスに対する変換マップを返す．
  const ClibIOMap&
  iomap() const
  {
    return mIoMap;
  }


public:
  //////////////////////////////////////////////////////////////////////
  // このグループに属しているセルの情報を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief セル数を返す．
  SizeType
  cell_num() const
  {
    return mCellList.size();
  }

  /// @brief セルを返す．
  SizeType
  cell(
    SizeType pos ///< [in] インデックス ( 0 <= pos < cell_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < cell_num() );
    return mCellList[pos];
  }

  /// @brief セルのリストを返す．
  const vector<SizeType>&
  cell_list() const
  {
    return mCellList;
  }


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    BinEnc& s ///< [in] 出力先のストリーム
  ) const;


public:
  //////////////////////////////////////////////////////////////////////
  // 情報を設定する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief セルを追加する．
  void
  add_cell(
    SizeType id
  )
  {
    mCellList.push_back(id);
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 属している ClibCellClass
  SizeType mRepClass{CLIB_NULLID};

  // ClibCellClass に対する入出力の変換関数
  ClibIOMap mIoMap;

  // セルのリスト
  vector<SizeType> mCellList;

};

END_NAMESPACE_YM_CLIB

#endif // CICELLGROUP_H
