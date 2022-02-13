#ifndef CIBUNDLE_H
#define CIBUNDLE_H

/// @file CiBundle.h
/// @brief CiBundle のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibBundle.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiBundle CiBundle.h "CiBundle.h"
/// @brief ClibBundle の実装クラス
//////////////////////////////////////////////////////////////////////
class CiBundle :
  public ClibBundle
{
public:

  /// @brief コンストラクタ
  CiBundle() = default;

  /// @brief デストラクタ
  ~CiBundle() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前の取得
  string
  name() const override;

  /// @brief 名前の取得
  ShString
  _name() const
  {
    return mName;
  }

  /// @brief ピン数の取得
  SizeType
  pin_num() const override;

  /// @brief ピンの取得
  const ClibPin&
  pin(
    SizeType pos ///< [in] 位置番号 ( 0 <= pos < pin_num() )
  ) const override;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    BinEnc& s ///< [in] 出力先のストリーム
  ) const override;


public:
  //////////////////////////////////////////////////////////////////////
  // 設定用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を初期化する．
  void
  init(
    const ShString& name,
    vector<const ClibPin*>&& pin_list
  );


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 名前
  ShString mName;

  // ピンのリスト
  vector<const ClibPin*> mPinList;

};

END_NAMESPACE_YM_CLIB

#endif // CIBUNDLE_H
