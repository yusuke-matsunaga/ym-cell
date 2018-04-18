#ifndef COMPLEXHANDLER_H
#define COMPLEXHANDLER_H

/// @file ComplexHandler.h
/// @brief ComplexHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "CGHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class ComplexHandler ComplexHandler.h "ComplexHandler.h"
/// @brief complex attribute 用のハンドラ
///
/// このクラスで DotlibHandler の仮想関数である parse_attr_value()
/// を実装している．
/// 具体的には
/// '(' <value>, <value>, <value>, ... ')' ';'
/// の形を仮定してパーズを行う．
/// '(' を読んだ直後に begin_header() を呼び出し，
/// 個々の <value> を読む度に read_value() を呼び出す．
/// 最後の ')' を読んだ直後に end_header() を呼び出す．
///
/// 継承クラスは以下の通り
///  * DefineHandler
///  * IndexHandler
///  * PieceWiseHandler
///  * UnitHandler
///  * ValuesHandler
//////////////////////////////////////////////////////////////////////
class ComplexHandler :
  public CGHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  ComplexHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~ComplexHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 属性値を読み込む．
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  parse_attr_value();


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

};

END_NAMESPACE_YM_DOTLIB

#endif // COMPLEXHANDLER_H
