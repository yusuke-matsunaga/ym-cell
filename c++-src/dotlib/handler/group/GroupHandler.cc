
/// @file GroupHandler.cc
/// @brief GroupHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/GroupHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス GroupHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
GroupHandler::GroupHandler(DotlibParser& parser) :
  DotlibHandler(parser)
{
}

// @brief デストラクタ
GroupHandler::~GroupHandler()
{
}

// @brief attr_type に対応する属性を読み込む．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
GroupHandler::read_group_attr(AttrType attr_type,
			      const FileRegion& attr_loc)
{
  if ( mFuncDict.count(attr_type) > 0 ) {
    auto func = mFuncDict.at(attr_type);
    auto node = func(parser(), attr_type, attr_loc);
    mNode.push_back(node);
    return true;
  }
  else {
    syntax_error(attr_type, attr_loc);
    return false;
  }
}

// @brief 属性がセットされているかチェックする．
// @param[in] val 値を持つノード
// @param[in] attr_type 属性の型
// @param[in] group_loc グループ記述全体の位置
// @retval true val が値を持っていた．
// @retval false val が nullptr だった．
//
// val が nullptr の時にエラー出力を行う．
bool
GroupHandler::check_attr(const AstNode* val,
			 AttrType attr_type,
			 const FileRegion& group_loc)
{
  if ( val == nullptr ) {
    ostringstream buf;
    buf << attr_type << " is missing.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    group_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }
  else {
    return true;
  }
}

// @brief パース関数を登録する．
// @param[in] attr_type 属性
// @param[in] func パース関数
void
GroupHandler::reg_func(AttrType attr_type,
		       ParseFunc func)
{
  mFuncDict[attr_type] = func;
}

END_NAMESPACE_YM_DOTLIB
