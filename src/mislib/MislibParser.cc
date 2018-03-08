
/// @file MislibParser.cc
/// @brief MislibParser の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "MislibParser.h"
#include "MislibMgr.h"
#include "MislibParserImpl.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
// クラス MislibParser
//////////////////////////////////////////////////////////////////////

// コンストラクタ
MislibParser::MislibParser() :
  mImpl(new MislibParserImpl)
{
}

// デストラクタ
MislibParser::~MislibParser()
{
  delete mImpl;
}

// @brief mislib ファイルを読み込んでライブラリを生成する．
// @param[in] filename ファイル名
// @param[in] mgr MislibNode を管理するクラス
// @param[out] gate_list ゲートのASTを格納するリスト
// @retval true 読み込みが成功した．
// @retval false 読み込みが失敗した．
bool
MislibParser::read_file(const string& filename,
			MislibMgr& mgr,
			vector<const MislibNode*>& gate_list)
{
  return mImpl->read_file(filename, mgr.mImpl, gate_list);
}

END_NAMESPACE_YM_MISLIB
