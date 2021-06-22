
/// @file HeaderHandler.cc
/// @brief HeaderHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/HeaderHandler.h"
#include "dotlib/Scanner.h"
#include "dotlib/AstValue.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス HeaderHandler
//////////////////////////////////////////////////////////////////////

// @brief ヘッダの開始処理
// @param[in] loc '(' のファイル上の位置
//
// '(' を読み込んだ時に呼ばれる．
void
HeaderHandler::begin_header(const FileRegion& loc)
{
  mLpLoc = loc;
  mValueList.clear();
  _begin_header();
}

// @brief ヘッダの値を読み込む処理
bool
HeaderHandler::read_header_value(Scanner& scanner,
				 int count)
{
  auto value{_read_header_value(scanner, count)};
  if ( value != nullptr ) {
    mValueList.push_back(std::move(value));
    return true;
  }
  else {
    return false;
  }
}

// @brief 読み込みが終了した時の処理を行う．
// @param[in] loc ')' のファイル上の位置
// @param[in] count 読み込んだ要素数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
//
// ')' を読み込んだ直後に呼ばれる．
AstValuePtr
HeaderHandler::end_header(const FileRegion& loc,
			  int count)
{
  mRpLoc = loc;
  if ( _end_header(count) ) {
    FileRegion loc{mLpLoc, mRpLoc};
    return AstValue::new_complex(mValueList, loc);
  }
  else {
    return {};
  }
}

// @brief ヘッダの開始処理
//
// '(' を読み込んだ時に呼ばれる．
void
HeaderHandler::_begin_header()
{
  // デフォルトではなにもしない．
}


//////////////////////////////////////////////////////////////////////
// クラス FixedElemHeader
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
FixedElemHeader::FixedElemHeader(const vector<SimpleHandler>& handler_list)
  : mHandlerList{handler_list}
{
}

// @brief 値を読み込む処理
// @param[in] count read_value() の呼ばれた回数
AstValuePtr
FixedElemHeader::_read_header_value(Scanner& scanner,
				    int count)
{
  ASSERT_COND( count >= 0 );
  if ( count < mHandlerList.size() ) {
    auto handler{mHandlerList[count]};
    return handler(scanner);
  }
  else {
    ostringstream buf;
    buf << "Syntx error: "
	<< "Too many values, expected " << mHandlerList.size() << ".";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    FileRegion(lp_loc(), rp_loc()),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    buf.str());
    return {};
  }
}

// @brief 読み込みが終了した時の処理を行う．
bool
FixedElemHeader::_end_header(int count)
{
  ASSERT_COND( count <= mHandlerList.size() );
  if ( count < mHandlerList.size() ) {
    ostringstream buf;
    buf << "Syntx error: "
	<< "Too few values, expected " << mHandlerList.size() << ".";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    FileRegion(lp_loc(), rp_loc()),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }
  else {
    return true;
  }
}


//////////////////////////////////////////////////////////////////////
// クラス ListHeader
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
ListHeader::ListHeader(SimpleHandler handler)
  : mHandler{handler}
{
}

// @brief 値を読み込む処理
AstValuePtr
ListHeader::_read_header_value(Scanner& scanner,
			       int count)
{
  // count は無視
  return mHandler(scanner);
}

// @brief 読み込みが終了した時の処理を行う．
bool
ListHeader::_end_header(int count)
{
  // count は無視
  return true;
}

END_NAMESPACE_YM_DOTLIB
