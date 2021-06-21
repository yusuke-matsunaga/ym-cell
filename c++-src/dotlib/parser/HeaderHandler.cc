
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
    if ( count == 1 ) {
      return std::move(mValueList[0]);
    }
    else {
      FileRegion loc{mLpLoc, mRpLoc};
      return AstValue::new_complex(mValueList, loc);
    }
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
// クラス FloatVectorListHeader
//////////////////////////////////////////////////////////////////////

// @brief ヘッダの値を読み込む処理
AstValuePtr
FloatVectorListHeader::_read_header_value(Scanner& scanner,
					  int count)
{
  return scanner.read_float_vector();
}

// @brief 読み込みが終了した時の処理を行う．
bool
FloatVectorListHeader::_end_header(int count)
{
  if ( count == 0 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    FileRegion(lp_loc(), rp_loc()),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, list of one ore more vectors expected.");
    return false;
  }
  else {
    return true;
  }
}


//////////////////////////////////////////////////////////////////////
// クラス StrListHeader
//////////////////////////////////////////////////////////////////////

// @brief 値を読み込む処理
AstValuePtr
StrListHeader::_read_header_value(Scanner& scanner,
				  int count)
{
  // count は無視
  return scanner.read_string();
}

// @brief 読み込みが終了した時の処理を行う．
bool
StrListHeader::_end_header(int count)
{
  return true;
}


//////////////////////////////////////////////////////////////////////
// クラス FixedElemHeader
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
FixedElemHeader::FixedElemHeader(int num)
  : mNum{num}
{
}

// @brief 値を読み込む処理
// @param[in] count read_value() の呼ばれた回数
AstValuePtr
FixedElemHeader::_read_header_value(Scanner& scanner,
				    int count)
{
  ASSERT_COND( count >= 0 );
  if ( count < mNum ) {
    return read_value(scanner, count);
  }
  else {
    ostringstream buf;
    buf << "Syntx error. "
	<< "Too many values.";
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
  ASSERT_COND( count <= mNum );
  if ( count < mNum ) {
    ostringstream buf;
    buf << "Syntx error. "
	<< "Too few values.";
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
// クラス EmptyHeader
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
EmptyHeader::EmptyHeader()
  : FixedElemHeader(0)
{
}

// @brief ヘッダの値を読み込む処理
AstValuePtr
EmptyHeader::read_value(Scanner& scanner,
			int count)
{
  // この関数が呼ばれることはない．
  ASSERT_NOT_REACHED;
  return {};
}


//////////////////////////////////////////////////////////////////////
// クラス FloatFloatHeader
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
FloatFloatHeader::FloatFloatHeader()
  : FixedElemHeader(2)
{
}

// @brief ヘッダの値を読み込む処理
AstValuePtr
FloatFloatHeader::read_value(Scanner& scanner,
			     int count)
{
  switch ( count ) {
  case 0:  return scanner.read_float();
  case 1:  return scanner.read_float();
  default: break;
  }

  ASSERT_NOT_REACHED;
  return {};
}


//////////////////////////////////////////////////////////////////////
// クラス FloatStrHeader
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
FloatStrHeader::FloatStrHeader()
  : FixedElemHeader(2)
{
}

// @brief ヘッダの値を読み込む処理
AstValuePtr
FloatStrHeader::read_value(Scanner& scanner,
			   int count)
{
  switch ( count ) {
  case 0:  return scanner.read_float();
  case 1:  return scanner.read_string();
  default: break;
  }

  ASSERT_NOT_REACHED;
  return {};
}


//////////////////////////////////////////////////////////////////////
// クラス FloatVectorHeader
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
FloatVectorHeader::FloatVectorHeader()
  : FixedElemHeader(1)
{
}

// @brief ヘッダの値を読み込む処理
AstValuePtr
FloatVectorHeader::read_value(Scanner& scanner,
			      int count)
{
  switch ( count ) {
  case 0:  return scanner.read_float_vector();
  default: break;
  }

  ASSERT_NOT_REACHED;
  return {};
}


//////////////////////////////////////////////////////////////////////
// クラス IntFloatHeader
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
IntFloatHeader::IntFloatHeader()
  : FixedElemHeader(2)
{
}

// @brief ヘッダの値を読み込む処理
AstValuePtr
IntFloatHeader::read_value(Scanner& scanner,
			   int count)
{
  switch ( count ) {
  case 0:  return scanner.read_int();
  case 1:  return scanner.read_float();
  default: break;
  }

  ASSERT_NOT_REACHED;
  return {};
}


//////////////////////////////////////////////////////////////////////
// クラス IntFloatVectorHeader
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
IntFloatVectorHeader::IntFloatVectorHeader()
  : FixedElemHeader(2)
{
}

// @brief ヘッダの値を読み込む処理
AstValuePtr
IntFloatVectorHeader::read_value(Scanner& scanner,
				 int count)
{
  switch ( count ) {
  case 0:  return scanner.read_int();
  case 1:  return scanner.read_float_vector();
  default: break;
  }

  ASSERT_NOT_REACHED;
  return {};
}


//////////////////////////////////////////////////////////////////////
// クラス IntVectorHeader
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
IntVectorHeader::IntVectorHeader()
  : FixedElemHeader(1)
{
}

// @brief ヘッダの値を読み込む処理
AstValuePtr
IntVectorHeader::read_value(Scanner& scanner,
			    int count)
{
  switch ( count ) {
  case 0:  return scanner.read_int_vector();
  default: break;
  }

  ASSERT_NOT_REACHED;
  return {};
}


//////////////////////////////////////////////////////////////////////
// クラス StrFloatHeader
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
StrFloatHeader::StrFloatHeader()
  : FixedElemHeader(2)
{
}

// @brief ヘッダの値を読み込む処理
AstValuePtr
StrFloatHeader::read_value(Scanner& scanner,
			   int count)
{
  switch ( count ) {
  case 0:  return scanner.read_string();
  case 1:  return scanner.read_float();
  default: break;
  }

  ASSERT_NOT_REACHED;
  return {};
}


//////////////////////////////////////////////////////////////////////
// クラス StrHeader
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
StrHeader::StrHeader()
  : FixedElemHeader(1)
{
}

// @brief ヘッダの値を読み込む処理
AstValuePtr
StrHeader::read_value(Scanner& scanner,
		      int count)
{
  switch ( count ) {
  case 0:  return scanner.read_string();
  default: break;
  }

  ASSERT_NOT_REACHED;
  return {};
}


//////////////////////////////////////////////////////////////////////
// クラス StrIntHeader
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
StrIntHeader::StrIntHeader()
  : FixedElemHeader(2)
{
}

// @brief ヘッダの値を読み込む処理
AstValuePtr
StrIntHeader::read_value(Scanner& scanner,
			 int count)
{
  switch ( count ) {
  case 0:  return scanner.read_string();
  case 1:  return scanner.read_int();
  default: break;
  }

  ASSERT_NOT_REACHED;
  return {};
}


//////////////////////////////////////////////////////////////////////
// クラス StrStrHeader
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
StrStrHeader::StrStrHeader()
  : FixedElemHeader(2)
{
}

// @brief ヘッダの値を読み込む処理
AstValuePtr
StrStrHeader::read_value(Scanner& scanner,
			 int count)
{
  switch ( count ) {
  case 0: return scanner.read_string();
  case 1: return scanner.read_string();
  default: break;
  }

  ASSERT_NOT_REACHED;
  return {};
}


//////////////////////////////////////////////////////////////////////
// クラス StrStrIntHeader
//////////////////////////////////////////////////////////////////////

// @brief ハンドラ用のコンストラクタ
StrStrIntHeader::StrStrIntHeader()
  : FixedElemHeader(3)
{
}

// @brief ヘッダの値を読み込む処理
AstValuePtr
StrStrIntHeader::read_value(Scanner& scanner,
			    int count)
{
  switch ( count ) {
  case 0:  return scanner.read_string();
  case 1:  return scanner.read_string();
  case 2:  return scanner.read_int();
  default: break;
  }

  ASSERT_NOT_REACHED;
  return {};
}


//////////////////////////////////////////////////////////////////////
// クラス StrStrStrHeader
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
StrStrStrHeader::StrStrStrHeader()
  : FixedElemHeader(3)
{
}

// @brief ヘッダの値を読み込む処理
AstValuePtr
StrStrStrHeader::read_value(Scanner& scanner,
			    int count)
{
  switch ( count ) {
  case 0:  return scanner.read_string();
  case 1:  return scanner.read_string();
  case 2:  return scanner.read_string();
  default: break;
  }

  ASSERT_NOT_REACHED;
  return {};
}


//////////////////////////////////////////////////////////////////////
// クラス TechnologyHeader
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
TechnologyHeader::TechnologyHeader()
  : FixedElemHeader(1)
{
}

// @brief ヘッダの値を読み込む処理
AstValuePtr
TechnologyHeader::read_value(Scanner& scanner,
			     int count)
{
  switch ( count ) {
  case 0:  return scanner.read_technology();
  default: break;
  }

  ASSERT_NOT_REACHED;
  return {};
}

END_NAMESPACE_YM_DOTLIB
