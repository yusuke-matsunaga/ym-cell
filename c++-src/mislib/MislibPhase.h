#ifndef MISLIBPHASE_H
#define MISLIBPHASE_H

/// @file MislibPhase.h
/// @brief MislibNoninv, MislibInv, MislibUnknown のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "MislibNode.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
/// @class MislibPhase MislibPhase.h "MislibPhase.h"
/// @brief 極性を表すクラス
//////////////////////////////////////////////////////////////////////
class MislibPhase :
  public MislibNode
{
  friend class MislibParser;
public:

  /// @breif 極性の種類
  enum Type {
    Noninv,
    Inv,
    Unknown,
  };


protected:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  MislibPhase(const FileRegion& loc);

  /// @brief デストラクタ
  virtual
  ~MislibPhase();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 種類を取り出す．
  virtual
  Type
  type() const = 0;

  /// @brief 内容を出力する．
  /// デバッグ用
  virtual
  void
  dump(ostream& s) const = 0;

};


//////////////////////////////////////////////////////////////////////
/// @class MislibNoninv MislibPhase.h "MislibPhase.h"
/// @brief NONINV 極性を表すクラス
//////////////////////////////////////////////////////////////////////
class MislibNoninv :
  public MislibPhase
{
  friend class MislibParser;

private:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  MislibNoninv(const FileRegion& loc);

  /// @brief デストラクタ
  virtual
  ~MislibNoninv();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 種類を取り出す．
  virtual
  Type
  type() const;

  /// @brief 内容を出力する．
  /// デバッグ用
  virtual
  void
  dump(ostream& s) const;

};


//////////////////////////////////////////////////////////////////////
/// @class MislibInv MislibPhase.h "MislibPhase.h"
/// @brief INV 極性を表すクラス
//////////////////////////////////////////////////////////////////////
class MislibInv :
  public MislibPhase
{
  friend class MislibParser;

private:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  MislibInv(const FileRegion& loc);

  /// @brief デストラクタ
  virtual
  ~MislibInv();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 種類を取り出す．
  virtual
  Type
  type() const;

  /// @brief 内容を出力する．
  /// デバッグ用
  virtual
  void
  dump(ostream& s) const;

};


//////////////////////////////////////////////////////////////////////
/// @class MislibUnknown MislibPhase.h "MislibPhase.h"
/// @brief UNKNOWN 極性を表すクラス
//////////////////////////////////////////////////////////////////////
class MislibUnknown :
  public MislibPhase
{
  friend class MislibParser;

private:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  MislibUnknown(const FileRegion& loc);

  /// @brief デストラクタ
  virtual
  ~MislibUnknown();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 種類を取り出す．
  virtual
  Type
  type() const;

  /// @brief 内容を出力する．
  /// デバッグ用
  virtual
  void
  dump(ostream& s) const;

};

END_NAMESPACE_YM_MISLIB

#endif // MISLIBPHASE_H
