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

  /// @brief バスタイプの辞書を作る．
  void
  reg_bustype(
    const vector<unique_ptr<CiBusType>>& obj_list
  )
  {
    SizeType id = 0;
    for ( auto& obj: obj_list ) {
      mBusTypeMap.emplace(obj.get(), id);
      ++ id;
    }
  }

  /// @brief ピンの辞書を作る．
  void
  reg_pin(
    const vector<unique_ptr<CiPin>>& obj_list
  )
  {
    SizeType id = 0;
    for ( auto& obj: obj_list ) {
      mPinMap.emplace(obj.get(), id);
      ++ id;
    }
  }

  /// @brief バスの辞書を作る．
  void
  reg_bus(
    const vector<unique_ptr<CiBus>>& obj_list
  )
  {
    SizeType id = 0;
    for ( auto& obj: obj_list ) {
      mBusMap.emplace(obj.get(), id);
      ++ id;
    }
  }

  /// @brief バンドルの辞書を作る．
  void
  reg_bundle(
    const vector<unique_ptr<CiBundle>>& obj_list
  )
  {
    SizeType id = 0;
    for ( auto& obj: obj_list ) {
      mBundleMap.emplace(obj.get(), id);
      ++ id;
    }
  }

  /// @brief タイミングの辞書を作る．
  void
  reg_timing(
    const vector<unique_ptr<CiTiming>>& obj_list
  )
  {
    SizeType id = 0;
    for ( auto& obj: obj_list ) {
      mTimingMap.emplace(obj.get(), id);
      ++ id;
    }
  }

  /// @brief LUTテンプレートの辞書を作る．
  void
  reg_luttemplate(
    const vector<unique_ptr<CiLutTemplate>>& obj_list
  )
  {
    SizeType id = 0;
    for ( auto& obj: obj_list ) {
      mLutTemplateMap.emplace(obj.get(), id);
      ++ id;
    }
  }

  /// @brief LUTの辞書を作る．
  void
  reg_lut(
    const vector<unique_ptr<CiLut>>& obj_list
  )
  {
    SizeType id = 0;
    for ( auto& obj: obj_list ) {
      mLutMap.emplace(obj.get(), id);
      ++ id;
    }
  }

  /// @brief セルの辞書を作る．
  void
  reg_cell(
    const vector<unique_ptr<CiCell>>& obj_list
  )
  {
    SizeType id = 0;
    for ( auto& obj: obj_list ) {
      mCellMap.emplace(obj.get(), id);
      ++ id;
    }
  }

  /// @brief セルグループの辞書を作る．
  void
  reg_cellgroup(
    const vector<unique_ptr<CiCellGroup>>& obj_list
  )
  {
    SizeType id = 0;
    for ( auto& obj: obj_list ) {
      mCellGroupMap.emplace(obj.get(), id);
      ++ id;
    }
  }

  /// @brief セルクラスの辞書を作る．
  void
  reg_cellclass(
    const vector<unique_ptr<CiCellClass>>& obj_list
  )
  {
    SizeType id = 0;
    for ( auto& obj: obj_list ) {
      mCellClassMap.emplace(obj.get(), id);
      ++ id;
    }
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
    auto id = mBusTypeMap.at(obj);
    out().write_64(id);
  }

  /// @brief ピン番号を出力する．
  void
  dump(
    const CiPin* obj
  )
  {
    auto id = mPinMap.at(obj);
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
    auto id = mBusMap.at(obj);
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
    auto id = mBundleMap.at(obj);
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
    auto id = mTimingMap.at(obj);
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
    auto id = mLutTemplateMap.at(obj);
    out().write_64(id);
  }

  /// @brief LUT番号を出力する．
  void
  dump(
    const CiLut* obj
  )
  {
    auto id = mLutMap.at(obj);
    out().write_64(id);
  }

  /// @brief セル番号を出力する．
  void
  dump(
    const CiCell* obj
  )
  {
    auto id = mCellMap.at(obj);
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
    auto id = mCellGroupMap.at(obj);
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
    auto id = mCellClassMap.at(obj);
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

  // バイナリエンコーダ
  BinEnc mS;

  // バスタイプ番号の辞書
  unordered_map<const CiBusType*, SizeType> mBusTypeMap;

  // ピン番号の辞書
  unordered_map<const CiPin*, SizeType> mPinMap;

  // バス番号の辞書
  unordered_map<const CiBus*, SizeType> mBusMap;

  // バンドル番号の辞書
  unordered_map<const CiBundle*, SizeType> mBundleMap;

  // タイミング番号の辞書
  unordered_map<const CiTiming*, SizeType> mTimingMap;

  // テンプレート番号の辞書
  unordered_map<const CiLutTemplate*, SizeType> mLutTemplateMap;

  // LUT番号の辞書
  unordered_map<const CiLut*, SizeType> mLutMap;

  // セル番号の辞書
  unordered_map<const CiCell*, SizeType> mCellMap;

  // セルグループ番号の辞書
  unordered_map<const CiCellGroup*, SizeType> mCellGroupMap;

  // セルクラス番号の辞書
  unordered_map<const CiCellClass*, SizeType> mCellClassMap;

};

END_NAMESPACE_YM_CLIB

#endif // SERIALIZER_H
