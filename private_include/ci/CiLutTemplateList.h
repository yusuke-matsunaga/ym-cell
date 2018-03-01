#ifndef CILUTTEMPLATELIST_H
#define CILUTTEMPLATELIST_H

/// @file CiLutTemplateList.h
/// @brief CiLutTemplateList のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibLutTemplateList.h"
#include "ym/Alloc.h"


BEGIN_NAMESPACE_YM_CLIB

class CiLutTemplate;

//////////////////////////////////////////////////////////////////////
/// @class CiLutTemplateList CiLutTemplateList.h "CiLutTemplateList.h"
/// @brief ClibLutTemplateList の実装クラス
//////////////////////////////////////////////////////////////////////
class CiLutTemplateList :
  public ClibLutTemplateList
{
public:

  /// @brief コンストラクタ
  ///
  /// 内容は不定
  CiLutTemplateList();

  /// @brief デストラクタ
  virtual
  ~CiLutTemplateList();


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
  const ClibLutTemplate*
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
  // CiLutTemplateList に固有の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を初期化する．
  /// @param[in] templ_list 要素のリスト
  /// @param[in] alloc メモリアロケータ
  void
  init(const vector<CiLutTemplate*>& templ_list,
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

  // 要素のポインタ配列
  const ClibLutTemplate** mArray;

};

END_NAMESPACE_YM_CLIB

#endif // CILUTTEMPLATELIST_H
