#ifndef FLOATVECTORLISTHANDLER_H
#define FLOATVECTORLISTHANDLER_H

/// @file FloatVectorListHandler.h
/// @brief FloatVectorListHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/HeaderHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class FloatVectorListHandler FloatVectorListHandler.h "dotlib/FloatVectorListHandler.h"
/// @brief ("float, float, ...", "float, float, ...", ... ) の形式のヘッダ用のハンドラ
///
/// 意味的には２次元の配列だが結果は AstFloatVector で返す．
//////////////////////////////////////////////////////////////////////
class FloatVectorListHandler :
  public HeaderHandler
{
public:

  /// @brief コンストラクタ
  FloatVectorListHandler(DotlibParser& parser); ///< [in] パーサー

  /// @brief デストラクタ
  ~FloatVectorListHandler();


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
  // HeaderHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの開始処理
  ///
  /// '(' を読み込んだ時に呼ばれる．
  void
  _begin_header() override;

  /// @brief 値を読み込む処理
  /// @param[in] count read_value() の呼ばれた回数
  bool
  _read_header_value(int count) override;

  /// @brief 読み込みが終了した時の処理を行う．
  /// @param[in] count 読み込んだ要素数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  _end_header(int count) override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 読み込んだ値
  vector<double> mValueList;

};

END_NAMESPACE_YM_DOTLIB

#endif // FLOATVECTORLISTHANDLER_H
