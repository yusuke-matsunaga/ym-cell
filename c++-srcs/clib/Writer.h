#ifndef WRITER_H
#define WRITER_H

/// @file Writer.h
/// @brief Writer のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibCellLibrary.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class Writer Writer.h "Writer.h"
/// @brief ClibCellLibrary の内容を出力するためのクラス
//////////////////////////////////////////////////////////////////////
class Writer
{
public:

  /// @brief コンストラクタ
  Writer(
    ostream& s,                    ///< [in] 出力ストリーム
    const ClibCellLibrary& library ///< [in] セルライブラリ
  );

  /// @brief デストラクタ
  ~Writer() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief セルライブラリの内容を出力する．
  void
  run();


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief セルクラスの情報を出力する．
  void
  display_class(
    const ClibCellClass& cclass
  );

  /// @brief セルグループの情報を出力する．
  void
  display_group(
    const ClibCellGroup& group
  );

  /// @brief セルの情報を出力する．
  void
  display_cell(
    const ClibCell& cell
  );

  /// @brief タイミング情報を出力する．
  void
  display_timing(
    const ClibCell& cell,
    SizeType ipos,
    SizeType opos,
    ClibTimingSense sense
  );

  /// @brief LUT の情報を出力する．
  void
  display_lut(
    const string& label,
    const ClibLut& lut
  );

  /// @brief DFF のセルクラスに名前をつける．
  void
  reg_dff_class();

  /// @brief ラッチのセルクラスに名前をつける．
  void
  reg_latch_class();

  /// @brief セルグループ名を登録する．
  void
  reg_group_name(
    const string& name,
    const ClibCellGroup& cgroup
  );

  /// @brief セルクラス名を登録する．
  void
  reg_class_name(
    const string& name,
    const ClibCellGroup& cgroup
  );


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 出力ストリーム
  ostream& mS;

  // セルライブラリ
  ClibCellLibrary mLibrary;

  // セルクラス番号の辞書
  // キーは ClibCellClass::key()
  std::unordered_map<SizeType, SizeType> mClassDict;

  // セルグループ番号の辞書
  // キーは ClibCellGroup::key()
  std::unordered_map<SizeType, SizeType> mGroupDict;

  // セル番号の辞書
  // キーは ClibCell::key()
  std::unordered_map<SizeType, SizeType> mCellDict;

  // 特定のクラスの名前を保持する辞書
  std::unordered_map<SizeType, string> mClassNameDict;

  // 特定のグループの名前を保持する辞書
  std::unordered_map<SizeType, string> mGroupNameDict;

};

END_NAMESPACE_YM_CLIB

#endif // WRITER_H
