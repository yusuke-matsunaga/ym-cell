#ifndef COMPLEXHANDLER_H
#define COMPLEXHANDLER_H

/// @file ComplexHandler.h
/// @brief ComplexHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class ComplexHandler ComplexHandler.h "ComplexHandler.h"
/// @brief complex attribute 用のハンドラ
//////////////////////////////////////////////////////////////////////
class ComplexHandler :
  public DotlibHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  /// @param[in] vector_mode ベクターモードで読み込むとき true にするフラグ
  ComplexHandler(DotlibParser& parser,
		 bool vector_mode = false);

  /// @brief デストラクタ
  virtual
  ~ComplexHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // DotlibHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 属性値を読み込む．
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @return 読み込んだ属性値を返す．
  ///
  /// エラーが起きたら nullptr を返す．
  virtual
  const AstNode*
  parse_attr_value(AttrType attr_type,
		   const FileRegion& attr_loc);


protected:
  //////////////////////////////////////////////////////////////////////
  // ComplexHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を表すノードを作る．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value_list 値のリスト
  /// @return value_list に対応した AstNode を返す．
  virtual
  const AstNode*
  gen_node(const FileRegion& loc,
	   const vector<const AstNode*>& value_list);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // parse_complex() 中でベクターモードで読み込む時 true にするフラグ
  bool mVectorMode;

};

END_NAMESPACE_YM_DOTLIB

#endif // COMPLEXHANDLER_H
