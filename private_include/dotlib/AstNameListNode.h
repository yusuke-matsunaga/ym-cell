#ifndef ASTNAMELISTNODE_H
#define ASTNAMELISTNODE_H

/// @file AstNameListNode.h
/// @brief AstNameListNode のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2019, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib_nsdef.h"
#include "AstNode.h"
#include "AstArray.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstNameListNode AstNameListNode.h "AstNameListNode.h"
/// @brief 名前のリストを持つ AstNode の基底クラス
///
/// StrListHandler をヘッダハンドラとして持つ．
//////////////////////////////////////////////////////////////////////
class AstNameListNode :
  public AstNode
{
public:

  /// @brief コンストラクタ
  AstNameListNode(const FileRegion& attr_loc,    ///< [in] ファイル上の位置
		  const StrListHandler& header); ///< [in] ヘッダを読み込んだハンドラ

  /// @brief デストラクタ
  ~AstNameListNode();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前のリストを返す．
  AstArray<const AstString*>
  name_list() const
  {
    return mNameList;
  }


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 名前のリスト
  AstArray<const AstString*> mNameList;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTNAMELISTNODE_H
