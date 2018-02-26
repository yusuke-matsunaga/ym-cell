#ifndef CITIMINGLIST_H
#define CITIMINGLIST_H

/// @file CiTimingList.h
/// @brief CiTimingList のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibTimingList.h"
#include "ym/Alloc.h"


BEGIN_NAMESPACE_YM_CLIB

class CiTiming;

//////////////////////////////////////////////////////////////////////
/// @class CiTimingList CiTimingList.h "CiTimingList.h"
/// @brief ClibTimingList の実装クラス
//////////////////////////////////////////////////////////////////////
class CiTimingList :
  public ClibTimingList
{
public:

  /// @brief コンストラクタ
  ///
  /// 内容は不定
  CiTimingList();

  /// @brief デストラクタ
  virtual
  ~CiTimingList();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を初期化する．
  /// @param[in] num 要素数
  /// @param[in] alloc メモリアロケータ
  ///
  /// ここでは領域を確保するだけ．
  void
  init(int num,
       Alloc& alloc);

  /// @brief 要素を設定する．
  /// @param[in] pos 位置番号 ( 0 <= pos < num() )
  /// @param[in] timing 設定する要素
  void
  set(int pos,
      const ClibTiming* timing);

  /// @brief 要素数を返す．
  virtual
  int
  num() const;

  /// @brief 先頭の反復子を返す．
  virtual
  iterator
  begin() const;

  /// @brief 末尾の反復子を返す．
  virtual
  iterator
  end() const;

  /// @brief 指定された位置の要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < num() )
  virtual
  const ClibTiming*
  operator[](int pos) const;


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

  // タイミングのポインタ配列
  const ClibTiming** mArray;

};

END_NAMESPACE_YM_CLIB

#endif // CITIMINGLIST_H
