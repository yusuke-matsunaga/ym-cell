#ifndef CIBUS_H
#define CIBUS_H

/// @file CiBus.h
/// @brief CiBus のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiBus CiBus.h "CiBus.h"
/// @brief ClibBus の実装クラス
//////////////////////////////////////////////////////////////////////
class CiBus
{
public:

  /// @brief 空のコンストラクタ(restore用)
  CiBus() = default;

  /// @brief コンストラクタ
  CiBus(
    const ShString& name,            ///< [in] 名前
    SizeType bus_type,               ///< [in] バスタイプ
    const vector<SizeType>& pin_list ///< [in] ピンリスト
  ) : mName{name},
      mBusType{bus_type},
      mPinList{pin_list}
  {
  }

  /// @brief デストラクタ
  ~CiBus() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前の取得
  string
  name() const
  {
    return mName;
  }

  /// @brief 名前の取得
  ShString
  _name() const
  {
    return mName;
  }

  /// @brief バスの型の取得
  SizeType
  bus_type() const
  {
    return mBusType;
  }

  /// @brief ピン数の取得
  SizeType
  pin_num() const
  {
    return mPinList.size();
  }

  /// @brief ピンの取得
  SizeType
  pin(
    SizeType pos ///< [in] 位置番号 ( 0 <= pos < pin_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < pin_num() );
    return mPinList[pos];
  }

  /// @brief ピン番号のリストの取得
  const vector<SizeType>&
  pin_list() const
  {
    return mPinList;
  }


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    BinEnc& s ///< [in] 出力先のストリーム
  ) const;

  /// @brief 内容を読み込む．
  void
  restore(
    BinDec& s ///< [in] 入力元のストリーム
  );


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 名前
  ShString mName;

  // バスの型
  SizeType mBusType{CLIB_NULLID};

  // ピン番号のリスト
  vector<SizeType> mPinList;

};

END_NAMESPACE_YM_CLIB

#endif // CIBUS_H
