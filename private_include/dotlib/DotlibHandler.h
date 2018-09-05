#ifndef DOTLIBHANDLER_H
#define DOTLIBHANDLER_H

/// @file DotlibHandler.h
/// @brief DotlibHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "dotlib/DotlibParser.h"
#include "ym/FileRegion.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibHandler DotlibHandler.h "DotlibHandler.h"
/// @brief liberty ファイルの各構文要素を読み込むためのクラス
///
/// 属性ごとに読み込んだ結果を表す構文木構造が異なるので仮想クラスにする．
/// 結果を取り出す関数は各継承クラス毎に独自のものを用意する．
///
/// liberty の構文は３種類に分類される．
/// - simple attribute:
///   <attr_name> : <value> ;
///   の形をとる．
///   * IntHandler
///   * FloatHandler
///   * StrHandler
///   * ExprHandler
///   * FuncHandler
///   * DelayModelHandler
///   * PinDirectionHandler
///   * TechnologyHandler
///   * TimingSenseHandler
///   * TimingTypeHandler
///   * VarTypeHandler
///
/// - complex attribute:
///   <attr_name> : ( <value_1>, <value_2>, ... ) ;
///   の形をとる．
///   * PieceWiseHandler
///   * UnitHandler
///   * IndexHandler
///   * ValuesHandler
///   * DefineHandler
///
/// - group attribute:
///   <attr_name> : ( <value_1>, <value_2>, ... ) {
///        子供の属性記述
///   }
///   の形をとる．前半部分は complex attribute と同じである．
///   * CellHandler
///   * CellInternalPowerHandler
///   * InputVoltageHandler
///   * InternalPowerHandler
///   * LibraryHandler
///   * OutputVoltageHandler
///   * PinHandler
///   * PowerHandler
///   * TableHandler
///   * TemplateHandler
///   * TimingHandler
///
/// それぞれ，SimpleHandler, ComplexHandler, GroupHandler (の継承クラス)
/// の parse_attr_value() というメンバ関数が実際のパース処理を行う．
///
/// このクラスの実際の役割は DotlibParser& を持つこと．
//////////////////////////////////////////////////////////////////////
class DotlibHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  DotlibHandler(DotlibParser& parser);

  /// @brief コピーコンストラクタは禁止
  DotlibHandler(const DotlibHandler& src) = delete;

  /// @brief ムーブコンストラクタも禁止
  DotlibHandler(DotlibHandler&& src) = delete;

  /// @brief デストラクタ
  virtual
  ~DotlibHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承のクラスが用いる便利関数
  // DotlibParser の同名の関数を呼び出す．
  //////////////////////////////////////////////////////////////////////

  /// @brief パーサーを得る．
  DotlibParser&
  parser();

  /// @brief 直前の read_token() に対応する文字列を返す．
  const char*
  cur_string();

  /// @brief 直前の read_token() に対応する整数値を返す．
  ///
  /// 型が INT_NUM でなかったときの値は不定
  int
  cur_int();

  /// @brief 直前の read_token() に対応する実数値を返す．
  ///
  /// 型が FLOAT_NUM/INT_NUM でなかったときの値は不定
  double
  cur_float();

  /// @brief 直前の read_token() に対応する位置を返す．
  FileRegion
  cur_loc();

  /// @brief 文字列を属性値に変換する．
  AttrType
  conv_to_attr(const char* str);

  /// @brief AstMgr を得る．
  AstMgr&
  mgr();

  /// @brief デバッグモードの時 true を返す．
  bool
  debug();

  /// @brief 未対応の属性名に対するエラーメッセージを出力する．
  /// @param[in] attr_type 対象の属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  static
  void
  syntax_error(AttrType attr_type,
	       const FileRegion& attr_loc);


#if 0
protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 引数の種類のトークンでなければエラーメッセージを出力する．
  /// @param[in] req_type 要求するトークンの型
  bool
  expect(TokenType req_type);

  /// @brief 行末まで読み込む．
  bool
  expect_nl();
#endif


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // パーサー
  DotlibParser& mParser;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief パーサーを得る．
inline
DotlibParser&
DotlibHandler::parser()
{
  return mParser;
}

// @brief 直前の read_token() に対応する文字列を返す．
inline
const char*
DotlibHandler::cur_string()
{
  return parser().cur_string();
}

// @brief 直前の read_token() に対応する整数値を返す．
//
// 型が INT_NUM でなかったときの値は不定
inline
int
DotlibHandler::cur_int()
{
  return parser().cur_int();
}

// @brief 直前の read_token() に対応する実数値を返す．
//
// 型が FLOAT_NUM/INT_NUM でなかったときの値は不定
inline
double
DotlibHandler::cur_float()
{
  return parser().cur_float();
}

// @brief 直前の read_token() に対応する位置を返す．
inline
FileRegion
DotlibHandler::cur_loc()
{
  return parser().cur_loc();
}

// @brief 文字列を属性値に変換する．
inline
AttrType
DotlibHandler::conv_to_attr(const char* str)
{
  return parser().conv_to_attr(str);
}

// @brief AstMgr を得る．
inline
AstMgr&
DotlibHandler::mgr()
{
  return parser().mgr();
}

// @brief デバッグモードの時 true を返す．
inline
bool
DotlibHandler::debug()
{
  return parser().debug();
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBHANDLER_H
