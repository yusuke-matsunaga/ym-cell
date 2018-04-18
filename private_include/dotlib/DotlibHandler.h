#ifndef DOTLIBHANDLER_H
#define DOTLIBHANDLER_H

/// @file DotlibHandler.h
/// @brief DotlibHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
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
  ~DotlibHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 他のクラスが用いる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief パーサーを得る．
  DotlibParser&
  parser();

  /// @brief AstMgr を得る．
  AstMgr&
  mgr();


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

  /// @brief 未対応の属性名に対するエラーメッセージを出力する．
  /// @param[in] attr_type 対象の属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  static
  void
  syntax_error(AttrType attr_type,
	       const FileRegion& attr_loc);

  /// @brief デバッグモードの時に true を返す．
  bool
  debug();


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // パーサー
  DotlibParser& mParser;

};

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBHANDLER_H
