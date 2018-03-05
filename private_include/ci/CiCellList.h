#ifndef CICELLLIST_H
#define CICELLLIST_H

/// @file CiCellList.h
/// @brief CiCellList のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibCellList.h"
#include "ym/Alloc.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCell;

//////////////////////////////////////////////////////////////////////
/// @class CiCellList CiCellList.h "CiCellList.h"
/// @brief ClibCellList の実装クラス
//////////////////////////////////////////////////////////////////////
class CiCellList :
  public ClibCellList
{
public:

  /// @brief 空のコンストラクタ
  ///
  /// 内容は不定
  CiCellList();

  /// @brief コンストラクタ
  /// @param[in] src_list セルのリスト
  /// @param[in] alloc メモリアロケータ
  CiCellList(const vector<CiCell*>& cell_list,
	     Alloc& alloc);

  /// @brief デストラクタ
  virtual
  ~CiCellList();


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
  const ClibCell*
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
  // CiCellList に固有の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を設定する．
  /// @param[in] src_list セルのリスト
  /// @param[in] alloc メモリアロケータ
  void
  init(const vector<CiCell*>& cell_list,
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

  // セルへのポインタ配列
  const ClibCell** mArray;

};

END_NAMESPACE_YM_CLIB

#endif // CICELLLIST_H
