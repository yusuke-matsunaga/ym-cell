#ifndef CICELLCLASS_H
#define CICELLCLASS_H

/// @file CiCellClass.h
/// @brief CiCellClass のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibCellClass.h"
#include "ym/ClibObjList.h"
#include "ym/Alloc.h"
#include "ym/IDO.h"
#include "ym/ODO.h"


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
  /// @param[in] alloc メモリアロケータ
  CiCellClass(int id,
	      const vector<NpnMapM>& idmap_list,
	      const vector<CiCellGroup*>& group_list,
	      Alloc& alloc);

  /// @brief エラーオブジェクト用のコンストラクタ
  CiCellClass();

  /// @brief デストラクタ
  ~CiCellClass();


public:
  //////////////////////////////////////////////////////////////////////
  // 一般的な情報を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号を返す．
  /// @note ClibCellLibrary::npn_class(id) で返されるオブジェクトの id() は id となる．
  int
  id() const override;

  /// @brief 同位体変換の個数を得る．
  /// @note 恒等変換は含まない．
  int
  idmap_num() const override;

  /// @brief 同位体変換を得る．
  /// @param[in] pos 位置番号 ( 0 <= pos < idmap_num() )
  const NpnMapM&
  idmap(int pos) const override;


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
  /// @param[in] bos 出力先のストリーム
  void
  dump(ODO& bos) const override;


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
