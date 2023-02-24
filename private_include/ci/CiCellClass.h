#ifndef CICELLCLASS_H
#define CICELLCLASS_H

/// @file CiCellClass.h
/// @brief CiCellClass のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibCellClass.h"
#include "ym/ClibIOMap.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiCellClass CiCellClass.h "CiCellClass.h"
/// @brief ClibCellClass の実装クラス
//////////////////////////////////////////////////////////////////////
class CiCellClass
{
public:

  /// @brief コンストラクタ
  CiCellClass(
    const vector<ClibIOMap>& idmap_list ///< [in] 同位体変換リスト
  ) : mIdMapList{idmap_list}
  {
  }

  /// @brief デストラクタ
  ~CiCellClass() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 一般的な情報を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 同位体変換の個数を得る．
  /// @note 恒等変換は含まない．
  SizeType
  idmap_num() const
  {
    return mIdMapList.size();
  }

  /// @brief 同位体変換を得る．
  const ClibIOMap&
  idmap(
    SizeType pos
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < idmap_num() );
    return mIdMapList[pos];
  }

  /// @brief 同位体変換のリストを得る．
  const vector<ClibIOMap>&
  idmap_list() const
  {
    return mIdMapList;
  }


public:
  //////////////////////////////////////////////////////////////////////
  // このクラスに属しているセルグループの情報を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ数を返す．
  SizeType
  cell_group_num() const
  {
    return mGroupList.size();
  }

  /// @brief グループを返す．
  SizeType
  cell_group(
    SizeType pos ///< [in] インデックス ( 0 <= pos < cell_group_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < cell_group_num() );
    return mGroupList[pos];
  }

  /// @brief グループのリストを返す．
  const vector<SizeType>&
  cell_group_list() const
  {
    return mGroupList;
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
  // 設定用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief このクラスに属しているセルグループを追加する．
  void
  add_group(
    SizeType id
  )
  {
    mGroupList.push_back(id);
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 同位体変換のリスト
  vector<ClibIOMap> mIdMapList;

  // セルグループ番号のリスト
  vector<SizeType> mGroupList;

};

END_NAMESPACE_YM_CLIB

#endif // CICELLCLASS_H
