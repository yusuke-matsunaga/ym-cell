
/// @file GroupHandler.cc
/// @brief GroupHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/GroupHandler.h"
#include "dotlib/Str1GroupHandler.h"
#include "dotlib/Str2GroupHandler.h"
#include "dotlib/Str2IntGroupHandler.h"
#include "dotlib/BoolHandler.h"
#include "dotlib/IntHandler.h"
#include "dotlib/FloatHandler.h"
#include "dotlib/StringHandler.h"
#include "dotlib/ExprHandler.h"
#include "dotlib/FuncHandler.h"
#include "dotlib/IndexHandler.h"
#include "dotlib/ValuesHandler.h"
#include "dotlib/Str1ComplexHandler.h"
#include "dotlib/Str2ComplexHandler.h"
#include "dotlib/Float2ComplexHandler.h"
#include "dotlib/AstBool.h"
#include "dotlib/AstInt.h"
#include "dotlib/AstFloat.h"
#include "dotlib/AstString.h"
#include "dotlib/AstExpr.h"
#include "dotlib/AstFloatVector.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス GroupHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
GroupHandler::GroupHandler(DotlibParser& parser) :
  CGHandler(parser)
{
}

// @brief デストラクタ
GroupHandler::~GroupHandler()
{
}

// @brief グループ記述の始まり
//
// デフォルトの実装ではなにもしない．
void
GroupHandler::begin_group()
{
}

// @brief attr_type に対応する属性を読み込む．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// デフォルトの実装ではなにもしないで true を返す．
bool
GroupHandler::read_group_attr(AttrType attr_type,
			      const FileRegion& attr_loc)
{
  return true;
}

// @brief グループ記述の終わり
// @param[in] group_loc グループ全体のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// デフォルトの実装ではなにもしないで true を返す．
bool
GroupHandler::end_group(const FileRegion& group_loc)
{
  return true;
}

// @brief Group Statement を読み込む．
// @retval true 正しく読み込めた．
// @retval false エラーが起こった．
bool
GroupHandler::parse_group_statement()
{
  return parser().parse_group_statement(*this);
}

// @brief ブール値 のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
GroupHandler::parse_bool(const AstBool*& dst,
			 AttrType attr_type,
			 const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    BoolHandler handler(parser());
    dst = handler.parse_value();
    return dst != nullptr;
  }
}

// @brief 整数値 のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
GroupHandler::parse_int(const AstInt*& dst,
			AttrType attr_type,
			const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    IntHandler handler(parser());
    dst = handler.parse_value();
    return dst != nullptr;
  }
}

// @brief float 値のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
GroupHandler::parse_float(const AstFloat*& dst,
			  AttrType attr_type,
			  const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    FloatHandler handler(parser());
    dst = handler.parse_value();
    return dst != nullptr;
  }
}

// @brief 文字列値のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
GroupHandler::parse_string(const AstString*& dst,
			   AttrType attr_type,
			   const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    StringHandler handler(parser());
    dst = handler.parse_value();
    return dst != nullptr;
  }
}

// @brief 式を読んでセットする．
// @param[in] dst 値を格納する変数
// @param[in] attr_type 属性の型(エラー出力に用いる)
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正しく読み込んだ．
// @retval false エラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
GroupHandler::parse_expr(const AstExpr*& dst,
			 AttrType attr_type,
			 const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    ExprHandler handler(parser());
    dst = handler.parse_value();
    return dst != nullptr;
  }
}

// @brief 論理関数を読んでセットする．
// @param[in] dst 値を格納する変数
// @param[in] attr_type 属性の型(エラー出力に用いる)
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正しく読み込んだ．
// @retval false エラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
GroupHandler::parse_function(const AstExpr*& dst,
			     AttrType attr_type,
			     const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    FuncHandler handler(parser());
    dst = handler.parse_value();
    return dst != nullptr;
  }
}

// @brief index attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
GroupHandler::parse_index(const AstFloatVector*& dst,
			  AttrType attr_type,
			  const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    IndexHandler handler(parser());
    dst = handler.parse_value();
    return dst != nullptr;
  }
}

// @brief values attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
GroupHandler::parse_values(const AstFloatVector*& dst,
			   AttrType attr_type,
			   const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    IndexHandler handler(parser());
    dst = handler.parse_value();
    return dst != nullptr;
  }
}

// @brief Str1Complex タイプの complex attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
GroupHandler::parse_str1complex(const AstString*& dst,
				AttrType attr_type,
				const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    Str1ComplexHandler handler(parser());
    dst = handler.parse_value();
    return dst != nullptr;
  }
}

// @brief Str2Complex タイプの complex attribute を読み込む．
// @param[in] dst1, dst2 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] group_loc グループ記述全体の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
GroupHandler::parse_str2complex(const AstString*& dst1,
				const AstString*& dst2,
				AttrType attr_type,
				const FileRegion& attr_loc)
{
  if ( dst1 != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst1);
    return false;
  }
  else {
    Str2ComplexHandler handler(parser());
    return handler.parse_value(dst1, dst2);
  }
}

// @brief Float2Complex タイプの complex attribute を読み込む．
// @param[in] dst1, dst2 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] group_loc グループ記述全体の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
GroupHandler::parse_float2complex(const AstFloat*& dst1,
				  const AstFloat*& dst2,
				  AttrType attr_type,
				  const FileRegion& attr_loc)
{
  if ( dst1 != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst1);
    return false;
  }
  else {
    Float2ComplexHandler handler(parser());
    return handler.parse_value(dst1, dst2);
  }
}

// @brief Str1Group タイプの group statement を読み込む．
// @param[in] attr_type 属性の型
// @param[in] group_loc グループ記述全体の位置
//
// ここでは全ての属性を読み飛ばし，true を返す．
bool
GroupHandler::parse_str1group(AttrType attr_type,
			      const FileRegion& attr_loc)
{
  Str1GroupHandler handler(parser());
  return handler.parse_group_statement();
}

// @brief Str2Group タイプの group statement を読み込む．
// @param[in] attr_type 属性の型
// @param[in] group_loc グループ記述全体の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// ここでは全ての属性を読み飛ばす．
bool
GroupHandler::parse_str2group(AttrType attr_type,
			      const FileRegion& attr_loc)
{
  Str2GroupHandler handler(parser());
  return handler.parse_group_statement();
}

// @brief Str2IntGroup タイプの group statement を読み込む．
// @param[in] attr_type 属性の型
// @param[in] group_loc グループ記述全体の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// ここでは全ての属性を読み飛ばす．
bool
GroupHandler::parse_str2intgroup(AttrType attr_type,
				 const FileRegion& attr_loc)
{
  Str2IntGroupHandler handler(parser());
  return handler.parse_group_statement();
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

// @brief 同じ属性が重複して定義されている時のエラーを出力する．
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] prev_node 以前に定義されたノード
void
GroupHandler::duplicate_error(AttrType attr_type,
			      const FileRegion& attr_loc,
			      const AstNode* prev_node)
{
  ostringstream buf;
  buf << attr_type << " appear more than once."
      << " Previously appears at " << prev_node->loc();
  MsgMgr::put_msg(__FILE__, __LINE__,
		    attr_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    buf.str());
}

END_NAMESPACE_YM_DOTLIB
