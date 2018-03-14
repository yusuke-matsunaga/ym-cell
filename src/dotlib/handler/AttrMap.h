#ifndef ATTRMAP_H
#define ATTRMAP_H

/// @file AttrMap.h
/// @brief AttrMap のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "AttrType.h"
#include "ym/HashMap.h"
#include "ym/FileRegion.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AttrMap AttrMap.h "AttrMap.h"
/// @brief 属性名をキーにした属性値のリストを表すクラス
//////////////////////////////////////////////////////////////////////
class AttrMap
{
public:

  /// @brief コンストラクタ
  /// @param[in] attr_top 先頭の属性ノード
  AttrMap(const AstAttr* attr_top);

  /// @brief デストラクタ
  ~AttrMap();


public:
  //////////////////////////////////////////////////////////////////////
  // 情報を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を得る．
  /// @param[in] attr 属性
  /// @param[out] node_list 値のリストを格納する変数
  /// @retval true その属性値が定義されていた．
  /// @retval false その属性値が定義されていなかった．
  bool
  get_value(AttrType attr,
	    vector<const AstNode*>& node_list) const;

  /// @brief 値が単一と仮定してそのノードを返す．
  /// @param[in] attr 属性
  /// @param[in] loc 属性全体のファイル位置(エラー出力用)
  /// @param[out] node 結果のノードを格納するノード
  /// @retval true 値の読み出しが成功した．
  /// @retval false エラーが起こった．
  bool
  expect_singleton(AttrType attr,
		   const FileRegion& loc,
		   const AstNode*& node) const;

  /// @brief 値が単一もしくは空と仮定してそのノードを返す．
  /// @param[in] attr 属性
  /// @param[out] node 結果のノードを格納するノード
  /// @retval true 値の読み出しが成功した．
  /// @retval false エラーが起こった．
  ///
  /// 空の時は node に nullptr を入れて true を返す．
  bool
  expect_singleton_or_null(AttrType attr,
			   const AstNode*& node) const;


public:
  //////////////////////////////////////////////////////////////////////
  // 情報を設定する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を初期化する．
  void
  init();

  /// @brief 値を追加する．
  /// @param[in] attr 属性
  /// @param[in] node 値を表すノード
  void
  add(AttrType attr,
      const AstNode* node);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ハッシュ表
  HashMap<AttrType, vector<const AstNode*> > mHash;

};

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBATTRMAP_H
