#ifndef CLIBLIST_H
#define CLIBLIST_H

/// @file ClibList.h
/// @brief ClibList のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/ClibLibraryPtr.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class ClibListIter ClibList.h "ClibList.h"
/// @brief ClibList の反復子
//////////////////////////////////////////////////////////////////////
template<class T>
class ClibListIter
{
public:

  /// @brief コンストラクタ
  ClibListIter(
    const ClibLibraryPtr& library,        ///< [in] ライブラリ
    vector<SizeType>::const_iterator iter ///< [in] セル番号のリストの反復子
  ) : mLibrary{library},
      mIter{iter}
  {
  }

  /// @brief デストラクタ
  ~ClibListIter() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を取り出す．
  T
  operator*() const
  {
    return T{mLibrary, *mIter};
  }

  /// @brief 一つ進める．
  ClibListIter&
  operator++()
  {
    ++ mIter;
    return *this;
  }

  /// @brief 等価比較演算子
  bool
  operator==(
    const ClibListIter& right
  ) const
  {
    return mLibrary == right.mLibrary && mIter == right.mIter;
  }

  /// @brief 非等価比較演算子
  bool
  operator!=(
    const ClibListIter& right
  ) const
  {
    return !operator==(right);
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 親のライブラリ
  ClibLibraryPtr mLibrary;

  // セル番号のリストの反復子
  vector<SizeType>::const_iterator mIter;

};


//////////////////////////////////////////////////////////////////////
/// @class ClibList ClibList.h "ClibList.h"
/// @brief ClibXXX のリストを表すクラス
///
/// コンストラクタが ClibXXX(const CiCellLibrary*, SizeType) であると
/// 仮定している．
//////////////////////////////////////////////////////////////////////
template<class T>
class ClibList
{
public:

  using iterator = ClibListIter<T>;

public:

  /// @brief 空のコンストラクタ
  ClibList() = default;

  /// @brief コンストラクタ
  ClibList(
    const ClibLibraryPtr& library,          ///< [in] ライブラリ
    vector<SizeType>::const_iterator begin, ///< [in] 番号のリストの先頭
    vector<SizeType>::const_iterator end    ///< [in] 番号のリストの末尾
  ) : mLibrary{library},
      mBegin{begin},
      mEnd{end}
  {
  }

  /// @brief コンストラクタ
  ClibList(
    const ClibLibraryPtr& library,  ///< [in] ライブラリ
    const vector<SizeType>& id_list ///< [in] 番号のリスト
  ) : mLibrary{library},
      mBegin{id_list.begin()},
      mEnd{id_list.end()}
  {
  }

  /// @brief デストラクタ
  ~ClibList() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 要素数を返す．
  SizeType
  size() const
  {
    return mEnd - mBegin;
  }

  /// @brief 要素を返す．
  T
  operator[](
    SizeType pos
  ) const
  {
    if ( pos < 0 || size() <= pos ) {
      throw std::out_of_range("out of range");
    }
    return T{mLibrary, *(mBegin + pos)};
  }

  /// @brief 先頭の反復子を返す．
  iterator
  begin() const
  {
    return iterator{mLibrary, mBegin};
  }

  /// @brief 末尾の反復子を返す．
  iterator
  end() const
  {
    return iterator{mLibrary, mEnd};
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 親のライブラリ
  ClibLibraryPtr mLibrary;

  // 番号のリストの先頭
  vector<SizeType>::const_iterator mBegin;

  // 番号のリストの末尾
  vector<SizeType>::const_iterator mEnd;

};


//////////////////////////////////////////////////////////////////////
// ClibList を用いたリスト型
//////////////////////////////////////////////////////////////////////

using ClibCellList = ClibList<ClibCell>;
using ClibCellGroupList = ClibList<ClibCellGroup>;
using ClibCellClassList = ClibList<ClibCellClass>;
using ClibPinList = ClibList<ClibPin>;
using ClibBusList = ClibList<ClibBus>;
using ClibBundleList = ClibList<ClibBundle>;
using ClibTimingList = ClibList<ClibTiming>;
using ClibLutList = ClibList<ClibLut>;
using ClibLutTemplateList = ClibList<ClibLutTemplate>;

END_NAMESPACE_YM_CLIB

BEGIN_NAMESPACE_YM

using nsClib::ClibCellList;
using nsClib::ClibCellGroupList;
using nsClib::ClibCellClassList;
using nsClib::ClibPinList;
using nsClib::ClibBusList;
using nsClib::ClibBundleList;
using nsClib::ClibTimingList;
using nsClib::ClibLutList;
using nsClib::ClibLutTemplateList;

END_NAMESPACE_YM

#endif // CLIBLIST_H
