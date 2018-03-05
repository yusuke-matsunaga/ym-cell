#ifndef CICELLCLASS_H
#define CICELLCLASS_H

/// @file CiCellClass.h
/// @brief CiCellClass のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibCellClass.h"
#include "ym/Alloc.h"
#include "ym/IDO.h"
#include "ym/ODO.h"

#include "CiCellGroupList.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCellLibrary;

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

  /// @brief デストラクタ
  virtual
  ~CiCellClass();


public:
  //////////////////////////////////////////////////////////////////////
  // 一般的な情報を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号を返す．
  /// @note ClibCellLibrary::npn_class(id) で返されるオブジェクトの id() は id となる．
  virtual
  int
  id() const;

  /// @brief 同位体変換の個数を得る．
  /// @note 恒等変換は含まない．
  virtual
  int
  idmap_num() const;

  /// @brief 同位体変換を得る．
  /// @param[in] pos 位置番号 ( 0 <= pos < idmap_num() )
  virtual
  const NpnMapM&
  idmap(int pos) const;


public:
  //////////////////////////////////////////////////////////////////////
  // このクラスに属しているセルグループの情報を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief セルグループのリストを返す．
  virtual
  const ClibCellGroupList&
  group_list() const;


public:
  //////////////////////////////////////////////////////////////////////
  // バイナリダンプ用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief バイナリダンプを行う．
  /// @param[in] bos 出力先のストリーム
  void
  dump(ODO& bos) const;


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
  CiCellGroupList mGroupList;

};

END_NAMESPACE_YM_CLIB

#endif // CICELLCLASS_H
