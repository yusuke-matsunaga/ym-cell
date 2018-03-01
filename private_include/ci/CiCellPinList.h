#ifndef CICELLPINLIST_H
#define CICELLPINLIST_H

/// @file CiCellPinList.h
/// @brief CiCellPinList のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibCellPinList.h"
#include "ym/Alloc.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCellPin;

//////////////////////////////////////////////////////////////////////
/// @class CiCellPinList CiCellPinList.h "CiCellPinList.h"
/// @brief ClibCellPinList の実装クラス
//////////////////////////////////////////////////////////////////////
class CiCellPinList :
  public ClibCellPinList
{
public:

  /// @brief コンストラクタ
  ///
  /// 内容は不定
  CiCellPinList();

  /// @brief デストラクタ
  virtual
  ~CiCellPinList();


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
  const ClibCellPin*
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
  // CiCellPinList に固有の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を初期化する．
  /// @param[in] group_list 要素のリスト
  /// @param[in] alloc メモリアロケータ
  void
  init(const vector<CiCellPin*>& group_list,
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
  const ClibCellPin** mArray;

};

END_NAMESPACE_YM_CLIB

#endif // CICELLPINLIST_H
