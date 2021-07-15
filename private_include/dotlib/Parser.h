﻿#ifndef PARSER_H
#define PARSER_H

/// @file Parser.h
/// @brief Parser のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"
#include "dotlib/AttrKwd.h"
#include "dotlib/HeaderHandler.h"
#include "dotlib/DotlibScanner.h"

#include "ym/FileRegion.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class Parser Parser.h "dotlib/Parser.h"
/// @brief Parser の実装クラス
//////////////////////////////////////////////////////////////////////
class Parser
{
public:

  /// @brief コンストラクタ
  Parser(
    istream& s,                ///< [in] 入力ストリーム
    const FileInfo& file_info, ///< [in] ファイル情報
    bool debug,                ///< [in] デバッグモード
    bool allow_no_semi = true  ///< [in] 行末のセミコロンなしを許すかどうか
  );

  /// @brief デストラクタ
  ~Parser();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief パーズする
  /// @return 読み込んだ library のASTを返す．
  ///
  /// エラーが起きたら nullptr を返す．
  AstAttrPtr
  parse();


public:
  //////////////////////////////////////////////////////////////////////
  // ハンドラ関数から使われる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief Simple Attribute を読み込む．
  /// @retrun 結果の AstAttr を返す．
  ///
  /// エラーが起こったら nullptr を返す．
  AstAttrPtr
  parse_simple_attribute(
    const AttrKwd& attr,  ///< [in] 属性の型
    SimpleHandler handler ///< [in] simple 属性ハンドラ
  );

  /// @brief Complex Attribute を読み込む．
  /// @retrun 結果の AstAttr を返す．
  ///
  /// エラーが起こったら nullptr を返す．
  AstAttrPtr
  parse_complex_attribute(
    const AttrKwd& attr,   ///< [in] 属性の型
    HeaderHandler& handler ///< [in] ヘッダ読み込みハンドラ
  );

  /// @brief Group Statement を読み込む．
  /// @retrun 結果の AstAttr を返す．
  ///
  /// エラーが起こったら nullptr を返す．
  AstAttrPtr
  parse_group_statement(
    const AttrKwd& attr,          ///< [in] 属性の型
    const char* group_name,       ///< [in] 親のグループ名
    HeaderHandler& header_handler ///< [in] ヘッダ読み込みハンドラ
  );

  /// @brief デバッグモードの時 true を返す．
  bool
  debug();


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる下請け関数
  //////////////////////////////////////////////////////////////////////

  /// @brief Complex Attribute, GroupStatement のヘッダを読み込む．
  /// @retrun 結果の AstAttr を返す．
  ///
  /// エラーが起こったら nullptr を返す．
  AstValuePtr
  parse_header(
    HeaderHandler& handler ///< [in] ハンドラ(HeaderHandler の継承クラス)
  );

  /// @brief 行末まで読み込む．
  ///
  /// 具体的には ';' '/n' を確認する．
  /// ただし， mAllowNoSemi が true の場合には
  /// ';' を無視する．
  bool
  read_tail();


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 字句解析器
  DotlibScanner mScanner;

  // デバッグモード
  bool mDebug;

  // 行末のセミコロンなしを許すかどうかのフラグ
  bool mAllowNoSemi;


public:

  // complex attribute/group statement header 用のハンドラ
  static FixedElemHeader sEmptyHeader;
  static FixedElemHeader sFloatFloatHeader;
  static FixedElemHeader sFloatFloatStrHeader;
  static FixedElemHeader sFloatStrHeader;
  static FixedElemHeader sFloatVectorHeader;
  static FixedElemHeader sIntFloatHeader;
  static FixedElemHeader sIntFloatVectorHeader;
  static FixedElemHeader sIntStrHeader;
  static FixedElemHeader sIntVectorHeader;
  static FixedElemHeader sStrFloatHeader;
  static FixedElemHeader sStrHeader;
  static FixedElemHeader sStrIntHeader;
  static FixedElemHeader sStrStrHeader;
  static FixedElemHeader sStrStrIntHeader;
  static FixedElemHeader sStrStrStrHeader;
  static FanoutLengthHeader sFanoutLengthHeader;
  static FixedElemHeader sTechnologyHeader;
  static ListHeader sFloatVectorListHeader;
  static ListHeader sIntListHeader;
  static ListHeader sStrListHeader;

  // グループハンドラの辞書
  static unordered_map<string, AttrHandler> sHandlerDict;

};

END_NAMESPACE_YM_DOTLIB

#endif // PARSER_H
