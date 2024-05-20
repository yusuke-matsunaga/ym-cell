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
  ) : mS{s}
  {
    // 各要素の0番目は nullptr
    mBusTypeList.push_back(nullptr);
    mPinList.push_back(nullptr);
    mBusList.push_back(nullptr);
    mBundleList.push_back(nullptr);
    mTimingList.push_back(nullptr);
    mLutTemplateList.push_back(nullptr);
    mLutList.push_back(nullptr);
    mCellClassList.push_back(nullptr);
    mCellGroupList.push_back(nullptr);
    mCellList.push_back(nullptr);
  }

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
  )
  {
    {
      SizeType n;
      restore(n);
      cout << "# of BusType: " << n << endl;
      for ( SizeType i = 0; i < n; ++ i ) {
	auto ptr = CiBusType::restore(*this, lib);
	mBusTypeList.push_back(ptr);
      }
    }
    {
      SizeType n;
      restore(n);
      cout << "# of LutTemplate: " << n << endl;
      for ( SizeType i = 0; i < n; ++ i ) {
	auto ptr = CiLutTemplate::restore(*this, lib);
	mLutTemplateList.push_back(ptr);
      }
    }
    {
      SizeType n;
      restore(n);
      cout << "# of Lut: " << n << endl;
      for ( SizeType i = 0; i < n; ++ i ) {
	auto ptr = CiLut::restore(*this, lib);
	mLutList.push_back(ptr);
      }
    }
    {
      SizeType n;
      restore(n);
      cout << "# of Pin: " << n << endl;
      for ( SizeType i = 0; i < n; ++ i ) {
	auto ptr = CiPin::restore(*this, lib);
	mPinList.push_back(ptr);
      }
    }
    {
      SizeType n;
      restore(n);
      cout << "# of Bus: " << n << endl;
      for ( SizeType i = 0; i < n; ++ i ) {
	auto ptr = CiBus::restore(*this, lib);
	mBusList.push_back(ptr);
      }
    }
    {
      SizeType n;
      restore(n);
      cout << "# of Bundle: " << n << endl;
      for ( SizeType i = 0; i < n; ++ i ) {
	auto ptr = CiBundle::restore(*this, lib);
	mBundleList.push_back(ptr);
      }
    }
    {
      SizeType n;
      restore(n);
      cout << "# of Timing: " << n << endl;
      for ( SizeType i = 0; i < n; ++ i ) {
	auto ptr = CiTiming::restore(*this, lib);
	mTimingList.push_back(ptr);
      }
    }
    {
      SizeType n;
      restore(n);
      cout << "# of CellClass: " << n << endl;
      for ( SizeType i = 0; i < n; ++ i ) {
	auto ptr = CiCellClass::restore(*this, lib);
	mCellClassList.push_back(ptr);
      }
    }
    {
      SizeType n;
      restore(n);
      cout << "# of CellGroup: " << n << endl;
      for ( SizeType i = 0; i < n; ++ i ) {
	auto ptr = CiCellGroup::restore(*this, lib);
	mCellGroupList.push_back(ptr);
      }
    }
    {
      SizeType n;
      restore(n);
      cout << "# of Cell: " << n << endl;
      for ( SizeType i = 0; i < n; ++ i ) {
	auto ptr = CiCell::restore(*this, lib);
	mCellList.push_back(ptr);
      }
    }
  }

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
  CiBusType*
  restore_bustype()
  {
    SizeType id;
    restore(id);
    return mBusTypeList[id];
  }

  /// @brief バスタイプの読み込み
  void
  restore(
    CiBusType*& dst
  )
  {
    dst = restore_bustype();
  }

  /// @brief ピンの読み込み
  CiPin*
  restore_pin()
  {
    SizeType id;
    restore(id);
    return mPinList[id];
  }

  /// @brief ピンの読み込み
  void
  restore(
    CiPin*& dst
  )
  {
    dst = restore_pin();
  }

  /// @brief バスの読み込み
  CiBus*
  restore_bus()
  {
    SizeType id;
    restore(id);
    return mBusList[id];
  }
  /// @brief バスの読み込み
  void
  restore(
    CiBus*& dst
  )
  {
    dst = restore_bus();
  }

  /// @brief バンドルの読み込み
  CiBundle*
  restore_bundle()
  {
    SizeType id;
    restore(id);
    return mBundleList[id];
  }

  /// @brief バンドルの読み込み
  void
  restore(
    CiBundle*& dst
  )
  {
    dst = restore_bundle();
  }

  /// @brief タイミングの読み込み
  CiTiming*
  restore_timing()
  {
    SizeType id;
    restore(id);
    return mTimingList[id];
  }

  /// @brief タイミングの読み込み
  void
  restore(
    CiTiming*& dst
  )
  {
    dst = restore_timing();
  }

  /// @brief LUTテンプレートの読み込み
  CiLutTemplate*
  restore_luttemplate()
  {
    SizeType id;
    restore(id);
    return mLutTemplateList[id];
  }

  /// @brief LUTテンプレートの読み込み
  void
  restore(
    CiLutTemplate*& dst
  )
  {
    dst = restore_luttemplate();
  }

  /// @brief LUTの読み込み
  CiLut*
  restore_lut()
  {
    SizeType id;
    restore(id);
    return mLutList[id];
  }

  /// @brief LUTの読み込み
  void
  restore(
    CiLut*& dst
  )
  {
    dst = restore_lut();
  }

  /// @brief セルの読み込み
  CiCell*
  restore_cell()
  {
    SizeType id;
    restore(id);
    return mCellList[id];
  }

  /// @brief セルの読み込み
  void
  restore(
    CiCell*& dst
  )
  {
    dst = restore_cell();
  }

  /// @brief セルグループの読み込み
  CiCellGroup*
  restore_cellgroup()
  {
    SizeType id;
    restore(id);
    return mCellGroupList[id];
  }

  /// @brief セルグループの読み込み
  void
  restore(
    CiCellGroup*& dst
  )
  {
    dst = restore_cellgroup();
  }

  /// @brief セルクラスの読み込み
  CiCellClass*
  restore_cellclass()
  {
    SizeType id;
    restore(id);
    return mCellClassList[id];
  }

  /// @brief セルクラスの読み込み
  void
  restore(
    CiCellClass*& dst
  )
  {
    dst = restore_cellclass();
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
  vector<CiBusType*> mBusTypeList;

  // LUTテンプレートのリスト
  vector<CiLutTemplate*> mLutTemplateList;

  // LUTのリスト
  vector<CiLut*> mLutList;

  // ピンのリスト
  vector<CiPin*> mPinList;

  // バスのリスト
  vector<CiBus*> mBusList;

  // バンドルのリスト
  vector<CiBundle*> mBundleList;

  // タイミングのリスト
  vector<CiTiming*> mTimingList;

  // セルのリスト
  vector<CiCell*> mCellList;

  // セルクラスのリスト
  vector<CiCellClass*> mCellClassList;

  // セルグループのリスト
  vector<CiCellGroup*> mCellGroupList;

};

END_NAMESPACE_YM_CLIB

#endif // DESERIALIZER_H
