#ifndef ASTlut_H
#define ASTlut_H

/// @file AstLut.h
/// @brief AstLut のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstLut AstLut.h "AstLut.h"
/// @brief lut 情報を表すクラス
//////////////////////////////////////////////////////////////////////
class AstLut :
  public AstNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] name 名前
  /// @param[in] index_1, index_2, index_3 インデックスのベクタ
  /// @param[in] value_list 値のリスト
  AstLut(const FileRegion& loc,
	 const AstString* name,
	 const AstFloatVector* index_1,
	 const AstFloatVector* index_2,
	 const AstFloatVector* index_3,
	 const AstFloatVector* value_list);

  /// @brief デストラクタ
  ~AstLut();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief テンプレート名を返す．
  const AstString*
  template_name() const;

  /// @brief 'index_1' のノードを返す．
  ///
  /// 未定義なら nullptr を返す．
  const AstFloatVector*
  index_1() const;

  /// @brief 'index_2' のノードを返す．
  ///
  /// 未定義なら nullptr を返す．
  const AstFloatVector*
  index_2() const;

  /// @brief 'index_3' のノードを返す．
  ///
  /// 未定義なら nullptr を返す．
  const AstFloatVector*
  index_3() const;

  /// @brief 値のリストを返す．
  const AstFloatVector*
  value_list() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  void
  dump(ostream& s,
       int indent = 0) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // テンプレート名
  const AstString* mName;

  // index_1
  const AstFloatVector* mIndex1;

  // index_2
  const AstFloatVector* mIndex2;

  // index_3
  const AstFloatVector* mIndex3;

  // 値のリスト
  const AstFloatVector* mValueList;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief テンプレート名を返す．
inline
const AstString*
AstLut::template_name() const
{
  return mName;
}

 // @brief 'index_1' のノードを返す．
inline
const AstFloatVector*
AstLut::index_1() const
{
  return mIndex1;
}

// @brief 'index_2' のノードを返す．
inline
const AstFloatVector*
AstLut::index_2() const
{
  return mIndex2;
}

// @brief 'index_3' のノードを返す．
inline
const AstFloatVector*
AstLut::index_3() const
{
  return mIndex3;
}

// @brief 値のリストを返す．
inline
const AstFloatVector*
AstLut::value_list() const
{
  return mValueList;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTlut_H
