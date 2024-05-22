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
///
/// BinDec からデータを読み込み，各要素を復元して mXXXList と mXXXTable
/// に格納する．
/// 各要素の0番目は nullptr として予約されている．
/// mXXXList は unique_ptr となっていて実際の unique_ptr に所有権を奪われるまで
/// は仮の所有者となる．
/// mXXXTable は参照のみを持つ．
/// このように２種類のリストを持つ理由は mXXXList は途中で所有権を奪われて無効化
/// されることがあるため．
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

  /// @brief SizeType の読み込み
  void
  restore(
    SizeType& dst
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

  /// @brief バスタイプの読み込み
  void
  restore(
    CiBusType*& dst
  )
  {
    SizeType id;
    restore(id);
    dst = mBusTypeTable[id];
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

  /// @brief ピンの読み込み
  void
  restore(
    CiPin*& dst
  )
  {
    SizeType id;
    restore(id);
    dst = mPinTable[id];
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

  /// @brief バスの読み込み
  void
  restore(
    CiBus*& dst
  )
  {
    SizeType id;
    restore(id);
    dst = mBusTable[id];
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

  /// @brief バンドルの読み込み
  void
  restore(
    CiBundle*& dst
  )
  {
    SizeType id;
    restore(id);
    dst = mBundleTable[id];
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

  /// @brief タイミングの読み込み
  void
  restore(
    CiTiming*& dst
  )
  {
    SizeType id;
    restore(id);
    dst = mTimingTable[id];
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

  /// @brief LUTテンプレートの読み込み
  void
  restore(
    CiLutTemplate*& dst
  )
  {
    SizeType id;
    restore(id);
    dst = mLutTemplateTable[id];
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

  /// @brief LUTの読み込み
  void
  restore(
    CiLut*& dst
  )
  {
    SizeType id;
    restore(id);
    dst = mLutTable[id];
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

  /// @brief セルの読み込み
  void
  restore(
    CiCell*& dst
  )
  {
    SizeType id;
    restore(id);
    dst = mCellTable[id];
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

  /// @brief セルグループの読み込み
  void
  restore(
    CiCellGroup*& dst
  )
  {
    SizeType id;
    restore(id);
    dst = mCellGroupTable[id];
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

  /// @brief セルクラスの読み込み
  void
  restore(
    CiCellClass*& dst
  )
  {
    SizeType id;
    restore(id);
    dst = mCellClassTable[id];
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

  // バスタイプのリスト(所有権あり)
  vector<unique_ptr<CiBusType>> mBusTypeList;

  // LUTテンプレートのリスト(所有権あり)
  vector<unique_ptr<CiLutTemplate>> mLutTemplateList;

  // LUTのリスト(所有権あり)
  vector<unique_ptr<CiLut>> mLutList;

  // ピンのリスト(所有権あり)
  vector<unique_ptr<CiPin>> mPinList;

  // バスのリスト(所有権あり)
  vector<unique_ptr<CiBus>> mBusList;

  // バンドルのリスト(所有権あり)
  vector<unique_ptr<CiBundle>> mBundleList;

  // タイミングのリスト(所有権あり)
  vector<unique_ptr<CiTiming>> mTimingList;

  // セルのリスト(所有権あり)
  vector<unique_ptr<CiCell>> mCellList;

  // セルグループのリスト(所有権あり)
  vector<unique_ptr<CiCellGroup>> mCellGroupList;

  // セルクラスのリスト(所有権あり)
  vector<unique_ptr<CiCellClass>> mCellClassList;

  // バスタイプの変換テーブル
  vector<CiBusType*> mBusTypeTable;

  // LUTテンプレートの変換テーブル
  vector<CiLutTemplate*> mLutTemplateTable;

  // LUTの変換テーブル
  vector<CiLut*> mLutTable;

  // ピンの変換テーブル
  vector<CiPin*> mPinTable;

  // バスの変換テーブル
  vector<CiBus*> mBusTable;

  // バンドルの変換テーブル
  vector<CiBundle*> mBundleTable;

  // タイミングの変換テーブル
  vector<CiTiming*> mTimingTable;

  // セルの変換テーブル
  vector<CiCell*> mCellTable;

  // セルグループの変換テーブル
  vector<CiCellGroup*> mCellGroupTable;

  // セルクラスの変換テーブル
  vector<CiCellClass*> mCellClassTable;

};

END_NAMESPACE_YM_CLIB

#endif // DESERIALIZER_H
