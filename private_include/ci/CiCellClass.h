#ifndef CICELLCLASS_H
#define CICELLCLASS_H

/// @file CiCellClass.h
/// @brief CiCellClass のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibCellClass.h"
#include "ym/ClibObjList.h"


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
  CiCellClass(
    int id,                                ///< [in] 番号
    const vector<NpnMapM>& idmap_list,     ///< [in] 同位体変換リスト
    const vector<CiCellGroup*>& group_list ///< [in] グループのリスト
  );

  /// @brief エラーオブジェクト用のコンストラクタ
  CiCellClass();

  /// @brief デストラクタ
  ~CiCellClass();


public:
  //////////////////////////////////////////////////////////////////////
  // 一般的な情報を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号を返す．
  ///
  /// ClibCellLibrary::npn_class(id) で返されるオブジェクトの id() は id となる．
  int
  id() const override;

  /// @brief 同位体変換の個数を得る．
  ///
  /// 恒等変換は含まない．
  int
  idmap_num() const override;

  /// @brief 同位体変換を得る．
  const NpnMapM&
  idmap(
    int pos ///< [in] 位置番号 ( 0 <= pos < idmap_num() )
  ) const override;


public:
  //////////////////////////////////////////////////////////////////////
  // このクラスに属しているセルグループの情報を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief セルグループのリストを返す．
  const ClibCellGroupList&
  group_list() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // バイナリダンプ用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief バイナリダンプを行う．
  /// @param[in] bos
  void
  dump(
    ostream& bos ///< [in] 出力先のストリーム
  ) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ID番号
  int mId;

  // 同位体変換の数
  int mIdmapNum;

  // 同位体変換の配列
  NpnMapM* mIdmapList;

  // セルグループのリスト
  ClibCellGroupList mGroupList;

};

END_NAMESPACE_YM_CLIB

#endif // CICELLCLASS_H
