#ifndef CICELLCLASS_H
#define CICELLCLASS_H

/// @file CiCellClass.h
/// @brief CiCellClass のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibCellClass.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCellLibrary;
class CiCellGroup;

//////////////////////////////////////////////////////////////////////
/// @class CiCellClass CiCellClass.h "CiCellClass.h"
/// @brief ClibCellClass の実装クラスの基底クラス
//////////////////////////////////////////////////////////////////////
class CiCellClass :
  public ClibCellClass
{
  friend class CiCellLibrary;

public:

  /// @brief コンストラクタ
  /// @param[in] id 番号
  /// @param[in] idmap_list 同位体変換リスト
  /// @param[in] group_list グループのリスト
  CiCellClass(
    SizeType id,
    const vector<NpnMapM>& idmap_list,
    const vector<CiCellGroup*>& group_list
  ) : mId{id},
      mIdmapList{idmap_list},
      mGroupList{group_list}
  {
  }

  /// @brief エラーオブジェクト用のコンストラクタ
  CiCellClass() = default;

  /// @brief デストラクタ
  ~CiCellClass() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 一般的な情報を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号を返す．
  /// @note ClibCellLibrary::npn_class(id) で返されるオブジェクトの id() は id となる．
  SizeType
  id() const override;

  /// @brief 同位体変換の個数を得る．
  /// @note 恒等変換は含まない．
  SizeType
  idmap_num() const override;

  /// @brief 同位体変換を得る．
  const NpnMapM&
  idmap(
    SizeType pos
  ) const override;


public:
  //////////////////////////////////////////////////////////////////////
  // このクラスに属しているセルグループの情報を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ数を返す．
  SizeType
  cell_group_num() const override;

  /// @brief グループを返す．
  const ClibCellGroup&
  cell_group(
    SizeType pos ///< [in] インデックス ( 0 <= pos < cell_group_num() )
  ) const override;


public:
  //////////////////////////////////////////////////////////////////////
  // バイナリダンプ用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief バイナリダンプを行う．
  void
  dump(
    ostream& bos ///< [in] 出力先のストリーム
  ) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ID番号
  SizeType mId{CLIB_NULLID};

  // 同位体変換の配列
  vector<NpnMapM> mIdmapList;

  // セルグループのリスト
  vector<CiCellGroup*> mGroupList;

};

END_NAMESPACE_YM_CLIB

#endif // CICELLCLASS_H
