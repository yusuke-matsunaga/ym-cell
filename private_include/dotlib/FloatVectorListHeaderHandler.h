#ifndef FLOATVECTORLISTHEADERHANDLER_H
#define FLOATVECTORLISTHEADERHANDLER_H

/// @file FloatVectorListHeaderHandler.h
/// @brief FloatVectorListHeaderHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HeaderHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class FloatVectorListHeaderHandler FloatVectorListHeaderHandler.h "dotlib/FloatVectorListHeaderHandler.h"
/// @brief ("float, float, ...", "float, float, ...", ... ) の形式のヘッダ用のハンドラ
///
/// 意味的には２次元の配列だが結果は AstFloatVector で返す．
//////////////////////////////////////////////////////////////////////
class FloatVectorListHeaderHandler :
  public HeaderHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  FloatVectorListHeaderHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~FloatVectorListHeaderHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 読み込んだ値を返す．
  const AstFloatVector*
  value() const;


public:
  //////////////////////////////////////////////////////////////////////
  // HeaderHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの開始処理
  ///
  /// '(' を読み込んだ時に呼ばれる．
  void
  begin_header() override;

  /// @brief 値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  /// @param[in] count read_value() の呼ばれた回数
  bool
  read_header_value(TokenType value_type,
		    const FileRegion& value_loc,
		    int count) override;

  /// @brief 読み込みが終了した時の処理を行う．
  /// @param[in] count 読み込んだ要素数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  end_header(int count) override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値のリスト
  vector<double> mValueList;

  // 読み込んだ値
  const AstFloatVector* mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 読み込んだ値を返す．
inline
const AstFloatVector*
FloatVectorListHeaderHandler::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // FLOATVECTORLISTHEADERHANDLER_H
