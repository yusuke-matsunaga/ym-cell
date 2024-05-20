#ifndef SERIALIZER_H
#define SERIALIZER_H

/// @file Serializer.h
/// @brief Serializer のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/BinEnc.h"


BEGIN_NAMESPACE_YM_CLIB

class CiBusType;
class CiPin;
class CiBus;
class CiBundle;
class CiTiming;
class CiLutTemplate;
class CiLut;
class CiCell;
class CiCellGroup;
class CiCellClass;

//////////////////////////////////////////////////////////////////////
/// @class Serializer Serializer.h "Serializer.h"
/// @brief dump 用の serializer
//////////////////////////////////////////////////////////////////////
class Serializer
{
public:

  /// @brief コンストラクタ
  Serializer(
    ostream& s ///< [in] 出力ストリーム
  ) : mS{s}
  {
  }

  /// @brief デストラクタ
  ~Serializer() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief バイナリエンコーダを返す．
  BinEnc&
  out()
  {
    return mS;
  }

  /// @brief バスタイプを追加する．
  void
  reg_obj(
    const CiBusType* obj
  )
  {
    mBusTypeList.put(obj);
  }

  /// @brief ピンを追加する．
  void
  reg_obj(
    const CiPin* obj
  )
  {
    mPinList.put(obj);
  }

  /// @brief バスを追加する．
  void
  reg_obj(
    const CiBus* obj
  )
  {
    mBusList.put(obj);
  }

  /// @brief バンドルを追加する．
  void
  reg_obj(
    const CiBundle* obj
  )
  {
    mBundleList.put(obj);
  }

  /// @brief タイミングを追加する．
  void
  reg_obj(
    const CiTiming* obj
  )
  {
    mTimingList.put(obj);
  }

  /// @brief LUTテンプレートを追加する．
  void
  reg_obj(
    const CiLutTemplate* obj
  )
  {
    mLutTemplateList.put(obj);
  }

  /// @brief LUTを追加する．
  void
  reg_obj(
    const CiLut* obj
  )
  {
    mLutList.put(obj);
  }

  /// @brief セルを追加する．
  void
  reg_obj(
    const CiCell* obj
  )
  {
    mCellList.put(obj);
  }

  /// @brief セルグループを追加する．
  void
  reg_obj(
    const CiCellGroup* obj
  )
  {
    mCellGroupList.put(obj);
  }

  /// @brief セルクラスを追加する．
  void
  reg_obj(
    const CiCellClass* obj
  )
  {
    mCellClassList.put(obj);
  }

  /// @brief 文字列をダンプする．
  void
  dump(
    const string& val
  )
  {
    out() << val;
  }

  /// @brief 整数をダンプする．
  void
  dump(
    SizeType val
  )
  {
    out().write_64(val);
  }

  /// @brief 整数のベクタをダンプする．
  void
  dump(
    const vector<SizeType>& vec
  )
  {
    out().write_64(vec.size());
    for ( auto v: vec ) {
      out().write_64(v);
    }
  }

  /// @brief 数値のベクタをダンプする．
  void
  dump(
    const vector<double>& vec
  )
  {
    out().write_64(vec.size());
    for ( auto v: vec ) {
      out() << v;
    }
  }

  /// @brief バスタイプ番号を出力する．
  void
  dump(
    const CiBusType* obj
  )
  {
    auto id = mBusTypeList.get_id(obj);
    out().write_64(id);
  }

  /// @brief ピン番号を出力する．
  void
  dump(
    const CiPin* obj
  )
  {
    auto id = mPinList.get_id(obj);
    out().write_64(id);
  }

  /// @brief ピン番号のリストを出力する．
  void
  dump(
    const vector<const CiPin*>& obj_list
  )
  {
    SizeType n = obj_list.size();
    out().write_64(n);
    for ( auto obj: obj_list ) {
      dump(obj);
    }
  }

  /// @brief バス番号を出力する．
  void
  dump(
    const CiBus* obj
  )
  {
    auto id = mBusList.get_id(obj);
    out().write_64(id);
  }

  /// @brief バス番号のリストを出力する．
  void
  dump(
    const vector<const CiBus*>& obj_list
  )
  {
    SizeType n = obj_list.size();
    out().write_64(n);
    for ( auto obj: obj_list ) {
      dump(obj);
    }
  }

  /// @brief バンドル番号を出力する．
  void
  dump(
    const CiBundle* obj
  )
  {
    auto id = mBundleList.get_id(obj);
    out().write_64(id);
  }

  /// @brief バンドル番号のリストを出力する．
  void
  dump(
    const vector<const CiBundle*>& obj_list
  )
  {
    SizeType n = obj_list.size();
    out().write_64(n);
    for ( auto obj: obj_list ) {
      dump(obj);
    }
  }

  /// @brief タイミング番号を出力する．
  void
  dump(
    const CiTiming* obj
  )
  {
    auto id = mTimingList.get_id(obj);
    out().write_64(id);
  }

  /// @brief タイミング番号のリストを出力する．
  void
  dump(
    const vector<const CiTiming*>& obj_list
  )
  {
    SizeType n = obj_list.size();
    out().write_64(n);
    for ( auto obj: obj_list ) {
      dump(obj);
    }
  }

  /// @brief LUTテンプレート番号を出力する．
  void
  dump(
    const CiLutTemplate* obj
  )
  {
    auto id = mLutTemplateList.get_id(obj);
    out().write_64(id);
  }

  /// @brief LUT番号を出力する．
  void
  dump(
    const CiLut* obj
  )
  {
    auto id = mLutList.get_id(obj);
    out().write_64(id);
  }

  /// @brief セル番号を出力する．
  void
  dump(
    const CiCell* obj
  )
  {
    auto id = mCellList.get_id(obj);
    out().write_64(id);
  }

  /// @brief セル番号のリストを出力する．
  void
  dump(
    const vector<const CiCell*>& obj_list
  )
  {
    SizeType n = obj_list.size();
    out().write_64(n);
    for ( auto obj: obj_list ) {
      dump(obj);
    }
  }

  /// @brief セルグループ番号を出力する．
  void
  dump(
    const CiCellGroup* obj
  )
  {
    auto id = mCellGroupList.get_id(obj);
    out().write_64(id);
  }

  /// @brief セルグループ番号のリストを出力する．
  void
  dump(
    const vector<const CiCellGroup*>& obj_list
  )
  {
    SizeType n = obj_list.size();
    out().write_64(n);
    for ( auto obj: obj_list ) {
      dump(obj);
    }
  }

  /// @brief セルクラス番号を出力する．
  void
  dump(
    const CiCellClass* obj
  )
  {
    auto id = mCellClassList.get_id(obj);
    out().write_64(id);
  }

  /// @brief セルクラス番号のリストを出力する．
  void
  dump(
    const vector<const CiCellClass*>& obj_list
  )
  {
    SizeType n = obj_list.size();
    out().write_64(n);
    for ( auto obj: obj_list ) {
      dump(obj);
    }
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 要素のリストと辞書
  template<class T>
  class ListMap
  {
  public:

    /// @brief コンストラクタ
    ListMap()
    {
      // nullptr を 0 番目の要素とする．
      mList.push_back(nullptr);
      mIdMap.emplace(nullptr, 0);
    }

    /// @brief デストラクタ
    ~ListMap() = default;

    /// @brief 要素を追加する．
    void
    put(
      const T* obj
    )
    {
      auto id = mList.size();
      mList.push_back(obj);
      mIdMap.emplace(obj, id);
    }

    /// @brief ID番号を得る．
    SizeType
    get_id(
      const T* obj
    ) const
    {
      return mIdMap.at(obj);
    }

    /// @brief 要素のリストを得る．
    const vector<const T*>&
    obj_list() const
    {
      return mList;
    }


  private:
    //////////////////////////////////////////////////////////////////////
    // データメンバ
    //////////////////////////////////////////////////////////////////////

    // 要素のリスト
    vector<const T*> mList;

    // 要素番号の辞書
    unordered_map<const T*, SizeType> mIdMap;

  };

  // バイナリエンコーダ
  BinEnc mS;

  // バスタイプのリスト
  ListMap<CiBusType> mBusTypeList;

  // ピンのリスト
  ListMap<CiPin> mPinList;

  // バスのリスト
  ListMap<CiBus> mBusList;

  // バンドルのリスト
  ListMap<CiBundle> mBundleList;

  // タイミングのリスト
  ListMap<CiTiming> mTimingList;

  // テンプレートのリスト
  ListMap<CiLutTemplate> mLutTemplateList;

  // LUTのリスト
  ListMap<CiLut> mLutList;

  // セルのリスト
  ListMap<CiCell> mCellList;

  // セルグループのリスト
  ListMap<CiCellGroup> mCellGroupList;

  // セルクラスのリスト
  ListMap<CiCellClass> mCellClassList;

};

END_NAMESPACE_YM_CLIB

#endif // SERIALIZER_H
