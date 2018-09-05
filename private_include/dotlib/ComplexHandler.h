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
/// 実は CGHandler をそのまま継承している．
/// どちらかというと alias 的な継承
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
  /// @param parser パーサー
  ComplexHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~ComplexHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いられる便利関数
  //////////////////////////////////////////////////////////////////////

  /// @brief Complex Attribute を読み込む．
  /// @retval true 正しく読み込めた．
  /// @retval false エラーが起こった．
  bool
  parse_complex_attribute();


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

};

END_NAMESPACE_YM_DOTLIB

#endif // COMPLEXHANDLER_H
