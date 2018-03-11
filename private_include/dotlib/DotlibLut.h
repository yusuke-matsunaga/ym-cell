#ifndef DOTLIBLUT_H
#define DOTLIBLUT_H

/// @file DotlibLut.h
/// @brief DotlibLut のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "DotlibNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibLut DotlibLut.h "DotlibLut.h"
/// @brief LUT 情報を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibLut :
  public DotlibNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] name 名前
  /// @param[in] index_1, index_2, index_3 インデックスのベクタ
  /// @param[in] value_list 値のリスト
  DotlibLut(const FileRegion& loc,
	    const DotlibString* name,
	    const DotlibFloatVector* index_1,
	    const DotlibFloatVector* index_2,
	    const DotlibFloatVector* index_3,
	    const DotlibList* value_list);

  /// @brief デストラクタ
  ~DotlibLut();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

#if 0
  /// @brief 内容をセットする．
  bool
  set_data(const DotlibNode* lut_node);
#endif

  /// @brief テンプレート名を返す．
  const DotlibString*
  template_name() const;

  /// @brief 'index_1' のノードを返す．
  ///
  /// 未定義なら nullptr を返す．
  const DotlibFloatVector*
  index_1() const;

  /// @brief 'index_2' のノードを返す．
  ///
  /// 未定義なら nullptr を返す．
  const DotlibFloatVector*
  index_2() const;

  /// @brief 'index_3' のノードを返す．
  ///
  /// 未定義なら nullptr を返す．
  const DotlibFloatVector*
  index_3() const;

  /// @brief 値のリストを返す．
  ///
  /// 1次元でもリストとなる．
  const DotlibList*
  value_list() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  virtual
  void
  dump(ostream& s,
       int indent = 0) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // テンプレート名
  const DotlibString* mName;

  // index_1
  const DotlibFloatVector* mIndex1;

  // index_2
  const DotlibFloatVector* mIndex2;

  // index_3
  const DotlibFloatVector* mIndex3;

  // 値のリスト
  const DotlibList* mValueList;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief テンプレート名を返す．
inline
const DotlibString*
DotlibLut::template_name() const
{
  return mName;
}

 // @brief 'index_1' のノードを返す．
inline
const DotlibFloatVector*
DotlibLut::index_1() const
{
  return mIndex1;
}

// @brief 'index_2' のノードを返す．
inline
const DotlibFloatVector*
DotlibLut::index_2() const
{
  return mIndex2;
}

// @brief 'index_3' のノードを返す．
inline
const DotlibFloatVector*
DotlibLut::index_3() const
{
  return mIndex3;
}

// @brief 値のリストを返す．
inline
const DotlibList*
DotlibLut::value_list() const
{
  return mValueList;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBLUT_H
