#ifndef DOTLIBOUTPUTVOLTAGE_H
#define DOTLIBOUTPUTVOLTAGE_H

/// @file DotlibOutputVoltage.h
/// @brief DotlibOutputVoltage のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "DotlibNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibOutputVoltage DotlibOutputVoltage.h "DotlibOutputVoltage.h"
/// @brief output voltage を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibOutputVoltage :
  public DotlibNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] name 名前
  /// @param[in] vol 'vol'
  /// @param[in] voh 'voh'
  /// @param[in] vomin 'vomin'
  /// @param[in] vomax 'vomax'
  DotlibOutputVoltage(const FileRegion& loc,
		      const DotlibString* name,
		      const DotlibExpr* vol,
		      const DotlibExpr* voh,
		      const DotlibExpr* vomin,
		      const DotlibExpr* vomax);

  /// @brief デストラクタ
  virtual
  ~DotlibOutputVoltage();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前を返す．
  const DotlibString*
  name() const;

  /// @brief 'vol' を返す．
  const DotlibExpr*
  vol() const;

  /// @brief 'voh' を返す．
  const DotlibExpr*
  voh() const;

  /// @brief 'vomin' を返す．
  const DotlibExpr*
  vomin() const;

  /// @brief 'vomax' を返す．
  const DotlibExpr*
  vomax() const;

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

  // vol
  const DotlibExpr* mVol;

  // voh
  const DotlibExpr* mVoh;

  // vomin
  const DotlibExpr* mVoMin;

  // vomax
  const DotlibExpr* mVoMax;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 名前を返す．
inline
const DotlibString*
DotlibOutputVoltage::name() const
{
  return mName;
}

// @brief 'vol' を返す．
inline
const DotlibExpr*
DotlibOutputVoltage::vol() const
{
  return mVol;
}

// @brief 'voh' を返す．
inline
const DotlibExpr*
DotlibOutputVoltage::voh() const
{
  return mVoh;
}

// @brief 'vomin' を返す．
inline
const DotlibExpr*
DotlibOutputVoltage::vomin() const
{
  return mVoMin;
}

// @brief 'vomax' を返す．
inline
const DotlibExpr*
DotlibOutputVoltage::vomax() const
{
  return mVoMax;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBOUTPUTVOLTAGE_H
