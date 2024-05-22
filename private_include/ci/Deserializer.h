#ifndef DESERIALIZER_H
#define DESERIALIZER_H

/// @file Deserializer.h
/// @brief Deserializer のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/BinDec.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCellLibrary;
class CiBusType;
class CiLutTemplate;
class CiLut;
class CiTiming;
class CiPin;
class CiCell;
class CiCellGroup;
class CiCellClass;

//////////////////////////////////////////////////////////////////////
/// @class Deserializer Deserializer.h "Deserializer.h"
/// @brief restore 用の Deserializer
//////////////////////////////////////////////////////////////////////
class Deserializer
{
public:

  /// @brief コンストラクタ
  Deserializer(
    istream& s ///< [in] 入力ストリーム
  );

  /// @brief デストラクタ
  ~Deserializer() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief バイナリデコーダの取得
  BinDec&
  in()
  {
    return mS;
  }

  /// @brief 要素のデシリアライズを行う．
  void
  deserialize(
    CiCellLibrary* lib ///< [in] 親のセルライブラリ
  );

  /// @brief 文字列の読み込み
  void
  restore(
    string& dst
  )
  {
    mS >> dst;
  }

  /// @brief std::uint8_t の読み込み
  void
  restore(
    std::uint8_t& dst
  )
  {
    dst = mS.read_8();
  }

  /// @brief std::uint16_t の読み込み
  void
  restore(
    std::uint16_t& dst
  )
  {
    dst = mS.read_16();
  }

  /// @brief std::uint32_t の読み込み
  void
  restore(
    std::uint32_t& dst
  )
  {
    dst = mS.read_32();
  }

  /// @brief std::uint64_t の読み込み
  void
  restore(
    std::uint64_t& dst
  )
  {
    dst = mS.read_64();
  }

  /// @brief doubleの読み込み
  void
  restore(
    double& dst
  )
  {
    mS >> dst;
  }

#if 0
  /// @brief バスタイプの読み込み
  CiBusType*
  restore_bustype()
  {
    SizeType id;
    restore(id);
    return mBusTypeList[id];
  }
#endif

  /// @brief バスタイプの読み込み
  void
  restore(
    CiBusType*& dst
  )
  {
    SizeType id;
    restore(id);
    dst = mBusTypeList[id].get();
  }

  /// @brief バスタイプの読み込み
  void
  restore(
    unique_ptr<CiBusType>& dst
  )
  {
    SizeType id;
    restore(id);
    std::swap(dst, mBusTypeList[id]);
  }

#if 0
  /// @brief ピンの読み込み
  CiPin*
  restore_pin()
  {
    SizeType id;
    restore(id);
    return mPinList[id];
  }
#endif

  /// @brief ピンの読み込み
  void
  restore(
    CiPin*& dst
  )
  {
    SizeType id;
    restore(id);
    dst = mPinList[id].get();
  }

  /// @brief ピンの読み込み
  void
  restore(
    unique_ptr<CiPin>& dst
  )
  {
    SizeType id;
    restore(id);
    std::swap(dst, mPinList[id]);
  }

#if 0
  /// @brief バスの読み込み
  CiBus*
  restore_bus()
  {
    SizeType id;
    restore(id);
    return mBusList[id];
  }
#endif

  /// @brief バスの読み込み
  void
  restore(
    CiBus*& dst
  )
  {
    SizeType id;
    restore(id);
    dst = mBusList[id].get();
  }

  /// @brief バスの読み込み
  void
  restore(
    unique_ptr<CiBus>& dst
  )
  {
    SizeType id;
    restore(id);
    std::swap(dst, mBusList[id]);
  }

#if 0
  /// @brief バンドルの読み込み
  CiBundle*
  restore_bundle()
  {
    SizeType id;
    restore(id);
    return mBundleList[id];
  }
#endif

  /// @brief バンドルの読み込み
  void
  restore(
    CiBundle*& dst
  )
  {
    SizeType id;
    restore(id);
    dst = mBundleList[id].get();
  }

  /// @brief バンドルの読み込み
  void
  restore(
    unique_ptr<CiBundle>& dst
  )
  {
    SizeType id;
    restore(id);
    std::swap(dst, mBundleList[id]);
  }

#if 0
  /// @brief タイミングの読み込み
  CiTiming*
  restore_timing()
  {
    SizeType id;
    restore(id);
    return mTimingList[id];
  }
#endif

  /// @brief タイミングの読み込み
  void
  restore(
    CiTiming*& dst
  )
  {
    SizeType id;
    restore(id);
    dst = mTimingList[id].get();
  }

  /// @brief タイミングの読み込み
  void
  restore(
    unique_ptr<CiTiming>& dst
  )
  {
    SizeType id;
    restore(id);
    std::swap(dst, mTimingList[id]);
  }

#if 0
  /// @brief LUTテンプレートの読み込み
  CiLutTemplate*
  restore_luttemplate()
  {
    SizeType id;
    restore(id);
    return mLutTemplateList[id];
  }
#endif

  /// @brief LUTテンプレートの読み込み
  void
  restore(
    CiLutTemplate*& dst
  )
  {
    SizeType id;
    restore(id);
    dst = mLutTemplateList[id].get();
  }

  /// @brief LUTテンプレートの読み込み
  void
  restore(
    unique_ptr<CiLutTemplate>& dst
  )
  {
    SizeType id;
    restore(id);
    std::swap(dst, mLutTemplateList[id]);
  }

#if 0
  /// @brief LUTの読み込み
  CiLut*
  restore_lut()
  {
    SizeType id;
    restore(id);
    return mLutList[id];
  }
#endif

  /// @brief LUTの読み込み
  void
  restore(
    CiLut*& dst
  )
  {
    SizeType id;
    restore(id);
    dst = mLutList[id].get();
  }

  /// @brief LUTの読み込み
  void
  restore(
    unique_ptr<CiLut>& dst
  )
  {
    SizeType id;
    restore(id);
    std::swap(dst, mLutList[id]);
  }

#if 0
  /// @brief セルの読み込み
  CiCell*
  restore_cell()
  {
    SizeType id;
    restore(id);
    return mCellList[id];
  }
#endif

  /// @brief セルの読み込み
  void
  restore(
    CiCell*& dst
  )
  {
    SizeType id;
    restore(id);
    dst = mCellList[id].get();
  }

  /// @brief セルの読み込み
  void
  restore(
    unique_ptr<CiCell>& dst
  )
  {
    SizeType id;
    restore(id);
    std::swap(dst, mCellList[id]);
  }

#if 0
  /// @brief セルグループの読み込み
  CiCellGroup*
  restore_cellgroup()
  {
    SizeType id;
    restore(id);
    return mCellGroupList[id];
  }
#endif

  /// @brief セルグループの読み込み
  void
  restore(
    CiCellGroup*& dst
  )
  {
    SizeType id;
    restore(id);
    dst = mCellGroupList[id].get();
  }

  /// @brief セルグループの読み込み
  void
  restore(
    unique_ptr<CiCellGroup>& dst
  )
  {
    SizeType id;
    restore(id);
    std::swap(dst, mCellGroupList[id]);
  }

#if 0
  /// @brief セルクラスの読み込み
  CiCellClass*
  restore_cellclass()
  {
    SizeType id;
    restore(id);
    return mCellClassList[id];
  }
#endif

  /// @brief セルクラスの読み込み
  void
  restore(
    CiCellClass*& dst
  )
  {
    SizeType id;
    restore(id);
    dst = mCellClassList[id].get();
  }

  /// @brief セルクラスの読み込み
  void
  restore(
    unique_ptr<CiCellClass>& dst
  )
  {
    SizeType id;
    restore(id);
    std::swap(dst, mCellClassList[id]);
  }

  /// @brief const 型の要素の読み込み
  template<class T>
  void
  restore(
    const T*& dst
  )
  {
    T* tmp_dst;
    restore(tmp_dst);
    dst = tmp_dst;
  }

  /// @brief 要素のリストの読み込み
  template<class T>
  void
  restore(
    vector<T>& dst
  )
  {
    SizeType n = mS.read_64();
    dst.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      restore(dst[i]);
    }
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // バイナリデコーダ
  BinDec mS;

  // バスタイプのリスト
  vector<unique_ptr<CiBusType>> mBusTypeList;

  // LUTテンプレートのリスト
  vector<unique_ptr<CiLutTemplate>> mLutTemplateList;

  // LUTのリスト
  vector<unique_ptr<CiLut>> mLutList;

  // ピンのリスト
  vector<unique_ptr<CiPin>> mPinList;

  // バスのリスト
  vector<unique_ptr<CiBus>> mBusList;

  // バンドルのリスト
  vector<unique_ptr<CiBundle>> mBundleList;

  // タイミングのリスト
  vector<unique_ptr<CiTiming>> mTimingList;

  // セルのリスト
  vector<unique_ptr<CiCell>> mCellList;

  // セルグループのリスト
  vector<unique_ptr<CiCellGroup>> mCellGroupList;

  // セルクラスのリスト
  vector<unique_ptr<CiCellClass>> mCellClassList;

};

END_NAMESPACE_YM_CLIB

#endif // DESERIALIZER_H
