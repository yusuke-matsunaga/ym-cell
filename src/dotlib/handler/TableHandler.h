#ifndef TABLEHANDLER_H
#define TABLEHANDLER_H

/// @file TableHandler.h
/// @brief TableHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "GroupHandler.h"
#include "IndexHandler.h"
#include "ValuesHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class TableHandler TableHandler.h "TableHandler.h"
/// @brief lut 用のハンドラ
//////////////////////////////////////////////////////////////////////
class TableHandler :
  public Str1GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  TableHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~TableHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値をクリアする．
  void
  clear_value();

  /// @brief 読み込んだ値を返す．
  const AstLut*
  value() const;


private:
  //////////////////////////////////////////////////////////////////////
  // GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ記述の始まり
  void
  begin_group() override;

  /// @brief attr_type に対応する属性を読み込む．
  /// @param[in] attr_type 対象の属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  /// @retval true 正常に処理した．
  /// @retval false 処理中にエラーが起こった．
  bool
  parse_attr(AttrType attr_type,
	     const FileRegion& attr_loc) override;

  /// @brief グループ記述の終わり
  /// @param[in] attr_type 対象の属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  bool
  end_group(const FileRegion& group_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // index_1
  IndexHandler mIndex1;

  // index_2
  IndexHandler mIndex2;

  // index_3
  IndexHandler mIndex3;

  // values
  ValuesHandler mValues;

  // 読み込んだ値
  AstLut* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // TABLEHANDLER_H
