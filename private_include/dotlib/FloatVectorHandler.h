#ifndef FLOATVECTORHANDLER_H
#define FLOATVECTORHANDLER_H

/// @file FloatVectorHandler.h
/// @brief FloatVectorHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/ElemHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class FloatVectorHandler FloatVectorHandler.h "dotlib/FloatVectorHandler.h"
/// @brief ( "float, float, ..." ) ; の形のヘッダ用のハンドラ
///
/// つまり全体は文字列だが，内容がコンマで区切られた浮動小数点数
//////////////////////////////////////////////////////////////////////
class FloatVectorHandler :
  public ElemHandler
{
public:

  /// @brief コンストラクタ
  FloatVectorHandler(DotlibParser& parser); ///< [in] パーサー

  /// @brief デストラクタ
  ~FloatVectorHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 読み込んだ値を返す．
  const vector<double>&
  value_list() const
  {
    return mValueList;
  }


private:
  //////////////////////////////////////////////////////////////////////
  // ElemHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief begin_header() 内で呼ばれる初期化関数
  void
  initialize() override;

  /// @brief ヘッダの値を読み込む処理
  /// @param[in] count read_value() の呼ばれた回数
  bool
  read_value(int count) override;

  /// @brief end_header() 内で呼ばれる終了処理関数
  void
  finalize() override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


protected:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 読み込んだ値
  vector<double> mValueList;

};

END_NAMESPACE_YM_DOTLIB

#endif // FLOATVECTORHANDLER_H
