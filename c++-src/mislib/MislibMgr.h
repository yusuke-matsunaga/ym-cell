#ifndef MISLIBMGR_H
#define MISLIBMGR_H

/// @file MislibMgr.h
/// @brief MislibMgr のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "mislib_nsdef.h"
#include "ym/FileRegion.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
/// @class MislibMgr MislibMgr.h "MislibMgr.h"
/// @brief MislibNode を管理するクラス
//////////////////////////////////////////////////////////////////////
class MislibMgr
{
public:

  /// @brief コンストラクタ
  MislibMgr();

  /// @brief デストラクタ
  ///
  /// このオブジェクトが確保したすべてのオブジェクトを破壊する．
  ~MislibMgr();


public:
  //////////////////////////////////////////////////////////////////////
  // MislibNode を生成する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 確保したオブジェクトをすべて削除する．
  void
  clear();

  /// @brief GATE ノードを生成する．(通常版)
  MislibGate*
  new_gate(const FileRegion& loc,
	   const MislibStr* name,
	   const MislibNum* area,
	   const MislibStr* oname,
	   const MislibExpr* expr,
	   const MislibPin* ipin_top);

  /// @brief PIN ノードを生成する．
  MislibPin*
  new_pin(const FileRegion& loc,
	  const MislibStr* name,
	  const MislibPhase* phase,
	  const MislibNum* input_load,
	  const MislibNum* max_load,
	  const MislibNum* rise_block_delay,
	  const MislibNum* rise_fanout_delay,
	  const MislibNum* fall_block_delay,
	  const MislibNum* fall_fanout_delay);

  /// @brief NOT ノードを生成する．
  MislibExpr*
  new_not(const FileRegion& loc,
	  const MislibExpr* child1);

  /// @brief AND ノードを生成する．
  MislibExpr*
  new_and(const FileRegion& loc,
	  const MislibExpr* child1,
	  const MislibExpr* child2);

  /// @brief OR ノードを生成する．
  MislibExpr*
  new_or(const FileRegion& loc,
	 const MislibExpr* child1,
	 const MislibExpr* child2);

  /// @brief XOR ノードを生成する．
  MislibExpr*
  new_xor(const FileRegion& loc,
	  const MislibExpr* child1,
	  const MislibExpr* child2);

  /// @brief 定数0ノードを生成する．
  MislibExpr*
  new_const0(const FileRegion& loc);

  /// @brief 定数1ノードを生成する．
  MislibExpr*
  new_const1(const FileRegion& loc);

  /// @brief 変数ノードを生成する．
  MislibExpr*
  new_varname(const FileRegion& loc,
	      ShString str);

  /// @brief NONINV ノードを生成する．
  MislibPhase*
  new_noninv(const FileRegion& loc);

  /// @brief INV ノードを生成する．
  MislibPhase*
  new_inv(const FileRegion& loc);

  /// @brief UNKNOWN ノードを生成する．
  MislibPhase*
  new_unknown(const FileRegion& loc);

  /// @brief 文字列ノードを生成する．
  MislibStr*
  new_str(const FileRegion& loc,
	  ShString str);

  /// @brief 数値ノードを生成する．
  MislibNum*
  new_num(const FileRegion& loc,
	  double num);


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 生成したノードのリスト
  vector<MislibNode*> mNodeList;

};

END_NAMESPACE_YM_MISLIB

#endif // MISLIBMGR_H
