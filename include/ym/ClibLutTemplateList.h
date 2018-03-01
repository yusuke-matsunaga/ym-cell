#ifndef CLIBLUTTEMPLATELIST_H
#define CLIBLUTTEMPLATELIST_H

/// @file ClibLutTemplateList.h
/// @brief ClibLutTemplateList のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ym/clib.h"
#include "ym/ArrayIterator.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class ClibLutTemplateList ClibLutTemplateList.h "ClibLutTemplateList.h"
/// @brief ClibLutTemplate のリストを表すクラス
///
/// @code
/// const ClibLutTemplateList& lut_templ_list = ...;
/// for ( auto lut_templ: lut_templ_list ) {
///   ...
/// }
/// @endcode
/// という風に使える．
//////////////////////////////////////////////////////////////////////
class ClibLutTemplateList
{
public:
  typedef ArrayIterator<const ClibLutTemplate*> iterator;

  /// @brief デストラクタ
  virtual
  ~ClibLutTemplateList() { }


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 要素数を返す．
  virtual
  int
  num() const = 0;

  /// @brief 要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < num() )
  virtual
  const ClibLutTemplate*
  operator[](int pos) const = 0;

  /// @brief 先頭の反復子を返す．
  virtual
  iterator
  begin() const = 0;

  /// @brief 末尾の反復子を返す．
  virtual
  iterator
  end() const = 0;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////


};

END_NAMESPACE_YM_CLIB

#endif // CLIBLUTTEMPLATELIST_H
