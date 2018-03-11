#ifndef DOTLIBINPUTVOLTAGE_H
#define DOTLIBINPUTVOLTAGE_H

/// @file DotlibInputVoltage.h
/// @brief DotlibInputVoltage のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "DotlibNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibInputVoltage DotlibInputVoltage.h "DotlibInputVoltage.h"
/// @brief input voltage を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibInputVoltage :
  public DotlibNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] name 名前
  /// @param[in] vil 'vil'
  /// @param[in] vih 'vih'
  /// @param[in] vimin 'vimin'
  /// @param[in] vimax 'vimax'
  DotlibInputVoltage(const FileRegion& loc,
		     const DotlibString* name,
		     const DotlibExpr* vil,
		     const DotlibExpr* vih,
		     const DotlibExpr* vimin,
		     const DotlibExpr* vimax);

  /// @brief デストラクタ
  virtual
  ~DotlibInputVoltage();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前を返す．
  const DotlibString*
  name() const;

  /// @brief 'vil' を返す．
  const DotlibExpr*
  vil() const;

  /// @brief 'vih' を返す．
  const DotlibExpr*
  vih() const;

  /// @brief 'vimin' を返す．
  const DotlibExpr*
  vimin() const;

  /// @brief 'vimax' を返す．
  const DotlibExpr*
  vimax() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  virtual
  void
  dump(ostream& s,
       int indent = 0) const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 名前
  const DotlibString* mName;

  // vil
  const DotlibExpr* mVil;

  // vih
  const DotlibExpr* mVih;

  // vimin
  const DotlibExpr* mViMin;

  // vimax
  const DotlibExpr* mViMax;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 名前を返す．
inline
const DotlibString*
DotlibInputVoltage::name() const
{
  return mName;
}

// @brief 'vil' を返す．
inline
const DotlibExpr*
DotlibInputVoltage::vil() const
{
  return mVil;
}

// @brief 'vih' を返す．
inline
const DotlibExpr*
DotlibInputVoltage::vih() const
{
  return mVih;
}

// @brief 'vimin' を返す．
inline
const DotlibExpr*
DotlibInputVoltage::vimin() const
{
  return mViMin;
}

// @brief 'vimax' を返す．
inline
const DotlibExpr*
DotlibInputVoltage::vimax() const
{
  return mViMax;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBINPUTVOLTAGE_H
