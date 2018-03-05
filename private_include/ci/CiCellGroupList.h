#ifndef CICELLGROUPLIST_H
#define CICELLGROUPLIST_H

/// @file CiCellGroupList.h
/// @brief CiCellGroupList のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibCellGroupList.h"
#include "ym/Alloc.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCellGroup;

//////////////////////////////////////////////////////////////////////
/// @class CiCellGroupList CiCellGroupList.h "CiCellGroupList.h"
/// @brief ClibCellGroupList の実装クラス
//////////////////////////////////////////////////////////////////////
class CiCellGroupList :
  public ClibCellGroupList
{
public:

  /// @brief コンストラクタ
  ///
  /// 内容は不定
  CiCellGroupList();

  /// @brief 内容を指定したコンストラクタ
  /// @param[in] group_list 要素のリスト
  /// @param[in] alloc メモリアロケータ
  CiCellGroupList(const vector<CiCellGroup*>& group_list,
		  Alloc& alloc);

  /// @brief デストラクタ
  virtual
  ~CiCellGroupList();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 要素数を返す．
  virtual
  int
  num() const;

  /// @brief 要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < num() )
  virtual
  const ClibCellGroup*
  operator[](int pos) const;

  /// @brief 先頭の反復子を返す．
  virtual
  iterator
  begin() const;

  /// @brief 末尾の反復子を返す．
  virtual
  iterator
  end() const;


public:
  //////////////////////////////////////////////////////////////////////
  // CiCellGroupList に固有の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を初期化する．
  /// @param[in] group_list 要素のリスト
  /// @param[in] alloc メモリアロケータ
  void
  init(const vector<CiCellGroup*>& group_list,
       Alloc& alloc);


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 要素数
  int mNum;

  // セルグループのポインタの配列
  const ClibCellGroup** mArray;

};

END_NAMESPACE_YM_CLIB

#endif // CICELLGROUPLIST_H
