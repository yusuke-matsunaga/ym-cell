
/// @file DotlibParser.cc
/// @brief DotlibParser の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibParser.h"
#include "dotlib/DotlibMgr.h"
#include "dotlib/HandlerFactory.h"
#include "dotlib/DotlibHandler.h"
#include "DotlibParserImpl.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibParser
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
DotlibParser::DotlibParser() :
  mImpl(new DotlibParserImpl),
  mLibHandler(HandlerFactory::new_library(*this))
{
}

// @brief デストラクタ
DotlibParser::~DotlibParser()
{
  delete mImpl;
  delete mLibHandler;
}

// @brief ファイルを読み込む．
// @param[in] filename ファイル名
// @param[in] mgr DotlibNode を管理するオブジェクト
// @param[in] debug デバッグモード
// @param[in] allow_no_semi 行末のセミコロンなしを許すかどうか
// @return 読み込んだ AST を返す．
//
// エラーが起きたら nullptr を返す．
const DotlibLibrary*
DotlibParser::read_file(const string& filename,
			DotlibMgr& mgr,
			bool debug,
			bool allow_no_semi)
{
  return mImpl->read_file(filename, mgr.mImpl, mLibHandler, debug, allow_no_semi);
}

// @brief 引数の種類のトークンでなければエラーメッセージを出力する．
bool
DotlibParser::expect(TokenType type)
{
  return mImpl->expect(type);
}

// @brief 行末まで読み込む．
bool
DotlibParser::expect_nl()
{
  return mImpl->expect_nl();
}

// @brief トークンを一つ読み込む．
// @param[out] loc ファイル上の位置情報を格納する変数
// @param[in] symbol_mode 数字も文字とみなすモード
// @return トークンの型を返す．
TokenType
DotlibParser::read_token(FileRegion& loc,
			 bool symbol_mode)
{
  return mImpl->read_token(loc, symbol_mode);
}

// @brief 直前の read_token() に対応する文字列を返す．
const char*
DotlibParser::cur_string() const
{
  return mImpl->cur_string();
}

// @brief 直前の read_token() に対応する整数値を返す．
//
// 型が INT_NUM でなかったときの値は不定
int
DotlibParser::cur_int() const
{
  return mImpl->cur_int();
}

// @brief 直前の read_token() に対応する実数値を返す．
//
// 型が FLOAT_NUM/INT_NUM でなかったときの値は不定
double
DotlibParser::cur_float() const
{
  return mImpl->cur_float();
}

// @brief 直前の read_token() に対応する位置を返す．
FileRegion
DotlibParser::cur_loc() const
{
  return mImpl->cur_loc();
}

// @brief 文字列を属性値に変換する．
AttrType
DotlibParser::conv_to_attr(const char* str)
{
  return mImpl->conv_to_attr(str);
}

// @brief DotlibMgrImpl* を返す．
DotlibMgrImpl*
DotlibParser::mgr()
{
  return mImpl->mgr();
}

// @brief デバッグモードの時 true を返す．
bool
DotlibParser::debug()
{
  return mImpl->debug();
}

END_NAMESPACE_YM_DOTLIB
