
/// @file PowerHandler.cc
/// @brief PowerHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HandlerFactory.h"
#include "PowerHandler.h"
#include "ComplexHandler.h"
#include "dotlib/DotlibMgrImpl.h"
#include "dotlib/DotlibFloatVector.h"
#include "dotlib/DotlibList.h"
#include "dotlib/DotlibLut.h"
#include "dotlib/DotlibAttr.h"
#include "ym/MsgMgr.h"



BEGIN_NAMESPACE_YM_DOTLIB

// @brief table group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_power(DotlibParser& parser)
{
  return new PowerHandler(parser);
}


//////////////////////////////////////////////////////////////////////
// クラス PowerHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
PowerHandler::PowerHandler(DotlibParser& parser) :
  Str1GroupHandler(parser)
{
  DotlibHandler* index_handler = HandlerFactory::new_index(parser);
  DotlibHandler* values_handler = HandlerFactory::new_values(parser);
  DotlibHandler* complex        = new ComplexHandler(parser);
  DotlibHandler* dummy_handler = HandlerFactory::new_group(parser);

  // simple attributes

  // complex attribute
  reg_handler(ATTR_INDEX_1,          index_handler);
  reg_handler(ATTR_INDEX_2,          index_handler);
  reg_handler(ATTR_INDEX_3,          index_handler);
  reg_handler(ATTR_VALUES,           values_handler);

  reg_handler(ATTR_ORDERS,           complex);
  reg_handler(ATTR_COEFS,            complex);

  // group statements
  reg_handler(ATTR_DOMAIN,           dummy_handler);
}

// @brief デストラクタ
PowerHandler::~PowerHandler()
{
}

// @brief 値を作る．
DotlibNode*
PowerHandler::gen_value(const FileRegion& loc,
			const DotlibString* name,
			const vector<DotlibAttr*>& attr_list)
{
  const DotlibFloatVector* index_1 = nullptr;
  const DotlibFloatVector* index_2 = nullptr;
  const DotlibFloatVector* index_3 = nullptr;
  const DotlibList* values = nullptr;
  for ( auto attr: attr_list ) {
    if ( attr->attr_type() == ATTR_INDEX_1 ) {
      if ( index_1 != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			kMsgError,
			"DOTLIB_PARSER",
			"'index_1' defined more than once.");
	return nullptr;
      }
      index_1 = dynamic_cast<const DotlibFloatVector*>(attr->attr_value());
      ASSERT_COND( index_1 != nullptr );
    }
    if ( attr->attr_type() == ATTR_INDEX_2 ) {
      if ( index_2 != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			kMsgError,
			"DOTLIB_PARSER",
			"'index_2' defined more than once.");
	return nullptr;
      }
      index_2 = dynamic_cast<const DotlibFloatVector*>(attr->attr_value());
      ASSERT_COND( index_2 != nullptr );
    }
    if ( attr->attr_type() == ATTR_INDEX_3 ) {
      if ( index_3 != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			kMsgError,
			"DOTLIB_PARSER",
			"'index_3' defined more than once.");
	return nullptr;
      }
      index_3 = dynamic_cast<const DotlibFloatVector*>(attr->attr_value());
      ASSERT_COND ( index_3 != nullptr );
    }
    if ( attr->attr_type() == ATTR_VALUES ) {
      if ( values != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			kMsgError,
			"DOTLIB_PARSER",
			"'values' defined more than once.");
	return nullptr;
      }
      values = dynamic_cast<const DotlibList*>(attr->attr_value());
      ASSERT_COND ( values != nullptr );
    }
  }
  return mgr()->new_lut(loc, name, index_1, index_2, index_3, values);
}

END_NAMESPACE_YM_DOTLIB
