
/// @file ComplexHandler.cc
/// @brief ComplexHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ComplexHandler.h"
#include "DotlibParserImpl.h"
#include "DotlibList.h"
#include "DotlibInt.h"
#include "DotlibFloat.h"
#include "DotlibFloatVector.h"
#include "DotlibString.h"
#include "GroupHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス ComplexHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parent 親のハンドラ
ComplexHandler::ComplexHandler(GroupHandler* parent) :
  DotlibHandler(parent)
{
}

// @brief デストラクタ
ComplexHandler::~ComplexHandler()
{
}

// @brief 構文要素を処理する．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @return 読み込んだ属性値を返す．
//
// エラーが起きたら nullptr を返す．
DotlibNode*
ComplexHandler::read_attr(AttrType attr_type,
			  const FileRegion& attr_loc)
{
  FileRegion end_loc;
  DotlibList* value_list = parse_complex(vector_mode(), end_loc);
  if ( value_list == nullptr ) {
    return nullptr;
  }

  if ( !expect_nl() ) {
    return nullptr;
  }

  if ( debug() ) {
    cout << attr_type << value_list << endl;
  }

  if ( !set_value(attr_type, attr_loc, value_list, end_loc) ) {
    return nullptr;
  }
#warning "TODO: 未完成"
  return nullptr;
}

// @brief 値を読み込んだ時の処理
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @param[in] value_list 値のリスト
// @param[in] end_loc 右括弧の位置
bool
ComplexHandler::set_value(AttrType attr_type,
			  const FileRegion& attr_loc,
			  DotlibList* value_list,
			  const FileRegion& end_loc)
{
  FileRegion loc(attr_loc, end_loc);
  return parent()->add_attr(attr_type, value_list, loc);
}

// @brief vector_mode で読み込むとき true を返す．
bool
ComplexHandler::vector_mode() const
{
  return false;
}


//////////////////////////////////////////////////////////////////////
// クラス Str1ComplexHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parent 親のハンドラ
Str1ComplexHandler::Str1ComplexHandler(GroupHandler* parent) :
  ComplexHandler(parent)
{
}

// @brief デストラクタ
Str1ComplexHandler::~Str1ComplexHandler()
{
}

// @brief 値を読み込んだ時の処理
// @param[in] attr_type 属性名
// @param[in] attr_loc ファイル上の位置
// @param[in] value_list 値のリスト
// @param[in] end_loc 右括弧の位置
bool
Str1ComplexHandler::set_value(AttrType attr_type,
			      const FileRegion& attr_loc,
			      DotlibList* value_list,
			      const FileRegion& end_loc)
{
  if ( value_list->list_size() != 1 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_list->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, a string expected.");
    return false;
  }
  const DotlibNode* top = value_list->list_elem(0);
  const DotlibString* str = dynamic_cast<const DotlibString*>(top);
  if ( str == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    top->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, a string expected.");
    return false;
  }

  return ComplexHandler::set_value(attr_type, attr_loc, value_list, end_loc);
}


//////////////////////////////////////////////////////////////////////
// クラス VectorComplexHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parent 親のハンドラ
VectorComplexHandler::VectorComplexHandler(GroupHandler* parent) :
  ComplexHandler(parent)
{
}

// @brief デストラクタ
VectorComplexHandler::~VectorComplexHandler()
{
}

// @brief 値を読み込んだ時の処理
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @param[in] value_list 値のリスト
// @param[in] end_loc 右括弧の位置
bool
VectorComplexHandler::set_value(AttrType attr_type,
				const FileRegion& attr_loc,
				DotlibList* value_list,
				const FileRegion& end_loc)
{
  if ( value_list->list_size() != 1 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_list->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, one vector expected.");
    return false;
  }
  ASSERT_COND( dynamic_cast<const DotlibFloatVector*>(value_list->list_elem(0)) );
  return ComplexHandler::set_value(attr_type, attr_loc, value_list, end_loc);
}

// @brief vector_mode で読み込むとき true を返す．
bool
VectorComplexHandler::vector_mode() const
{
  return true;
}


//////////////////////////////////////////////////////////////////////
// クラス VectorListComplexHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parent 親のハンドラ
VectorListComplexHandler::VectorListComplexHandler(GroupHandler* parent) :
  VectorComplexHandler(parent)
{
}

// @brief デストラクタ
VectorListComplexHandler::~VectorListComplexHandler()
{
}

// @brief 値を読み込んだ時の処理
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @param[in] value_list 値のリスト
// @param[in] end_loc 右括弧の位置
bool
VectorListComplexHandler::set_value(AttrType attr_type,
				    const FileRegion& attr_loc,
				    DotlibList* value_list,
				    const FileRegion& end_loc)
{
  int n = value_list->list_size();
  if ( n == 0 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_list->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, one ore moare vectors expected.");
    return false;
  }
  for ( int i = 0; i < n; ++ i ) {
    const DotlibNode* elem = value_list->list_elem(i);
    ASSERT_COND( dynamic_cast<const DotlibFloatVector*>(elem) );
  }

  return ComplexHandler::set_value(attr_type, attr_loc, value_list, end_loc);
}


//////////////////////////////////////////////////////////////////////
// クラス UnitComplexHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parent 親のハンドラ
UnitComplexHandler::UnitComplexHandler(GroupHandler* parent) :
  ComplexHandler(parent)
{
}

// @brief デストラクタ
UnitComplexHandler::~UnitComplexHandler()
{
}

// @brief 値を読み込んだ時の処理
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @param[in] value_list 値のリスト
// @param[in] end_loc 右括弧の位置
bool
UnitComplexHandler::set_value(AttrType attr_type,
			      const FileRegion& attr_loc,
			      DotlibList* value_list,
			      const FileRegion& end_loc)
{
  if ( value_list->list_size() != 2 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_list->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, (number, string) pair expected.");
    return false;
  }
  const DotlibNode* top = value_list->list_elem(0);
  if ( dynamic_cast<const DotlibFloat*>(top) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    top->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, first element should be a number.");
    return false;
  }
  const DotlibNode* next = value_list->list_elem(1);
  if ( dynamic_cast<const DotlibString*>(next) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    next->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, second element should be a string.");
    return false;
  }

  return ComplexHandler::set_value(attr_type, attr_loc, value_list, end_loc);
}


//////////////////////////////////////////////////////////////////////
// クラス PwComplexHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parent 親のハンドラ
PwComplexHandler::PwComplexHandler(GroupHandler* parent) :
  ComplexHandler(parent)
{
}

// @brief デストラクタ
PwComplexHandler::~PwComplexHandler()
{
}

// @brief 値を読み込んだ時の処理
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @param[in] value_list 値のリスト
// @param[in] end_loc 右括弧の位置
bool
PwComplexHandler::set_value(AttrType attr_type,
			    const FileRegion& attr_loc,
			    DotlibList* value_list,
			    const FileRegion& end_loc)
{
  if ( value_list->list_size() != 2 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_list->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, (integer, float) pair expected.");
    return false;
  }
  const DotlibNode* top = value_list->list_elem(0);
  if ( dynamic_cast<const DotlibInt*>(top) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    top->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, first element should be an ID number.");
    return false;
  }
  const DotlibNode* next = value_list->list_elem(1);
  if ( dynamic_cast<const DotlibFloat*>(next) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    next->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, second element should be a float number.");
    return false;
  }

  return ComplexHandler::set_value(attr_type, attr_loc, value_list, end_loc);
}

END_NAMESPACE_YM_DOTLIB
