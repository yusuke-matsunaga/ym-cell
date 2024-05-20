#ifndef CICELLGROUP_H
#define CICELLGROUP_H

/// @file CiCellGroup.h
/// @brief CiCellGroup のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibCellGroup.h"
#include "ym/ClibIOMap.h"
#include "ym/logic.h"
#include "ci/CiLibObj.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCellClass;
class Serializer;
class Deserializer;

//////////////////////////////////////////////////////////////////////
/// @class CiCellGroup CiCellGroup.h "CiCellGroup.h"
/// @brief ClibCellGroup の実装クラス
//////////////////////////////////////////////////////////////////////
class CiCellGroup :
  public CiLibObj
{
public:

  /// @brief restore() 用のコンストラクタ
  CiCellGroup(
    const CiCellLibrary* lib     ///< [in] 親のセルライブラリ
  ) : CiLibObj{lib}
  {
  }

  /// @brief コンストラクタ
  CiCellGroup(
    const CiCellLibrary* lib,     ///< [in] 親のセルライブラリ
    const CiCellClass* rep_class, ///< [in] 親のセルクラス
    const ClibIOMap& iomap        ///< [in] 変換マップ
  ) : CiLibObj{lib},
      mRepClass{rep_class},
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
  const CiCellClass*
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
  const CiCell*
  cell(
    SizeType pos ///< [in] インデックス ( 0 <= pos < cell_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < cell_num() );
    return mCellList[pos];
  }

  /// @brief セルのリストを返す．
  const vector<const CiCell*>&
  cell_list() const
  {
    return mCellList;
  }


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をシリアライズする．
  void
  serialize(
    Serializer& s ///< [in] シリアライザ
  ) const;

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    Serializer& s ///< [in] シリアライザ
  ) const;

  /// @brief 内容を読み込む．
  static
  CiCellGroup*
  restore(
    Deserializer& s,   ///< [in] デシリアライザ
    CiCellLibrary* lib ///< [in] 親のセルライブラリ
  );


public:
  //////////////////////////////////////////////////////////////////////
  // 情報を設定する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief セルを追加する．
  void
  add_cell(
    const CiCell* cell
  )
  {
    mCellList.push_back(cell);
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 属している ClibCellClass
  const CiCellClass* mRepClass{nullptr};

  // ClibCellClass に対する入出力の変換関数
  ClibIOMap mIoMap;

  // セルのリスト
  vector<const CiCell*> mCellList;

};

END_NAMESPACE_YM_CLIB

#endif // CICELLGROUP_H
