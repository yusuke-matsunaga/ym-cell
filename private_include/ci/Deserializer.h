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

  /// @brief バスタイプの登録
  void
  reg_obj(
    const CiBusType* obj
  )
  {
    mBusTypeList.push_back(obj);
  }

  /// @brief LUTテンプレートの登録
  void
  reg_obj(
    const CiLutTemplate* obj
  )
  {
    mLutTemplateList.push_back(obj);
  }

  /// @brief LUTの登録
  void
  reg_obj(
    const CiLut* obj
  )
  {
    mLutList.push_back(obj);
  }

  /// @brief ピンの登録
  void
  reg_obj(
    const CiPin* obj
  )
  {
    mPinList.push_back(obj);
  }

  /// @brief バスの登録
  void
  reg_obj(
    const CiBus* obj
  )
  {
    mBusList.push_back(obj);
  }

  /// @brief バンドルの登録
  void
  reg_obj(
    const CiBundle* obj
  )
  {
    mBundleList.push_back(obj);
  }

  /// @brief タイミングの登録
  void
  reg_obj(
    const CiTiming* obj
  )
  {
    mTimingList.push_back(obj);
  }

  /// @brief セルの登録
  void
  reg_obj(
    const CiCell* obj
  )
  {
    mCellList.push_back(obj);
  }

  /// @brief セルグループの登録
  void
  reg_obj(
    const CiCellGroup* obj
  )
  {
    mCellGroupList.push_back(obj);
  }

  /// @brief セルクラスの登録
  void
  reg_obj(
    const CiCellClass* obj
  )
  {
    mCellClassList.push_back(obj);
  }

  /// @brief SizeType の読み込み
  void
  restore(
    SizeType& dst
  )
  {
    dst = mS.read_64();
  }

  /// @brief 番号のベクタの読み込み
  void
  restore(
    vector<SizeType>& dst
  )
  {
    SizeType n = mS.read_64();
    dst.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      restore(dst[i]);
    }
  }

  /// @brief 数値の読み込み
  void
  restore(
    double& dst
  )
  {
    mS >> dst;
  }

  /// @brief 数値のベクタの読み込み
  void
  restore(
    vector<double>& dst
  )
  {
    SizeType n = mS.read_64();
    dst.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      restore(dst[i]);
    }
  }

  /// @brief バスタイプの読み込み
  void
  restore(
    const CiBusType*& dst
  )
  {
    SizeType id;
    mS >> id;
    dst = mBusTypeList[id];
  }

  /// @brief ピンの読み込み
  void
  restore(
    const CiPin*& dst
  )
  {
    SizeType id;
    mS >> id;
    dst = mPinList[id];
  }

  /// @brief ピンのリストの読み込み
  void
  restore(
    vector<const CiPin*>& dst
  )
  {
    SizeType n = mS.read_64();
    dst.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      restore(dst[i]);
    }
  }

  /// @brief バスの読み込み
  void
  restore(
    const CiBus*& dst
  )
  {
    SizeType id;
    mS >> id;
    dst = mBusList[id];
  }

  /// @brief バスのリストの読み込み
  void
  restore(
    vector<const CiBus*>& dst
  )
  {
    SizeType n = mS.read_64();
    dst.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      restore(dst[i]);
    }
  }

  /// @brief バンドルの読み込み
  void
  restore(
    const CiBundle*& dst
  )
  {
    SizeType id;
    mS >> id;
    dst = mBundleList[id];
  }

  /// @brief バンドルのリストの読み込み
  void
  restore(
    vector<const CiBundle*>& dst
  )
  {
    SizeType n = mS.read_64();
    dst.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      restore(dst[i]);
    }
  }

  /// @brief タイミングの読み込み
  void
  restore(
    const CiTiming*& dst
  )
  {
    SizeType id;
    mS >> id;
    dst = mTimingList[id];
  }

  /// @brief タイミングのリストの読み込み
  void
  restore(
    vector<const CiTiming*>& dst
  )
  {
    SizeType n = mS.read_64();
    dst.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      restore(dst[i]);
    }
  }

  /// @brief LUTテンプレートの読み込み
  void
  restore(
    const CiLutTemplate*& dst
  )
  {
    SizeType id;
    mS >> id;
    dst = mLutTemplateList[id];
  }

  /// @brief LUTテンプレートのリストの読み込み
  void
  restore(
    vector<const CiLutTemplate*>& dst
  )
  {
    SizeType n = mS.read_64();
    dst.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      restore(dst[i]);
    }
  }

  /// @brief LUTの読み込み
  void
  restore(
    const CiLut*& dst
  )
  {
    SizeType id;
    mS >> id;
    dst = mLutList[id];
  }

  /// @brief LUTのリストの読み込み
  void
  restore(
    vector<const CiLut*>& dst
  )
  {
    SizeType n = mS.read_64();
    dst.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      restore(dst[i]);
    }
  }

  /// @brief セルの読み込み
  void
  restore(
    const CiCell*& dst
  )
  {
    SizeType id;
    mS >> id;
    dst = mCellList[id];
  }

  /// @brief セルのリストの読み込み
  void
  restore(
    vector<const CiCell*>& dst
  )
  {
    SizeType n = mS.read_64();
    dst.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      restore(dst[i]);
    }
  }

  /// @brief セルグループの読み込み
  void
  restore(
    const CiCellGroup*& dst
  )
  {
    SizeType id;
    mS >> id;
    dst = mCellGroupList[id];
  }

  /// @brief セルグループのリストの読み込み
  void
  restore(
    vector<const CiCellGroup*>& dst
  )
  {
    SizeType n = mS.read_64();
    dst.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      restore(dst[i]);
    }
  }

  /// @brief セルクラスの読み込み
  void
  restore(
    const CiCellClass*& dst
  )
  {
    SizeType id;
    mS >> id;
    dst = mCellClassList[id];
  }

  /// @brief セルクラスのリストの読み込み
  void
  restore(
    vector<const CiCellClass*>& dst
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
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // バイナリデコーダ
  BinDec mS;

  // バスタイプのリスト
  vector<const CiBusType*> mBusTypeList;

  // ピンのリスト
  vector<const CiPin*> mPinList;

  // バスのリスト
  vector<const CiBus*> mBusList;

  // バンドルのリスト
  vector<const CiBundle*> mBundleList;

  // タイミングのリスト
  vector<const CiTiming*> mTimingList;

  // LUTテンプレートのリスト
  vector<const CiLutTemplate*> mLutTemplateList;

  // LUTのリスト
  vector<const CiLut*> mLutList;

  // セルのリスト
  vector<const CiCell*> mCellList;

  // セルグループのリスト
  vector<const CiCellGroup*> mCellGroupList;

  // セルクラスのリスト
  vector<const CiCellClass*> mCellClassList;

};

END_NAMESPACE_YM_CLIB

#endif // DESERIALIZER_H
