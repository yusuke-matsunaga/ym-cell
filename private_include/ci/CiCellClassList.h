#ifndef CICELLCLASSLIST_H
#define CICELLCLASSLIST_H

/// @file CiCellClassList.h
/// @brief CiCellClassList のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibCellClassList.h"
#include "ym/Alloc.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCellClass;

//////////////////////////////////////////////////////////////////////
/// @class CiCellClassList CiCellClassList.h "CiCellClassList.h"
/// @brief ClibCellClassList の実装クラス
//////////////////////////////////////////////////////////////////////
class CiCellClassList :
  public ClibCellClassList
{
public:

  /// @brief コンストラクタ
  ///
  /// 内容は不定
  CiCellClassList();

  /// @brief デストラクタ
  virtual
  ~CiCellClassList();


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
  const ClibCellClass*
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
  // CiCellClassList に固有の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を初期化する．
  /// @param[in] class_list セルクラスのリスト
  /// @param[in] alloc メモリアロケータ
  void
  init(const vector<CiCellClass*>& class_list,
       Alloc& alloc);

  /// @brief 要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < num() )
  const CiCellClass*
  _elem(int pos) const;


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

  // セルクラスへのポインタ配列
  CiCellClass** mArray;

};

END_NAMESPACE_YM_CLIB

#endif // CICELLCLASSLIST_H
